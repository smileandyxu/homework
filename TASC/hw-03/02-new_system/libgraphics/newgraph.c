#include "graphics.h"
#include "math.h"
#define pi acos(-1)

double ang = 0;

void forward(double dis)
{
    double x = GetCurrentX();
    double y = GetCurrentY();
    DrawLine(dis * cos(ang / 180.0 * pi), dis * sin(ang / 180.0 * pi));
}
void turn(double angle)
{
    ang -= angle;
}
void move(double dis)
{
    double x = GetCurrentX();
    double y = GetCurrentY();
    MovePen(x + dis * cos(ang / 180 * pi), y + dis * sin(ang / 180 * pi));
}
double GetCurrentAng()
{
	return ang;
}
