#include <CUnit/Basic.h>
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>


/* Parsing */
extern int parsing_suite_init(void) ;
extern int parsing_suite_clean(void) ;
extern void parsing_test_getHeight(void);

// The main() function for setting up and running the tests.
// Returns a CUE_SUCCESS on successful running, another
// CUnit error code on failure.
int main(void) {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  // Add a suite to the registry
  pSuite =
      CU_add_suite("parsing_suite", parsing_suite_init, parsing_suite_clean);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Add the tests to the suite
  if ((NULL == CU_add_test(pSuite, "Parsing test", parsing_test_getHeight))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Run all tests using the CUnit Basic interface
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}