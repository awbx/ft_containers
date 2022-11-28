#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>

#include "reverse_iterator.hpp"
#include "vector_iterator.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
   public:
    // member types
    typedef T                                                       value_type;
    typedef Alloc                                                   allocator_type;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef typename allocator_type::size_type                      size_type;
    typedef ft::vector_iterator<pointer>                            iterator;
    typedef ft::vector_iterator<const_pointer>                      const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type difference_type;

   private:
    pointer        arr;
    allocator_type alloc;
    size_type      cap;
    size_type      _size;

    void init(size_type cap, size_type _size, const allocator_type& alloc = allocator_type()) {
        this->alloc = alloc;
        this->cap = cap;
        this->_size = _size;
    }

   public:
    // constructors of vector
    explicit vector(const allocator_type& alloc = allocator_type()) {
        this->init(0, 0, alloc);
        this->arr = nullptr;
    }
    explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) {
        if (n > this->max_size()) throw std::length_error("vector");

        this->init(n, 0, alloc);
        this->arr = this->alloc.allocate(n);
        for (size_type i = 0; i < n; i++, this->_size++) {
            this->alloc.construct(this->arr + i, val);
        }
    }

    template <class InputIterator>
    vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) {
        difference_type diff = ft::distance(first, last);

        if (diff < 0 || (size_type)diff > this->max_size()) throw std::length_error("vector");

        this->init(diff, diff, alloc);
        this->arr = this->alloc.allocate(diff);

        size_type idx = 0;
        while (first != last) {
            this->alloc.construct(this->arr + idx, *first);
            first++, idx++;
        }
    }

    // copy constructor
    vector(const vector& x) {
        this->init(x.size(), x.size(), x.get_allocator());
        this->arr = this->alloc.allocate(this->capacity());

        // copy `arr` of x to `this->arr`
        std::memcpy(this->arr, x.arr, this->size() * sizeof(value_type));
    }

    // -------------------------------- Iterator function -------------------------------

    iterator       begin() { return iterator(this->arr); };
    const_iterator begin() const { return const_iterator(this->arr); }

    iterator       end() { return iterator(this->arr + this->size()); }
    const_iterator end() const { return const_iterator(this->arr + this->size()); }

    reverse_iterator       rbegin() { return reverse_iterator(this->end()); };
    const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); };

    reverse_iterator       rend() { return reverse_iterator(this->begin()); };
    const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); };

    // --------------------------------  End of iterator function ------------------------

    // -------------------------------- Capacity functions -----------------------------

    size_type capacity() const { return this->cap; }
    size_type size() const { return this->_size; }
    size_type max_size() const { return this->alloc.max_size(); }
    bool      empty() const { return !this->size(); }

    // Todo : make this function private !

    void extend(size_type new_cap, bool do_copy = true) {
        size_type tmp_cap = this->capacity();
        pointer   tmp_arr = this->arr;

        this->cap = new_cap;
        this->arr = this->alloc.allocate(this->capacity());
        if (do_copy) std::memcpy(this->arr, tmp_arr, this->size() * sizeof(value_type));
        for (size_type idx = 0; idx < this->size(); idx++) this->alloc.destroy(tmp_arr + idx);
        this->alloc.deallocate(tmp_arr, tmp_cap);
    }

    void resize(size_type n, value_type val = value_type()) {
        if (n > this->max_size()) throw std::length_error("vector");

        if (n < this->size()) {
            size_type idx = n;
            for (; idx < this->size(); idx++) this->alloc.destroy(this->arr + idx);
        } else {
            if (n > this->capacity()) {
                if (n < this->capacity() * 2)
                    this->extend(this->capacity() * 2);
                else
                    this->extend(n);
            }

            for (; this->_size < n; this->_size++) this->alloc.construct(this->arr + this->_size, val);
        }
        this->_size = n;
    }

    void reserve(size_type n) {
        if (n > this->max_size()) throw std::length_error("vector");

        if (n > this->capacity()) this->extend(n);
    }

    // -------------------------------- End of capacity functions -----------------------------

    // -------------------------------- Element access functions ------------------------------

    reference       front() { return this->arr[0]; }
    const_reference front() const { return this->arr[0]; }

    reference       back() { return this->arr[this->size() - 1]; }
    const_reference back() const { return this->arr[this->size() - 1]; }

    // -------------------------------- End of element access functions -----------------------

    // -------------------------------- Modifiers function -----------------------------------

    template <class InputIterator>
    void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {
        difference_type diff = ft::distance(first, last);
        if (diff < 0 || (size_type)diff > this->max_size()) throw std::length_error("vector");

        bool do_construct = false;
        if ((size_type)diff > this->capacity()) {
            this->extend(diff, false);
            do_construct = true;
            this->_size = 0;
        }
        size_type idx = 0;
        for (; idx < (size_type)diff && first != last; idx++, first++) {
            if (do_construct)
                this->alloc.construct(this->arr + idx, *first);
            else
                this->arr[idx] = *first;
        }
        for (; idx < this->size(); idx++) this->alloc.destroy(this->arr + idx);
        this->_size = diff;
    }

    void assign(size_type n, const value_type& val) {
        if (n > this->max_size()) throw std::length_error("vector");

        bool do_construct = false;

        if (n > this->capacity()) {
            this->extend(n, false);
            do_construct = true;
            this->_size = 0;
        }

        size_type idx = 0;
        for (; idx < n; idx++) {
            if (do_construct)
                this->alloc.construct(this->arr + idx, val);
            else
                this->arr[idx] = val;
        }
        for (; idx < this->size(); idx++) this->alloc.destroy(this->arr + idx);

        this->_size = n;
    }

    void push_back(const value_type& val) {
        if (!this->capacity()) this->reserve(1);

        if (this->size() == this->capacity()) this->extend(this->capacity() * 2);

        this->alloc.construct(this->arr + this->_size++, val);
    }

    void pop_back() { this->alloc.destroy(this->arr + this->_size--); }  // CHECK : does linux implementation throw an error in case of empty vector!

    // -------------------------------- End of modifiers functions ----------------------------

    // allocator functions
    allocator_type get_allocator() const { return this->alloc; }

    // destructor
    ~vector() {
        if (!this->capacity()) return;

        for (size_type idx = 0; idx < this->size(); idx++) {
            this->alloc.destroy(this->arr + idx);
        }

        this->alloc.deallocate(this->arr, this->capacity());
    }
};
}  // namespace ft

#endif