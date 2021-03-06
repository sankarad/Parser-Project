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
void test_and(char *, char *);
void test_equal(char *, char *, int);
void test_negate(char *, int, int);
void divideTestError(char *, char *);
void divideTestArithmetic(char *, char *, int);
void remainderTestError(char *, char *);
void remainderTestArithmetic(char *, char *, int);

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

void andTest00(void) { test_and(":true:", ":true:"); }
void andTest01(void) { test_and(":false:", ":false:"); }
void andTest02(void) { test_and(":true:", ":false:"); }
void andTest03(void) { test_and(":false:", ":true:"); }
void andTest04(void) { test_and(":true:", "5"); }
void andTest05(void) { test_and("5", ":false:"); }
void andTest06(void) { test_and("\"string\"", "5"); }

void equalTest00(void) { test_equal("notANumber", "5", 0); }
void equalTest01(void) { test_equal("-12", ":false:", 0); }
void equalTest02(void) { test_equal("10", "-10", 0); }
void equalTest03(void) { test_equal("432", "432", 1); }
void equalTest04(void) { test_equal("-0", "0", 1); }
void equalTest05(void) { test_equal("-32", "-32", 1); }

void negateTest00(void) { test_negate("0", 0, 1); }
void negateTest01(void)	{ test_negate("14", -14, 1); }
void negateTest02(void)	{ test_negate("-21", 21, 1); }
void negateTest03(void)	{ test_negate(":true:", 0, 0); }
void negateTest04(void) { test_negate("\"5\"", 0, 0); }

void divideTest01(void) { divideTestError("3","0");}
void divideTest02(void) { divideTestError("5","0");}
void divideTest03(void) { divideTestError("-10","0");}
void divideTest04(void) { divideTestError("hello","0");}
void divideTest05(void) { divideTestError("3","hello");}
void divideTest06(void) { divideTestError("goodbye","hello");}
void divideTest07(void) { divideTestArithmetic("15","5", 3);}
void divideTest08(void) { divideTestArithmetic("-15","5", -3);}
void divideTest09(void) { divideTestArithmetic("15","-5", -3);}
void divideTest10(void) { divideTestArithmetic("0","-5", 0);}
void divideTest11(void) { divideTestArithmetic("0","5", 0);}
void divideTest12(void) { divideTestArithmetic("-25","-5", 5);}
void remainderTest01(void) { remainderTestError("5", "0");}
void remainderTest02(void) { remainderTestError("3","0");}
void remainderTest03(void) { remainderTestError("-10","0");}
void remainderTest04(void) { remainderTestError("hello","0");}
void remainderTest05(void) { remainderTestError("3","hello");}
void remainderTest06(void) { remainderTestError("goodbye","hello");}
void remainderTest07(void) { remainderTestArithmetic("55", "3", 1);}
void remainderTest08(void) { remainderTestArithmetic("55", "-3", 1);}
void remainderTest09(void) { remainderTestArithmetic("-55", "3", 2);}
void remainderTest10(void) { remainderTestArithmetic("-55", "-3", 2);}
void remainderTest11(void) { remainderTestArithmetic("400","20",0);}
void remainderTest12(void) { remainderTestArithmetic("-400","20",0);}
void remainderTest13(void) { remainderTestArithmetic("400","-20",0);}
void remainderTest14(void) { remainderTestArithmetic("-400","-20",0);}
void remainderTest15(void) { remainderTestArithmetic("0","-5", 0);}
void remainderTest16(void) { remainderTestArithmetic("0","5", 0);}

void test_negate(char * val1, int result, int isInt) {
	//set up environment and stack
        struct ExprList *stack = exprList_Empty();
        struct BindList *env = bindList_Empty();
        struct BindListList *envList = bindListList_Empty();
        bindListList_push(envList,env);

        //push first value
        struct Expr * toPush1 = parse(val1, envList);
        eval(toPush1, stack, envList);
        struct Expr * val1Result = exprList_top(stack);

	//push negate Primitive
        struct Expr * negatePrim = parse("neg", envList);
        eval(negatePrim, stack, envList);
        struct Expr * negateResult = exprList_top(stack);

        CU_ASSERT(isPrimitive(negatePrim));
        CU_ASSERT_STRING_EQUAL(nameOf(negatePrim), "negate");
        CU_ASSERT_EQUAL(arityOf(negatePrim), 1);
        CU_ASSERT_EQUAL(valueOf(negatePrim), -1);

	if (isInt) {
		CU_ASSERT(isNumber(val1Result));
		CU_ASSERT(isNumber(negateResult));
		CU_ASSERT_EQUAL(valueOf(negateResult), result);
	} else {
		CU_ASSERT(isError(negateResult));
	}
}

void test_equal(char * val1, char * val2, int isEqual) {
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

        //push equal Primitive
        struct Expr * equalPrim = parse("equal", envList);
        eval(equalPrim, stack, envList);
        struct Expr * equalResult = exprList_top(stack);

	CU_ASSERT(isPrimitive(equalPrim));
        CU_ASSERT_STRING_EQUAL(nameOf(equalPrim), "equal");
        CU_ASSERT_EQUAL(arityOf(equalPrim), 2);
        CU_ASSERT_EQUAL(valueOf(equalPrim), -1);

	if (isNumber(val1Result) && isNumber(val2Result)) {
		if (isEqual) {
			CU_ASSERT_EQUAL(valueOf(val1Result), valueOf(val2Result));
			CU_ASSERT(isBoolean(equalResult));
			CU_ASSERT(valueOf(equalResult));
		} else {
			CU_ASSERT_NOT_EQUAL(valueOf(val1Result), valueOf(val2Result));
			CU_ASSERT(isBoolean(equalResult));
			CU_ASSERT(!valueOf(equalResult));
		}
	} else {
		CU_ASSERT(isError(equalResult));
		CU_ASSERT(!isEqual);
	}
}

void test_and(char * val1, char * val2) {
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

        //push and Primitive
        struct Expr * andPrim = parse("and", envList);
        eval(andPrim, stack, envList);
        struct Expr * andResult = exprList_top(stack);

        CU_ASSERT(isPrimitive(andPrim));
        CU_ASSERT_STRING_EQUAL(nameOf(andPrim), "and");
        CU_ASSERT_EQUAL(arityOf(andPrim), 2);
        CU_ASSERT_EQUAL(valueOf(andPrim), -1);

        if ((strcmp(":false:", val1)==0 && strcmp(":false:", val2)==0)
         || (strcmp(":true:", val1)==0 && strcmp(":false:", val2)==0)
         || (strcmp(":false:", val1)==0 && strcmp(":true:", val2)==0)) {

	        CU_ASSERT(isBoolean(val1Result));
                CU_ASSERT(isBoolean(val2Result));
                CU_ASSERT(isBoolean(andResult));
                CU_ASSERT(!valueOf(andResult));

        } else if ((strcmp(":true:", val1)==0 && strcmp(":true:", val2)==0)) {
                CU_ASSERT(isBoolean(val1Result));
                CU_ASSERT(isBoolean(val2Result));
                CU_ASSERT(isBoolean(andResult));
                CU_ASSERT(valueOf(andResult));
        } else {
                CU_ASSERT(!isBoolean(val1Result) || !isBoolean(val2Result));
        }
}

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

void divideTestError(char * input1, char * input2){

   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);


   struct Expr * a = parse(input1, envList);
   eval(a, stack, envList);
   struct Expr * b = parse(input2, envList);
   eval(b, stack, envList);
   struct Expr * div = parse("div", envList);
   eval(div, stack, envList); 	
 
   struct Expr * res = exprList_top(stack);
   struct Expr * expected = Error();
   printf("divide test: stack is [%s %s div] with actual result of %s expected is %s\n", input1, input2, res->subtype.error.name, expected->subtype.error.name);
   CU_ASSERT(res->type == ERROR && res->subtype.error.name == expected->subtype.error.name);
}

void divideTestArithmetic(char *input1, char * input2, int expected){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);
   struct Expr * a = parse(input1, envList);
   eval(a, stack, envList);
   struct Expr * b = parse(input2, envList);
   eval(b, stack, envList);
   struct Expr * div = parse("div", envList);
   eval(div, stack, envList); 
   
   struct Expr * res = exprList_top(stack);
   
   printf("Subtract test: Stack is [%s %s div] with actual result of %d and expected is %d\n", input1, input2, res->subtype.number.value, expected);
   CU_ASSERT(res->type == NUMBER && res->subtype.number.value == expected);
}

void remainderTestError(char * input1, char * input2){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);   

   struct Expr * a = parse(input1, envList);
   eval(a, stack, envList);
   struct Expr * b = parse(input2, envList);
   eval(b, stack, envList);
   struct Expr * rem = parse("rem", envList);
   eval(rem, stack, envList);

   struct Expr * res = exprList_top(stack);
   struct Expr * expected = Error();
   printf("divide test: stack is [%s %s rem] with actual result of %s expected is %s\n", input1, input2, res->subtype.error.name, expected->subtype.error.name);
   CU_ASSERT(res->type == ERROR && res->subtype.error.name == expected->subtype.error.name);
}
void remainderTestArithmetic(char * input1, char * input2, int expected){
	struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env); 
   
   struct Expr * a = parse(input1, envList);
   eval(a, stack, envList);
   struct Expr * b = parse(input2, envList);
   eval(b, stack, envList);
   struct Expr * rem = parse("rem", envList);
   eval(rem, stack, envList);
   
   struct Expr * res = exprList_top(stack);
   
   printf("Subtract test: Stack is [%s %s rem] with actual result of %d and expected is %d\n", input1, input2, res->subtype.number.value, expected);
   CU_ASSERT(res->type == NUMBER && res->subtype.number.value == expected);
}

void test_stringLength(char * str, int expected){
   struct ExprList *stack = exprList_Empty();
   struct BindList *env = bindList_Empty();
   struct BindListList *envList = bindListList_Empty();
   bindListList_push(envList,env);

   struct Expr * strExpr  = parse(str, envList);
   eval(strExpr, stack, envList); 
   struct Expr * lenExpr  = parse("length", envList);
   eval(lenExpr, stack, envList); 
  
   struct Expr * res = exprList_top(stack);
   printf("Expected %d but actual is %d\n", expected, res->subtype.number.value);	
   if(res->type == ERROR){
   	CU_ASSERT(expected == -1);
	return;
   }	
   CU_ASSERT(res->type == NUMBER && res->subtype.number.value == expected);
}

void stringLengthTest01(void){ test_stringLength("\"lol\"", 3);}
void stringLengthTest02(void){ test_stringLength("\"cse306 is cool\"", 14);}
void stringLengthTest03(void){ test_stringLength("\"just kidding!\"", 13);}
void stringLengthTest04(void){ test_stringLength("\"\"", 0);}
void stringLengthTest05(void){ test_stringLength("\" \"", 1);}
void stringLengthTest06(void){ test_stringLength(" ", -1);}
void stringLengthTest07(void) {test_stringLength("", -1);}

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
	|| (NULL == CU_add_test(pSuite, "divideTest02", divideTest02))
	|| (NULL == CU_add_test(pSuite, "divideTest03", divideTest03))
	|| (NULL == CU_add_test(pSuite, "divideTest04", divideTest04))
	|| (NULL == CU_add_test(pSuite, "divideTest05", divideTest05))
	|| (NULL == CU_add_test(pSuite, "divideTest06", divideTest06))
	|| (NULL == CU_add_test(pSuite, "divideTest07", divideTest07))
	|| (NULL == CU_add_test(pSuite, "divideTest08", divideTest08))
	|| (NULL == CU_add_test(pSuite, "divideTest09", divideTest09))
	|| (NULL == CU_add_test(pSuite, "divideTest10", divideTest10))
	|| (NULL == CU_add_test(pSuite, "divideTest11", divideTest11))
	|| (NULL == CU_add_test(pSuite, "divideTest12", divideTest12))
	|| (NULL == CU_add_test(pSuite, "remainderTest01", remainderTest01))
	|| (NULL == CU_add_test(pSuite, "remainderTest02", remainderTest02))
	|| (NULL == CU_add_test(pSuite, "remainderTest03", remainderTest03))
	|| (NULL == CU_add_test(pSuite, "remainderTest04", remainderTest04))
	|| (NULL == CU_add_test(pSuite, "remainderTest05", remainderTest05))
	|| (NULL == CU_add_test(pSuite, "remainderTest06", remainderTest06))
	|| (NULL == CU_add_test(pSuite, "remainderTest07", remainderTest07))
	|| (NULL == CU_add_test(pSuite, "remainderTest08", remainderTest08))
	|| (NULL == CU_add_test(pSuite, "remainderTest09", remainderTest09))
	|| (NULL == CU_add_test(pSuite, "remainderTest10", remainderTest10))
	|| (NULL == CU_add_test(pSuite, "remainderTest11", remainderTest11))
	|| (NULL == CU_add_test(pSuite, "remainderTest12", remainderTest12))
	|| (NULL == CU_add_test(pSuite, "remainderTest13", remainderTest13))
	|| (NULL == CU_add_test(pSuite, "remainderTest14", remainderTest14))
	|| (NULL == CU_add_test(pSuite, "remainderTest15", remainderTest15))
	|| (NULL == CU_add_test(pSuite, "remainderTest16", remainderTest16))
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
	|| (NULL == CU_add_test(pSuite, "and: true true", andTest00))
        || (NULL == CU_add_test(pSuite, "and: false false", andTest01))
        || (NULL == CU_add_test(pSuite, "and: true false", andTest02))
        || (NULL == CU_add_test(pSuite, "and: false true", andTest03))
        || (NULL == CU_add_test(pSuite, "and: true notBool", andTest04))
        || (NULL == CU_add_test(pSuite, "and: notBool false", andTest05))
        || (NULL == CU_add_test(pSuite, "and: notBool notBool", andTest06))
	|| (NULL == CU_add_test(pSuite, "equal: notNum, pos", equalTest00))
        || (NULL == CU_add_test(pSuite, "equal: neg, notNum", equalTest01))
        || (NULL == CU_add_test(pSuite, "equal: -10, 10", equalTest02))
        || (NULL == CU_add_test(pSuite, "equal: 432, 432", equalTest03))
        || (NULL == CU_add_test(pSuite, "equal: -0 0", equalTest04))
        || (NULL == CU_add_test(pSuite, "equal: -32 -32", equalTest05))
	|| (NULL == CU_add_test(pSuite, "neg: 0", negateTest00))
        || (NULL == CU_add_test(pSuite, "neg: 14", negateTest01))
        || (NULL == CU_add_test(pSuite, "neg: -21", negateTest02))
        || (NULL == CU_add_test(pSuite, "neg: :true:", negateTest03))
	|| (NULL == CU_add_test(pSuite, "neg: \"5\"", negateTest04))
	|| (NULL == CU_add_test(pSuite, "stringLengthTest01", stringLengthTest01))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest02", stringLengthTest02))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest03", stringLengthTest03))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest04", stringLengthTest04))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest05", stringLengthTest05))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest06", stringLengthTest06))     
	|| (NULL == CU_add_test(pSuite, "stringLengthTest07", stringLengthTest06))     
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
