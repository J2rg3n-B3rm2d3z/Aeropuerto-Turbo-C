#ifndef BUTTON_H
#define BUTTON_H 1
#pragma region includes
#ifndef MAXCOLORS
#include <GRAPHICS.H>
#endif
#ifndef	__DOS_DEF_
#include <mouse.h>
#endif
#ifndef	__OLDCONIO__
#include <conio.h>
#endif
#ifndef strcmpi(s1,s2)
#include <string.h>
#endif
#ifndef STDBOOL_H
#include "stdbool.h"
#endif
#ifndef GTOOLS_H
#include "GTools.h"
#endif
#pragma endregion

typedef struct
{
    int x1, y1, x2, y2, width, high, effect;
    char text[20];
} button;

typedef struct
{
    int x1, y1, x2, y2, width, high, effect;

} box;

enum buttonEffects
{
    UNPRESS,
    PRESS,
    SELECTED
};

enum effects3d
{
    DEPRESSED,
    ELEVATE
};


void effect3d(int x1, int y1, int x2, int y2, unsigned int thickness, int effect)
{
    unsigned int i;
    for(i = 0; i < thickness; i++)
    {
        setcolor(effect?DARKGRAY:WHITE);
        line(x2 - i, y1 + i, x2 - i, y2 - i);
        line(x2 - i, y2 - i, x1 + i, y2 - i);
        
        setcolor(effect?WHITE:DARKGRAY);
        line(x2 - i, y1 + i, x1 + i, y1 + i);
        line(x1 + i, y1 + i, x1 + i, y2 - i);
    }
}

bool limit(int x0, int y0,int x1,int y1,int x2,int y2)
{
    if((x0>=x1) && (x0<=x2) && (y0>=y1) && (y0<=y2))
        return 1;
    return 0;
}

void drawButton(button* btn)
{
    button button = *btn;
    setlinestyle(SOLID_LINE,1,1);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(button.x1,button.y1,button.x2,button.y2);

    setcolor(button.effect==PRESS?BLACK:WHITE);
    line(button.x1,button.y1,button.x2,button.y1);
    line(button.x1,button.y1,button.x1,button.y2);

    setcolor(button.effect==PRESS?WHITE:BLACK);
    line(button.x2,button.y2,button.x1,button.y2);
    line(button.x2,button.y2,button.x2,button.y1);
    
    settextstyle(SMALL_FONT,0,4);
    if(button.effect != SELECTED)
        setcolor(BLACK);
    else
        setcolor(BLUE);

    outtextxy(2 + button.x1,button.high/2-5 + button.y1, button.text);
}

void newButton(button* btn, int x, int y, char* text)
{
    button temp;
    temp.width = strlen(text) * 6;
    temp.high = 15;
    temp.x1 = x;
    temp.x2 = x + temp.width;
    temp.y1 = y;
    temp.y2 = y + temp.high;
    temp.effect = UNPRESS;
    strcpy(temp.text,text);
    *btn = temp;
    drawButton(btn);
}

void drawInputBox(box* input)
{
    box box = *input;
    setlinestyle(SOLID_LINE,1,1);
    setfillstyle(SOLID_FILL,WHITE);
    bar(box.x1,box.y1,box.x2,box.y2);

    /*setcolor(button.effect==PRESS?BLACK:WHITE);*/
    setcolor(box.effect==PRESS?DARKGRAY:WHITE);
    line(box.x1,box.y1,box.x2,box.y1);
    line(box.x1,box.y1,box.x1,box.y2);

    /*setcolor(button.effect==PRESS?WHITE:BLACK);*/
    setcolor(box.effect==PRESS?WHITE:DARKGRAY);
    line(box.x2,box.y2,box.x1,box.y2);
    line(box.x2,box.y2,box.x2,box.y1);
}

void inputBox(box* input, int x, int y)
{
    box temp;
    temp.width = 110;
    temp.high = 30;
    temp.x1 = x;
    temp.x2 = x + temp.width;
    temp.y1 = y;
    temp.y2 = y + temp.high;
    temp.effect = UNPRESS;
    *input = temp;
    drawInputBox(input);
}
void ErrorMessage(int x1, int y1, int x2, int y2, char* text)
{
    effect3d(x1, y1, x2, y2, 2, DEPRESSED);
    setfillstyle(SOLID_FILL, 4);
	bar(x1+2, y1+2, x2-2, y2-2);

    /* Tipo de fuente y efecto 3D */
	settextstyle(SMALL_FONT, HORIZ_DIR, 4);
	Text3D(x1+4, y1+6, 1, 8, 15, text);
}
void drawButton2(button* btn)
{
    button button = *btn;
    setlinestyle(SOLID_LINE,1,1);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(button.x1,button.y1,button.x2,button.y2);

    /*setcolor(button.effect==PRESS?BLACK:WHITE);*/
    setcolor(button.effect==PRESS?DARKGRAY:WHITE);
    line(button.x1,button.y1,button.x2,button.y1);
    line(button.x1,button.y1,button.x1,button.y2);

    /*setcolor(button.effect==PRESS?WHITE:BLACK);*/
    setcolor(button.effect==PRESS?WHITE:DARKGRAY);
    line(button.x2,button.y2,button.x1,button.y2);
    line(button.x2,button.y2,button.x2,button.y1);
    
    /*settextstyle(SMALL_FONT,0,4);*/
    settextstyle(DEFAULT_FONT,0,1);
    if(button.effect != SELECTED)
        setcolor(DARKGRAY);
        /*setcolor(BLACK);*/
    else
        /*setcolor(BLUE);*/
        setcolor(WHITE);

    /*outtextxy(2 + button.x1,button.high/2-5 + button.y1, button.text);*/
    Text3D(18 + button.x1, button.high/2-4 + button.y1, 1, 8, 15, button.text);
    /*outtextxy(20 + button.x1,button.high/2-5 + button.y1, button.text);*/
}

void newButton2(button* btn, int x, int y, char* text)
{
    button temp;
    /*temp.width = strlen(text) * 6;*/
    temp.width = 100;
    /*temp.high = 15;*/
    temp.high = 30;
    temp.x1 = x;
    temp.x2 = x + temp.width;
    temp.y1 = y;
    temp.y2 = y + temp.high;
    temp.effect = UNPRESS;
    strcpy(temp.text,text);
    *btn = temp;
    drawButton2(btn);
}
#endif