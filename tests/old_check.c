#include <check.h>
#include <stdlib.h>
#include "../src/sandwich.h"

START_TEST(test_sandwich_make) {
  ck_assert_int_eq(6,6);
}
END_TEST

Suite * sandwich_suite(void)
{
  Suite *s = suite_create("Sandwich");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sandwich_make);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{ 
  Suite *s = sandwich_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  int num_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return num_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

