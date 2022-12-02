#include "tests.hpp"

static void test_constructor(void) {
    // constructors used in the same order as described above:
    ft::vector<int> first;                                // empty vector of ints
    ft::vector<int> second(4, 100);                       // four ints with value 100
    ft::vector<int> third(second.begin(), second.end());  // iterating through second
    ft::vector<int> fourth(third);                        // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int             myints[] = {16, 2, 77, 29};
    ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';
}

static void test_assignment_operator(void) {
    ft::vector<int> foo(3, 0);
    ft::vector<int> bar(5, 0);

    bar = foo;
    foo = ft::vector<int>();

    std::cout << "Size of foo: " << int(foo.size()) << '\n';
    std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

static void test_begin_end(void) {
    ft::vector<int> myvector;
    for (int i = 1; i <= 5; i++) myvector.push_back(i);

    std::cout << "myvector contains:";
    for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';
}

static void test_rbegin_rend(void) {
    ft::vector<int> myvector(5);  // 5 default-constructed ints

    int i = 0;

    ft::vector<int>::reverse_iterator rit = myvector.rbegin();
    for (; rit != myvector.rend(); ++rit) *rit = ++i;

    std::cout << "myvector contains:";
    for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';
}

static void test_size(void) {
    ft::vector<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i = 0; i < 10; i++) myints.push_back(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.insert(myints.end(), 10, 100);
    std::cout << "2. size: " << myints.size() << '\n';

    myints.pop_back();
    std::cout << "3. size: " << myints.size() << '\n';
}

static void test_max_size(void) {
    ft::vector<int> myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << "\n";
    std::cout << "capacity: " << myvector.capacity() << "\n";
    std::cout << "max_size: " << myvector.max_size() << "\n";
}

static void test_resize(void) {
    ft::vector<int> myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++) myvector.push_back(i);

    myvector.resize(5);
    myvector.resize(8, 100);
    myvector.resize(12);

    std::cout << "myvector contains:";
    for (size_t i = 0; i < myvector.size(); i++) std::cout << ' ' << myvector[i];
    std::cout << '\n';
}

static void test_capacity(void) {
    ft::vector<int> myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++) myvector.push_back(i);

    std::cout << "size: " << myvector.size() << '\n';
    std::cout << "capacity: " << myvector.capacity() << '\n';
    std::cout << "max_size: " << myvector.max_size() << '\n';
}

static void test_empty(void) {
    ft::vector<int> myvector;
    int             sum(0);

    for (int i = 1; i <= 10; i++) myvector.push_back(i);

    while (!myvector.empty()) {
        sum += myvector.back();
        myvector.pop_back();
    }

    std::cout << "is empty: " << std::boolalpha << myvector.empty() << "\n";
    std::cout << "total: " << sum << '\n';
}

static void test_reserve(void) {
    ft::vector<int>::size_type sz;

    ft::vector<int> foo;
    sz = foo.capacity();
    std::cout << "making foo grow:\n";
    for (int i = 0; i < 100; ++i) {
        foo.push_back(i);
        if (sz != foo.capacity()) {
            sz = foo.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }

    ft::vector<int> bar;
    sz = bar.capacity();
    bar.reserve(100);  // this is the only difference with foo above
    std::cout << "making bar grow:\n";
    for (int i = 0; i < 100; ++i) {
        bar.push_back(i);
        if (sz != bar.capacity()) {
            sz = bar.capacity();
            std::cout << "capacity changed: " << sz << '\n';
        }
    }
}

static void test_access_element(void) {
    ft::vector<int> myvector(10);  // 10 zero-initialized elements

    ft::vector<int>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++) myvector[i] = i;

    // reverse vector using operator[]:
    for (unsigned i = 0; i < sz / 2; i++) {
        int temp;
        temp = myvector[sz - 1 - i];
        myvector[sz - 1 - i] = myvector[i];
        myvector[i] = temp;
    }

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < sz; i++) std::cout << ' ' << myvector[i];
    std::cout << '\n';
}

static void test_at(void) {
    ft::vector<int> myvector(10);  // 10 zero-initialized ints

    // assign some values:
    for (unsigned i = 0; i < myvector.size(); i++) myvector.at(i) = i;

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++) std::cout << ' ' << myvector.at(i);
    std::cout << '\n';
}

static void test_front_back(void) {
    {
        ft::vector<int> myvector;

        myvector.push_back(78);
        myvector.push_back(16);

        // now front equals 78, and back 16

        myvector.front() -= myvector.back();

        std::cout << "myvector.front() is now " << myvector.front() << '\n';
    }

    {
        ft::vector<int> myvector;

        myvector.push_back(10);

        while (myvector.back() != 0) {
            myvector.push_back(myvector.back() - 1);
        }

        std::cout << "myvector contains:";
        for (unsigned i = 0; i < myvector.size(); i++) std::cout << ' ' << myvector[i];
        std::cout << '\n';
    }
}

static void test_assign(void) {
    ft::vector<int> first;
    ft::vector<int> second;
    ft::vector<int> third;

    first.assign(7, 100);  // 7 ints with a value of 100

    ft::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1);  // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3);  // assigning from array.

    std::cout << "Size of first: " << int(first.size()) << '\n';
    std::cout << "Size of second: " << int(second.size()) << '\n';
    std::cout << "Size of third: " << int(third.size()) << '\n';
}

static void test_push_back(void) {
    ft::vector<int> myvector;

    std::cout << "Please enter some integers (enter 0 to end):\n";

    size_t idx = 0;
    while (idx < 100) {
        myvector.push_back(idx + 1);
        idx++;
    }

    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
}

static void test_pop_back(void) {
    ft::vector<int> myvector;
    int             sum(0);
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    while (!myvector.empty()) {
        sum += myvector.back();
        myvector.pop_back();
    }

    std::cout << "The elements of myvector add up to " << sum << '\n';
}

static void test_insert(void) {
    ft::vector<int>           myvector(3, 100);
    ft::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);

    myvector.insert(it, 2, 300);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    ft::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);

    std::cout << "myvector contains:";
    for (it = myvector.begin(); it < myvector.end(); it++) std::cout << ' ' << *it;
    std::cout << '\n';
}

static void test_erase(void) {
    ft::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++) myvector.push_back(i);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); ++i) std::cout << ' ' << myvector[i];
    std::cout << '\n';
}

static void test_swap(void) {
    ft::vector<int> foo(3, 100);  // three ints with a value of 100
    ft::vector<int> bar(5, 200);  // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (unsigned i = 0; i < foo.size(); i++) std::cout << ' ' << foo[i];
    std::cout << '\n';

    std::cout << "bar contains:";
    for (unsigned i = 0; i < bar.size(); i++) std::cout << ' ' << bar[i];
    std::cout << '\n';
}

static void test_clear(void) {
    ft::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++) std::cout << ' ' << myvector[i];
    std::cout << '\n';

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    std::cout << "myvector contains:";
    for (unsigned i = 0; i < myvector.size(); i++) std::cout << ' ' << myvector[i];
    std::cout << '\n';
}

static void test_get_allocator(void) {
    ft::vector<int> myvector;
    int*            p;
    unsigned int    i;

    // allocate an array with space for 5 elements using vector's allocator:
    p = myvector.get_allocator().allocate(5);

    // construct values in-place on the array:
    for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i], i);

    std::cout << "The allocated array contains:";
    for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
    std::cout << '\n';

    // destroy and deallocate:
    for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
    myvector.get_allocator().deallocate(p, 5);
}

static void test_relational_operators(void) {
    ft::vector<int> foo(3, 100);  // three ints with a value of 100
    ft::vector<int> bar(2, 200);  // two ints with a value of 200

    if (foo == bar) std::cout << "foo and bar are equal\n";
    if (foo != bar) std::cout << "foo and bar are not equal\n";
    if (foo < bar) std::cout << "foo is less than bar\n";
    if (foo > bar) std::cout << "foo is greater than bar\n";
    if (foo <= bar) std::cout << "foo is less than or equal to bar\n";
    if (foo >= bar) std::cout << "foo is greater than or equal to bar\n";
}

static void test_non_member_swap(void) {
    ft::vector<int> foo(3, 100);  // three ints with a value of 100
    ft::vector<int> bar(5, 200);  // five ints with a value of 200

    foo.swap(bar);

    std::cout << "foo contains:";
    for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';

    std::cout << "bar contains:";
    for (ft::vector<int>::iterator it = bar.begin(); it != bar.end(); ++it) std::cout << ' ' << *it;
    std::cout << '\n';
}

void vector_main() {
    start_test("Test Constructor", test_constructor);
    start_test("Test Assignment Operator", test_assignment_operator);
    start_test("Test begin, end", test_begin_end);
    start_test("Test rbegin, rend", test_rbegin_rend);
    start_test("Test size", test_size);
    start_test("Test max_size", test_max_size);
    start_test("Test resize", test_resize);
    start_test("Test capacity", test_capacity);
    start_test("Test empty", test_empty);
    start_test("Test reserve", test_reserve);
    start_test("Test access element[]", test_access_element);
    start_test("Test at", test_at);
    start_test("Test front, back", test_front_back);
    start_test("Test assign", test_assign);
    start_test("Test push_back", test_push_back);
    start_test("Test pop_back", test_pop_back);
    start_test("Test insert", test_insert);
    start_test("Test erase", test_erase);
    start_test("Test swap", test_swap);
    start_test("Test clear", test_clear);
    start_test("Test get_allocator", test_get_allocator);
    start_test("Test relational operators", test_relational_operators);
    start_test("Test non-member swap", test_non_member_swap);
}