#include<graphics.h>
#include<conio.h>
void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	setfillstyle(1,7);
	int i=100;
	for(int j = 100;j<400;j+=50)
	{int pts[18]={i+j,i,i+j,i+16,i+10+j,i+24,i+30+j,i+24,i+20+j,i+16,i+j,i+16,i+20+j,i+16,i+20+j,i,i+j,i};
	fillpoly(9,pts);}
	getch();
}
