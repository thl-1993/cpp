// #include <gtest/gtest.h>
#include "../s21_map/s21_map.hpp"

#include "../tests.cpp"
using namespace s21;

TEST(map_constructor, no_arg) {
  s21::map<int, int> _map;
  EXPECT_EQ(_map.empty(), 1);
}

TEST(map_constructor, initializer_list) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  EXPECT_EQ(_map.empty(), 0);
}

TEST(map_constructor, copy) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  s21::map<int, int> map_copy(_map);
  auto j = map_copy.begin();
  for (auto i = _map.begin(); i != _map.end(); ++i) {
    ASSERT_TRUE(i->first == j->first);
    ASSERT_TRUE(i->second == j->second);
    ++j;
  }
}

TEST(map_constructor, move) {
  s21::map<int, int> _map({std::pair<int, int>{11, 2}, {99, 0}});
  s21::map<int, int> map_copy(_map);
  s21::map<int, int> map_moved(std::move(_map));
  auto j = map_moved.begin();
  for (auto i = map_copy.begin(); i != map_copy.end(); ++i) {
    ASSERT_TRUE(i->first == j->first);
    ASSERT_TRUE(i->second == j->second);
    ++j;
  }
  EXPECT_EQ(_map.empty(), 1);
}

TEST(map_operator, move_assignment) {
  s21::map<std::string, char> first({std::pair<std::string, char>{"this", 'k'},
                                     {"world", 'o'},
                                     {"is mine", '!'}});
  s21::map<std::string, char> copy(first);
  s21::map<std::string, char> second;
  second = std::move(first);
  auto j = second.begin();
  for (auto i = copy.begin(); i != copy.end(); ++i) {
    ASSERT_TRUE(i->first == j->first);
    ASSERT_TRUE(i->second == j->second);
    ++j;
  }
  EXPECT_EQ(first.empty(), 1);
}

TEST(map_operator, braces) {
  s21::map<int, int> _map({std::pair<int, int>{0, 0}, {9, 123}});
  EXPECT_EQ(_map[0], 0);
  EXPECT_EQ(_map[9], 123);
}

TEST(map_at, at) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  EXPECT_EQ(_map.at("this"), 'k');
  EXPECT_EQ(_map.at("world"), 'o');
  EXPECT_EQ(_map.at("is mine"), '!');
  EXPECT_THROW(_map.at("something"), std::out_of_range);
  EXPECT_THROW(_map.at("aaa"), std::out_of_range);
}

TEST(map_iterator, begin) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto i = _map.begin();
  EXPECT_EQ(i->first, "is mine");
  EXPECT_EQ(i->second, '!');
}

TEST(map_iterator, end) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto i = _map.end();  // BUG ent указывает на элемент следующий за последним.
  --i;                  // Поэтому нкрементируем.
  EXPECT_EQ(i->first, "world");
  EXPECT_EQ(i->second, 'o');
}

TEST(map_iterator_operator, increment) {
  s21::map<std::string, char> _map({std::pair<std::string, char>{"this", 'k'},
                                    {"world", 'o'},
                                    {"is mine", '!'}});
  auto i = _map.begin();
  ++i;
  EXPECT_EQ(i->first, "this");
  EXPECT_EQ(i->second, 'k');
  i++;
  EXPECT_EQ(i->first, "world");
  EXPECT_EQ(i->second, 'o');
}

TEST(map_iterator_operator, decrement_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.end();
  --i;
  EXPECT_EQ(i->first, 5);
  EXPECT_EQ(i->second, 4);
  i--;
  EXPECT_EQ(i->first, 4);
  EXPECT_EQ(i->second, 3);
}

TEST(map_iterator_operator, decrement_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.end();
  int j = 5;
  while (i != _map.begin()) {
    --i;
    EXPECT_EQ(i->first, j);
    --j;
  }
}

TEST(map_insert, insert_test_0) {
  s21::map<int, int> _map;
  _map.insert(0, 9);
  auto i = _map.begin();
  EXPECT_EQ(i->first, 0);
  EXPECT_EQ(i->second, 9);
}

TEST(map_insert, insert_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert(5, 9);
  EXPECT_EQ(_map[5], 4);
}

TEST(map_insert, insert_value_type_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert(std::pair<int, int>(9, 7));
  EXPECT_EQ(_map[9], 7);
}

TEST(map_insert, insert_or_assign_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  _map.insert_or_assign(5, 9);
  EXPECT_EQ(_map[5], 9);
}

TEST(map_erase, erase_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert(8, 9);
  _map.erase(i.first);
  EXPECT_THROW(_map.at(8), std::out_of_range);
}

TEST(map_erase, erase_test_1) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_erase, erase_test_2) {
  s21::map<int, int> _map;
  auto i = _map.insert(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_erase, erase_test_3) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(1, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(1), std::out_of_range);
}

TEST(map_erase, erase_test_4) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  auto i = _map.insert_or_assign(4, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(4), std::out_of_range);
}

TEST(map_erase, erase_test_5) {
  s21::map<int, int> _map({std::pair<int, int>{5, 4},
                           {1, 0},
                           {2, 1},
                           {9, 3},
                           {7, 3},
                           {17, 3},
                           {3, 2}});
  auto i = _map.insert_or_assign(5, 9).first;
  _map.erase(i);
  EXPECT_THROW(_map.at(5), std::out_of_range);
}

TEST(map_swap, swap_test_0) {
  s21::map<std::string, char> one(
      {std::pair<std::string, char>{"one", '1'}, {"two", '2'}, {"three", '3'}});
  s21::map<std::string, char> another(
      {std::pair<std::string, char>{"this", 'k'},
       {"world", 'o'},
       {"is mine", '!'},
       {"horse", '.'}});
  s21::map<std::string, char> one_copy(one);
  s21::map<std::string, char> another_copy(another);
  one.swap(another);
  auto j = another.begin();
  for (auto i = one_copy.begin(); i != one_copy.end(); ++i) {
    ASSERT_TRUE(i->first == j->first);
    ASSERT_TRUE(i->second == j->second);
    ++j;
  }
  j = one.begin();
  for (auto i = another_copy.begin(); i != another_copy.end(); ++i) {
    ASSERT_TRUE(i->first == j->first);
    ASSERT_TRUE(i->second == j->second);
    ++j;
  }
}

TEST(map_merge, merge_test_0) {
  s21::map<int, int> _first(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  s21::map<int, int> _second({std::pair<int, int>{-50, 4},
                              {10, 0},
                              {-20, 1},
                              {40, 3},
                              {-30, 2},
                              {5, 5},
                              {2, 2}});
  s21::map<int, int> _result({std::pair<int, int>{5, 4},
                              {1, 0},
                              {2, 1},
                              {4, 3},
                              {3, 2},
                              {-50, 4},
                              {10, 0},
                              {-20, 1},
                              {40, 3},
                              {-30, 2},
                              {5, 5},
                              {2, 2}});
  _first.merge(_second);
  auto it = _first.begin();
  for (auto i = _result.begin(); i != _result.end(); ++i) {
    EXPECT_EQ(i->first, it->first);
    EXPECT_EQ(i->second, it->second);
    ++it;
  }
}

TEST(map_contains, contains_test_0) {
  s21::map<int, int> _map(
      {std::pair<int, int>{5, 4}, {1, 0}, {2, 1}, {4, 3}, {3, 2}});
  ASSERT_TRUE(!_map.contains(789));
  ASSERT_TRUE(_map.contains(5));
}

template <typename K, typename T>
void test_eq(map<K, T> &a, std::map<K, T> &std_a) {
  EXPECT_EQ(a.size(), std_a.size());
  auto iter_std = std_a.begin();
  auto iter = a.begin();
  while (iter_std != std_a.end() && iter != a.end()) {
    EXPECT_EQ(iter->first, iter_std->first);
    EXPECT_EQ(iter->second, iter_std->second);
    ++iter;
    ++iter_std;
  }
}

TEST(s21_map, create_1) {
  std::map<int, double> std_a;
  map<int, double> a;
  test_eq(a, std_a);
  std_a.insert({5, 2});
  a.insert({5, 2});
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, create_2) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, create_3_copy) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b(a);
  std::map<int, double> std_b(std_a);
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, create_3_move) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b(std::move(a));
  std::map<int, double> std_b(std::move(std_a));
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, insert_1) {
  std::map<int, double> std_a;
  map<int, double> a;
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ((std_a.insert({1, 2}).second), (a.insert({1, 2}).second));  // true
  EXPECT_EQ((std_a.insert({1, 3}).second), (a.insert({1, 3}).second));  // false
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ((std_a.insert({0, 4}).first->second),
            (a.insert({0, 4}).first->second));
  EXPECT_EQ((std_a.insert({2, 4}).first->first),
            (a.insert({2, 4}).first->first));
  std_a.insert({5, 2});
  std_a.insert({2, 2});
  std_a.insert({3, 2});
  std_a.insert({3, 3});
  std_a.insert({3, 0});
  a.insert({5, 2});
  a.insert({2, 2});
  a.insert({3, 2});
  a.insert({3, 3});
  a.insert({3, 0});
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, erase_it) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  EXPECT_EQ(a.size(), std_a.size());
  int i = 0;
  auto iter_std = std_a.begin();
  auto iter = a.begin();

  while (iter_std != std_a.end() && iter != a.end()) {
    auto tmp_std = iter_std;
    auto tmp = iter;
    ++iter_std;
    ++iter;
    if (i % 2 == 0) {
      std_a.erase(tmp_std);
      a.erase(tmp);
    }
    i++;
  }
  test_eq(a, std_a);
}

TEST(s21_map, operator_eq) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());
  map<int, double> b{{1, 1}};
  std::map<int, double> std_b{{1, 1}};
  b = a;
  std_b = std_a;
  test_eq<int, double>(a, std_a);
  test_eq<int, double>(b, std_b);
}

TEST(s21_map, contains) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  EXPECT_EQ(a.size(), std_a.size());

  for (int i = -1; i < 20; i++) {
    auto iter_std = std_a.find(i);
    bool flag = (iter_std != std_a.end());
    EXPECT_EQ(a.contains(i), flag);
  }
}

TEST(s21_map, find) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};

  for (int i = -1; i < 20; i++) {
    if (a.contains(i)) {
      EXPECT_EQ(a.find(5)->first, std_a.find(5)->first);
      EXPECT_EQ(a.find(5)->second, std_a.find(5)->second);
    } else {
      EXPECT_EQ((std_a.find(i) == std_a.end()), (a.find(i) == a.end()));
    }
  }
}

TEST(s21_map, at) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  std_a.at(5) = 20;
  a.at(5) = 20;
  std_a.at(3) = 30;
  a.at(3) = 30;
// утечка на маке в leaks
#ifndef __APPLE__
  EXPECT_THROW(std_a.at(-1), std::out_of_range);
  EXPECT_THROW(a.at(-1), std::out_of_range);
#endif
  test_eq<int, double>(a, std_a);
}

TEST(s21_map, operator_at) {
  std::map<int, double> std_a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                              {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  map<int, double> a{{1, 2}, {2, 2}, {2, 3}, {3, 3}, {4, 2},
                     {4, 3}, {5, 5}, {5, 7}, {8, 2}};
  std_a[5] = 20;
  a[5] = 20;
  std_a[3] = 30;
  a[3] = 30;

  test_eq<int, double>(a, std_a);
// утечка на маке в leaks
#ifndef __APPLE__
  EXPECT_THROW(a[-1], std::out_of_range);
#endif
}
