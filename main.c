#include "MSC.h"
#include "myTerm.h"
#include <stdio.h>

int main() {
    unsigned int x = 0, y = 0, d, R = 2, C = 1;
    unsigned int *row = &x, *col = &y;

    sc_regInit();
    sc_memoryInit();
    
    mt_clrscr();
    mt_clrscr();

    sc_memorySet(10, 45);
    int cell;
    sc_memoryGet(10, &cell);
    // printf("\n memory cell value = %d\n", cell);
    
    sc_memorySave("save.bin");
    sc_memoryLoad("save.bin");

    sc_regSet(MEM_OUT, 1);
    int val;
    sc_regGet(1, &val);
    // printf("\n flag value - %d\n", val);
    
    sc_commandEncode(0x56, 0x60, &val);
    int command;
    int oper;
    sc_commandDecode(val, &command, &oper);
    // printf("\n command - %x \n", command);
    // printf("\n operand - %x \n", oper);
    
    d = mt_getscreensize(row, col);	
    mt_gotoXY(*row/(*row), *col/4);
    mt_setfgcolor(red);
    mt_setgbcolor(blue);
    write(1, "Memory", 6);
    for (int i = 0; i < 10; i++)
      {
	for (int j = 0; j < 10; j++)
	  {
	    	mt_gotoXY(R, C);
		sc_memoryGet(i*10+j, &cell);
		//		printf("%d", sc_memory[i+j]);
		//write(1,"+0000", 5);
		printf("%+05d", cell);
		//write(1, cell, 6);
		C = C + 6;	
	}
	C = 1;
	R = R + 1;
	}
    
    d = mt_gotoXY(1, *col-18);
    mt_setgbcolor(blue);
    write(1, "Flags", 5);
    mt_setgbcolor(9);
    mt_setfgcolor(9);
    d = mt_gotoXY(2, *col-19);
    write(1, "O", 1);
    d = mt_gotoXY(2, *col-17);
    write(1, "E", 1);
    d = mt_gotoXY(2, *col-15);
    write(1, "V", 1);
    d = mt_gotoXY(2, *col-13);
    write(1, "M", 1);

    
    d = mt_gotoXY(4, *col-18);
    mt_setfgcolor(yellow);
    mt_setgbcolor(green);
    write(1, "Keys:", 5);
    mt_setfgcolor(9);
    mt_setgbcolor(9);
    d = mt_gotoXY(5, *col-19);
    write(1, "l  -  load", 10);
    d = mt_gotoXY(6, *col-19);
    write(1, "s  -  save", 10);
    d = mt_gotoXY(7, *col-19);
    write(1, "r  -  run", 9);
    d = mt_gotoXY(8, *col-19);
    write(1, "t  -  step", 10);
    d = mt_gotoXY(9, *col-19);
    write(1, "i  -  reset", 11);
    d = mt_gotoXY(10, *col-19);
    write(1, "F5 -  accumulator", 17);
    d = mt_gotoXY(11, *col-19);
    write(1, "F6 -  instrCounter", 18);

    mt_setfgcolor(9);
    d = mt_gotoXY(12, 1);
}
