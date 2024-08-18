#ifndef TEST
#define TEST
// #include "s21_containers.h"
// #include "s21_containersplus.h"

#include <gtest/gtest.h>

#include "s21_array/s21_array_test.cpp"
#include "s21_list/s21_list_test.cpp"
#include "s21_map/s21_map_test.cpp"
#include "s21_multiset/s21_multiset_test.cpp"
#include "s21_queue/s21_queue_test.cc"
#include "s21_set/s21_set_test.cpp"
#include "s21_stack/s21_stack_test.cc"
#include "s21_vector/s21_vector_test.cc"

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif  // TEST