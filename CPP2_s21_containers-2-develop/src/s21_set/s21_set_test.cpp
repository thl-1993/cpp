#include "s21_set.hpp"

#include <gtest/gtest.h>

#include <set>

#include "../tests.cpp"
using namespace s21;

template <typename T>
void test_eq(set<T> &a, std::set<T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_a.begin();
  auto iter = a.begin();
  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(*iter, *iter_std);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_set, create_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.empty(), std_a.empty());
  a.max_size();
  a.insert(5);
  std_a.insert(5);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_2) {
  set<int> a{1, 2, 3, 4, 5};
  std::set<int> std_a{1, 2, 3, 4, 5};
  a.insert(5);
  std_a.insert(5);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_3_copy) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(a);
  std::set<int> std_b(std_a);
  test_eq<int>(a, std_a);
}

TEST(s21_set, create_3_move) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b(std::move(a));
  std::set<int> std_b(std::move(std_a));
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, operator_equal) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b{1};
  std::set<int> std_b{1};
  b = a;
  std_b = std_a;
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, operator_eq) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  set<int> b{1};
  std::set<int> std_b{1};
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(a.size(), std_a.size());
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
  b = a;
  std_b = std_a;
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}

TEST(s21_set, insert_1) {
  set<int> a;
  std::set<int> std_a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(*a.insert(5).first, *std_a.insert(5).first);
  EXPECT_EQ(a.insert(5).second, std_a.insert(5).second);
  EXPECT_EQ(a.insert(6).second, std_a.insert(6).second);
  EXPECT_EQ(*a.insert(7).first, *std_a.insert(7).first);
  test_eq<int>(a, std_a);
}

TEST(s21_set, find_1) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10, 5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(a.contains(5), true);
  EXPECT_EQ(*a.find(5), *std_a.find(5));
  EXPECT_EQ(a.contains(12), true);
  EXPECT_EQ(*a.find(12), *std_a.find(12));
  EXPECT_EQ(a.contains(20), false);
  EXPECT_EQ(a.find(20) == a.end(), true);
  EXPECT_EQ(std_a.find(20) == std_a.end(), true);
}

TEST(s21_set, swap_1) {
  set<int> a{12, 9, 4, 2, 1, 3, 11, 10};
  std::set<int> std_a{12, 9, 4, 2, 1, 3, 11, 10};
  set<int> b{5, 6, 18, 25, 16, 14, 17, 13};
  std::set<int> std_b{5, 6, 18, 25, 16, 14, 17, 13};
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(b.size(), std_b.size());
  a.swap(b);
  std_a.swap(std_b);
  test_eq<int>(a, std_a);
  test_eq<int>(b, std_b);
}
