#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>

#define eps 1e-3
#define MAX_LAYER 10000
#define edge 0.2
#define sqr(x) x * x

int mode;          //0-select 1-line 2-rectangle 3-oval 4-text
int layer_num = 0; //number of layers
int current_id;
int current_option;  //which place mouse stays on current layer
double mx, my;       //x & y of mouse
double lastx, lasty; //x&y of mouse(use in drawing layer)
bool mouse_special;

typedef struct
{
	int kind, length; //length is length of text
	double x1, x2, y1, y2;
	char text[100];
} graph;

graph layer[MAX_LAYER]; //start from 1

static string penColor[] = {"White", "Black"};

void MouseEventProcess(int, int, int, int);
void KeyboardEventProcess(int, int);
void CharEventProcess(char);

void draw(bool);
void drawbg(bool);
void drawbox(double, double, double, double);
void drawoval(double, double, double, double);
void drawimaginarybox(double, double, double, double);
void add_char(int, char);
void del(int);
int menu_check(double, double);
int layer_check(double, double);
void insert_layer(double, double);
void move_layer(int, double, double, double, double);
void deviate_layer(int, double, double, double, double);
void layer_transform(double, double);
void mydrawline(double, double, double, double);
bool inDrawingArea(double, double);
bool onLayer(int, double, double);
bool doubleEqual(double, double);

void Main()
{
	OpenConsole();
	InitGraphics();
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);
	draw(1);
}

void MouseEventProcess(int x, int y, int button, int event)
{	


    /*
    */
	int i, t;
	printf("%d %d %d %d\n",x,y,button,event);
	/*if (button != LEFT_BUTTON)
		return;*/
	double nx = ScaleXInches(x);
	double ny = ScaleYInches(y);
	if (event == BUTTON_UP)
	{
		t = menu_check(nx, ny);
		if (t)
		{
			mode = t % 5, current_id = 0;
			draw(0), draw(1);
		}
		else if (!inDrawingArea(nx, ny))
			mode = 0, current_id = 0;
		else if (mode == 0)
			current_id = layer_check(nx, ny), current_option = 0;
		else if (current_option == 10)
			current_id = layer_num, current_option = 0;
	}
	else if (event == BUTTON_DOWN)
	{
		if (mode == 0)
		{
			if (current_id)
				current_option = option_check(nx, ny);
		}
		else
		{
			//insert_layer(lastx, lasty);
			insert_layer(nx, ny);
			current_id = layer_num, current_option = 10;
		}
	}
	else if (event == MOUSEMOVE)
	{
		if (current_id && current_option)
			layer_transform(nx, ny);
	}
	mx = nx, my = ny;
}

void KeyboardEventProcess(int key, int event)
{
	if (event == KEY_DOWN)
		if (mode == 0 && current_id && key == VK_DELETE)
			del(current_id), current_id = 0;
}

void CharEventProcess(char c)
{
	if (mode == 4 && current_id)
	{
		draw(0);
		if (c == '\r')
			mode = 0, add_char(current_id, 0);
		else
			add_char(current_id, c);
		draw(1);
	}
}

/*
drawmode-0 clear all elements
drawmode-1 draw all elements
*/
void draw(bool drawmode)
{
	int i;
	SetPenColor(penColor[drawmode]);
	drawbg(drawmode);
	for (i = 1; i <= layer_num; i++) {
		if (i == current_id)
			;//special_judge
		if (layer[i].kind == 1) {
			MovePen(layer[i].x1, layer[i].y1);
			DrawLine(layer[i].x2 - layer[i].x1, layer[i].y2 - layer[i].y1);
		}
		else if (layer[i].kind == 2) {
			drawbox(layer[i].x1,layer[i].y1,layer[i].x2,layer[i].y2); 
		}
		else if (layer[i].kind == 3) {
			double midx = (layer[i].x1 + layer[i].x2) / 2;
			double midy = (layer[i].y1 + layer[i].y2) / 2;
			MovePen(midx, midy);
			double rx = layer[i].x2 - layer[i].x1;
			double ry = layer[i].y2 - layer[i].y1;
			DrawEllipticalArc(rx, ry, 0.0, 360.0);
		}
		else {
			double width = layer[i].x2 - layer[i].x1;
			double average = width / layer[i].length;
			MovePen(layer[i].x1, layer[i].y1);
		}
	}
}

//judge point(x,y) is in valid drawing area or not
bool inDrawingArea(double x, double y)
{
	if (x < 1.5 + edge)
		return 0;
	if (x > 10.0 - edge)
		return 0;
	if (y < edge)
		return 0;
	if (y > 7.0 - edge)
		return 0;
	return 1;
}

void drawbox(double x1, double y1, double x2, double y2) //x1<x2,y1<y2
{
	if (!inDrawingArea(x1, y1) && !inDrawingArea(x2, y2))
		return;
	if (inDrawingArea(x1, y1) && inDrawingArea(x2, y2))
	{
		MovePen(x1, y1);
		DrawLine(x2 - x1, 0);
		DrawLine(0, y2 - y1);
		DrawLine(x1 - x2, 0);
		DrawLine(0, y1 - y2);
		return;
	}
	if (inDrawingArea(x1, y1))
	{
		MovePen(x1, y1);
		if (x2 < 10.0 - edge)
		{
			DrawLine(x2 - x1, 0);
			DrawLine(0, 7.0 - edge - y1);
			MovePen(x1, y1);
			DrawLine(0, 7.0 - edge - y1);
			return;
		}
		else if (y2 < 7.0 - edge)
		{
			DrawLine(10.0 - edge - x1, 0);
			MovePen(x1, y1);
			DrawLine(0, y2 - y1);
			DrawLine(10.0 - edge - x1, 0);
			return;
		}
		else
		{
			DrawLine(10.0 - edge - x1, 0);
			MovePen(x1, y1);
			DrawLine(0, 7.0 - edge - y1);
		}
	}
	else
	{
		MovePen(x2, y2);
		if (x1 > 1.5 + edge)
		{
			DrawLine(x1 - x2, 0);
			DrawLine(0, edge - y2);
			MovePen(x2, y2);
			DrawLine(0, edge - y2);
			return;
		}
		else if (y1 > edge)
		{
			DrawLine(1.5 + edge - x2, 0);
			MovePen(x2, y2);
			DrawLine(0, y1 - y2);
			DrawLine(1.5 + edge - x2, 0);
			return;
		}
		else
		{
			DrawLine(1.5 + edge - x2, 0);
			MovePen(x2, y2);
			DrawLine(0, edge - y2);
		}
	}
}

void drawoval(double x1, double y1, double x2, double y2) //x1<x2,y1<y2
{
}

void drawimaginarybox(double x1, double y1, double x2, double y2) //x1<x2,y1<y2
{
}

void drawline(double x1, double y1, double x2, double y2) //x1<x2,y1<y2
{
}

void drawbg(bool drawmode)
{
	MovePen(1.5, 0);
	DrawLine(0, 7);
	int i;
	for (i = 0; i <= 4; i++)
	{
		if (drawmode && mode == i)
			SetPenColor("Blue");
		MovePen(0.25, 0.2 + (4 - i) * 1.4);
		DrawLine(1, 0);
		DrawLine(0, 1);
		DrawLine(-1, 0);
		DrawLine(0, -1);
		if (drawmode && mode == i)
			SetPenColor("Black");
	}
	if (drawmode && mode == 0)
		SetPenColor("Blue");
	MovePen(0.55, 5.9);
	DrawLine(0.1, 0.2);
	DrawLine(-0.22, 0);
	DrawLine(0.5, 0.53);
	DrawLine(0, -0.63);
	DrawLine(-0.18, 0.1);
	DrawLine(-0.1, -0.2);
	DrawLine(-0.1, 0);
	if (drawmode && mode == 0)
		SetPenColor("Black");
	if (drawmode && mode == 1)
		SetPenColor("Blue");
	MovePen(0.45, 5.25);
	DrawArc(0.05, 0, 360);
	MovePen(1.15, 4.55);
	DrawArc(0.05, 0, 360);
	MovePen(0.4, 5.25);
	DrawLine(0.7, -0.7);
	if (drawmode && mode == 1)
		SetPenColor("Black");
	if (drawmode && mode == 2)
		SetPenColor("Blue");
	MovePen(0.35, 3.8);
	DrawLine(0.6, 0);
	DrawLine(0, -0.4);
	DrawLine(-0.6, 0);
	DrawLine(0, 0.4);
	MovePen(0.75, 3.5);
	DrawLine(0.4, 0);
	DrawLine(0, -0.4);
	DrawLine(-0.4, 0);
	DrawLine(0, 0.4);
	if (drawmode && mode == 2)
		SetPenColor("Black");
	if (drawmode && mode == 3)
		SetPenColor("Blue");
	MovePen(1.05, 2.1);
	DrawArc(0.3, 0, 360);
	MovePen(0.9, 2.1);
	DrawArc(0.15, 0, 360);
	if (drawmode && mode == 3)
		SetPenColor("Black");
	if (drawmode && mode == 4)
		SetPenColor("Blue");
	MovePen(0.45, 0.95);
	DrawLine(0, 0.1);
	MovePen(1.05, 0.95);
	DrawLine(0, 0.1);
	MovePen(0.45, 1);
	DrawLine(0.6, 0);
	MovePen(0.75, 1);
	DrawLine(0, -0.65);
	DrawLine(-0.1, 0);
	DrawLine(0.2, 0);
	if (drawmode && mode == 4)
		SetPenColor("Black");
}

//add char c to layer[id].text 's end
void add_char(int id, char c)
{
	layer[id].text[layer[id].length] = c;
	layer[id].length++;
}

//del layer[id] than make [id+1, layer_num] -> [id, layer_num-1]
void del(int id)
{
	int i;
	draw(0);
	for (i = id; i <= layer_num - 1; i++)
		layer[i] = layer[i + 1];
	layer_num--;
	draw(1);
}

//return which mode is mouse stay in the menu, if not return 0
int menu_check(double x, double y)
{
	if (x >= 0.25 && x <= 1.25)
	{
		int i;
		for (i = 0; i <= 4; i++)
		{
			if (y >= 0.2 + i * 1.4 && y <= 1.2 + i * 1.4)
				return 4 - i > 0 ? 4 - i : 5;
		}
		return 0;
	}
	else
		return 0;
}

bool doubleEqual(double a, double b) {
	return fabs(a-b) < eps;
}

bool onLayerEdge(int id, double x, double y) {
	if (layer[id].kind == 1) {
		double maxx = max(layer[id].x1, layer[id].x2);
		double minx = min(layer[id].x1, layer[id].x2);
		double maxy = max(layer[id].y1, layer[id].y2);
		double miny = min(layer[id].y1, layer[id].y2);
		if (x < minx || x > maxx || y < miny || y > maxy)
			return FALSE;
		return doubleEqual((y - layer[id].y1) * (layer[id].x2 - layer[id].x1), (x - layer[id].x1) * (layer[id].y2 - layer[id].y1));
	}
	else if (layer[id].kind == 2 || layer[id].kind == 4)
		return (doubleEqual(layer[id].x1, x) || doubleEqual(layer[id].x2, x)) && (doubleEqual(layer[id].y1, y) || doubleEqual(layer[id].y2, y));
	else if (layer[id].kind == 3) {
		if (x < layer[id].x1 || x > layer[id].x2)
			return FALSE;
		if (y < layer[id].y1 || y > layer[id].y1)
			return FALSE;
		double a = (layer[id].x2 - layer[id].x1) / 2;
		double b = (layer[id].y2 - layer[id].y1) / 2;
		double midx = (layer[id].x2 + layer[id].x1) / 2;
		double midy = (layer[id].y2 + layer[id].y1) / 2;
		return doubleEqual(sqr(fabs(x - midx) / a) + sqr(fabs(y - midy) / b), 1);
	}
}

//return which layer_edge is mouse stay, if not return 0
int layer_check(double x, double y)
{
	int i;
	for (i = 1; i <= layer_num; i++)
		if (onLayerEdge(i, x, y))
			return i;
	return 0;
}

/*
if mouse stay on edge return 1-4
else if mouse stay on corner return 5-8
*/
int option_check(double x, double y)
{
	if (mode) {
		//do nothing
	}
	else {
		int t = onLayerCorner(current_id, x, y); 
		if (t) {
			return t;
		}
		else if (onLayerEdge(current_id, x, y)) {
			return 1; //1-4
		}

	}
}

/*
return in which corner mouse is
5-downleft
6-donwright
7-upright
8-upleft
*/
int onLayerCorner(int i, double x, double y)
{
	double x1 = layer[i].x1;
	double x2 = layer[i].x2;
	double y1 = layer[i].y1;
	double y2 = layer[i].y2;
	if (dist(x, y, x1, y1) < eps)
		return 5;
	if (dist(x, y, x2, y1) < eps)
		return 6;
	if (dist(x, y, x2, y2) < eps)
		return 7;
	if (dist(x, y, x1, y2) < eps)
		return 8;
}


/*
insert a new layer with a start point
*/
void insert_layer(double x, double y)
{
	draw(0);
	layer_num++;
	layer[layer_num].kind = mode;
	layer[layer_num].x1 = x, layer[layer_num].y1 = y;
	layer[layer_num].x2 = x, layer[layer_num].y2 = y;
	draw(1);
}

//use for layer's transforming
void layer_transform(double x, double y)
{
	draw(0);
	switch (current_option) {
		case 1:
			deviate_layer(layer_num, x - mx, y - my, x - mx, y - my);
			break;
		case 5:
			deviate_layer(layer_num, x - mx, y - my, 0, 0);
			break;
		case 6:
			deviate_layer(layer_num, 0, y - my, x - mx, 0);
			break;
		case 7:
			deviate_layer(layer_num, 0, 0, x - mx, y - my);
			break;
		case 8:
			deviate_layer(layer_num, x - mx, 0, 0, y - my);
			break;
		case 10:
			
			layer[layer_num].x2 = x;
			layer[layer_num].y2 = y;
			
			break;
	}
	draw(1);
}

/*
modify layer i by deviating its corners
*/
void deviate_layer (int i, double dx1, double dy1, double dx2, double dy2)
{
	layer[i].x1 += dx1;
	layer[i].x2 += dx2;
	layer[i].y1 += dy1;
	layer[i].y2 += dy2;
}

/*
move layer i to a place with four fixed corners
*/
void move_layer(int i, double x1, double y1, double x2, double y2)
{
	layer[i].x1 = x1;
	layer[i].x2 = x2;
	layer[i].y1 = y1;
	layer[i].y2 = y2;
}
