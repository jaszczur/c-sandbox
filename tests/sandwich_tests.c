#include <stdlib.h>
#include "ctest.h"
#include "sandwich.h"

CTEST_DATA(sandwich_test) {
  Sandwich *cut;
};

CTEST_TEARDOWN(sandwich_test) {
  free_sandwich(data->cut);
}

CTEST2(sandwich_test, describe_should_work_for_one_filling) {
  Filling fillings[] = {FILLING_CHEESE};
  data->cut = make_sandwich(fillings, 1);
  
  ASSERT_STR("A tasty sandwich with cheese", describe_sandwich(data->cut));
}

CTEST2(sandwich_test, describe_should_work_for_two_fillings) {
  Filling fillings[] = {FILLING_HAM, FILLING_CHEESE};
  data->cut = make_sandwich(fillings, 2);
  
  ASSERT_STR("A tasty sandwich with ham and cheese", describe_sandwich(data->cut));
}

CTEST2(sandwich_test, describe_should_work_for_three_fillings) {
  Filling fillings[] = {FILLING_BUTTER, FILLING_CHEESE, FILLING_HAM};
  data->cut = make_sandwich(fillings, 3);
  
  ASSERT_STR("A tasty sandwich with butter, cheese and ham", describe_sandwich(data->cut));
}

CTEST2(sandwich_test, add_filling_should_add_specified_filling) {
  data->cut = make_sandwich(NULL, 0);

  add_filling(data->cut, FILLING_CHEESE);

  ASSERT_TRUE(has_filling(data->cut, FILLING_CHEESE));
  ASSERT_FALSE(has_filling(data->cut, FILLING_HAM));              
}

