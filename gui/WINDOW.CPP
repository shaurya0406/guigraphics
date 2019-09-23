


	  
	#ifndef __WINDOW_CPP
	#define __WINDOW_CPP

	#include <window.h>
	#include <graphics.h>
	#include <stdlib.h>

Window::Window(int left, int top, int width, int height, char caption[])
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		WindowLeft=Left;
		WindowTop=Top;
		WindowWidth=Width;
		strcpy(Caption,caption);
	}
	void Window::SSLogo()
	{
		setcolor(3);
		setfillstyle(SOLID_FILL,3);
		fillellipse(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-1,TITLEBARHEIGHT/2-1);
		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		circle(Left+(BORDERWIDTH)+TITLEBARHEIGHT/2,Top+TITLEBARHEIGHT/2,TITLEBARHEIGHT/2-3);
		settextstyle(SMALL_FONT,0,0);
		outtextxy(Left+6,Top+4,"SS");
		settextstyle(0,0,0);
	}
	void Window::Draw()
	{
	
		setfillstyle(SOLID_FILL,RED);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(WHITE);
		line(Left,Top,Left+Width,Top);
		line(Left,Top,Left,Top+Height);

		setcolor(BLACK);
		line(Left,Top+Height,Left+Width,Top+Height);
		line(Left+Width,Top,Left+Width,Top+Height);

		setfillstyle(SOLID_FILL,BLUE);
		bar(Left+BORDERWIDTH,Top+BORDERWIDTH,
		Left+Width-(BORDERWIDTH*2),Top+TITLEBARHEIGHT);

		setcolor(WHITE);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
		CloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9809);
		CloseBtn->Draw();

		SSLogo();
	
	}
	void Window::EnableClickHandler()
	{
		CloseBtn->EnableClickHandler();
		if (ButtonId == 9809)
		exit(0);
		
	}
      
  #endif //__WINDOW_CPP  			


















	

 
