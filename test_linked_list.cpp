#include "linked_list.h"
#include "catch.hpp"

#include <stdexcept>
#include <type_traits>
#include <utility>

TEST_CASE("create and destroy") {
  jmb::LinkedList list;
  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
}

TEST_CASE("insert one at front") {
  jmb::LinkedList list;
  list.append_front("hello");
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(list[0] == "hello");
}

TEST_CASE("insert one at back") {
  jmb::LinkedList list;
  list.append_back("hello");
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(list[0] == "hello");
}

TEST_CASE("insert several at front") {
  jmb::LinkedList list;
  list.append_front("abc");
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  list.append_front("def");
  REQUIRE(list.size() == 2);
  list.append_front("12345");
  REQUIRE(list.size() == 3);
  list.append_front("last");
  REQUIRE(list.size() == 4);
  REQUIRE(list[3] == "abc");
  REQUIRE(list[2] == "def");
  REQUIRE(list[1] == "12345");
  REQUIRE(list[0] == "last");
}

TEST_CASE("insert several at back") {
  jmb::LinkedList list;
  list.append_back("abc");
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  list.append_back("def");
  REQUIRE(list.size() == 2);
  list.append_back("12345");
  REQUIRE(list.size() == 3);
  list.append_back("last");
  REQUIRE(list.size() == 4);
  REQUIRE(list[0] == "abc");
  REQUIRE(list[1] == "def");
  REQUIRE(list[2] == "12345");
  REQUIRE(list[3] == "last");
}

//TODO append front and append back

TEST_CASE("can modify contained strings") {
  jmb::LinkedList list;
  list.append_front("hi");
  list[0][0] = 'x';
  REQUIRE(list[0] == "xi");
}

TEST_CASE("const correctness on at") {
  const jmb::LinkedList list;
  REQUIRE(std::is_const_v<std::remove_reference_t<decltype(list[0])>>);
}

TEST_CASE("const correctness on size and empty") {
  const jmb::LinkedList list;
  list.empty();
  list.size();
}

TEST_CASE("copy constructor") {
  jmb::LinkedList original;
  original.append_back("two");
  original.append_back("three");
  original.append_front("one");


  // in this case we have options:
  // 1) LinkedList copy{original}
  // 2) LinkedList copy(original);
  // 3) LinkedList copy = original; (looks like operator= but isn't)
  jmb::LinkedList copy{original};
  REQUIRE(copy.size() == 3);
  REQUIRE(copy[0] == "one");
  REQUIRE(copy[1] == "two");
  REQUIRE(copy[2] == "three");

  original[0] = "";
  REQUIRE(copy[0] == "one");
}

TEST_CASE("copy assignment") {
  jmb::LinkedList original;
  original.append_back("dos");
  original.append_back("tres");
  original.append_front("uno");

  jmb::LinkedList copy;
  copy.append_back("hey");
  copy.append_back("you");

  copy = original;

  REQUIRE(copy[0] == "uno");
  REQUIRE(copy[1] == "dos");
  REQUIRE(copy[2] == "tres");
}

TEST_CASE("remove front") {
  jmb::LinkedList list;
  list.append_front("three");
  list.append_front("two");
  list.append_front("one");
  list.remove(0);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 2);
  REQUIRE(list[0] == "two");
  REQUIRE(list[1] == "three");
}

TEST_CASE("remove last") {
  jmb::LinkedList list;
  list.append_front("three");
  list.append_front("two");
  list.append_front("one");
  list.remove(2);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 2);
  REQUIRE(list[0] == "one");
  REQUIRE(list[1] == "two");
}

TEST_CASE("remove middle") {
  jmb::LinkedList list;
  list.append_back("one");
  list.append_back("two");
  list.append_back("three");
  list.append_back("four");
  list.append_back("five");

  list.remove(2);
  REQUIRE(list.size() == 4);
  REQUIRE(list[0] == "one");
  REQUIRE(list[1] == "two");
  REQUIRE(list[2] == "four");
  REQUIRE(list[3] == "five");

  list.remove(2);
  REQUIRE(list.size() == 3);
  REQUIRE(list[0] == "one");
  REQUIRE(list[1] == "two");
  REQUIRE(list[2] == "five");

  list.remove(1);
  REQUIRE(list.size() == 2);
  REQUIRE(list[0] == "one");
  REQUIRE(list[1] == "five");
}

TEST_CASE("remove all elements") {
  jmb::LinkedList list;

  list.append_back("one");
  list.append_back("two");
  list.append_back("three");

  list.remove(2);
  list.remove(1);
  list.remove(0);

  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
}

TEST_CASE("equality") {
  jmb::LinkedList list1;

  list1.append_back("one");
  list1.append_back("two");
  list1.append_back("three");

  auto list2 = list1;
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);

  list1.append_front("zero");
  REQUIRE_FALSE(list1 == list2);
  REQUIRE(list1 != list2);

  list1.remove(0);
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);

  list1.append_back("four");
  REQUIRE_FALSE(list1 == list2);
  REQUIRE(list1 != list2);

  list1.remove(3);
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);

  list1[0][0] = 'x';
  REQUIRE_FALSE(list1 == list2);
  REQUIRE(list1 != list2);
}

TEST_CASE("out of range exceptions") {
  jmb::LinkedList list;
  list.append_back("one");
  REQUIRE_THROWS_AS(list[1], std::out_of_range);
  REQUIRE_THROWS_AS(std::as_const(list)[1], std::out_of_range);
  REQUIRE_THROWS_AS(list.remove(1), std::out_of_range);

  list.remove(0);
  REQUIRE(list.empty());
  REQUIRE_THROWS_AS(list[0], std::out_of_range);
  REQUIRE_THROWS_AS(std::as_const(list)[0], std::out_of_range);
  REQUIRE_THROWS_AS(list.remove(0), std::out_of_range);
}
