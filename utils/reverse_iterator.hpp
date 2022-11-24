#ifndef __REVERSE_ITERATOR_HPP__
#define __REVERSE_ITERATOR_HPP__

#include "iterator_traits.hpp"

namespace ft {

template <class Iterator>
class reverse_iterator {
       protected:
        Iterator current;

       public:
        typedef Iterator                                                  iterator_type;
        typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
        typedef typename ft::iterator_traits<Iterator>::value_type        value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer           pointer;
        typedef typename ft::iterator_traits<Iterator>::reference         reference;

        // member functions
        reverse_iterator() : current() {}

        explicit reverse_iterator(iterator_type it) : current(it) {}

        reverse_iterator(const reverse_iterator<Iterator> &rev_it) : current(rev_it.base()) {}

        iterator_type base() const { return this->current; }

        reference operator*() const {
                Iterator tmp = this->current;
                return *--tmp;
        }

        reverse_iterator operator+(difference_type n) const { return reverse_iterator(this->current - n); }

        reverse_iterator operator-(difference_type n) const { return reverse_iterator(this->current + n); }

        reverse_iterator &operator++() {
                --this->current;
                return *this;
        }

        reverse_iterator operator++(int) {
                reverse_iterator tmp = *this;
                ++(*this);
                return tmp;
        }

        reverse_iterator &operator--() {
                ++this->current;
                return *this;
        }

        reverse_iterator operator--(int) {
                reverse_iterator tmp = *this;
                --(*this);
                return tmp;
        }

        reverse_iterator &operator+=(difference_type n) {
                this->current -= n;
                return *this;
        }

        reverse_iterator &operator-=(difference_type n) {
                this->current += n;
                return *this;
        }

        pointer operator->() const { return &(operator*()); }

        reference operator[](difference_type n) const { return *(*this + n); }
};

// relational operators
template <class Iterator>
bool operator==(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() == rhs.base();
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() != rhs.base();
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() > rhs.base();
}
template <class Iterator>
bool operator<=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() >= rhs.base();
}
template <class Iterator>
bool operator>(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return lhs.base() <= rhs.base();
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &rev_it) {
        return reverse_iterator<Iterator>(rev_it - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator> &lhs, const reverse_iterator<Iterator> &rhs) {
        return rhs.base() - lhs.base();
}

}  // namespace ft

#endif
