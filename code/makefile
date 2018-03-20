OBJECTS = Bind.o BindList.o BindListList.o Expr.o ExprList.o \
	Primitives.o REPL.o

CUNIT_PATH_PREFIX = /util/CUnit/
CUNIT_DIRECTORY = CUnit/
CC = gcc
FLAGS = -c -g -Wall -std=c11

interpreter : $(OBJECTS) interpreter.o interpreter.c
	$(CC) -Wall -lm -o interpreter $(OBJECTS) interpreter.o

interpreter.o : interpreter.c
	$(CC) $(FLAGS) interpreter.c

Bind.o : defs.h Bind.c
	$(CC) $(FLAGS) Bind.c

BindList.o : defs.h BindList.c Bind.c
	$(CC) $(FLAGS) BindList.c

BindListList.o : defs.h BindListList.c BindList.c Bind.c
	$(CC) $(FLAGS) BindListList.c

Expr.o : defs.h Expr.c
	$(CC) $(FLAGS) Expr.c

ExprList.o : defs.h ExprList.c Expr.c
	$(CC) $(FLAGS) ExprList.c

Primitives.o : defs.h Primitives.c
	$(CC) $(FLAGS) Primitives.c

REPL.o : defs.h REPL.c 
	$(CC) $(FLAGS) REPL.c

tests: $(OBJECTS) tests.c
	$(CC) -Wall -lm -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) $(OBJECTS) tests.c -o tests -lcunit -lgcov

testsClang: $(OBJECTS) tests.c
	clang -Wall -lm -L $(CUNIT_PATH_PREFIX)lib -I $(CUNIT_PATH_PREFIX)include/$(CUNIT_DIRECTORY) $(OBJECTS) tests.c -o tests -lcunit -lgcov
clean :
	rm -fv interpreter tests *.o *~

