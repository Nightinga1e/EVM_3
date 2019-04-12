#pragma once
all:
	gcc -c mTmain.c -o mTmain.o
	gcc -c myTerm.c -o myTerm.o
	gcc mTmain.o myTerm.o -o output
	./output
