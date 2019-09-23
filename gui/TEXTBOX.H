


	  
	#ifndef __TEXTBOX_H
	#define __TEXTBOX_H
	
	#ifndef __GUI_H
	#include <gui.h>
	#endif //__GUI_H

	


  class TextBox
  {

	private:


	int Alignment;
  	bool bReadOnly;
    bool Hide;
	int Left,Top,Width,Height,ID;
	char Caption[50];
	char HiddenText[50];
	
	void MouseDown();

	public:
	
	TextBox(int left, int top, int width, int height, char caption[],int Align,int Id);
	void Draw();
	void EnableClickHandler();
	void SetReadOnly(bool ReadOnly);
	void HideText(bool Hide);
	void SetText(char text[]);
	char *GetText();
	void Clear();
  }; 	
      
  #endif //__TEXTBOX_H  			


















	

 
