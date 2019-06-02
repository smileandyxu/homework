#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "graphics.h"
#include "genlib.h"
#include "conio.h"
#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <stdio.h>
#include <stdlib.h>
#include "genlib.h"
#include "simpio.h"
#include "graphics.h"

const double initx = 3;
const double inity = 3;
const double deviation = 20.0; 
const double smallang = 60.0;
const double bigang = 120.0;
const double len = 1.0;
void draw_diamond()
{
	forward(len);
	turn(smallang);
	forward(len);
	turn(bigang);
	forward(len);
	turn(smallang);
	forward(len);
	turn(bigang);
}
void draw_hexagon()
{
	double d = 2 * len;
	move(d);
	turn(bigang);
	int i;
	for (i = 0; i != 6; ++i) {
		forward(d);
		turn(smallang);
	}
	turn(smallang);
	move(d);
	turn(-180.0);
}
void draw_star()
{
	int i;
	for (i = 0; i != 18; ++i) {
		draw_diamond();
		turn(deviation);
	}
}
void draw_edge()
{
	int i;
	for (i = 0; i != 18; ++i) {
		draw_hexagon();
		turn(deviation);
	}
}
void draw_pic()
{
	InitGraphics();
	SetPenSize(2);
	DefineColor("Green", 0.05, 0.9, 0.05);
	SetPenColor("Green");
	MovePen(initx, inity);
	turn(-90.0);
	draw_star();
	draw_edge();
}

Main() 
{
	draw_pic();
}

