


	  
	#ifndef __WINDOW_H
	#define __WINDOW_H
	
	#ifndef __GUI_H
	#include <gui.h>
	#endif //__GUI_H

	
	
  class Window
  {

	private:
	
	int Left,Top,Width,Height;
	char Caption[50];
	Button *CloseBtn;
	void SSLogo();
	public:
	
	Window(int left, int top, int width, int height, char caption[]);
	void Draw();
	void EnableClickHandler();	
  }; 	
      
  #endif //__WINDOW_H  			


















	

 
