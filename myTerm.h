#ifndef __GUARD_MYTERM_H
#define __GUARD_MYTERM_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

enum color { 	black, red, green, 
				yellow, blue, 
				lilac, tarquoise,
				gray, nope,  purple
			};
			
int mt_clrscr();
int mt_gotoXY(int x, int y);
int mt_getscreensize(unsigned int *rows, unsigned int *cols);
int mt_setfgcolor(enum color x);
int mt_setgbcolor(enum color x);

#endif
