#include <check.h>
#include <stdio.h>
#include <stdlib.h>

START_TEST(cat_test_b) {
  system("mkdir -p tests/cat_txt");
  char *com = "cat -b tests/t2.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_b.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_b.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_b.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_b.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_e) {
  char *com = "cat -e tests/t1.txt tests/t2.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_t.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_t.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_t.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_t.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_n1) {
  char *com = "cat -n tests/t1.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_n1.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_n1.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_n1.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_n1.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_n2) {
  char *com = "cat tests/t2.txt -n";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_n2.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_n2.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_n2.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_n2.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_s) {
  char *com = "cat -s tests/t1.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_s.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_s.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_s.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_s.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_t) {
  char *com = "cat -t tests/t2.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_t.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_t.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_t.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_t.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_0) {
  char *com = "cat tests/t1.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_0.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_0.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_0.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_0.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_best) {
  char *com = "cat -b -e -s -t tests/t1.txt tests/t2.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_best.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_best.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_best.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_best.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_vtbn_bytes) {
  char *com = "cat -v -t -b -n tests/bytes.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_vtbn_bytes.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_vtbn_bytes.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_vtbn_bytes.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_vtbn_bytes.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

START_TEST(cat_test_s_bytes) {
  char *com = "cat -s tests/bytes.txt";
  char com_s21[512], com_org[512];
  sprintf(com_s21, "./s21_%s > tests/cat_txt/s21_s_bytes.txt", com);
  sprintf(com_org, "%s > tests/cat_txt/org_s_bytes.txt", com);
  system(com_s21);
  system(com_org);
  FILE *s21_file = fopen("tests/cat_txt/s21_s_bytes.txt", "r");
  FILE *org_file = fopen("tests/cat_txt/org_s_bytes.txt", "r");
  char s21_str[1000], org_str[1000];
  while (1) {
    fgets(s21_str, sizeof(s21_str), s21_file);
    fgets(org_str, sizeof(org_str), org_file);
    ck_assert_str_eq(s21_str, org_str);
    if (feof(org_file)) {
      break;
    }
  }
}
END_TEST

Suite *cat_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("CAT");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, cat_test_b);
  tcase_add_test(tc_core, cat_test_e);
  tcase_add_test(tc_core, cat_test_n1);
  tcase_add_test(tc_core, cat_test_n2);
  tcase_add_test(tc_core, cat_test_s);
  tcase_add_test(tc_core, cat_test_t);
  tcase_add_test(tc_core, cat_test_0);
  tcase_add_test(tc_core, cat_test_best);
  tcase_add_test(tc_core, cat_test_vtbn_bytes);
  tcase_add_test(tc_core, cat_test_s_bytes);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *s;
  SRunner *sr;
  int number_failed;
  s = cat_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  return 0;
}
