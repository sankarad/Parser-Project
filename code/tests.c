#include <stdio.h>
#include "CUnit.h"
#include "Basic.h"
#include "defs.h"
#include "REPL.h"

void check_createStack();
void check_createEnv();
void check_createEnvList();
void test_addStringMultTimes(char *, char *, int);
void test_concatenationTest(char *, char *, char *);
void test_conditional(char *, char *, char *);
void test_or(char *, char *);
void test_and(char *, char *, char *);
void test_equal(char *, char *, char *);
void test_lessThan(char *, char *, char *);

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

void concatTest00(void) { test_concatenationTest("\"Good\"", "\" morning\"", "\"Good morning\""); }
void concatTest01(void) { test_concatenationTest("\"\"", "\"\"", "\"\""); }
void concatTest02(void) { test_concatenationTest("\"many\nlines\"", "\"\nin\none\"", "\"many\nlines\nin\none\""); }
void concatTest03(void) { test_concatenationTest("\"CSE\"", "\"306\"", "\"CSE306\""); }
void concatTest04(void) { test_concatenationTest("CSE", "306", ":error:"); }

void conditionalTest00(void) { test_conditional("true", "false", ":error:"); }
void conditionalTest01(void) { test_conditional(":error:", "aName", ":true:"); }
void conditionalTest02(void) { test_conditional(":error:", "aName", ":false:"); }

void orTest00(void) { test_or(":true:", ":true:"); }
void orTest01(void) { test_or(":false:", ":false:"); }
void orTest02(void) { test_or(":true:", ":false:"); }
void orTest03(void) { test_or(":false:", ":true:"); }
void orTest04(void) { test_or(":true:", "5"); }
void orTest05(void) { test_or("5", ":false:"); }
void orTest06(void) { test_or("\"string\"", "5"); }

void test_or(char * val1, char * val2) {
	//set up environment and stack
        struct ExprList *stack = exprList_Empty();
        struct BindList *env = bindList_Empty();
        struct BindListList *envList = bindListList_Empty();
        bindListList_push(envList,env);

	//push first value
        struct Expr * toPush1 = parse(val1, envList);
        eval(toPush1, stack, envList);
        struct Expr * val1Result = exprList_top(stack);

        //push second value
        struct Expr * toPush2 = parse(val2, envList);
        eval(toPush2, stack, envList);
        struct Expr * val2Result = exprList_top(stack);

        //push or Primitive
        struct Expr * orPrim = parse("or", envList);
        eval(orPrim, stack, envList);
        struct Expr * orResult = exprList_top(stack);

	CU_ASSERT(isPrimitive(orPrim));
        CU_ASSERT_STRING_EQUAL(nameOf(orPrim), "or");
        CU_ASSERT_EQUAL(arityOf(orPrim), 2);
        CU_ASSERT_EQUAL(valueOf(orPrim), -1);

	if ((strcmp(":true:", val1)==0 && strcmp(":true:", val2)==0)
	 || (strcmp(":true:", val1)==0 && strcmp(":false:", val2)==0)
	 || (strcmp(":false:", val1)==0 && strcmp(":true:", val2)==0)) {

		CU_ASSERT(isBoolean(val1Result));
		CU_ASSERT(isBoolean(val2Result));
		CU_ASSERT(isBoolean(orResult));
		CU_ASSERT(valueOf(orResult));
		
	} else if ((strcmp(":false:", val1)==0 && strcmp(":false:", val2)==0)) {
		CU_ASSERT(isBoolean(val1Result));
                CU_ASSERT(isBoolean(val2Result));
                CU_ASSERT(isBoolean(orResult));
                CU_ASSERT(!valueOf(orResult));		
	} else {
		CU_ASSERT(!isBoolean(val1Result) || !isBoolean(val2Result));
	}
}

void test_conditional(char * val1, char * val2, char * booleanValue) {
	//set up environment and stack
        struct ExprList *stack = exprList_Empty();
        struct BindList *env = bindList_Empty();
        struct BindListList *envList = bindListList_Empty();
        bindListList_push(envList,env);

        //push first value
        struct Expr * toPush1 = parse(val1, envList);
        eval(toPush1, stack, envList);
	struct Expr * val1Result = exprList_top(stack);

        //push second value
        struct Expr * toPush2 = parse(val2, envList);
        eval(toPush2, stack, envList);
	struct Expr * val2Result = exprList_top(stack);

	//push boolean value
	struct Expr * pushBoolean = parse(booleanValue, envList);
	eval(pushBoolean, stack, envList);
	struct Expr * booleanResult = exprList_top(stack);
	
        struct Expr * ifPrim = parse("if", envList);
        eval(ifPrim, stack, envList);
        struct Expr * ifResult = exprList_top(stack);

        CU_ASSERT(isPrimitive(ifPrim));
        CU_ASSERT_STRING_EQUAL(nameOf(ifPrim), "if");
        CU_ASSERT_EQUAL(arityOf(ifPrim), 3);
        CU_ASSERT_EQUAL(valueOf(ifPrim), -1);	

	if (strcmp(":true:", booleanValue) == 0) {
		CU_ASSERT(isBoolean(booleanResult));
		CU_ASSERT(valueOf(booleanResult));
		CU_ASSERT_STRING_EQUAL(nameOf(ifResult), nameOf(val1Result));
		CU_ASSERT_EQUAL(arityOf(ifResult), arityOf(val1Result));
		CU_ASSERT_EQUAL(valueOf(ifResult), valueOf(val1Result));
	} else if (strcmp(":false:", booleanValue) == 0) {
		CU_ASSERT(isBoolean(booleanResult));
                CU_ASSERT(!valueOf(booleanResult));
                CU_ASSERT_STRING_EQUAL(nameOf(ifResult), nameOf(val2Result));
                CU_ASSERT_EQUAL(arityOf(ifResult), arityOf(val2Result));
                CU_ASSERT_EQUAL(valueOf(ifResult), valueOf(val2Result));
	} else {
		CU_ASSERT(!isBoolean(booleanResult));
		CU_ASSERT(isError(ifResult));
	}

}

void test_addStringMultTimes(char * input, char * strippedString, int count) {
	//First check that the String is a String method can properly identify
	CU_ASSERT_TRUE(stringIsAString(input));

	//Check that the stripped string is what is expected
	CU_ASSERT_STRING_EQUAL(stripFirstAndLast(input), strippedString);
	
	//set up environment and stack
	struct ExprList *stack = exprList_Empty();
	struct BindList *env = bindList_Empty();
	struct BindListList *envList = bindListList_Empty();
	bindListList_push(envList,env);

	for (int i=0; i<count; i++) {
		
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

void test_concatenationTest(char * input1, char * input2, char * concatted) {
	//set up environment and stack
        struct ExprList *stack = exprList_Empty();
        struct BindList *env = bindList_Empty();
        struct BindListList *envList = bindListList_Empty();
	bindListList_push(envList,env);

	//push first value
	struct Expr * toPush1 = parse(input1, envList);
        eval(toPush1, stack, envList);

	//push second value
	struct Expr * toPush2 = parse(input2, envList);
        eval(toPush2, stack, envList);

	struct Expr * concatPrim = parse("concat", envList);
	eval(concatPrim, stack, envList);
	struct Expr * concatResult = exprList_top(stack);
	
	CU_ASSERT(isPrimitive(concatPrim));
	CU_ASSERT_STRING_EQUAL(nameOf(concatPrim), "concat");
	CU_ASSERT_EQUAL(arityOf(concatPrim), 2);
	CU_ASSERT_EQUAL(valueOf(concatPrim), -1);

	if (!stringIsAString(input1) || !stringIsAString(input2)) {
		CU_ASSERT(isError(concatResult));
		CU_ASSERT_STRING_EQUAL(concatted, ":error:");
	} else if (stringIsAString(input1) && stringIsAString(input2)) {
		CU_ASSERT(isString(concatResult));		
		CU_ASSERT_STRING_EQUAL(nameOf(concatResult), stripFirstAndLast(concatted));
		CU_ASSERT_STRING_EQUAL(expression2string(concatResult), concatted);
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
   struct Expr * expected = Error();
   printf("divide test: stack is [3 0 div] with actual result of %s expected is %s\n", res->subtype.error.name, expected->subtype.error.name);
   CU_ASSERT(res->type == ERROR && res->subtype.error.name == expected->subtype.error.name);
}

void remainderTest01(void){
   struct ExprList *stack = exprList_Empty();	
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);

   struct Expr * a = parse("5", envList);
   eval(a, stack, envList);
   struct Expr * b = parse("0", envList);
   eval(b,stack,envList);
   struct Expr * rem = parse("rem", envList);
   eval(rem, stack, envList);
   
   struct Expr * res = exprList_top(stack);
   struct Expr * expected = Error();
   printf("remainder test: stack is [5 0 rem] with actual result of %s and expected result of %s\n", res->subtype.error.name, expected->subtype.error.name);
   CU_ASSERT(res->type == ERROR && res->subtype.error.name == expected->subtype.error.name);
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
	|| (NULL == CU_add_test(pSuite, "Good + morning", concatTest00))
	|| (NULL == CU_add_test(pSuite, "empty + empty", concatTest01))
	|| (NULL == CU_add_test(pSuite, "Multiline+multiline", concatTest02))
	|| (NULL == CU_add_test(pSuite, "CSE + 306", concatTest03))
	|| (NULL == CU_add_test(pSuite, "names: CSE + 306", concatTest04))
	|| (NULL == CU_add_test(pSuite, "divideTest01", divideTest01))
	|| (NULL == CU_add_test(pSuite, "remainderTest01", remainderTest01))
	|| (NULL == CU_add_test(pSuite, "if: not a boolean value", conditionalTest00))
        || (NULL == CU_add_test(pSuite, "if: true", conditionalTest01))
	|| (NULL == CU_add_test(pSuite, "if: false", conditionalTest02))
	|| (NULL == CU_add_test(pSuite, "or: true true", orTest00))
	|| (NULL == CU_add_test(pSuite, "or: false false", orTest01))
	|| (NULL == CU_add_test(pSuite, "or: true false", orTest02))
	|| (NULL == CU_add_test(pSuite, "or: false true", orTest03))
	|| (NULL == CU_add_test(pSuite, "or: true notBool", orTest04))
	|| (NULL == CU_add_test(pSuite, "or: notBool false", orTest05))
	|| (NULL == CU_add_test(pSuite, "or: notBool notBool", orTest06))

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
