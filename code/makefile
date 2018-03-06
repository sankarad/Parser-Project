objects = Bind.o BindList.o BindListList.o \
	Expr.o ExprList.o \
	Primitives.o \
	REPL.o \
	interpreter.o

CC = gcc
FLAGS = -c -Wall -std=c11

interpreter : $(objects) interpreter.c
	$(CC) -Wall -lm -o interpreter $(objects) 

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

clean :
	rm -fv interpreter $(objects) *~
