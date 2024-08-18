#include "s21_list.h"

#include <gtest/gtest.h>

#include <iostream>
#include <iterator>
#include <list>

#include "../s21_containersplus.h"
#include "../tests.cpp"
using namespace s21;

TEST(list_constructor_suit, default_constructor) {
  s21::list<int> s21list;
  std::list<int> stdlist;
  ASSERT_EQ(s21list.empty(), stdlist.empty());
  ASSERT_EQ(s21list.size(), stdlist.size());
}

TEST(list_constructor_suit, size_constructor) {
  s21::list<int> s21list(5);
  std::list<int> stdlist(5);
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(list_constructor_suit, init_constructor) {
  s21::list<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::list<int>::iterator s21it = s21list.begin();
  std::list<int>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(list_constructor_suit, init_char_constructor) {
  s21::list<char> s21list{'a', 'b', 'c'};
  std::list<char> stdlist{'a', 'b', 'c'};
  s21::list<char>::iterator s21it = s21list.begin();
  std::list<char>::iterator stdit = stdlist.begin();
  ASSERT_EQ(s21list.size(), stdlist.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(list_constructor_suit, copy_constructor) {
  s21::list<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::list<int> s21list2(s21list);
  std::list<int> stdlist2(stdlist);
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(list_constructor_suit, move_constructor) {
  s21::list<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::list<int> s21list2(std::move(s21list));
  std::list<int> stdlist2(std::move(stdlist));
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}

TEST(list_constructor_suit, move_operator_constructor) {
  s21::list<int> s21list{77, 55, 0, 87};
  std::list<int> stdlist{77, 55, 0, 87};
  s21::list<int> s21list2 = std::move(s21list);
  std::list<int> stdlist2 = std::move(stdlist);
  s21::list<int>::iterator s21it = s21list2.begin();
  std::list<int>::iterator stdit = stdlist2.begin();
  ASSERT_EQ(s21list2.size(), stdlist2.size());
  for (size_t i = 0; i <= s21list.size() + 1; i++) {
    ASSERT_EQ(*s21it, *stdit);
    ++s21it;
    ++stdit;
  }
}