#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"

#include "layer.h"

#define TYPE_SELECT 0
#define TYPE_LINE 1
#define TYPE_RECTANGLE 2
#define TYPE_OVAL 3
#define TYPE_TEXT 4

#define BAR_HEIGHT 0.1
#define MENU_NUM 5
#define MENU_X 0.5
#define MENU_Y (GetWindowHeight() - 4 * BAR_HEIGHT)
#define MENU_WIDTH 5.0
#define MENU_HEIGHT (GetFontHeight() * 1.2)
#define HINT_X 0.5
#define HINT_Y 0.25
#define HINT_LEN 20
#define BOARD_X 0.5
#define BOARD_Y 0.5
#define BOARD_WIDTH (GetWindowWidth() - 1)
#define BOARD_HEIGHT (MENU_Y - BAR_HEIGHT - BOARD_Y)
#define CORNER_SIZE 0.05

#define DEFAULT_COLOR "Black"
#define EMPTY_COLOR "White"

#define LAYER_NUM 500

static string menu_text[MENU_NUM] = {"Select", "Line", "Rectangle", "Oval", "Text"};
static layerptr layers[LAYER_NUM];
static int layersize = 0;
static int mode = 0;
static int current_layer = 0;

void InitConfig();

void DrawMenu();
void DrawBoard();
void DrawLayer(int);
void DrawImage(double, double, double, double, int);
void DrawCleanImage(double, double, double, double, int);
void FixLayer(int);
void DrawHint(int);
void DrawCleanHint(int);
void UpdateHint();

void DrawBorder(int); //Draw the border of layer k

void KeyboardEventProcess(int,int);
void CharEventProcess(char);
void MouseEventProcess(int, int, int, int);
void TimerEventProcess(int);

bool inmenu(double, double);
bool inboard(double, double);
bool incorner(double, double, int);
bool inlayer(double, double, int);
bool layer_intersect(int, int);/**/
int menuindex(double, double);
int select_layer(double, double, int);

Main()
{
	InitConfig();
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerMouseEvent(MouseEventProcess);
	//registerTimerEvent();
}

void InitConfig()
{
	InitGraphics();
	DrawMenu();
	DrawBoard();
	DrawHint(TYPE_SELECT);
	SetPenColor(DEFAULT_COLOR);
	int i;
	for (i = 0; i != LAYER_NUM; ++i)
		layers[i] = NULL;
}

/*Implementations*/
void KeyboardEventProcess(int key, int event)/**/
{

}
void CharEventProcess(char c)/**/
{

}
void MouseEventProcess(int x, int y, int button, int event)/**/
{
	static double ox, oy, nx, ny;
	static bool isdrawing = 0;
	static bool isselecting = 0;
	switch (event) {
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON) {
			if (mode == TYPE_SELECT) {
				double cx = ScaleXInches(x);
				double cy = ScaleYInches(y);
				if (inboard(cx, cy)) {
					//top = layersize - 1;
					
					/*DONT KNOW HOW TO DEAL WITH OVERLAP!!!*/
					
					/*static int top;
					if (!isselecting) {
						isselecting = 1;
						top = layer_size - 1;
					}
					else {
						top = select_layer(cx, cy, top) - 1;
					}
					int k = select_layer(cx, cy, top);
					if (k == -1) {
							
					}
					*/
					int k = select_layer(cx, cy, layersize - 1);
					if (k == -1) {
						isselecting = 0;
					}
					else if (!isselecting) {
						isselecting = 1;
					}
					else {
					}
					UpdateBorder(k);
					
					
					/*Scaling and Moving layer is incomplete*/
					
					/*else if (incorner(cx, cy, k)) {
						
						DrawCursor("")
					}
					else {
						 //Drag the layer and move it.
					}*/
				}
			}
			else {
				isdrawing = TRUE;
				ox = ScaleXInches(x);
				oy = ScaleYInches(y);
				nx = ox;
				ny = oy;
				layers[layersize] = NewLayer(mode, ox, oy, nx, ny);
			}
			
		}
		break;

	case BUTTON_UP:
		if (button == LEFT_BUTTON) {
			if (inmenu(ScaleXInches(x), ScaleYInches(y))) {
				mode = menuindex(ScaleXInches(x), ScaleYInches(y));
				isdrawing = FALSE;
				UpdateHint();
				UpdateBorder(-1);
			}
			/*else if (mode == TYPE_SELECT) {
				if (isdragging) {
					
				}
				else {
					
				}
			}*/
			else if (mode != TYPE_SELECT) {
				isdrawing = FALSE;
				nx = ScaleXInches(x);
				ny = ScaleYInches(y);
				FreeBlock(layers[layersize]);
				layers[layersize++] = NewLayer(mode, ox, oy, nx, ny);
			}
		}
		break;

	case MOUSEMOVE: 
		if (inboard(ScaleXInches(x), ScaleYInches(y))) {
			if (isdrawing) {
				DrawCleanImage(ox, oy, nx, ny, mode);
				FixLayer(layersize);
				nx = ScaleXInches(x);
				ny = ScaleYInches(y);
				FreeBlock(layers[layersize]);
				layers[layersize] = NewLayer(mode, ox, oy, nx, ny);
				DrawImage(ox, oy, nx, ny, mode);
			}
			/*if (isselecting) {
				layerptr tmp = layers[layersize - 1];
				
			}*/
		}
		break;

	default:
		break;
	}

}

void DrawImage(double x1, double y1, double x2, double y2, int mode)
{
	double nx = GetCurrentX();
	double ny = GetCurrentY();
	switch (mode) {
	case TYPE_LINE:
		MovePen(x1, y1);
		DrawLine(x2 - x1, y2 - y1);
		break;

	case TYPE_RECTANGLE:
		DrawBox(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
		break;

	case TYPE_OVAL:
		DrawOval(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));/**/
		break;

	case TYPE_TEXT:/**/
		break;

	default:
		break;
	}
	MovePen(nx, ny);
}

/*Basically Completed*/

bool layer_intersect(int i, int j) /* TOO SLOW!!!!!!! Have to find another way to do this job!!! */
{
	layerptr x = layers[i];
	layerptr y = layers[j];
	double xx1 = min(x->x1, x->x2);
	double xy1 = min(x->y1, x->y2);
	double xx2 = max(x->x1, x->x2);
	double xy2 = max(x->y1, x->y2);
	double yx1 = min(y->x1, y->x2);
	double yy1 = min(y->y1, y->y2);
	double yx2 = max(y->x1, y->x2);
	double yy2 = max(y->y1, y->y2);
	return box_intersect(xx1, xy1, xx2, xy2, yx1, yy1, yx2, yy2);
}

void DrawBorder(int k) /*May change the design*/
{
	if (k == -1)
		return;
	
	layerptr tmp = layers[k];
	double x1 = min(tmp->x1, tmp->x2);
	double y1 = min(tmp->y1, tmp->y2);
	double x2 = max(tmp->x1, tmp->x2);
	double y2 = max(tmp->y1, tmp->y2);
	DrawBox(x1, y1, x2, y2);
	
	/**/
	DrawBox(x1, y1, x1 + CORNER_SIZE, y1 + CORNER_SIZE);
	DrawBox(x2 - CORNER_SIZE, y1, x2, y1 + CORNER_SIZE);
	DrawBox(x1, y2 - CORNER_SIZE, x1 + CORNER_SIZE, y2);
	DrawBox(x2 - CORNER_SIZE, y2 - CORNER_SIZE, x2, y2);
	/**/
}

bool incorner(double x, double y, int k) /*May change the design*/
{
	layerptr tmp = layers[k];
	if (!tmp)
		return FALSE;
	else {
		double x1 = min(tmp->x1, tmp->x2);
		double y1 = min(tmp->y1, tmp->y2);
		double x2 = max(tmp->x1, tmp->x2);
		double y2 = max(tmp->y1, tmp->y2);
		double mindist = min(min(dist(x, y, x1, y1), dist(x, y, x1, y2)), min(dist(x, y, x2, y1), dist(x, y, x2, y2)));
		return (mindist <= CORNER_SIZE);
	}
}


/*Completed*/

bool inlayer(double x, double y, int k)
{
	layerptr tmp = layers[k];
	double x1 = min(tmp->x1, tmp->x2);
	double y1 = min(tmp->y1, tmp->y2);
	double x2 = max(tmp->x1, tmp->x2);
	double y2 = max(tmp->y1, tmp->y2);
	return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}
int select_layer(double x, double y, int top)
{
	int i, k = -1;
	for (i = top; i >= 0; --i) {
		if (inlayer(x, y, i)) {
			k = i;
			break;
		}
	}
	return k;
	
}
void UpdateBorder(int k)
{
	static int lastlayer = -1;
	DrawCleanBorder(lastlayer);
	DrawLayer(lastlayer);
	FixLayer(lastlayer);
	lastlayer = k;
	DrawBorder(k);
}
void DrawCleanBorder(int k)
{
	string color = GetPenColor();
	SetPenColor(EMPTY_COLOR);
	DrawBorder(k);
	SetPenColor(color);
}
int menuindex(double x, double y)
{
	return (int)((x - MENU_X) * MENU_NUM / MENU_WIDTH);
}
void UpdateHint()
{
	static int lastmode = 0;
	DrawCleanHint(lastmode);
	lastmode = mode;
	DrawHint(mode);
}
void DrawHint(int mode)
{
	char tmp[HINT_LEN] = " mode: ";
	strcat(tmp, menu_text[mode]);
	strcat(tmp, " ");
	DrawTextBox(HINT_X, HINT_Y, tmp);
}
void DrawCleanHint(int mode)
{
	string color = GetPenColor();
	SetPenColor(EMPTY_COLOR);
	DrawHint(mode);
	SetPenColor(color);
}
void DrawCleanImage(double x1, double y1, double x2, double y2, int mode)
{
	string tmp = GetPenColor();
	SetPenColor(EMPTY_COLOR);
	DrawImage(x1, y1, x2, y2, mode);
	SetPenColor(tmp);
}
void FixLayer(int k)
{
	if (k == -1)
		return;
	int i;
	for (i = 0; i != layersize; ++i) {
		if (i != k && layer_intersect(i, k))
			DrawLayer(i);
	}
}
void DrawLayer(int i)
{
	if (i == -1 || !layers[i])
		return;
	layerptr tmp = layers[i];
	DrawImage(tmp->x1, tmp->y1, tmp->x2, tmp->y2, tmp->type);
}

bool inmenu(double x, double y)
{
	return MENU_X < x && x < MENU_X + MENU_WIDTH && MENU_Y < y && y < MENU_Y + MENU_HEIGHT;
}
bool inboard(double x, double y)
{
	return BOARD_X < x && x < BOARD_X + BOARD_WIDTH && BOARD_Y < y && y < BOARD_Y + BOARD_HEIGHT;
}
void DrawMenu()
{
	double maxwidth = 0;
	double x = MENU_X;
	double y = MENU_Y;
	int i;
	MovePen(x, y);
	for (i = 0; i != MENU_NUM; ++i) {
		DrawFixTextBox(x, y, MENU_WIDTH / MENU_NUM, MENU_HEIGHT, menu_text[i]);
		x += MENU_WIDTH / MENU_NUM;
		MovePen(x, y);
	}
}
void DrawBoard()
{
	double x = BOARD_X;
	double y = BOARD_Y;
	MovePen(x, y);
	DrawBox(x, y, x + BOARD_WIDTH, y + BOARD_HEIGHT);
}
