#include "tests.hpp"

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const int& lhs, const int& rhs) const { return lhs < rhs; }
};

static void test_constructor(void) {
  ft::set<int> first;  // empty set of ints

  int          myints[] = {10, 20, 30, 40, 50};
  ft::set<int> second(myints, myints + 5);  // range

  ft::set<int> third(second);  // a copy of second

  ft::set<int> fourth(second.begin(), second.end());  // iterator ctor.

  ft::set<int, classcomp> fifth;  // class as Compare

  bool (*fn_pt)(int, int) = fncomp;
  ft::set<int, bool (*)(int, int)> sixth(fn_pt);
}

static void test_assignment_operator(void) {
  int          myints[] = {12, 82, 37, 64, 15};
  ft::set<int> first(myints, myints + 5);  // set with 5 ints
  ft::set<int> second;                     // empty set

  second = first;          // now second contains the 5 ints
  first = ft::set<int>();  // and first is empty

  std::cout << "Size of first: " << int(first.size()) << '\n';
  std::cout << "Size of second: " << int(second.size()) << '\n';
}

static void test_begin_end(void) {
  int          myints[] = {75, 23, 65, 42, 13};
  ft::set<int> myset(myints, myints + 5);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;

  std::cout << '\n';
}

static void test_rbegin_rend(void) {
  int          myints[] = {21, 64, 17, 78, 49};
  ft::set<int> myset(myints, myints + 5);

  ft::set<int>::reverse_iterator rit;

  std::cout << "myset contains:";
  for (rit = myset.rbegin(); rit != myset.rend(); ++rit) std::cout << ' ' << *rit;

  std::cout << '\n';
}

static void test_empty(void) {
  ft::set<int> myset;

  myset.insert(20);
  myset.insert(30);
  myset.insert(10);

  std::cout << "myset contains:";
  while (!myset.empty()) {
    std::cout << ' ' << *myset.begin();
    myset.erase(myset.begin());
  }
  std::cout << '\n';
}

static void test_size(void) {
  ft::set<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i = 0; i < 10; ++i) myints.insert(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert(100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.erase(5);
  std::cout << "3. size: " << myints.size() << '\n';
}

static void test_max_size(void) {
  int          i;
  ft::set<int> myset;

  if (myset.max_size() > 1000) {
    for (i = 0; i < 1000; i++) myset.insert(i);
    std::cout << "The set contains 1000 elements.\n";
  } else
    std::cout << "The set could not hold 1000 elements.\n";
}

static void test_insert(void) {
  ft::set<int>                           myset;
  ft::set<int>::iterator                 it;
  ft::pair<ft::set<int>::iterator, bool> ret;

  // set some initial values:
  for (int i = 1; i <= 5; ++i) myset.insert(i * 10);  // set: 10 20 30 40 50

  ret = myset.insert(20);  // no new element inserted

  if (ret.second == false) it = ret.first;  // "it" now points to element 20

  myset.insert(it, 25);  // max efficiency inserting
  myset.insert(it, 24);  // max efficiency inserting
  myset.insert(it, 26);  // no max efficiency inserting

  int myints[] = {5, 10, 15};  // 10 already in set, not inserted
  myset.insert(myints, myints + 3);

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}

static void test_erase(void) {
  ft::set<int>           myset;
  ft::set<int>::iterator it;

  // insert some values:
  for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

  it = myset.begin();
  ++it;  // "it" points now to 20

  myset.erase(it);

  myset.erase(40);

  it = myset.find(60);
  myset.erase(it, myset.end());

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}

static void test_swap(void) {
  int          myints[] = {12, 75, 10, 32, 20, 25};
  ft::set<int> first(myints, myints + 3);       // 10,12,75
  ft::set<int> second(myints + 3, myints + 6);  // 20,25,32

  first.swap(second);

  std::cout << "first contains:";
  for (ft::set<int>::iterator it = first.begin(); it != first.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "second contains:";
  for (ft::set<int>::iterator it = second.begin(); it != second.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}

static void test_clear(void) {
  ft::set<int> myset;

  myset.insert(100);
  myset.insert(200);
  myset.insert(300);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';

  myset.clear();
  myset.insert(1101);
  myset.insert(2202);

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}

static void test_key_comp(void) {
  ft::set<int> myset;
  int          highest;

  ft::set<int>::key_compare mycomp = myset.key_comp();

  for (int i = 0; i <= 5; i++) myset.insert(i);

  std::cout << "myset contains:";

  highest = *myset.rbegin();
  ft::set<int>::iterator it = myset.begin();
  do {
    std::cout << ' ' << *it;
  } while (mycomp(*(++it), highest));

  std::cout << '\n';
}

static void test_value_comp(void) {
  ft::set<int> myset;

  ft::set<int>::value_compare mycomp = myset.value_comp();

  for (int i = 0; i <= 5; i++) myset.insert(i);

  std::cout << "myset contains:";

  int                    highest = *myset.rbegin();
  ft::set<int>::iterator it = myset.begin();
  do {
    std::cout << ' ' << *it;
  } while (mycomp(*(++it), highest));

  std::cout << '\n';
}

static void test_find(void) {
  ft::set<int>           myset;
  ft::set<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; i++) myset.insert(i * 10);  // set: 10 20 30 40 50

  it = myset.find(20);
  myset.erase(it);
  myset.erase(myset.find(40));

  std::cout << "myset contains:";
  for (it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}

static void test_count(void) {
  ft::set<int> myset;

  // set some initial values:
  for (int i = 1; i < 5; ++i) myset.insert(i * 3);  // set: 3 6 9 12

  for (int i = 0; i < 10; ++i) {
    std::cout << i;
    if (myset.count(i) != 0)
      std::cout << " is an element of myset.\n";
    else
      std::cout << " is not an element of myset.\n";
  }
}

static void test_lower_upper_bound(void) {
  ft::set<int>           myset;
  ft::set<int>::iterator itlow, itup;

  for (int i = 1; i < 10; i++) myset.insert(i * 10);  // 10 20 30 40 50 60 70 80 90

  itlow = myset.lower_bound(30);  //       ^
  itup = myset.upper_bound(60);   //                   ^

  myset.erase(itlow, itup);  // 10 20 70 80 90

  std::cout << "myset contains:";
  for (ft::set<int>::iterator it = myset.begin(); it != myset.end(); ++it) std::cout << ' ' << *it;
  std::cout << '\n';
}
static void test_equal_range(void) {
  ft::set<int> myset;

  for (int i = 1; i <= 5; i++) myset.insert(i * 10);  // myset: 10 20 30 40 50

  ft::pair<ft::set<int>::const_iterator, ft::set<int>::const_iterator> ret;
  ret = myset.equal_range(30);

  std::cout << "the lower bound points to: " << *ret.first << '\n';
  std::cout << "the upper bound points to: " << *ret.second << '\n';
}

static void test_get_allocator(void) {
  ft::set<int> myset;
  int*         p;
  unsigned int i;

  // allocate an array of 5 elements using myset's allocator:
  p = myset.get_allocator().allocate(5);

  // assign some values to array
  for (i = 0; i < 5; i++) p[i] = (i + 1) * 10;

  std::cout << "The allocated array contains:";
  for (i = 0; i < 5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  myset.get_allocator().deallocate(p, 5);
}

// static void test_relational_operators(void) {}

void set_main() {
  start_test("Test Constructor", test_constructor);
  start_test("Test Assignment Operator", test_assignment_operator);
  start_test("Test begin, end", test_begin_end);
  start_test("Test rbegin, rend", test_rbegin_rend);
  start_test("Test empty", test_empty);
  start_test("Test size", test_size);
  start_test("Test max_size", test_max_size);
  start_test("Test insert", test_insert);
  start_test("Test erase", test_erase);
  start_test("Test swap", test_swap);
  start_test("Test clear", test_clear);
  start_test("Test key_comp", test_key_comp);
  start_test("Test value_comp", test_value_comp);
  start_test("Test find", test_find);
  start_test("Test count", test_count);
  start_test("Test lower/upper bound", test_lower_upper_bound);
  start_test("Test equal_range", test_equal_range);
  start_test("Test get_allocator", test_get_allocator);
}