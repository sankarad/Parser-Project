#include <stdio.h>
#include "CUnit.h"
#include "Basic.h"
#include "defs.h"
#include "REPL.h"

void check_createStack();
void check_createEnv();
void check_createEnvList();
void test_addStringMultTimes(char *, char *, int);

void envTest00(void) { check_createStack(); }
void envTest01(void) { check_createEnv(); }
void envTest02(void) { check_createEnvList(); }
void stringTest00(void) { test_addStringMultTimes("\"true\"", "true", 1); }
void stringTest01(void)	{ test_addStringMultTimes("\"This is one string\"", "This is one string", 1); }
void stringTest02(void)	{ test_addStringMultTimes("\"a\"", "a", 1); }
void stringTest03(void)	{ test_addStringMultTimes("\" \"", " ", 1); }
void stringTest04(void)	{ test_addStringMultTimes("\"\"", "", 1); }
void stringTest05(void) { test_addStringMultTimes("\"this\nis\na\nmultiline\nstring\"", "this\nis\na\nmultiline\nstring", 10); }
void stringTest06(void) { test_addStringMultTimes("\"true\"", "true", 10); }
void stringTest07(void) { test_addStringMultTimes("\"This is one string\"", "This is one string", 10); }
void stringTest08(void) { test_addStringMultTimes("\"a\"", "a", 10); }
void stringTest09(void) { test_addStringMultTimes("\" \"", " ", 10); }
void stringTest10(void) { test_addStringMultTimes("\"\"", "", 10); }
void stringTest11(void) { test_addStringMultTimes("\"this\nis\na\nmultiline\nstring\"", "this\nis\na\nmultiline\nstring", 10); }


void test_addStringMultTimes(char * input, char * strippedString, int count) {
	//First check that the String is a String method can properly identify
	CU_ASSERT_TRUE(stringIsAString(input));

	//Check that the stripped string is what is expected
	CU_ASSERT_STRING_EQUAL(stripFirstAndLast(input), strippedString);
	
	//set up environment and stack
	struct ExprList *stack = exprList_Empty();
	struct BindList *env = bindList_Empty();
	struct BindListList *envList = bindListList_Empty();

	for (int i=0; i<count; i++) {
		bindListList_push(envList,env);
		
		//push String to stack
		struct Expr * toPush = parse(input, envList);
		eval(toPush, stack, envList);
		struct Expr * top = exprList_top(stack);
		
		//Check what has been sent to the stack
		CU_ASSERT_TRUE(isString(top));
		CU_ASSERT_STRING_EQUAL(nameOf(top), strippedString);
		CU_ASSERT_STRING_EQUAL(expression2string(top), input);	
	}
}

void subtractTest01(void){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);

   struct Expr * a = parse("5", envList);
   eval(a, stack, envList); 
   struct Expr * b = parse("7", envList); 
   eval(b, stack, envList); 
   struct Expr * sub = parse("sub", envList); 
   eval(sub, stack, envList); 

   struct Expr * res = exprList_top(stack);
   int expected = -2;
   printf("Subtract test: Stack is [5 7 sub] with actual result of %d and expected is %d\n", res->subtype.number.value, expected);
   CU_ASSERT(res->type == NUMBER && res->subtype.number.value == expected);
}

void subtractTest02(void){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);

   struct Expr * a = parse("-100", envList);
   eval(a, stack, envList); 
   struct Expr * b = parse("50", envList); 
   eval(b, stack, envList); 
   struct Expr * sub = parse("sub", envList); 
   eval(sub, stack, envList); 

   struct Expr * res = exprList_top(stack);
   int expected = -150;
   printf("Subtract test: Stack is [-100 50 sub] with actual result of %d and expected is %d\n", res->subtype.number.value, expected);
   CU_ASSERT(res->type == NUMBER && res->subtype.number.value == expected);
}

void divideTest01(void){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);

   struct Expr * a = parse("3", envList);
   eval(a, stack, envList);
   struct Expr * b = parse("0", envList);
   eval(b, stack, envList);
   struct Expr * div = parse("div", envList);
   eval(div, stack, envList); 	
 
   struct Expr * res = exprList_top(stack);
   char * expected = ":error:";
   printf("divide test: stack is [3 0 div] with actual result of %s and expected is %s\n", res->subtype.error.name, expected);
   CU_ASSERT(res->type == ERROR && res->subtype.error.name == expected);
}
 
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
           (NULL == CU_add_test(pSuite, "createStackTest", envTest00))
	|| (NULL == CU_add_test(pSuite, "createEnvTest", envTest01))
	|| (NULL == CU_add_test(pSuite, "createEnvListTest", envTest02))
	|| (NULL == CU_add_test(pSuite, "subtractTest01", subtractTest01))     
	|| (NULL == CU_add_test(pSuite, "subtractTest02", subtractTest02))
	|| (NULL == CU_add_test(pSuite, "\"true\" test", stringTest00))
	|| (NULL == CU_add_test(pSuite, "\"This is a string\" test", stringTest01))
	|| (NULL == CU_add_test(pSuite, "\"a\" test", stringTest02))
	|| (NULL == CU_add_test(pSuite, "\" \" test", stringTest03))
	|| (NULL == CU_add_test(pSuite, "Empty string test", stringTest04))      
        || (NULL == CU_add_test(pSuite, "Multi-line string test", stringTest05))
	|| (NULL == CU_add_test(pSuite, "x10: \"true\" test", stringTest06))
        || (NULL == CU_add_test(pSuite, "x10: \"This is a string\" test", stringTest07))
        || (NULL == CU_add_test(pSuite, "x10: \"a\" test", stringTest08))
        || (NULL == CU_add_test(pSuite, "x10: \" \" test", stringTest09))
        || (NULL == CU_add_test(pSuite, "x10: Empty string test", stringTest10))
        || (NULL == CU_add_test(pSuite, "x10: Multi-line string test", stringTest11))
	|| (NULL == CU_add_test(pSuite, "divideTest01", divideTest01))
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
