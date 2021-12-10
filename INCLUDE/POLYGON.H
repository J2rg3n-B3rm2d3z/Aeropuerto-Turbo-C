#ifndef POLYGON_H
#define POLYGON_H 1
#ifndef __COLORS
#include <GRAPHICS.H>
#endif
#ifndef _MATH_H
#include <math.h>
#endif
#include <stdio.h>

int* regpolypoints(int x1, int y1, int x2, int y2, int sides, double inclination, int startPoint, int endPoint)
{
    int i,j=0, polygon[31][2];
    double x0 = (x2-x1)/2, y0 = (y2-y1)/2, angle = 2*M_PI/sides;

    inclination *= M_PI / 180;

    for(i = startPoint; i <= endPoint; i++)
    {
        polygon[j][0] = x1 + x0 + floor(x0 * cos(angle * i + inclination));
        polygon[j][1] = y1 + y0 - floor(y0 * sin(angle * i + inclination));
        j++;
    }

    return *polygon;
}

void drawregpoly(int x, int y, int radius, int sides) { if(sides <= 30 && sides >= 3) drawpoly(sides+1, regpolypoints(x-radius,y-radius,x+radius,y+radius,sides,0,0,sides)); }
void fillregpoly(int x, int y, int radius, int sides) { if(sides <= 30 && sides >= 3) fillpoly(sides+1, regpolypoints(x-radius,y-radius,x+radius,y+radius,sides,0,0,sides)); }
void drawpolyinellipse(int x, int y, int xradius, int yradius, int sides) { if(sides <= 30 && sides >= 3) drawpoly(sides+1, regpolypoints(x-xradius,y-yradius,x+xradius,y+yradius,sides,0,0,sides)); }
void fillpolyinellipse(int x, int y, int xradius, int yradius,int sides) { if(sides <= 30 && sides >= 3) fillpoly(sides+1, regpolypoints(x-xradius,y-yradius,x+xradius,y+yradius,sides,0,0,sides)); }
void fillpolyinrectangle(int x1, int y1, int x2, int y2, int sides, double inclination) { if(sides <= 30 && sides >= 3) fillpoly(sides+1, regpolypoints(x1,y1,x2,y2,sides,inclination,0,sides)); }
void drawpolyinrectangle(int x1, int y1, int x2, int y2, int sides,double inclination, int startPoint, int endPoint) { drawpoly((endPoint - startPoint)+1, regpolypoints(x1,y1,x2,y2,sides,inclination,startPoint,endPoint)); }
#endif