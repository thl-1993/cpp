#include "s21_vector.h"

#include <gtest/gtest.h>

#include <vector>

#include "../tests.cpp"

TEST(vector_constructor, case1) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_EQ(s21_vec_int.size(), 0U);
  EXPECT_EQ(s21_vec_int.capacity(), 0U);
  EXPECT_EQ(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.size(), 0U);
  EXPECT_EQ(s21_vec_double.capacity(), 0U);
  EXPECT_EQ(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.size(), 0U);
  EXPECT_EQ(s21_vec_string.capacity(), 0U);
  EXPECT_EQ(&s21_vec_string[0], nullptr);
}

TEST(vector_constructor, case2) {
  s21::vector<int> s21_vec_int(5);
  s21::vector<double> s21_vec_double(5);
  s21::vector<std::string> s21_vec_string(5);

  EXPECT_EQ(s21_vec_int.size(), 5U);
  EXPECT_EQ(s21_vec_int.capacity(), 5U);
  EXPECT_NE(&s21_vec_int[0], nullptr);

  EXPECT_EQ(s21_vec_double.size(), 5U);
  EXPECT_EQ(s21_vec_double.capacity(), 5U);
  EXPECT_NE(&s21_vec_double[0], nullptr);

  EXPECT_EQ(s21_vec_string.size(), 5U);
  EXPECT_EQ(s21_vec_string.capacity(), 5U);
  EXPECT_NE(&s21_vec_string[0], nullptr);
}

TEST(vector_constructor, case3) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.size(), 4U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_int[0], 1);
  EXPECT_EQ(s21_vec_int[1], 4);
  EXPECT_EQ(s21_vec_int[2], 8);
  EXPECT_EQ(s21_vec_int[3], 9);

  EXPECT_EQ(s21_vec_double.size(), 4U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_double[1], 4.8);
  EXPECT_EQ(s21_vec_double[2], 8.9);
  EXPECT_EQ(s21_vec_double[3], 9.1);

  EXPECT_EQ(s21_vec_string.size(), 4U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_string[0], "Hello");
  EXPECT_EQ(s21_vec_string[1], ",");
  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
}

TEST(vector_constructor, case4) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), s21_vec_res_int.size());
  EXPECT_EQ(s21_vec_ref_int.capacity(), s21_vec_res_int.capacity());
  EXPECT_EQ(s21_vec_ref_int[0], s21_vec_res_int[0]);
  EXPECT_EQ(s21_vec_ref_int[1], s21_vec_res_int[1]);
  EXPECT_EQ(s21_vec_ref_int[2], s21_vec_res_int[2]);
  EXPECT_EQ(s21_vec_ref_int[3], s21_vec_res_int[3]);

  EXPECT_EQ(s21_vec_ref_double.size(), s21_vec_res_double.size());
  EXPECT_EQ(s21_vec_ref_double.capacity(), s21_vec_res_double.capacity());
  EXPECT_EQ(s21_vec_ref_double[0], s21_vec_res_double[0]);
  EXPECT_EQ(s21_vec_ref_double[1], s21_vec_res_double[1]);
  EXPECT_EQ(s21_vec_ref_double[2], s21_vec_res_double[2]);
  EXPECT_EQ(s21_vec_ref_double[3], s21_vec_res_double[3]);

  EXPECT_EQ(s21_vec_ref_string.size(), s21_vec_res_string.size());
  EXPECT_EQ(s21_vec_ref_string.capacity(), s21_vec_res_string.capacity());
  EXPECT_EQ(s21_vec_ref_string[0], s21_vec_res_string[0]);
  EXPECT_EQ(s21_vec_ref_string[1], s21_vec_res_string[1]);
  EXPECT_EQ(s21_vec_ref_string[2], s21_vec_res_string[2]);
  EXPECT_EQ(s21_vec_ref_string[3], s21_vec_res_string[3]);
}

TEST(vector_constructor, case5) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int = std::move(s21_vec_ref_int);
  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double = std::move(s21_vec_ref_double);
  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), 0U);
  EXPECT_EQ(s21_vec_ref_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  EXPECT_EQ(s21_vec_ref_double.size(), 0U);
  EXPECT_EQ(s21_vec_ref_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  EXPECT_EQ(s21_vec_ref_string.size(), 0U);
  EXPECT_EQ(s21_vec_ref_string.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");
}

TEST(vector_constructor, case6) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int;
  s21_vec_res_int = std::move(s21_vec_ref_int);

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double;
  s21_vec_res_double = std::move(s21_vec_ref_double);

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string;
  s21_vec_res_string = std::move(s21_vec_ref_string);

  EXPECT_EQ(s21_vec_ref_int.size(), 0U);
  EXPECT_EQ(s21_vec_ref_int.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[0], 1);
  EXPECT_EQ(s21_vec_res_int[1], 4);
  EXPECT_EQ(s21_vec_res_int[2], 8);
  EXPECT_EQ(s21_vec_res_int[3], 9);

  EXPECT_EQ(s21_vec_ref_double.size(), 0U);
  EXPECT_EQ(s21_vec_ref_double.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[0], 1.4);
  EXPECT_EQ(s21_vec_res_double[1], 4.8);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);
  EXPECT_EQ(s21_vec_res_double[3], 9.1);

  EXPECT_EQ(s21_vec_ref_string.size(), 0U);
  EXPECT_EQ(s21_vec_ref_string.capacity(), 0U);
  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[0], "Hello");
  EXPECT_EQ(s21_vec_res_string[1], ",");
  EXPECT_EQ(s21_vec_res_string[2], "world");
  EXPECT_EQ(s21_vec_res_string[3], "!");
}

TEST(vector_at, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.at(0), 1);
  EXPECT_EQ(s21_vec_double.at(0), 1.4);
  EXPECT_EQ(s21_vec_string.at(0), "Hello");
}

TEST(vector_at, case2) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(vector_at, case3) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  EXPECT_THROW(s21_vec_int.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_double.at(5), std::out_of_range);
  EXPECT_THROW(s21_vec_string.at(5), std::out_of_range);
}

TEST(vector_square_braces, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int[3], 9);
  EXPECT_EQ(s21_vec_double[0], 1.4);
  EXPECT_EQ(s21_vec_string[0], "Hello");
}

TEST(vector_front, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.front(), 1);
  EXPECT_EQ(s21_vec_double.front(), 1.4);
  EXPECT_EQ(s21_vec_string.front(), "Hello");
}

TEST(vector_back, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.back(), 9);
  EXPECT_EQ(s21_vec_double.back(), 9.1);
  EXPECT_EQ(s21_vec_string.back(), "!");
}

TEST(VectorTest, Element_data) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

TEST(vector_data, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.data(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.data(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.data(), &s21_vec_string[0]);
}

TEST(vector_begin, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.begin(), &s21_vec_int[0]);
  EXPECT_EQ(s21_vec_double.begin(), &s21_vec_double[0]);
  EXPECT_EQ(s21_vec_string.begin(), &s21_vec_string[0]);
}

TEST(vector_end, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.end(), &s21_vec_int[0] + 4);
  EXPECT_EQ(s21_vec_double.end(), &s21_vec_double[0] + 4);
  EXPECT_EQ(s21_vec_string.end(), &s21_vec_string[0] + 4);
}

TEST(vector_empty, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_vec_int.empty(), 0);
  EXPECT_EQ(s21_vec_double.empty(), 0);
  EXPECT_EQ(s21_vec_string.empty(), 0);
}

TEST(vector_empty, case2) {
  s21::vector<int> s21_vec_int{};
  s21::vector<double> s21_vec_double{};
  s21::vector<std::string> s21_vec_string{};

  EXPECT_EQ(s21_vec_int.empty(), 1);
  EXPECT_EQ(s21_vec_double.empty(), 1);
  EXPECT_EQ(s21_vec_string.empty(), 1);
}

TEST(VectorTest, Capacity_size_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_capacity_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_capacity_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(vector, max_size) {
  s21::vector<int> vector_int;
  std::vector<int> true_vector_int;
  EXPECT_EQ(true_vector_int.max_size(), vector_int.max_size());
}

TEST(VectorTest, Capacity_reserve_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_shrink_to_fit_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_shrink_to_fit_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Modifiers_clear_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_clear_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_insert_1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.insert(s21_v.begin() + 1, 5);
  std_v.insert(std_v.begin() + 1, 5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_insert_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.insert(s21_v.begin() + s21_v.size(), 100);
  std_v.insert(std_v.begin() + std_v.size(), 100);

  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Modifiers_insert_3) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.insert(s21_v.begin() + 10, 100);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_insert_4) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.insert(s21_v.begin() - 4, 100);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_erase_1) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  s21_v.erase(s21_v.begin() + 1);
  std_v.erase(std_v.begin() + 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_erase_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.begin());
  std_v.erase(std_v.begin());

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_erase_3) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_erase_4) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.erase(s21_v.begin() - 1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_erase_5) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.erase(s21_v.end() + 1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_push_back_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_push_back_2) {
  s21::vector<int> s21_v{1, 2};
  std::vector<int> std_v{1, 2};

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(vector_pop_back, case1) {
  s21::vector<int> s21_vec_int{1, 4, 8, 9};
  s21::vector<double> s21_vec_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<std::string> s21_vec_string{"Hello", ",", "world", "!"};

  s21_vec_int.pop_back();
  s21_vec_double.pop_back();
  s21_vec_string.pop_back();

  EXPECT_EQ(s21_vec_int.size(), 3U);
  EXPECT_EQ(s21_vec_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_double.size(), 3U);
  EXPECT_EQ(s21_vec_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_string.size(), 3U);
  EXPECT_EQ(s21_vec_string.capacity(), 4U);
}

TEST(VectorTest, Modifiers_swap_1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v;
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_2) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_3) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_4) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2, 3, 4, 5, 6};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2, 3, 4, 5, 6};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(vector_swap, case1) {
  s21::vector<int> s21_vec_ref_int{1, 4, 8, 9};
  s21::vector<int> s21_vec_res_int{0, 0, 0};

  s21::vector<double> s21_vec_ref_double{1.4, 4.8, 8.9, 9.1};
  s21::vector<double> s21_vec_res_double{0.0, 0.0, 0.0};

  s21::vector<std::string> s21_vec_ref_string{"Hello", ",", "world", "!"};
  s21::vector<std::string> s21_vec_res_string{"", "", ""};

  s21_vec_ref_int.swap(s21_vec_res_int);
  s21_vec_ref_double.swap(s21_vec_res_double);
  s21_vec_ref_string.swap(s21_vec_res_string);

  EXPECT_EQ(s21_vec_res_int.size(), 4U);
  EXPECT_EQ(s21_vec_res_int.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_int[2], 8);

  EXPECT_EQ(s21_vec_res_double.size(), 4U);
  EXPECT_EQ(s21_vec_res_double.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_double[2], 8.9);

  EXPECT_EQ(s21_vec_res_string.size(), 4U);
  EXPECT_EQ(s21_vec_res_string.capacity(), 4U);
  EXPECT_EQ(s21_vec_res_string[2], "world");
}

TEST(vector_insert_many, case1) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  auto pos_int = s21_vec_int.begin() + 1;
  auto pos_double = s21_vec_double.begin() + 1;
  auto pos_string = s21_vec_string.begin() + 1;

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[1], 2);
  EXPECT_EQ(s21_vec_int[2], 3);

  EXPECT_EQ(s21_vec_double[1], 2.0);
  EXPECT_EQ(s21_vec_double[2], 3.56);

  EXPECT_EQ(s21_vec_string[1], "world");
  EXPECT_EQ(s21_vec_string[2], "!");
}

TEST(vector_insert_many, case2) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_int[1], 3);

  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_double[1], 3.56);

  EXPECT_EQ(s21_vec_string[0], "world");
  EXPECT_EQ(s21_vec_string[1], "!");
}

TEST(vector_insert_many, case3) {
  s21::vector<int> s21_vec_int;
  s21::vector<double> s21_vec_double;
  s21::vector<std::string> s21_vec_string;

  auto pos_int = s21_vec_int.begin();
  auto pos_double = s21_vec_double.begin();
  auto pos_string = s21_vec_string.begin();

  s21_vec_int.insert_many(pos_int, 2, 3);
  s21_vec_double.insert_many(pos_double, 2.0, 3.56);
  s21_vec_string.insert_many(pos_string, "world", "!");

  EXPECT_EQ(s21_vec_int[0], 2);
  EXPECT_EQ(s21_vec_int[1], 3);

  EXPECT_EQ(s21_vec_double[0], 2.0);
  EXPECT_EQ(s21_vec_double[1], 3.56);

  EXPECT_EQ(s21_vec_string[0], "world");
  EXPECT_EQ(s21_vec_string[1], "!");
}

TEST(vector_insert_many_back, case1) {
  s21::vector<int> s21_vec_int{1, 4};
  s21::vector<double> s21_vec_double{1.4, 4.8};
  s21::vector<std::string> s21_vec_string{"Hello", ","};

  s21_vec_int.insert_many_back(2, 3);
  s21_vec_double.insert_many_back(2.0, 3.56);
  s21_vec_string.insert_many_back("world", "!");

  EXPECT_EQ(s21_vec_int[2], 2);
  EXPECT_EQ(s21_vec_int[3], 3);

  EXPECT_EQ(s21_vec_double[2], 2.0);
  EXPECT_EQ(s21_vec_double[3], 3.56);

  EXPECT_EQ(s21_vec_string[2], "world");
  EXPECT_EQ(s21_vec_string[3], "!");
}
