#include "linked_list.hpp"
#include "catch.hpp"

#include <stdexcept>
#include <type_traits>
#include <utility>
#include <string>

TEST_CASE("create and destroy") {
  jmb::LinkedList<int> list;
  REQUIRE(list.empty());
  REQUIRE(list.size() == 0);
}

TEST_CASE("insert one at front") {
  jmb::LinkedList<std::string> list;
  list.append_front("hello");
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(list[0] == "hello");
}

TEST_CASE("insert one at back") {
  jmb::LinkedList<double> list;
  list.append_back(12.5);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  REQUIRE(list[0] == 12.5);
}

TEST_CASE("insert several at front") {
  jmb::LinkedList<int> list;
  list.append_front(1);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 1);
  list.append_front(27);
  REQUIRE(list.size() == 2);
  list.append_front(12);
  REQUIRE(list.size() == 3);
  list.append_front(17);
  REQUIRE(list.size() == 4);
  REQUIRE(list[3] == 1);
  REQUIRE(list[2] == 27);
  REQUIRE(list[1] == 12);
  REQUIRE(list[0] == 17);
}

TEST_CASE("insert several at back") {
  jmb::LinkedList<std::string> list;
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

TEST_CASE("const correctness on at") {
  const jmb::LinkedList<std::string> list;
  REQUIRE(std::is_const_v<std::remove_reference_t<decltype(list[0])>>);
}

TEST_CASE("const correctness on size and empty") {
  const jmb::LinkedList<int> list;
  list.empty();
  list.size();
}

TEST_CASE("copy constructor") {
  jmb::LinkedList<std::string> original;
  original.append_back("two");
  original.append_back("three");
  original.append_front("one");


  // in this case we have options:
  // 1) LinkedList copy{original}
  // 2) LinkedList copy(original);
  // 3) LinkedList copy = original; (looks like operator= but isn't)
  jmb::LinkedList<std::string> copy{original};
  REQUIRE(copy.size() == 3);
  REQUIRE(copy[0] == "one");
  REQUIRE(copy[1] == "two");
  REQUIRE(copy[2] == "three");

  original[0] = "";
  REQUIRE(copy[0] == "one");
}

TEST_CASE("copy assignment") {
  jmb::LinkedList<std::string> original;
  original.append_back("dos");
  original.append_back("tres");
  original.append_front("uno");

  jmb::LinkedList<std::string> copy;
  copy.append_back("hey");
  copy.append_back("you");

  copy = original;

  REQUIRE(copy[0] == "uno");
  REQUIRE(copy[1] == "dos");
  REQUIRE(copy[2] == "tres");
}

TEST_CASE("remove front") {
  jmb::LinkedList<int> list;
  list.append_front(3);
  list.append_front(2);
  list.append_front(1);
  list.remove(0);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 2);
  REQUIRE(list[0] == 2);
  REQUIRE(list[1] == 3);
}

TEST_CASE("remove last") {
  jmb::LinkedList<float> list;
  list.append_front(3);
  list.append_front(2);
  list.append_front(1);
  list.remove(2);
  REQUIRE_FALSE(list.empty());
  REQUIRE(list.size() == 2);
  REQUIRE(list[0] == 1);
  REQUIRE(list[1] == 2);
}

TEST_CASE("remove middle") {
  jmb::LinkedList<std::string> list;
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
  jmb::LinkedList<std::string> list;

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
  jmb::LinkedList<int> list1;

  list1.append_back(1);
  list1.append_back(2);
  list1.append_back(3);

  auto list2 = list1;
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);

  list1.append_front(0);
  REQUIRE_FALSE(list1 == list2);
  REQUIRE(list1 != list2);

  list1.remove(0);
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);

  list1.append_back(4);
  REQUIRE_FALSE(list1 == list2);
  REQUIRE(list1 != list2);

  list1.remove(3);
  REQUIRE(list1 == list2);
  REQUIRE_FALSE(list1 != list2);
}

TEST_CASE("out of range exceptions") {
  jmb::LinkedList<std::string> list;
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
