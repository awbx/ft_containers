#ifndef __ITERATOR_TRAITS_HPP__
#define __ITERATOR_TRAITS_HPP__

#include "iterator.hpp"

namespace ft {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag, public output_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iterator>
class iterator_traits {
   public:
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer          *pointer;
    typedef typename Iterator::reference        &reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T *> {
   public:
    typedef ptrdiff_t                      difference_type;
    typedef T                              value_type;
    typedef T                             *pointer;
    typedef T                             &reference;
    typedef ft::random_access_iterator_tag iterator_category;
};

template <class T>
class iterator_traits<const T *> {
   public:
    typedef ptrdiff_t                      difference_type;
    typedef T                              value_type;
    typedef const T                       *pointer;
    typedef const T                       &reference;
    typedef ft::random_access_iterator_tag iterator_category;
};
}  // namespace ft

#endif