#ifndef __STACK_HPP__
#define __STACK_HPP__

#include "vector.hpp"

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {
   public:
    // member types
    typedef T         value_type;
    typedef Container container_type;
    typedef size_t    size_type;

   private:
    container_type c;

   public:
    // default constructor
    explicit stack(const container_type& ctnr = container_type()) { this->c = ctnr; }

    // copy constructot
    stack(const stack& copy) : c(copy.c) {}

    // assignment operator
    stack& operator=(const stack& rhs) {
        if (this != &rhs) {
            c = rhs.c;
        }
        return *this;
    }

    // member functions

    bool      empty() const { return this->c.empty(); }
    size_type size() const { return this->c.size(); }

    value_type&       top() { return this->c.back(); }
    const value_type& top() const { return this->back(); }

    void push(const value_type& val) { this->c.push_back(val); }
    void pop() { this->c.pop_back(); }
};

// relational operators

template <class T, class Container>
bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c == rhs.c;
}

template <class T, class Container>
bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c != rhs.c;
}

template <class T, class Container>
bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c < rhs.c;
}

template <class T, class Container>
bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c <= rhs.c;
}

template <class T, class Container>
bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c > rhs.c;
}

template <class T, class Container>
bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return lhs.c >= rhs.c;
}

}  // namespace ft

#endif