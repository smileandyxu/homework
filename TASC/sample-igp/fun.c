#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define PI 3.1415926
#define TIMER_BLINK  1

static int N1 = 180, N2 = 100;
const int mseconds = 50;
static double ccx = 1.0, ccy = 1.0;/*Բ������*/
static double r1 = 3.0; /*Բ�뾶*/
static double r2 = 2.0; /*Բ�뾶*/
static double xx1, yy1, xx2, yy2, theta1, theta2, d1, d2;
bool flag = FALSE;

void DrawCenteredCircle(double x, double y, double r);/*������Բ*/
void Line(double x1, double y1, double x2, double y2);
void KeyboardEventProcess(int key,int event);/*������Ϣ�ص�����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/

void Main() /*����ʼ��ִ��һ��*/
{
    InitGraphics();        	
	
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/
	
	SetPenColor("Red"); 
    SetPenSize(1);
    
    ccx = GetWindowWidth()/2;
    ccy = GetWindowHeight()/2;
    DrawCenteredCircle(ccx, ccy, r1);
    DrawCenteredCircle(ccx, ccy, r2);
    xx1 = 0; yy1 = r1;
	xx2 = 0; yy2 = r2;
	d1 = 2.0*PI/N1;
	d2 = 2.0*PI/N2;
	theta1 = theta2 = 0.0;
	//Line(xx1+ccx, yy1+ccy, xx2+ccx, yy2+ccy);
	//startTimer(TIMER_BLINK, mseconds);
}

void TimerEventProcess(int timerID)
{
	  switch (timerID) {
	    case TIMER_BLINK: 
			xx1 = r1 * sin(theta1); yy1 = r1 * cos(theta1);
			xx2 = r2 * sin(theta2); yy2 = r2 * cos(theta2);		
			Line(xx1+ccx, yy1+ccy, xx2+ccx, yy2+ccy);
			//repaint();
			theta1 += d1; theta2 += d2;
			break;
	    default:
			break;
	  }
}

void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360.0);
}

void Line(double x1, double y1, double x2, double y2)
{
	MovePen(x1, y1);
	DrawLine(x2-x1, y2-y1);
}

void KeyboardEventProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{
     switch (event) {
	 	case KEY_DOWN:
	 		 if (key == VK_ESCAPE) flag = !flag;
			 if (flag) {
			 	startTimer(TIMER_BLINK, mseconds);
			 } else {
			 	cancelTimer(TIMER_BLINK);	
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}
