#include <stdio.h>
#include "CUnit.h"
#include "Basic.h"
#include "defs.h"

void check_createStack();
void check_createEnv();
void check_createEnvList();

void test00(void) { check_createStack(); }
void test01(void) { check_createEnv(); }
void test02(void) { check_createEnvList(); }

void check_createStack() {
	struct ExprList *stack = exprList_Empty();
	CU_ASSERT(exprList_isEmpty(stack));
	CU_ASSERT_PTR_NULL(exprList_top(stack));
	CU_ASSERT_PTR_NULL(exprList_pop(stack));
}

void check_createEnv() {
	struct BindList *env = bindList_Empty();
	CU_ASSERT(bindList_isEmpty(env));
	CU_ASSERT_PTR_NULL(bindList_pop(env));
}

void check_createEnvList() {
	struct BindListList *envList = bindListList_Empty();
	CU_ASSERT(bindListList_isEmpty(envList));
	CU_ASSERT_PTR_NULL(bindListList_top(envList));
        CU_ASSERT_PTR_NULL(bindListList_pop(envList));
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry()) { return CU_get_error(); }

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", NULL, NULL);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if (
        	(NULL == CU_add_test(pSuite, "createStackTest", test00))
	||	(NULL == CU_add_test(pSuite, "createEnvTest", test01))
	||	(NULL == CU_add_test(pSuite, "createEnvListTest", test02))
      )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   //   CU_basic_show_failures(CU_get_failure_list());
   CU_cleanup_registry();
   return CU_get_error();
}
