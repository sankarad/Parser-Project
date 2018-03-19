#ifndef REPL_H
#define REPL_H

#include "defs.h"

#define INTERACTIVE 1
#define NON_INTERACTIVE 0

int stringIsAString(char * str);
char * stripFirstAndLast(char * str);
struct Expr * parse(char * string, struct BindListList * env);
struct ExprList * eval(struct Expr * token, struct ExprList * stack, struct BindListList * env);
char * nextToken(FILE * inStr, struct ExprList * stack, int interactive);
void repl();

#endif
