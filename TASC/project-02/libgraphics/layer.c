#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <wincon.h>
#include <Windows.h>

#include "genlib.h"
#include "gcalloc.h"
#include "strlib.h"
#include "extgraph.h"

#include "layer.h"

#define TYPE_LINE 1
#define TYPE_RECTANGLE 2
#define TYPE_OVAL 3
#define TYPE_TEXT 4

int isline(layer x)
{
    return x.type == TYPE_LINE;
}

int isrectangle(layer x)
{
    return x.type == TYPE_RECTANGLE;
}

int isoval(layer x)
{
    return x.type == TYPE_OVAL;
}

int istext(layer x)
{
    return x.type == TYPE_TEXT;
}

layerptr NewLayer(int type, double x1, double y1, double x2, double y2)
{
    layerptr tmp = New(layerptr);
    tmp->type = type;
    tmp->x1 = x1;
    tmp->x2 = x2;
    tmp->y1 = y1;
    tmp->y2 = y2;
    return tmp;
}