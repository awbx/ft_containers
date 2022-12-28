#include "tests.hpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
  bool operator()(const char& lhs, const char& rhs) const { return lhs < rhs; }
};

static void test_constructor(void) {
  ft::map<char, int> first;

  first['a'] = 10;
  first['b'] = 30;
  first['c'] = 50;
  first['d'] = 70;

  ft::map<char, int> second(first.begin(), first.end());

  ft::map<char, int> third(second);

  ft::map<char, int, classcomp> fourth;  // class as Compare

  bool (*fn_pt)(char, char) = fncomp;
  ft::map<char, int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compa

  for (ft::map<char, int>::iterator it = first.begin(); it != first.end(); it++) std::cout << it->first << "\n";
}

static void test_assignment_operator(void) {
  ft::map<char, int> first;
  ft::map<char, int> second;

  first['x'] = 8;
  first['y'] = 16;
  first['z'] = 32;

  second = first;                // second now contains 3 ints
  first = ft::map<char, int>();  // and first is now empty

  std::cout << "Size of first: " << first.size() << '\n';
  std::cout << "Size of second: " << second.size() << '\n';
}

static void test_begin_end(void) {
  ft::map<char, int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}

// static void test_rbegin_rend(void) {
//   ft::map<char, int> mymap;

//   mymap['x'] = 100;
//   mymap['y'] = 200;
//   mymap['z'] = 300;

//   // show content:
//   ft::map<char, int>::reverse_iterator rit;
//   for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit) std::cout << rit->first << " => " << rit->second << '\n';
// }

static void test_empty(void) {
  ft::map<char, int> mymap;

  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;

  while (!mymap.empty()) {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }
}

static void test_size(void) {
  ft::map<char, int> mymap;
  mymap['a'] = 101;
  mymap['b'] = 202;
  mymap['c'] = 302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';
}

static void test_max_size(void) {
  int               i;
  ft::map<int, int> mymap;

  if (mymap.max_size() > 1000) {
    for (i = 0; i < 1000; i++) mymap[i] = 0;
    std::cout << "The map contains 1000 elements.\n";
  } else
    std::cout << "The map could not hold 1000 elements.\n";
}

static void test_access_element(void) {
  ft::map<char, std::string> mymap;

  mymap['a'] = "an element";
  mymap['b'] = "another element";
  mymap['c'] = mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

static void test_insert(void) {
  ft::map<char, int> mymap;

  // first insert function version (single parameter):
  mymap.insert(ft::pair<char, int>('a', 100));
  mymap.insert(ft::pair<char, int>('z', 200));

  ft::pair<ft::map<char, int>::iterator, bool> ret;
  ret = mymap.insert(ft::pair<char, int>('z', 500));
  if (ret.second == false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  ft::map<char, int>::iterator it = mymap.begin();
  mymap.insert(it, ft::pair<char, int>('b', 300));  // max efficiency inserting
  mymap.insert(it, ft::pair<char, int>('c', 400));  // no max efficiency inserting

  // third insert function version (range insertion):
  ft::map<char, int> anothermap;
  anothermap.insert(mymap.begin(), mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it = anothermap.begin(); it != anothermap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}

static void test_erase(void) {
  ft::map<char, int>           mymap;
  ft::map<char, int>::iterator it;

  // insert some values:
  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;
  mymap['d'] = 40;
  mymap['e'] = 50;
  mymap['f'] = 60;

  it = mymap.find('b');
  mymap.erase(it);  // erasing by iterator

  mymap.erase('c');  // erasing by key

  it = mymap.find('e');
  mymap.erase(it, mymap.end());  // erasing by range

  // show content:
  for (it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}

static void test_swap(void) {
  ft::map<char, int> foo, bar;

  foo['x'] = 100;
  foo['y'] = 200;

  bar['a'] = 11;
  bar['b'] = 22;
  bar['c'] = 33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it) std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}

static void test_clear(void) {
  ft::map<char, int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  std::cout << "mymap contains:\n";
  for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a'] = 1101;
  mymap['b'] = 2202;

  std::cout << "mymap contains:\n";
  for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}

// void test_key_comp(void) {
//   ft::map<char, int> mymap;

//   ft::map<char, int>::key_compare mycomp = mymap.key_comp();

//   mymap['a'] = 100;
//   mymap['b'] = 200;
//   mymap['c'] = 300;

//   std::cout << "mymap contains:\n";

//   char highest = mymap.rbegin()->first;  // key value of last element

//   ft::map<char, int>::iterator it = mymap.begin();
//   do {
//     std::cout << it->first << " => " << it->second << '\n';
//   } while (mycomp((*it++).first, highest));
// }

// void test_value_comp(void) {
//   ft::map<char, int> mymap;

//   mymap['x'] = 1001;
//   mymap['y'] = 2002;
//   mymap['z'] = 3003;

//   std::cout << "mymap contains:\n";

//   ft::pair<char, int> highest = *mymap.rbegin();  // last element

//   ft::map<char, int>::iterator it = mymap.begin();
//   do {
//     std::cout << it->first << " => " << it->second << '\n';
//   } while (mymap.value_comp()(*it++, highest));
// }

static void test_find(void) {
  ft::map<char, int>           mymap;
  ft::map<char, int>::iterator it;

  mymap['a'] = 50;
  mymap['b'] = 100;
  mymap['c'] = 150;
  mymap['d'] = 200;

  it = mymap.find('b');
  if (it != mymap.end()) mymap.erase(it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';
}

static void test_count(void) {
  ft::map<char, int> mymap;
  char               c;

  mymap['a'] = 101;
  mymap['c'] = 202;
  mymap['f'] = 303;

  for (c = 'a'; c < 'h'; c++) {
    std::cout << c;
    if (mymap.count(c) > 0)
      std::cout << " is an element of mymap.\n";
    else
      std::cout << " is not an element of mymap.\n";
  }
}

static void test_lower_upper_bound(void) {
  ft::map<char, int>           mymap;
  ft::map<char, int>::iterator itlow, itup;

  mymap['a'] = 20;
  mymap['b'] = 40;
  mymap['c'] = 60;
  mymap['d'] = 80;
  mymap['e'] = 100;

  itlow = mymap.lower_bound('b');  // itlow points to b
  itup = mymap.upper_bound('d');   // itup points to e (not d!)

  mymap.erase(itlow, itup);  // erases [itlow,itup)

  // print content:
  for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) std::cout << it->first << " => " << it->second << '\n';
}
static void test_equal_range(void) {
  ft::map<char, int> mymap;

  mymap['a'] = 10;
  mymap['b'] = 20;
  mymap['c'] = 30;

  ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';
}

static void test_get_allocator(void) {
  int                        psize;
  ft::map<char, int>         mymap;
  ft::pair<const char, int>* p;

  // allocate an array of 5 elements using mymap's allocator:
  p = mymap.get_allocator().allocate(5);

  // assign some values to array
  psize = sizeof(ft::map<char, int>::value_type) * 5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap.get_allocator().deallocate(p, 5);
}

// static void test_relational_operators(void) {}


void map_main() {
  start_test("Test Constructor", test_constructor);
  start_test("Test Assignment Operator", test_assignment_operator);
  start_test("Test begin, end", test_begin_end);
  //   start_test("Test rbegin, rend", test_rbegin_rend);
  start_test("Test empty", test_empty);
  start_test("Test size", test_size);
  start_test("Test max_size", test_max_size);
  start_test("Test access element[]", test_access_element);
  start_test("Test insert", test_insert);
  start_test("Test erase", test_erase);
  start_test("Test swap", test_swap);
  start_test("Test clear", test_clear);
  //   start_test("Test key_comp", test_key_comp);
  //   start_test("Test value_comp", test_value_comp);
  start_test("Test find", test_find);
  start_test("Test count", test_count);
  start_test("Test lower/upper bound", test_lower_upper_bound);
  start_test("Test equal_range", test_equal_range);
  start_test("Test get_allocator", test_get_allocator);
  // start_test("Test relational operators", test_relational_operators);
}