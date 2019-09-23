#include <graphics.h>
#include <conio.h>
void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	setfillstyle(1,5);
	for(int i = 100;i<400;i+=50)
	{int pts[18]={i,i,i,i+16,i+10,i+24,i+30,i+24,i+20,i+16,i,i+16,i+20,i+16,i+20,i,i,i};
	fillpoly(9,pts);}
	getch();
}