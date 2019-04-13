#pragma once
all:
	gcc -c main.c -o main.o
	gcc -c myTerm.c -o myTerm.o
	gcc -c MSC.c -o MSC.o
	gcc main.o myTerm.o MSC.o -o output
	./output
