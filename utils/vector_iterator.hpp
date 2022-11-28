#ifndef __VECTOR_ITERATOR_HPP__
#define __VECTOR_ITERATOR_HPP__

#include "iterator.hpp"

namespace ft {

template <typename T>
class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {
   public:
    typedef T                                                              iterator_type;
    typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename ft::iterator_traits<iterator_type>::value_type        value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename ft::iterator_traits<iterator_type>::pointer           pointer;
    typedef typename ft::iterator_traits<iterator_type>::reference         reference;

   private:
    pointer ptr;

   public:
    // member functions
    vector_iterator() : ptr(nullptr){};

    explicit vector_iterator(pointer _ptr) : ptr(_ptr) {}

    vector_iterator(const vector_iterator<T> &vector_iter) : ptr(vector_iter.base()) {}

    pointer base() const { return this->ptr; }

    reference operator*() const { return *ptr; }

    vector_iterator operator+(difference_type n) const { return vector_iterator(this->ptr + n); }

    vector_iterator operator-(difference_type n) const { return vector_iterator(this->ptr - n); }

    vector_iterator &operator++() {
        this->ptr++;
        return *this;
    }

    vector_iterator operator++(int) {
        vector_iterator<T> tmp = *this;
        ++(*this);
        return tmp;
    }

    vector_iterator &operator--() {
        this->ptr--;
        return *this;
    }

    vector_iterator operator--(int) {
        vector_iterator tmp = *this;
        --(*this);
        return tmp;
    }

    vector_iterator &operator+=(difference_type n) {
        this->ptr += n;
        return *this;
    }

    vector_iterator &operator-=(difference_type n) {
        this->ptr -= n;
        return *this;
    }

    pointer operator->() const { return this->ptr; }

    reference operator[](difference_type n) const { return this->ptr[n]; }
};

// relational operators
template <class T>
bool operator==(const vector_iterator<T> &lhs, const vector_iterator<T> &rhs) {
    return lhs.base() == rhs.base();
}

template <class T>
bool operator!=(const vector_iterator<T> &lhs, const vector_iterator<T> &rhs) {
    return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs) {
    return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator<=(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs) {
    return lhs.base() <= rhs.base();
}

template <class Iterator>
bool operator>(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs) {
    return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator>=(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs) {
    return lhs.base() >= rhs.base();
}

template <class Iterator>
vector_iterator<Iterator> operator+(typename vector_iterator<Iterator>::difference_type n, const vector_iterator<Iterator> &vector_iter) {
    return vector_iterator<Iterator>(vector_iter + n);
}

template <class Iterator>
typename vector_iterator<Iterator>::difference_type operator-(const vector_iterator<Iterator> &lhs, const vector_iterator<Iterator> &rhs) {
    return rhs.base() - lhs.base();
}

}  // namespace ft

#endif