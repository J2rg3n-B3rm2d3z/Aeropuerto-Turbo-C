#ifndef GTOOLS_H
#define GTOOLS_H 1

void Text3D(int x, int y, int depth, int bgcolor, int fcolor, char *str)
{
  int i;
  setcolor(bgcolor);
  for(i = 0; i < depth; i++)
	  outtextxy(x+i,y+i,str);
  setcolor(fcolor);
  outtextxy(x+i,y+i,str);
}

void back3D(int x1, int y1, int x2, int y2, int upCol, int downCol)
{
  setlinestyle(SOLID_LINE,1,1);
  setcolor(upCol);
	line(x1, y1, x2, y1);
	line(x1, y1, x1, y2);

	setcolor(downCol);
	line(x1, y2, x2, y2);
	line(x2, y1, x2, y2);
}

void inputBar(int x1, int y1, int x2, int y2, int color)
{
  setfillstyle(SOLID_FILL, color);
  bar(x1,y1,x2,y2);
}

void DrawButton(int x1, int y1, int x2, int y2, char *text)
{
  /* setlinestyle(SOLID_LINE,1,1); */
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(x1,y1,x2,y2);

	settextstyle(SMALL_FONT, HORIZ_DIR, 5);
	Text3D(x1 + 20, y1 + 5, 1, 8, 15, text);
}
#endif