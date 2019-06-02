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

const double wal_len = 6;
const double wal_hig = 4;

void draw_rec(double x, double y, double len, double hig)
{
	MovePen(x, y);
	DrawLine(len, 0);
	MovePen(x + len, y);
	DrawLine(0, hig);
	MovePen(x + len, y + hig);
	DrawLine(-len, 0);
	MovePen(x, y);
	DrawLine(0, hig);
}
void draw_wall(double x, double y)
{
	draw_rec(x, y, wal_len, wal_hig);
}
void draw_door(double x, double y)
{
	draw_rec(x + wal_len * 0.5, y, wal_len * 0.2, wal_len * 0.2 * 2);
}
void draw_window(double x, double y)
{
	double len = wal_len * 0.2;
	double nx = x + wal_len * 0.15;
	double ny = y + wal_hig * 0.2;
	draw_rec(nx, ny, len * 0.5, len * 0.5);
	draw_rec(nx + 0.5*len, ny, len * 0.5, len * 0.5);
	draw_rec(nx, ny + 0.5*len, len * 0.5, len * 0.5);
	draw_rec(nx + 0.5*len, ny + 0.5*len, len * 0.5, len * 0.5);
}
void draw_roof(double x, double y)
{
	MovePen(x, y);
	DrawLine(wal_len * 0.5, wal_len * 0.3);
	MovePen(x + wal_len, y);
	DrawLine(-wal_len * 0.5, wal_len * 0.3);
	MovePen(x + wal_len * 0.1, y + wal_len * 0.1 * 0.6);
	DrawLine(0, wal_len * 0.2 - GetCurrentY() + y);
	MovePen(x + wal_len * 0.25, y + wal_len * 0.25 * 0.6);
	DrawLine(0, wal_len * 0.2 - GetCurrentY() + y);
	draw_rec(x + wal_len * 0.1 * (1-0.2), y + wal_len * 0.2, wal_len * 0.2, wal_hig * 0.04);
}
void draw_house()
{
	const double initx = 0.5, inity = 0.5;
	InitGraphics();
	draw_wall(initx, inity);
	draw_door(initx, inity);
	draw_window(initx, inity);
	draw_roof(initx, inity + wal_hig);
}
Main() 
{
	draw_house();
}

