#ifndef _layer_h
#define _layer_h

typedef struct
{
    int type;
    double x1, y1, x2, y2;
} layer;

typedef layer *layerptr;

int isline(layer);
int isrectangle(layer);
int isoval(layer);
int istext(layer);
layerptr NewLayer(int, double, double, double, double);


#endif