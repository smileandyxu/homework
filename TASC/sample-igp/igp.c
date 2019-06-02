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

#define deltax 0.03
#define deltay 0.03

#define TIMER_BLINK500  1     /*500ms��ʱ���¼���־��*/
#define TIMER_BLINK1000 2     /*1000ms��ʱ��ʱ���־��*/

const int mseconds500 = 500;   
const int mseconds1000 = 1000; 

static double ccx = 1.0, ccy = 1.0;/*Բ������*/
static double radius = 1.0; /*Բ�뾶*/

static char text[100]; /*������ַ���������*/
static int textlen = 0;/*������ַ�������*/
static double textx, texty; /*�ַ�������ʼλ��*/

static bool isBlink = FALSE;   /*�Ƿ���˸��־*/
static bool isDisplayText = FALSE; /*�ַ�����ʾ��־*/
static bool isDisplayCircle = TRUE; /*Բ��ʾ��־*/

void DrawCenteredCircle(double x, double y, double r);/*������Բ*/
/*�жϵ�(x0,y0)�Ƿ��ھ��ΰ�Χ��(x1, y1) --> (x2, y2)��Χ��*/
bool inBox(double x0, double y0, double x1, double x2, double y1, double y2);

void KeyboardEventProcess(int key,int event);/*������Ϣ�ص�����*/
void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/

void Main() /*����ʼ��ִ��һ��*/
{
    InitGraphics();        	
	
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ�ص�����*/
	registerCharEvent(CharEventProcess);/*ע���ַ���Ϣ�ص�����*/
	registerMouseEvent(MouseEventProcess);/*ע�������Ϣ�ص�����*/
	registerTimerEvent(TimerEventProcess);/*ע�ᶨʱ����Ϣ�ص�����*/

	SetPenColor("Red"); 
    SetPenSize(1);
    
    ccx = GetWindowWidth()/2;
    ccy = GetWindowHeight()/2;
    DrawCenteredCircle(ccx, ccy, radius);
}

void DrawCenteredCircle(double x, double y, double r)
{
    MovePen(x + r, y);
    DrawArc(r, 0.0, 360.0);
}

void KeyboardEventProcess(int key,int event)/*ÿ������������Ϣ����Ҫִ��*/
{
 	 double oldradius;
 	 
     switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_UP:/*UP*/
			         SetEraseMode(TRUE);/*����ǰһ��*/
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccy += deltay;
					 SetEraseMode(FALSE);/*���µ�*/
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_DOWN:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccy -= deltay;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_LEFT:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccx -= deltax;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_RIGHT:
			         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 ccx += deltax;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_F1:
  					 SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
		 	         SetPenSize(GetPenSize()+1);
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
					 break;
			     case VK_F2:
  					 SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
		 	         SetPenSize(GetPenSize()-1);
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_F3:
			     case VK_PRIOR:
	 	     		 SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     radius += 0.1;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_F4:
			     case VK_NEXT:
		 	         SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     radius -= 0.1;
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_F9:
			         OpenConsole();
			         oldradius = radius;
			         printf("Input radius: ");
			         radius = GetReal();
			         CloseConsole();
  					 SetEraseMode(TRUE);
                     DrawCenteredCircle(ccx, ccy, oldradius);
					 SetEraseMode(FALSE);
                     DrawCenteredCircle(ccx, ccy, radius);
                     break;
			     case VK_ESCAPE:/*�򿪻�رն�ʱ��*/
                     isBlink = !isBlink;
                     if (isBlink ) {
						startTimer(TIMER_BLINK500, mseconds500);/*500ms��ʱ������*/
						startTimer(TIMER_BLINK1000, mseconds1000);/*1000ms��ʱ������*/
                     } else {
						cancelTimer(TIMER_BLINK500);/*500ms��ʱ���ر�*/
    					cancelTimer(TIMER_BLINK1000);/*500ms��ʱ���ر�*/
					 }
                     break;
			 }
			 break;
		case KEY_UP:
			 break;
	 }	 
}

void CharEventProcess(char c)
{
 	 static char str[2] = {0, 0};

     switch (c) {
       case '\r':  /* ע�⣺�س������ﷵ�ص��ַ���'\r'������'\n'*/
		   isDisplayText = TRUE;/*�����ַ�����ʾ��־*/
           textx = GetCurrentX()-TextStringWidth(text);/*�����ַ�������ʼ����*/
		   texty = GetCurrentY();
   	 	   break;
 	   case 27: /*ESC*/
 	       break;
      default:
	  	   str[0] = c;/*�γɵ�ǰ�ַ����ַ���*/
	 	   text[textlen++] = c;/*����ǰ�ַ����뵽�����ַ���������*/
	 	   text[textlen] = '\0';
	 	   DrawTextString(str);/*�����ǰ�ַ��������λ����Ӧ����*/
	 	   break;
    }
}

bool inBox(double x0, double y0, double x1, double x2, double y1, double y2)
{
	return (x0 >= x1 && x0 <= x2 && y0 >= y1 && y0 <= y2);
}

void MouseEventProcess(int x, int y, int button, int event)
{
 	 static bool isMoveCircle = FALSE;/*�ƶ�Բ��־*/
 	 static bool isMoveText = FALSE; /*�ƶ��ı���־*/ 
	 static bool isChangeRadius = FALSE;/*�ı�Բ�뾶��־*/
 	 static double omx, omy;
     double mx, my;
	 
 	 mx = ScaleXInches(x);/*pixels --> inches*/
 	 my = ScaleYInches(y);/*pixels --> inches*/

     switch (event) {
         case BUTTON_DOWN:
   		 	  if (button == LEFT_BUTTON) {
				  if (inBox(mx, my, ccx-radius, ccx+radius, ccy-radius, ccy+radius)){
					  isMoveCircle = TRUE;
				  } else if (inBox(mx, my, textx, textx+TextStringWidth(text), 
				                           texty, texty+GetFontHeight())){
				  	  isMoveText = TRUE;
				  }
			  } else if (button == RIGHT_BUTTON && inBox(mx, my, ccx-radius, ccx+radius, ccy-radius, ccy+radius)) {
				  isChangeRadius = TRUE;
			  }
		      omx = mx; omy = my;
              break;
    	 case BUTTON_DOUBLECLICK:
			  break;
         case BUTTON_UP:
  		 	  if (button == LEFT_BUTTON) {
  		 	  	isMoveCircle = FALSE;
  		 	  	isMoveText = FALSE;
  		 	  }else if (button == RIGHT_BUTTON) {
  		 	  	isChangeRadius = FALSE;
  		 	  } 
              break;
         case MOUSEMOVE:
			  if (isMoveCircle) {
                  SetEraseMode(TRUE);/*����ǰһ��*/
				  DrawCenteredCircle(ccx, ccy, radius);
				  SetEraseMode(FALSE);/*���µ�*/
				  MovePen(textx, texty);/*��ʼλ��*/
				  DrawTextString(text);
                  ccx += mx - omx;
				  ccy += my - omy;
				  omx = mx;
				  omy = my;
                  DrawCenteredCircle(ccx, ccy, radius);
			  } else if (isChangeRadius) {
                  SetEraseMode(TRUE);/*����ǰһ��*/
                  DrawCenteredCircle(ccx, ccy, radius);
				  SetEraseMode(FALSE);/*���µ�*/
                  MovePen(textx, texty);/*��ʼλ��*/
				  DrawTextString(text);
				  radius += mx - omx;
				  omx = mx;
				  omy = my;
                  DrawCenteredCircle(ccx, ccy, radius);
			  } else if (isMoveText) {
					SetEraseMode(TRUE);
	          		MovePen(textx, texty);/*��ʼλ��*/
					DrawTextString(text);
					SetEraseMode(FALSE);
	                DrawCenteredCircle(ccx, ccy, radius);
	 				textx += mx - omx;
					texty += my - omy;
					omx = mx;
					omy = my;				
					MovePen(textx, texty);/*��ʼλ��*/
					DrawTextString(text);
					break;
			  }
              break;
     }	
}

void TimerEventProcess(int timerID)
{
      bool erasemode;

	  switch (timerID) {
	    case TIMER_BLINK500: /*500ms�ı���˸��ʱ��*/
		  if (!isBlink) return;
	      erasemode = GetEraseMode();
          MovePen(textx, texty);/*��ʼλ��*/
		  SetEraseMode(isDisplayText);/*���ݵ�ǰ��ʾ��־����������ʾ���������ַ���*/
		  DrawTextString(text);/*��ǰλ�û����ַ�������*/
	      SetEraseMode(erasemode);
		  isDisplayText = !isDisplayText;/*������ʾ/�����ַ�������*/
		  break;
	    case TIMER_BLINK1000: /*1000msԲ��˸��ʱ��*/
		  if (!isBlink) return;
	      erasemode = GetEraseMode();
		  SetEraseMode(isDisplayCircle);
          DrawCenteredCircle(ccx, ccy, radius);
	      SetEraseMode(erasemode);
		  isDisplayCircle = !isDisplayCircle;
		  break;
	    default:
		  break;
	  }
}
