#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include "iterator_traits.hpp"

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
struct iterator {
   public:
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last, ft::input_iterator_tag) {
    typename ft::iterator_traits<InputIterator>::difference_type diff(0);
    for (; first != last; ++first) ++diff;
    return diff;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
    typename ft::iterator_traits<InputIterator>::difference_type diff(0);
    for (; first != last; ++first) ++diff;
    return diff;
}

template <class _RandIter>
typename ft::iterator_traits<_RandIter>::difference_type distance(_RandIter first, _RandIter last, ft::random_access_iterator_tag) {
    return last - first;
}

template <class _RandIter>
typename ft::iterator_traits<_RandIter>::difference_type distance(_RandIter first, _RandIter last, std::random_access_iterator_tag) {
    return last - first;
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
    return distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
}

};  // namespace ft

#endif