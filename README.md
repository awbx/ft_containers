# ft_containers

A C++98 implementation of standard STL containers, including vector, stack, map, and set. This project reimplements these fundamental data structures from scratch, providing the same interface and functionality as their STL counterparts.

## Overview

This project is part of the 42 School curriculum and focuses on understanding the inner workings of STL containers by implementing them from the ground up. All containers are implemented following C++98 standards with proper memory management, iterator support, and exception safety.

## Implemented Containers

### 📦 Vector (`ft::vector`)
- Dynamic array implementation with automatic memory management
- Random access iterators
- Capacity management with exponential growth
- Full STL vector interface compatibility

### 📚 Stack (`ft::stack`)
- LIFO (Last In, First Out) container adapter
- Uses `ft::vector` as default underlying container
- Support for custom underlying containers
- Protected access to underlying container for inheritance

### 🗺️ Map (`ft::map`)
- Associative container with unique key-value pairs
- Implemented using Red-Black Tree for O(log n) operations
- Bidirectional iterators
- Custom key comparison support

### 🎯 Set (`ft::set`)
- Associative container with unique elements
- Implemented using Red-Black Tree for O(log n) operations
- Bidirectional iterators
- Custom value comparison support

## Key Features

### Red-Black Tree Implementation
- Self-balancing binary search tree
- Guarantees O(log n) time complexity for insertions, deletions, and searches
- Custom iterator implementation for tree traversal
- Used as the underlying data structure for both `map` and `set`

### Iterator System
- Custom iterator implementations for each container
- Support for reverse iterators
- Full iterator traits compatibility
- Proper iterator categories (random access, bidirectional)

### Utility Components
- **`ft::pair`**: Key-value pair implementation
- **Iterator traits**: Type information for iterators
- **Type traits**: Template metaprogramming utilities
- **Algorithm utilities**: `equal`, `lexicographical_compare`
- **Reverse iterator**: Adapter for backward iteration

## Project Structure

```
ft_containers/
├── vector/             # Vector implementation
│   ├── vector.hpp
│   └── vector_tests.cpp
├── stack/              # Stack implementation
│   ├── stack.hpp
│   └── stack_tests.cpp
├── map/                # Map implementation
│   ├── map.hpp
│   └── map_tests.cpp
├── set/                # Set implementation
│   ├── set.hpp
│   └── set_tests.cpp
├── red_black_tree/     # Red-Black Tree implementation
│   ├── red_black_tree.hpp
│   └── rbt_iterator.hpp
├── utils/              # Utility components
│   ├── pair.hpp
│   ├── iterator_traits.hpp
│   ├── type_traits.hpp
│   ├── equal.hpp
│   ├── lexicographical_compare.hpp
│   ├── reverse_iterator.hpp
│   └── vector_iterator.hpp
└── tests/              # Test framework
    ├── tests.hpp
    └── tests.cpp
```

## Building and Testing

### Build the main executable
```bash
make
```

### Build and run tests
```bash
make test
./test
```

### Run the main program with STL comparison
```bash
# Run with ft implementation
./ft_containers 42

# Compare with STL (requires compilation with STD=1)
make fclean
make CFLAGS="-Wall -Werror -Wextra -std=c++98 -D STD"
./ft_containers 42
```

### Clean build files
```bash
make clean    # Remove object files
make fclean   # Remove object files and executables
```

## Compilation

- **Compiler**: C++ with C++98 standard
- **Flags**: `-Wall -Werror -Wextra -std=c++98`
- **Debug**: AddressSanitizer enabled (`-fsanitize=address`)
- **Macros**:
  - `FT`: Use ft implementations
  - `STD`: Use standard STL implementations (for comparison)

## Testing

The project includes comprehensive test suites for each container:

- **Unit tests**: Individual functionality testing
- **Performance tests**: Large-scale operations with memory monitoring
- **Comparison tests**: Behavior verification against STL implementations
- **Iterator tests**: Iterator functionality and compliance
- **Exception safety**: Proper exception handling verification

### Test Features
- Configurable seed for reproducible random testing
- Memory usage monitoring with configurable limits
- STL vs ft implementation comparison
- Comprehensive edge case coverage

## Implementation Details

### Memory Management
- Custom allocator support
- Proper RAII (Resource Acquisition Is Initialization)
- Exception-safe operations
- No memory leaks or undefined behavior

### Performance Characteristics
- **Vector**: Amortized O(1) push_back, O(1) random access
- **Stack**: O(1) push/pop operations
- **Map/Set**: O(log n) insert/find/erase operations
- **Iterators**: Efficient traversal with proper complexity guarantees

### Standards Compliance
- Full C++98 compatibility
- STL-compatible interfaces
- Proper const-correctness
- Exception specifications where applicable

## Usage Example

```cpp
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "set.hpp"

int main() {
    // Vector usage
    ft::vector<int> vec;
    vec.push_back(42);
    vec.push_back(21);

    // Map usage
    ft::map<std::string, int> mp;
    mp["hello"] = 42;
    mp["world"] = 21;

    // Stack usage
    ft::stack<int> stk;
    stk.push(42);
    stk.push(21);

    // Set usage
    ft::set<int> st;
    st.insert(42);
    st.insert(21);

    return 0;
}
```

## Requirements

- C++98 compatible compiler
- Standard C++ library headers
- POSIX-compliant system (for testing framework)

---

*This project demonstrates deep understanding of data structures, memory management, and template programming in C++. All implementations maintain STL compatibility while providing educational insight into container internals.*