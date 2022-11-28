#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <memory>

#include "iterator.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class vector {
   public:
    // member types
    typedef T                                                           value_type;
    typedef Alloc                                                       allocator_type;
    typedef typename allocator_type::reference                          reference;
    typedef typename allocator_type::const_reference                    const_reference;
    typedef typename allocator_type::pointer                            pointer;
    typedef typename allocator_type::const_pointer                      const_pointer;
    typedef typename allocator_type::size_type                          size_type;
    typedef ft::iterator<ft::random_access_iterator_tag, pointer>       iterator;
    typedef ft::iterator<ft::random_access_iterator_tag, const_pointer> const_iterator;
    typedef ft::reverse_iterator<iterator>                              reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;
    typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;

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
        this->init(n, 0, alloc);
        this->arr = this->alloc.allocate(n);
        for (size_type i = 0; i < n; i++, this->_size++) {
            this->alloc.construct(this->arr + i, val);
        }
    }

    template <class InputIterator>
    vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& alloc = allocator_type()) {
        difference_type diff = ft::distance(first, last);

        if (diff < 0) throw std::length_error("vector");

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

    // capacity functions
    size_type capacity() const { return this->cap; }
    size_type size() const { return this->_size; }
    size_type max_size() const { return this->alloc.max_size(); }
    bool      empty() const { return !this->size(); }

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