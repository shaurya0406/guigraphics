#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <dos.h>

// Message Box Buttons Type
#define jcOKOnly 		1
#define jcOKCancel 		2
#define jcAbortRetryIgnore 	3
#define jcYesNoCancel 		4
#define jcYesNo 		5
#define jcRetryCancel 		6

// Icons
#define jcCritical			16
#define jcQuestion			32
#define jcExclamation		48
#define jcInformation       64
#define jcAbout             80
#define jcNone				90

//Buttons
#define jcOK				8001
#define jcCancel			8002
#define jcAbort             8003
#define jcRetry             8004
#define jcIgnore            8005
#define jcYes               8006
#define jcNo                8009


		#define MAX_WORD_IN_LINE      30

		#define TITLEBARHEIGHT		  21
		#define BORDERWIDTH			  1
		#define MSGBTNDEFAULTWIDTH    60
		#define MSGBTNDEFAULTHEIGHT   25
		#define MSGBOXDEFAULTWIDTH	  80
		#define MSGBOXDEFAULTHEIGHT   80
		#define ICONWIDTH			  20
		#define ICONHEIGHT            20

		int ButtonId;
		int LabelId;
		int MenuId;
		int MenuItemId;
		int TextBoxId;
		int RadioButtonId;
		int PictureBoxId;
		int WindowLeft;
		int WindowTop;
		int WindowWidth;
		int NumberOfMenus=-1;
		int MenuWidth[70];
		enum bool{false,true};
		enum BUTTON{MOUSE_NORMAL = 0,MOUSE_LBUTTON=1,MOUSE_RBUTTON=2,MOUSE_MBUTTON=4};
		bool IsComboClick = false;
		bool IsMenuClick = false;
		bool IsMenuBarCreated=false;

		/* buffer area used for storing portion of images temporarily */
		/* the address 0xa000a000l represents the starting of second  */

			//char far *buffer=(char far *)0xa000a000l;
			void far *buffer=(void far *)0xa000a000l;
class Mouse

	{


		private:

			int MouseXpos, MouseYpos;
			BUTTON MouseBtn;
			union REGS in,out;

		public:

			int InstallMouse();
			int ShowMouse();
			int HideMouse();
			void GetMouseStatus();
			BUTTON GetButton();
			int GetPosX();
			int GetPosY();
			void SetMousePosi(int &xpos, int &ypos);
			int MouseInside(int x1, int y1, int x2, int y2);
			void RestrictMousePtr(int x1, int y1, int x2, int y2);

	};

  int Mouse::InstallMouse()
	{

		in.x.ax = 0;
		int86(51,&in,&out);
		return out.x.ax;

	}
	int Mouse::ShowMouse()
	{

		in.x.ax = 1;
		int86(51,&in,&out);
		return 1;

	}
	int Mouse::HideMouse()
	{

		in.x.ax = 2;
		int86(51,&in,&out);
		return 1;

	}
	void Mouse::GetMouseStatus()
	{

		in.x.ax = 3;
		int86(51,&in,&out);
		MouseXpos = out.x.cx;
		MouseYpos = out.x.dx;
		MouseBtn = out.x.bx;

	}
	BUTTON Mouse::GetButton()
	{
		return MouseBtn;
	}

	int Mouse::GetPosX()
	{
		return MouseXpos;
	}

	int Mouse::GetPosY()
	{
		return MouseYpos;
	}

	void Mouse::SetMousePosi(int &xpos, int &ypos)
	{
		in.x.ax = 4;
		in.x.cx = xpos;
		in.x.dx = ypos;
		int86(51,&in,&out);
	}
	int Mouse::MouseInside(int x1, int y1, int x2, int y2)
	{
		int x_pos, y_pos;
		in.x.ax = 3;
		int86(51,&in,&out);
		x_pos = out.x.cx;
		y_pos = out.x.dx;

		if(x_pos >= x1 && y_pos >= y1 && x_pos <= x2 && y_pos <= y2)
			return 1;
		else
			return 0;

	}
	void Mouse::RestrictMousePtr(int x1, int y1, int x2, int y2)
	{

		in.x.ax = 7;
		in.x.cx = x1;
		in.x.dx = x2;
		int86(51,&in,&out);

		in.x.ax = 8;
		in.x.cx = y1;
		in.x.dx = y2;
		int86(51,&in,&out);

	}
	Mouse mouse;

enum BUTTON_STATUS
	{
		 BUTTON_STATUS_NORMAL,
		 BUTTON_STATUS_DOWN
	};


  class Button
  {

	private:

	int Left,Top,Width,Height,ID;
	char Caption[50];
	BUTTON_STATUS btnStatus;
	void MouseDown();
	void MouseUp();
	bool State;

	public:
	
	Button(int left, int top, int width, int height, char caption[], int Id);
	void Draw();
	void EnableClickHandler();	
	
  }; 	
    Button::Button(int left, int top, int width, int height, char caption[], int Id)
    {
	Left = left;
	Top = top;
	Width = width;
	Height = height;
	strcpy(Caption,caption);
	ID = Id;
	btnStatus = BUTTON_STATUS_NORMAL;
	State = false;
    }				


    void Button::Draw()
   {
	setfillstyle(SOLID_FILL,BLACK);
	bar(Left,Top,Left+Width,Top+Height);

	setcolor(WHITE);
	line(Left,Top,Left+Width,Top);
	line(Left,Top,Left,Top+Height);

	setcolor(BLACK);
	line(Left+Width,Top,Left+Width,Top+Height);
	line(Left,Top+Height,Left+Width,Top+Height);

	settextjustify(LEFT_TEXT,TOP_TEXT);
	setcolor(YELLOW);
	outtextxy(Left + (Width/2) - textwidth(Caption)/2 + 1,
	Top + (Height/2) - textheight(Caption)/2 + 1, Caption);
	
	

   }

   void Button::MouseDown()
   {




				mouse.HideMouse();

				setcolor(BLACK);
				line(Left,Top,Left+Width,Top);
				line(Left,Top,Left,Top+Height);

				setcolor(WHITE);
				line(Left+Width,Top,Left+Width,Top+Height);
				line(Left,Top+Height,Left+Width,Top+Height);

				mouse.ShowMouse();




   }

   void Button::MouseUp()
   {



					mouse.HideMouse();

					setcolor(WHITE);
					line(Left,Top,Left+Width,Top);
					line(Left,Top,Left,Top+Height);

					setcolor(BLACK);
					line(Left+Width,Top,Left+Width,Top+Height);
					line(Left,Top+Height,Left+Width,Top+Height);

					mouse.ShowMouse();






   }


   void Button::EnableClickHandler()
   {

		if(IsComboClick || IsMenuClick)return;

		if(State)
		{
			ButtonId = 0;
			State = false;
			return;
		}
	
		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				MouseDown();
				btnStatus = BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL) 
			{
				MouseUp();
				ButtonId = ID;
				btnStatus = BUTTON_STATUS_NORMAL;
				State = true;
				
			}

		}

	}

	
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
       TextBox::TextBox(int left, int top, int width, int height, char caption[],int Align,int Id)
    {
	Left = left;
	Top = top;
	Width = width;
	Height = height;
	strcpy(Caption,caption);
	ID = Id;
	Alignment = Align;
	bReadOnly = false;
	int i;
	    for(i=0;i<strlen(Caption);i++)
		HiddenText[i] = '*';
	    HiddenText[i]=0;
    }				


    void TextBox::Draw()
   {
   	    
		setfillstyle(SOLID_FILL,BLACK);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(DARKGRAY);
		rectangle(Left,Top,Left+Width,Top+Height);

		setcolor(RED);

		settextjustify(Alignment,TOP_TEXT);
		if(Alignment==LEFT_TEXT)
			{
				if(Hide == true){
                   
                   outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),HiddenText);
				}	
				else{outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);}
			}
		else
			if(Alignment==RIGHT_TEXT)
				if(Hide==true){
                   
                   outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),HiddenText);
				}
				else{outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);}
		else
			if(Hide==true){
                   
                   outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),HiddenText);
			}
			else{outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),Caption);}
			
	
   }

   void TextBox::MouseDown()
   {
		
		if(bReadOnly) return; 

		int ch;
		int len=strlen(Caption),curpos,curx;
		

		mouse.HideMouse();
		curpos=len;
		do{
			curx=Left+textwidth(Caption)+1;

			if(!kbhit())
			{
				setwritemode(XOR_PUT);
				setcolor(WHITE);
				line(curx,Top+2,curx,Top+Height-2);
				do{
					line(curx,Top+2,curx,Top+Height-2);
					delay(100);
				  }while(!kbhit());
					setwritemode(COPY_PUT);
			}


			ch=getch();
			if(ch==0) ch=getch();
			switch (ch)
			{
				case 8: 
					if(len>0)
					{
						Caption[curpos-1]=0;
						HiddenText[curpos-1]=0;						
						curpos--;
						len--;
					}
			    break;
			}
			if(isprint(ch))
			{
				Caption[curpos]=ch;
				HiddenText[curpos]='*';
				Caption[curpos+1]=0;
				HiddenText[curpos+1]=0;
				if(Left+textwidth(Caption)>Left+Width)
				{
					Caption[curpos]=0;
					HiddenText[curpos]=0;
					Draw();
					break;
				}
				else
				{
					curpos++;
					len++;
				}
			}

				Draw();
		}while(ch!=13 && ch!=27);
		mouse.ShowMouse();

		}
		
	void TextBox::SetReadOnly(bool ReadOnly)
	{
		bReadOnly = ReadOnly;
	}
	void TextBox::HideText(bool hide)
	{
		Hide = hide;
	}
	void TextBox::SetText(char text[])
	{
		if (Left + textwidth(Caption) <= Left + Width - textwidth(" "))
		{
			strcat(Caption,text);
			Draw();
		}
	}

	char *TextBox::GetText()
	{
		return Caption;
	}
	
	void TextBox::Clear()
	{
		strcpy(Caption,"");
		strcpy(HiddenText,"");
		Draw();
	}

   void TextBox::EnableClickHandler()
   {
	if(IsComboClick || IsMenuClick)return;
		
		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				Clear();
				MouseDown();
				TextBoxId = ID;
			}
		}
 
   }
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
	#define CHECK_BOX_HEIGHT 10
	#define CHECK_BOX_WIDTH 10

   enum CHECKBOX_STATUS
	{
		 CHECKBOX_STATUS_NORMAL,
		 CHECKBOX_STATUS_DOWN
	};

  class CheckBox
  {

	private:

	int Left,Top,Width,Height;
	char Caption[50];
	int Alignment;
	CHECKBOX_STATUS chkStatus;
	bool State;
	bool hide;
	
	public:
	
	CheckBox(int left, int top, int width, int height, char caption[], int Align, bool state);
	void Draw();
	void EnableClickHandler();	
	bool IsChecked();
	void Checked();
	void UnChecked();
	void Hide();
	void Show();
	void SetText(char text[]);
	char *GetText();
	void Clear();
  }; 	
   CheckBox::CheckBox(int left, int top, int width, int height, char caption[],int Align, bool state)
    {
	 Left = left;
	 Top = top;
	 Width = width;
	 Height = height;
	 strcpy(Caption,caption);
	 Alignment = Align;
	 State = state;
	 hide = false;
	 chkStatus = CHECKBOX_STATUS_NORMAL;
    }				


    void CheckBox::Draw()
   {
	  int TopAlign = (Height/2) - (CHECK_BOX_HEIGHT/2);
	  int LeftAlign = 0;
	  
	  if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-CHECK_BOX_WIDTH;

	  setfillstyle(SOLID_FILL,LIGHTGRAY);
	  bar(Left,Top,Left+Width,Top+Height);

      setfillstyle(SOLID_FILL,WHITE);
      bar(Left+LeftAlign+1,Top+TopAlign+1,Left+LeftAlign+CHECK_BOX_WIDTH,Top+TopAlign+CHECK_BOX_HEIGHT);

      setcolor(DARKGRAY);
      line(Left+LeftAlign,Top+TopAlign,Left+LeftAlign+CHECK_BOX_WIDTH,Top+TopAlign);
      line(Left+LeftAlign,Top+TopAlign,Left+LeftAlign,Top+TopAlign+CHECK_BOX_HEIGHT);

      setcolor(BLACK);
      line(Left+LeftAlign+1,Top+TopAlign+1,Left+LeftAlign+(CHECK_BOX_WIDTH-1),Top+TopAlign+1);
      line(Left+LeftAlign+1,Top+TopAlign+1,Left+LeftAlign+1,Top+TopAlign+(CHECK_BOX_HEIGHT-1));

      setcolor(LIGHTGRAY);
      line(Left+LeftAlign+(CHECK_BOX_WIDTH-1),Top+TopAlign+1,Left+LeftAlign+(CHECK_BOX_WIDTH-1),Top+TopAlign+(CHECK_BOX_HEIGHT-1));
      line(Left+LeftAlign+1,Top+TopAlign+(CHECK_BOX_HEIGHT-1),Left+LeftAlign+(CHECK_BOX_WIDTH-1),Top+TopAlign+(CHECK_BOX_HEIGHT-1));

      setcolor(WHITE);
      line(Left+LeftAlign,Top+TopAlign+CHECK_BOX_HEIGHT,Left+LeftAlign+CHECK_BOX_WIDTH,Top+TopAlign+CHECK_BOX_HEIGHT);
      line(Left+LeftAlign+CHECK_BOX_WIDTH,Top+TopAlign,Left+LeftAlign+CHECK_BOX_WIDTH,Top+TopAlign+CHECK_BOX_HEIGHT);

      setcolor(BLACK);
      if(Alignment==LEFT_TEXT)
      {
        settextjustify(LEFT_TEXT,CENTER_TEXT);
        outtextxy(Left+CHECK_BOX_WIDTH+3,Top+(Height/2)+1,Caption);
      }
     else
     {

	settextjustify(RIGHT_TEXT,CENTER_TEXT);
	outtextxy(Left+Width-(CHECK_BOX_WIDTH+3),Top+(Height/2)+1,Caption);
      }


	  if(State)
	  {
		setlinestyle(SOLID_LINE,0,3);
		setcolor(BLACK);
		line(Left+LeftAlign+2,Top+TopAlign+2,Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+(CHECK_BOX_HEIGHT-2));
		line(Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+2,Left+LeftAlign+2,Top+TopAlign+(CHECK_BOX_HEIGHT-2));
		setlinestyle(SOLID_LINE,0,1);
	  }


   }

   void CheckBox::Checked()
   {

       int TopAlign = (Height/2) - (CHECK_BOX_HEIGHT/2);
	   int LeftAlign = 0;
	   
	   if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-CHECK_BOX_WIDTH;
	   
		if (hide) return;
		
	    setlinestyle(SOLID_LINE,0,3);
		setcolor(BLACK);
		line(Left+LeftAlign+2,Top+TopAlign+2,Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+(CHECK_BOX_HEIGHT-2));
		line(Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+2,Left+LeftAlign+2,Top+TopAlign+(CHECK_BOX_HEIGHT-2));
		setlinestyle(SOLID_LINE,0,1);

		State = true;

   }


    void CheckBox::UnChecked()
   {

	    int TopAlign = (Height/2) - (CHECK_BOX_HEIGHT/2);
	    int LeftAlign = 0;
		
		if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-CHECK_BOX_WIDTH;

		if (hide) return;

	    setfillstyle(SOLID_FILL,WHITE);
	    bar(Left+LeftAlign+2,Top+TopAlign+2,Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+(CHECK_BOX_HEIGHT-2));

		State = false;


   }


   void CheckBox::EnableClickHandler()
   {


	  if(IsComboClick || IsMenuClick)return;
	
	  int TopAlign = (Height/2) - (CHECK_BOX_HEIGHT/2);
	  int LeftAlign = 0;
	  
	  mouse.ShowMouse();

	  if(hide) return;

	  if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-CHECK_BOX_WIDTH;

		if(mouse.MouseInside(Left+LeftAlign+2,Top+TopAlign+2,Left+LeftAlign+(CHECK_BOX_WIDTH-2),Top+TopAlign+(CHECK_BOX_HEIGHT-2)) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
				   chkStatus = CHECKBOX_STATUS_DOWN;



			else if(mouse.GetButton() == MOUSE_NORMAL && chkStatus == CHECKBOX_STATUS_DOWN)
			{

			   if(!State)
			   {
			     mouse.HideMouse();
			     Checked();
			     mouse.ShowMouse();
			   }

			   else
			   {
			      mouse.HideMouse();
			      UnChecked();
			      mouse.ShowMouse();

			    }
				  chkStatus = CHECKBOX_STATUS_NORMAL;
			}

		}

	}

	bool CheckBox::IsChecked()
	{
		return State;
	}

	void CheckBox::Hide()
	{
		if(hide) return;
		hide = true;
		setfillstyle(SOLID_FILL,LIGHTGRAY);
		bar(Left,Top,Left+Width,Top+Height);
	}
	void CheckBox::Show()
	{
		if(!hide) return;
		hide = false;
		Draw();
	}
	
	void CheckBox::SetText(char text[])
	{
		
		strcpy(Caption,text);
		Draw();
		
	}

	char *CheckBox::GetText()
	{
		return Caption;
	}
	
	void CheckBox::Clear()
	{
		strcpy(Caption,"");
		Draw();
	}
	#define RADIO_BUTTON_RADIUS 8
	#define MOUSE_RADIUS 2

	
	
	enum RADIO_BUTTON_STATUS
	{
		 RADIO_BUTTON_STATUS_NORMAL,
		 RADIO_BUTTON_STATUS_DOWN
	};

  class RadioButton
  {

	private:

	int Left,Top,Width,Height,ID;
	char Caption[50];
	int Alignment;
	RADIO_BUTTON_STATUS radioBtnStatus;
	bool State;
	
	void Enable();
	void Disable();
	bool IsMouseInside(int R_Xpos,int R_Ypos,int M_Xpos,int M_Ypos);

	public:

	RadioButton(int left, int top, int width, int height, char caption[], int Align,int ID);
	void Draw();
	void EnableClickHandler();
	void EnableRadioButton();
	void DisableRadioButton();
	void SetText(char text[]);
	char *GetText();
	void Clear();
  };
   RadioButton::RadioButton(int left, int top, int width, int height, char caption[], int Align, int Id)
    {
	 Left = left;
	 Top = top;
	 Width = width;
	 Height = height;
	 strcpy(Caption,caption);
	 Alignment = Align;
	 ID = Id;
	 State = true;
	 radioBtnStatus = RADIO_BUTTON_STATUS_NORMAL;
    }


    void RadioButton::Draw()
   {

	  int LeftAlign = RADIO_BUTTON_RADIUS + 1;

	  if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-RADIO_BUTTON_RADIUS - 1;

	 setfillstyle(SOLID_FILL,LIGHTGRAY);
	 bar(Left,Top,Left+Width,Top+Height);

	 setfillstyle(SOLID_FILL,LIGHTGRAY);
	 setcolor(LIGHTGRAY);
	 circle(Left + LeftAlign,Top + (Height/2) + 1,RADIO_BUTTON_RADIUS);
	 floodfill(Left + LeftAlign,Top + (Height/2) + 1,LIGHTGRAY);

	 setcolor(DARKGRAY);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,0,180,RADIO_BUTTON_RADIUS);
	 setcolor(BLACK);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,0,180,RADIO_BUTTON_RADIUS-1);
	 setcolor(WHITE);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,180,0,RADIO_BUTTON_RADIUS);
	 setcolor(DARKGRAY);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,180,0,RADIO_BUTTON_RADIUS-1);


	 setcolor(BLACK);
    if(Alignment==LEFT_TEXT)
    {
	  settextjustify(LEFT_TEXT,CENTER_TEXT);
	  outtextxy(Left+(2*RADIO_BUTTON_RADIUS)+4,Top+(Height/2)+1,Caption);
    }
     else
     {

	   settextjustify(RIGHT_TEXT,CENTER_TEXT);
	    outtextxy(Left+(Width)-((2*RADIO_BUTTON_RADIUS)+3),Top+(Height/2)+1,Caption);
      }


	  if(State)
	  {
		setfillstyle(SOLID_FILL,WHITE);
		setcolor(DARKGRAY);
		circle(Left+LeftAlign,Top+(Height/2)+1,RADIO_BUTTON_RADIUS/2);
		floodfill(Left+LeftAlign,Top+(Height/2)+1,DARKGRAY);

		RadioButtonId = ID;
	  }


   }

   void RadioButton::Enable()
   {


		int LeftAlign = RADIO_BUTTON_RADIUS + 1;

		if(Alignment==RIGHT_TEXT)
		    LeftAlign=Width-RADIO_BUTTON_RADIUS - 1;

		mouse.HideMouse();

		setfillstyle(SOLID_FILL,WHITE);
		setcolor(DARKGRAY);
		circle(Left+LeftAlign,Top+(Height/2)+1,RADIO_BUTTON_RADIUS/2);
		floodfill(Left+LeftAlign,Top+(Height/2)+1,DARKGRAY);

		RadioButtonId = ID;

		mouse.ShowMouse();
   }


    void RadioButton::Disable()
   {

	int LeftAlign = RADIO_BUTTON_RADIUS + 1;

		if(Alignment==RIGHT_TEXT)
		    LeftAlign=Width-RADIO_BUTTON_RADIUS - 1;


	      //	mouse.HideMouse();

	 setfillstyle(SOLID_FILL,LIGHTGRAY);
	 setcolor(LIGHTGRAY);
	 circle(Left + LeftAlign,Top + (Height/2) + 1,RADIO_BUTTON_RADIUS);
	 floodfill(Left + LeftAlign,Top + (Height/2) + 1,LIGHTGRAY);

	 setcolor(DARKGRAY);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,0,180,RADIO_BUTTON_RADIUS);
	 setcolor(BLACK);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,0,180,RADIO_BUTTON_RADIUS-1);
	 setcolor(WHITE);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,180,0,RADIO_BUTTON_RADIUS);
	 setcolor(DARKGRAY);
	 arc(Left + LeftAlign,Top + (Height/2) + 1,180,0,RADIO_BUTTON_RADIUS-1);


	      //	mouse.ShowMouse();
   }


   bool RadioButton::IsMouseInside(int R_Xpos,int R_Ypos,int M_Xpos,int M_Ypos)
   {
	   double dx,dy;
	   double dist;

	   dx = M_Xpos - R_Xpos;
	   dy = M_Ypos - R_Ypos;

	   dist = sqrt(dx*dx + dy*dy);

	   return (dist < (RADIO_BUTTON_RADIUS + MOUSE_RADIUS));

   }


   void RadioButton::EnableRadioButton()
   {
		RadioButtonId = ID;
   }

   void RadioButton::DisableRadioButton()
   {
		RadioButtonId = 0;
   }


   void RadioButton::EnableClickHandler()
   {

	if(IsComboClick || IsMenuClick)return;

	int LeftAlign = RADIO_BUTTON_RADIUS + 1;

	  if(Alignment==RIGHT_TEXT)
		LeftAlign=Width-RADIO_BUTTON_RADIUS - 1;

		if(RadioButtonId != ID )
		 Disable();







		if(IsMouseInside(Left + LeftAlign,Top + (Height/2) + 1,mouse.GetPosX(),mouse.GetPosY()))
		{

			   if(mouse.GetButton() == MOUSE_LBUTTON)
				   radioBtnStatus = RADIO_BUTTON_STATUS_DOWN;



			else if(mouse.GetButton() == MOUSE_NORMAL && radioBtnStatus == RADIO_BUTTON_STATUS_DOWN)
			{
				 Enable();
				 radioBtnStatus = RADIO_BUTTON_STATUS_NORMAL;

			}




		}




	}

	void RadioButton::SetText(char text[])
	{

		strcpy(Caption,text);
		Draw();

	}

	char *RadioButton::GetText()
	{
		return Caption;
	}

	void RadioButton::Clear()
	{
		strcpy(Caption,"");
		Draw();
	}

	
	enum LABEL_BUTTON_STATUS
	{
		 LABEL_BUTTON_STATUS_NORMAL,
		 LABEL_BUTTON_STATUS_DOWN
	};	

	
	
  class Label
  {

	private:
	
	int Left,Top,Width,Height;
	char Caption[50];
	int Bgcolor,Fgcolor,ID;
	int Alignment;
	bool State;
	bool Click;
	LABEL_BUTTON_STATUS btnStatus;
	
	public:
	
	Label(int left, int top, int width, int height, char caption[], int Align, int bgcolor , int fgcolor, int Id );
	void Draw();
	void EnableClickHandler(int bgcolor1 ,int fgcolor1 , int bgcolor2 , int fgcolor2 );	
	void SetText(char text[]);
	char *GetText();
	void Clear();
	
  }; 	
  Label::Label(int left, int top, int width, int height, char caption[], int Align, int bgcolor = LIGHTGRAY, int fgcolor = BLACK, int Id = 0)
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		strcpy(Caption,caption);
		Bgcolor = bgcolor;
		Fgcolor = fgcolor;
		State = false;
		Click = false;
		Alignment = Align;
		ID = Id;
		
	}
	void Label::Draw()
	{
	
		setfillstyle(SOLID_FILL,Bgcolor);
		bar(Left,Top,Left+Width,Top+Height);

		setcolor(Fgcolor);

		settextjustify(Alignment,TOP_TEXT);
		settextstyle(SMALL_FONT,0,0);
		if(Alignment==LEFT_TEXT)
			outtextxy(Left+2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			if(Alignment==RIGHT_TEXT)
				outtextxy(Left+Width-2,Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		else
			outtextxy(Left+(Width/2),Top+1+((Height/2)-(textheight(Caption)/2)),Caption);
		
		settextstyle(0,0,0);
	
	}
	
	void Label::EnableClickHandler(int bgcolor1 = LIGHTGRAY,int fgcolor1 = BLACK, int bgcolor2 = LIGHTGRAY, int fgcolor2 = BLACK)
	{

		
	
		if(Click)
		{
			LabelId = 0;
			Click = false;
			return;
		}
		

		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height)==1)
		{
			if(!State)
			{

		   Bgcolor = bgcolor1;
		   Fgcolor = fgcolor1;
		   State = true;
		   mouse.HideMouse();
		   Draw();
		   mouse.ShowMouse();
		   
		   }


			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = LABEL_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == LABEL_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL) 
			{
				
				LabelId = ID;
				btnStatus = LABEL_BUTTON_STATUS_NORMAL;
				Click = true;
				
			}



		}
		else
		{
		     if(!State)
			return;
		     Bgcolor = bgcolor2;
		     Fgcolor = fgcolor2;
		      State = false;
		      mouse.HideMouse();
		      Draw();
		      mouse.ShowMouse();
		}

	}
	
	
	void Label::SetText(char text[])
	{
		
		strcpy(Caption,text);
		Draw();
		
	}

	char *Label::GetText()
	{
		return Caption;
	}
	
	void Label::Clear()
	{
		strcpy(Caption,"");
		Draw();
	}
	#define PALETTE_INDEX       0x03c8
 #define PALETTE_DATA        0x03c9
 
 typedef unsigned char BYTE;
 typedef unsigned int WORD;
 typedef unsigned long DWORD;
 typedef signed long LONG;

 BYTE Palette_Data[256*3];
 void *buff; 	
 
 
 class Bitmap
 {
 
	private:
	
	int Left,Top,Width,Height;
	char bmpfile[35];
	void LoadBitmap();
	bool ImgType();
	public:
	void DrawBitmap(int left, int top, int value);
	Bitmap(int left, int top, int width, int height, char file[35]);
	void SetPalette();
	void RotatePalette();
	void FreeBlock();
 };
 Bitmap::Bitmap(int left, int top, int width, int height, char file[35])
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		strcpy(bmpfile,file);
		LoadBitmap();
	}
	
	
	bool Bitmap::ImgType()
	{
		WORD type;
		fstream file;
		file.open(bmpfile,ios::in|ios::binary);
		file.read((char *) &type,sizeof(WORD));
		file.close();
		if(type == 19778) 
		return true;
		else
		return false;
	}
	
	
	void Bitmap::LoadBitmap()
	{
		fstream bitmap_file;

		/*****************************************************/
		
		DWORD index;
		BYTE ch,str;
		BYTE rgbquad[4];
		
		int Xpos = Left;
		int Ypos = Top;
		
		/*****************************************************/

		/* Open bitmap file. */

		bitmap_file.open(bmpfile,ios::in|ios::binary);

		if(!bitmap_file)
		{
			cout<<"Error opening file "<<bmpfile;
			exit(1);
		}
		
		/* check to see if it is a valid bitmap file */

		if(ImgType() == false)
		{
			bitmap_file.close();
			cout<<bmpfile<<" is not a bitmap file.";
			exit(1);
		}
		
		/* Skip Header */
		
		bitmap_file.seekg(54,ios::beg);
		
		/* Read the palette information. */
		
		for(index = 0;index < 256;index++)
		{
			bitmap_file.read((char *) &rgbquad,4);
			
			Palette_Data[(int)index*3+2] = rgbquad[0];
			Palette_Data[(int)index*3+1] = rgbquad[1];
			Palette_Data[(int)index*3+0] = rgbquad[2];
		}
		
		
		/* Draw Bitmap */

		for(int i=0;i<Height;i++)
		{
			for(int j=0;j<Width;j++)
			{
				bitmap_file.read((char *) &ch,1);
				putpixel(Xpos+j,Ypos+Height-1-i,(int)ch);
			}
		}

		buff = malloc(imagesize(Left,Top,Left+Width,Top+Height));
		getimage(Left,Top,Left+Width,Top+Height,buff);
		
		bitmap_file.close();

	}

	
	void Bitmap::DrawBitmap(int left, int top, int value)
	{
		putimage(left,top,buff,value);	
	}
	
	void Bitmap::SetPalette()
	{
		int i;

		outp(PALETTE_INDEX,0);              /* tell the VGA that palette data
                                         is coming. */
		for(i=0;i<256*3;i++)
			outp(PALETTE_DATA,Palette_Data[i]);    /* write the data */
	}

        void Bitmap::RotatePalette()
	{
		int i,red,green,blue;

		red  = Palette_Data[3];
		green= Palette_Data[4];
		blue = Palette_Data[5];

		for(i=3;i<256*3-3;i++)
			Palette_Data[i]=Palette_Data[i+3];

		Palette_Data[256*3-3]=red;
		Palette_Data[256*3-2]=green;
		Palette_Data[256*3-1]=blue;

		SetPalette();
	}
	
	void Bitmap::FreeBlock()
	{
		free(buff);
	}
	
	enum COMBO_BUTTON_STATUS
	{
		 COMBO_BUTTON_STATUS_NORMAL,
		 COMBO_BUTTON_STATUS_DOWN
	};



  class ComboBox
  {

	private:

	int Left,Top,Width,Height,Items;
	unsigned char Caption[250];
	char ComboText[50];
	char cap[50];
	bool bReadOnly;
	bool Click;
	COMBO_BUTTON_STATUS btnStatus;
	Label *pComboLabel[30];
	
	int _i, _j;
	
	
	TextBox *pComboTxt;

	
	void DrawItems();
	void HideItems();
	
	
	public:
	
	ComboBox(int left, int top, int width, int height, char *combotext,char *caption);
	void Draw();
	void EnableClickHandler();
	void SetText(char text[]);
	char *GetText();
	void Clear();
	void SetReadOnly(bool ReadOnly);
	void AddText(char text[]);
  }; 	

  ComboBox::ComboBox(int left, int top, int width, int height, char *combotext,char *caption)
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		Click = false;
		strcpy(Caption,caption);
		strcpy(ComboText,combotext);
		bReadOnly = false;
		btnStatus = COMBO_BUTTON_STATUS_NORMAL;
		_i = 0;
		_j = 0;
		
		while (_i < strlen(Caption))
		{
			if(Caption[_i] == 44)
			_j++;

			_i++;
		}

		if(_j > 0)	
		Items = _j+1;
		else
		{
			if(strlen(Caption) > 0)
			Items = 1;
			else
			Items = 0;
		}	
	}


	void ComboBox::Draw()
	{
		pComboTxt = new TextBox(Left, Top, Width, Height, ComboText,LEFT_TEXT, 9809);
		pComboTxt->Draw();

		setfillstyle(SOLID_FILL,WHITE);
		bar(Left+Width,Top,Left+Width+12,Top+Height);
		setcolor(DARKGRAY);
		rectangle(Left+Width,Top,Left+Width+12,Top+Height);
		setcolor(WHITE);
		line(Left+Width,Top+1,Left+Width,Top+Height-1);

		
		setcolor(BLACK);
		outtextxy(Left+Width+2,Top+(Height/2)-(textheight("")/2)+1,"");
		
	}
	

	void ComboBox::DrawItems()
	{

		if(Items == 0)return;
		
		int l=0,m=0;
		int i=0;
		int x = Left, y = Top+Height;


		while(l < strlen(Caption))
		{
			if(Caption[l] == 44)
			{
				pComboLabel[i] = new Label(x,y+1,Width+12,Height,cap,CENTER_TEXT,WHITE,BLACK,i+1);
				pComboLabel[i]->Draw();
				for(int s=0; s<=m; s++)
				cap[s] = 0;
				m=0;
				l++;
				i++;
				y += Height;
			}

			cap[m] = Caption[l];

			l++;
			m++;
		}
		pComboLabel[i] = new Label(x,y+1,Width+12,Height,cap,CENTER_TEXT,WHITE,BLACK,i+1);
		pComboLabel[i]->Draw();

	}


	void ComboBox::HideItems()
	{
	    if(Items == 0)return;
		int i=0;
		
		do {
		
			delete pComboLabel[i];
			
			i++;
			
		}while(i < Items);
				
	}
	
	void ComboBox::AddText(char text[])
	{
	
		int i = 0;
		int j = 0;
		
		while (i < strlen(text))
		{
			if(text[i] == 44)
			j++;

			i++;
		}
	
		if(Items > 0 && strlen(text) > 0)
		{
			strcat(Caption,",");
			strcat(Caption,text);
		}
		else if(Items == 0 && strlen(text) > 0)
		strcpy(Caption,text);

		if(j > 0)
		Items += j+1;
		else
		{
			if(strlen(text) > 0)
			Items += 1;
			else
			{
			}

		}	
		
		
	}
	
	void ComboBox::SetText(char text[])
	{
		pComboTxt->Clear();
		pComboTxt->SetText(text);
	}
	char *ComboBox::GetText()
	{
		return pComboTxt->GetText();
	}
	void ComboBox::Clear()
	{
		pComboTxt->Clear();
	}
	void ComboBox::SetReadOnly(bool ReadOnly)
	{
		bReadOnly = ReadOnly;
	}
	void ComboBox::EnableClickHandler()
	{
		if(IsMenuClick)return;

		if(!bReadOnly)
		{
		  pComboTxt->EnableClickHandler();
		  setcolor(WHITE);
		  line(Left+Width,Top+1,Left+Width,Top+Height-1);
		}


		if(mouse.MouseInside(Left+Width,Top,Left+Width+12,Top+Height) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = COMBO_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == COMBO_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL && Click == false && IsComboClick == false)
			{
					btnStatus = COMBO_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					getimage(Left,Top+Height,Left+Width+12,Top+1+(Items+1)*Height,buffer);
					DrawItems();
					mouse.ShowMouse();
					Click = true;
					IsComboClick = true;


			}

			else if(btnStatus == COMBO_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL && Click == true)
			{
					btnStatus = COMBO_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					HideItems();
					flushall();
					putimage(Left,Top+Height,buffer,COPY_PUT);
					mouse.ShowMouse();
					Click = false;
					IsComboClick = false;

			}
		}

		if(mouse.MouseInside(Left+Width,Top,Left+Width+12,Top+Height) != 1 && mouse.MouseInside(Left,Top+Height,Left+Width+12,Top+1+(Items+1)*Height) != 1 && Click == true && IsComboClick == true)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = COMBO_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == COMBO_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL )
			{
					
					btnStatus = COMBO_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					HideItems();
					flushall();
					putimage(Left,Top+Height,buffer,COPY_PUT);
					mouse.ShowMouse();
					Click = false;
					IsComboClick = false;

			}
        }
		
		
				if(Click)
				{
						for(int i=0;i<Items;i++)
							pComboLabel[i]->EnableClickHandler(CYAN,BLACK,WHITE,BLACK);

						if(LabelId !=0)
						{

							pComboTxt->Clear();
							pComboTxt->SetText(pComboLabel[LabelId-1]->GetText());
							mouse.HideMouse();
							HideItems();
							flushall();
							putimage(Left,Top+Height,buffer,COPY_PUT);
							mouse.ShowMouse();
							Click = false;
							IsComboClick = false;
							LabelId = 0;



						}


				}

	}
	enum MENU_BUTTON_STATUS
	{
		 MENU_BUTTON_STATUS_NORMAL,
		 MENU_BUTTON_STATUS_DOWN
	};


  class Menu
  {

	private:

	int Left,Top,Width,Height,Items,MenuItemWidth;
	int ID;
	long int totalWidth,maxWidth;
	unsigned char Caption[250];
	char MenuText[50];
	char cap[50];
	bool Click;
	bool State;
	bool IsMousePointerInside;
	MENU_BUTTON_STATUS btnStatus;
	Label *pMenuButton[30];
	Label *pMenu;
	
	int _i, _j;
	

	
	void DrawItems();
	void HideItems();
	void MouseDown();
	void MouseUp();
	
	
	public:
	
	Menu(char *menutext,char *caption);
	void Draw();
	void EnableClickHandler();
  }; 	
  

	Menu::Menu(char *menutext,char *caption)
	{
		ID = NumberOfMenus+2;
		Click = false;
		State=false;
		totalWidth=0;
		maxWidth=0;
		IsMousePointerInside=false;
		strcpy(Caption,caption);
		strcpy(MenuText,menutext);
		NumberOfMenus++;
		
		settextstyle(SMALL_FONT,0,0);
		
		MenuWidth[NumberOfMenus]=textwidth(MenuText)+2;
		Width = textwidth(MenuText)+3;
		btnStatus = MENU_BUTTON_STATUS_NORMAL;
		_i = 0;
		_j = 0;

		while (_i < strlen(Caption))
		{
			if(Caption[_i] == 44)
			_j++;

			_i++;
		}

		if(_j > 0)
		Items = _j+1;
		else
		{
			if(strlen(Caption) > 0)
			Items = 1;
			else
			Items = 0;
		}

		for(int w=0;w<NumberOfMenus;w++)
		{
			totalWidth+=MenuWidth[w];
		}

		
			Left = WindowLeft+totalWidth+1+NumberOfMenus*5;

		Top = WindowTop+TITLEBARHEIGHT+2;
		Height =TITLEBARHEIGHT;

		int maxlen=0;
		for(int mx=0;mx<strlen(Caption);mx++)
		{
			if(Caption[mx]==44)
			{
				if(maxlen>maxWidth)
					maxWidth=maxlen;
				maxlen=0;

			}
			maxlen++;
		}
		if(maxlen>maxWidth)
			maxWidth=maxlen;

		MenuItemWidth=textwidth(MenuText)+maxWidth*textwidth("H")+4;
		
		settextstyle(0,0,0);

	}


	void Menu::Draw()
	{

		if(IsMenuBarCreated==false)
		{
			setcolor(DARKGRAY);
			line(WindowLeft+2,WindowTop+2*Height+2,WindowLeft+WindowWidth-2,WindowTop+2*Height+2);
			setcolor(WHITE);
			line(WindowLeft+2,WindowTop+2*Height+3,WindowLeft+WindowWidth-2,WindowTop+2*Height+3);

			IsMenuBarCreated=true;
		}

		setfillstyle(SOLID_FILL,LIGHTGRAY);
		bar(Left+3,Top+1,Left+Width+1,Top+Height-2);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(SMALL_FONT,0,0);
		setcolor(BLACK);
		outtextxy(Left+5,Top+((Height/2)-(textheight(MenuText)/2))-2,MenuText);
		settextstyle(0,0,0);
	}
	
	void Menu::MouseDown()
   {
		mouse.HideMouse();
		setcolor(DARKGRAY);
		line(Left+3,Top+1,Left+Width+2,Top+1);
		line(Left+3,Top+1,Left+3,Top+Height-2);

		setcolor(WHITE);
		line(Left+Width+2,Top+1,Left+Width+2,Top+Height-2);
		line(Left+3,Top+Height-2,Left+Width+2,Top+Height-2);
		mouse.ShowMouse();

   }

   void Menu::MouseUp()
   {
		mouse.HideMouse();
		setcolor(LIGHTGRAY);
		line(Left+3,Top+1,Left+Width+2,Top+1);
		line(Left+3,Top+1,Left+3,Top+Height-2);

		line(Left+Width+2,Top+1,Left+Width+2,Top+Height-2);
		line(Left+3,Top+Height-2,Left+Width+2,Top+Height-2);
		mouse.ShowMouse();

   }
	

	void Menu::DrawItems()
	{

		if(Items == 0)return;
		
		int l=0,m=0;
		int i=0;
		int x = Left+7, y = Top+Height+7;
		
		setfillstyle(SOLID_FILL,LIGHTGRAY);
		bar(Left+3,Top+Height+3,Left+MenuItemWidth+22,Top+10+(Items+1)*Height);
		
		setcolor(WHITE);
		line(Left+3,Top+Height+3,Left+MenuItemWidth+22,Top+Height+3);
		line(Left+3,Top+Height+3,Left+3,Top+10+(Items+1)*Height);
		
		setcolor(BLACK);
		line(Left+MenuItemWidth+22,Top+Height+3,Left+MenuItemWidth+22,Top+10+(Items+1)*Height);
		line(Left+3,Top+10+(Items+1)*Height,Left+MenuItemWidth+22,Top+10+(Items+1)*Height);
		
		setcolor(DARKGRAY);
		line(Left+MenuItemWidth+22-1,Top+Height+3+1,Left+MenuItemWidth+22-1,Top+10+(Items+1)*Height-1);
		line(Left+3+1,Top+10+(Items+1)*Height-1,Left+MenuItemWidth+22-1,Top+10+(Items+1)*Height-1);
		
		setcolor(WHITE);
		line(Left+3+2,Top+Height+3+2,Left+MenuItemWidth+22-2,Top+Height+3+2);
		line(Left+3+2,Top+Height+3+2,Left+3+2,Top+10+(Items+1)*Height-2);


		while(l < strlen(Caption))
		{
			if(Caption[l] == 44)
			{
				
				pMenuButton[i] = new Label(x,y+1,MenuItemWidth+12,Height,cap,LEFT_TEXT,LIGHTGRAY,BLACK,i+1);
				pMenuButton[i]->Draw();
				for(int s=0; s<=m; s++)
				cap[s] = 0;
				m=0;
				l++;
				i++;
				y += Height;
			}

			cap[m] = Caption[l];

			l++;
			m++;
		}
		
		pMenuButton[i] = new Label(x,y+1,MenuItemWidth+12,Height,cap,LEFT_TEXT,LIGHTGRAY,BLACK,i+1);
		pMenuButton[i]->Draw();
		

	}


	void Menu::HideItems()
	{
	    if(Items == 0)return;
		int i=0;
		
		do {

			delete pMenuButton[i];

			i++;

		}while(i < Items);

	}


	void Menu::EnableClickHandler()
	{
		if(IsComboClick)return;

		if(State)
		{
			State=false;
			MenuId=0;
			MenuItemId=0;
			return;
		}


		if(mouse.MouseInside(Left+3,Top+1,Left+Width+1,Top+Height-2) == 1)
		{
			if(IsMousePointerInside==false)
			{
				MouseDown();
				IsMousePointerInside=true;
			}

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = MENU_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == MENU_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL && Click == false && IsMenuClick == false)
			{
					btnStatus = MENU_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					getimage(Left+3,Top+Height+3,Left+MenuItemWidth+22,Top+10+(Items+1)*Height,buffer);
					DrawItems();
					MouseDown();
					mouse.ShowMouse();
					Click = true;
					IsMenuClick = true;
					IsMousePointerInside=false;


			}

			else if(btnStatus == MENU_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL && Click == true)
			{
					btnStatus = MENU_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					HideItems();
					flushall();
					MouseDown();
					putimage(Left+3,Top+Height+3,buffer,COPY_PUT);
					mouse.ShowMouse();
					Click = false;
					IsMenuClick = false;
					MenuId=0;
					MenuItemId=0;

			}
		}

		else if(IsMousePointerInside && Click==false)
		{
			MouseUp();
			IsMousePointerInside=false;
		}
		if(mouse.MouseInside(Left+3,Top+1,Left+Width+1,Top+Height-2) != 1 && mouse.MouseInside(Left+7,Top+Height+7,Left+7+MenuItemWidth+13,Top+7+(Items+1)*Height) != 1 && Click == true && IsMenuClick == true)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				btnStatus = MENU_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == MENU_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL )
			{

					btnStatus = MENU_BUTTON_STATUS_NORMAL;
					mouse.HideMouse();
					HideItems();
					flushall();
					MouseUp();
					putimage(Left+3,Top+Height+3,buffer,COPY_PUT);
					mouse.ShowMouse();
					Click = false;
					IsMenuClick = false;
					MenuId=0;
					MenuItemId=0;

			}
	}


				if(Click)
				{
						for(int i=0;i<Items;i++)
							pMenuButton[i]->EnableClickHandler(CYAN,BLACK,LIGHTGRAY,BLACK);

						if(LabelId !=0)
						{
							mouse.HideMouse();
							HideItems();
							flushall();
							putimage(Left+3,Top+Height+3,buffer,COPY_PUT);
							mouse.ShowMouse();
							IsMenuClick = false;
							MenuItemId=LabelId;
							MenuId=ID;
							LabelId = 0;
							Click=false;
							State=true;

						}


				}

	}

enum PICTURE_BUTTON_STATUS
	{
		 PICTURE_BUTTON_STATUS_NORMAL,
		 PICTURE_BUTTON_STATUS_DOWN
	};	

  class PictureBox
  {

	private:

	int Left,Top,Width,Height,ID;
	char Path[70];
	Bitmap *pBitmap;
	PICTURE_BUTTON_STATUS btnStatus;
	void MouseDown();
	void MouseUp();
	bool State;

	void DrawFrame();
	public:
	
	PictureBox(int left, int top, int width, int height, char *path, int Id);
	void Draw();
	void EnableClickHandler();
	
  }; 	
  PictureBox::PictureBox(int left, int top, int width, int height, char *path, int Id)
	{
		Left = left;
		Top = top;
		Width = width;
		Height = height;
		strcpy(Path,path);
		ID = Id;
		btnStatus = BUTTON_STATUS_NORMAL;
		State = false;

		pBitmap = new Bitmap(Left,Top,Width,Height,Path);

	}

	void PictureBox::DrawFrame()
	{
		int left,top,width,height;
		left=Left-2;
		top=Top-2;
		width=Width+4;
		height=Height+4;

		setfillstyle(SOLID_FILL,WHITE);
		bar(left,top,left+width,top+height);


		setcolor(WHITE);
		line(left,top,left+width,top);
		line(left,top,left,top+height);

		setcolor(BLACK);
		line(left+width,top,left+width,top+height);
		line(left,top+height,left+width,top+height);

	}
	
	void PictureBox::MouseDown()
   {
	    int left,top,width,height;
	    left=Left-2;
		top=Top-2;
		width=Width+4;
		height=Height+4;

		mouse.HideMouse();

		setcolor(BLACK);
		line(left,top,left+width,top);
		line(left,top,left,top+height);

		setcolor(WHITE);
		line(left+width,top,left+width,top+height);
		line(left,top+height,left+width,top+height);

		mouse.ShowMouse();


   }

   void PictureBox::MouseUp()
   {
		int left,top,width,height;
	    left=Left-2;
		top=Top-2;
		width=Width+4;
		height=Height+4;
		
		mouse.HideMouse();

		setcolor(WHITE);
		line(left,top,left+width,top);
		line(left,top,left,top+height);

		setcolor(BLACK);
		line(left+width,top,left+width,top+height);
		line(left,top+height,left+width,top+height);

		mouse.ShowMouse();

   }

	void PictureBox::Draw()
	{
		DrawFrame();
		pBitmap->DrawBitmap(Left,Top,COPY_PUT);

	}
	
	void PictureBox::EnableClickHandler()
   {

		if(IsComboClick || IsMenuClick)return;

		if(State)
		{
			PictureBoxId = 0;
			State = false;
			return;
		}
	
		if(mouse.MouseInside(Left,Top,Left+Width,Top+Height) == 1)
		{

			if(mouse.GetButton() == MOUSE_LBUTTON)
			{
				MouseDown();
				btnStatus = PICTURE_BUTTON_STATUS_DOWN;
			}

			else if(btnStatus == PICTURE_BUTTON_STATUS_DOWN && mouse.GetButton() == MOUSE_NORMAL) 
			{
				MouseUp();
				PictureBoxId = ID;
				btnStatus = PICTURE_BUTTON_STATUS_NORMAL;
				State = true;
				
			}

		}

	}

	class MsgBox
  {

	private:
	
	int Left,Top,Width,Height;
	int MsgBtnType;
	int MsgIcon;
	char Caption[50];
	Button *MsgCloseBtn;
	Button *MsgBtn[3];
	TextBox *pInputBox;
	void SSLogo();
	void CriticalIcon(int left, int top);
	void QuestionIcon(int left, int top);			
	void ExclamationIcon(int left, int top);
	void InformationIcon(int left, int top);       
	void AboutIcon(int left, int top);
	int TotalLines(int x, int y, int width, char *str);
	void WriteMessage(int x, int y, int width, int fontColor, char *str);
	public:
	
	int MessageBox(int left, int top, char *title, char *msgtext, int fontColor, int btntype, int icon);
	char *InputBox(int left, int top, char *title, char *msgtext, int fontColor);
	
  }; 	
  void MsgBox::CriticalIcon(int left, int top)
	{
		setcolor(RED);
		setfillstyle(SOLID_FILL,RED);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		settextstyle(0,0,2);
		setcolor(WHITE);
		outtextxy(left+(ICONWIDTH/2)-6,top+2+((ICONHEIGHT/2)-(textheight("X")/2)),"X");
		settextstyle(0,0,0);
	}
	void MsgBox::QuestionIcon(int left, int top)
	{
		int utr[]={left+(ICONWIDTH)/2-3,top+ICONWIDTH+ICONWIDTH/2-5,   left+(ICONWIDTH)/2+5,top+ICONWIDTH+ICONWIDTH/2+2,    left+(ICONWIDTH)/2+3,top+ICONWIDTH+ICONWIDTH/2-5};
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		fillpoly(3,utr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(left+(ICONWIDTH/2)-5,top+2+((ICONHEIGHT/2)-(textheight("?")/2)),"?");
		settextstyle(0,0,0);
	}
	void MsgBox::ExclamationIcon(int left, int top)
	{
		setcolor(DARKGRAY);
		setfillstyle(SOLID_FILL,YELLOW);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);

		settextstyle(0,0,2);
		setcolor(BLACK);
		outtextxy(left+(ICONWIDTH/2)-5,top+2+((ICONHEIGHT/2)-(textheight("!")/2)),"!");
		settextstyle(0,0,0);

	}
	void MsgBox::InformationIcon(int left, int top)
	{
		int utr[]={left+(ICONWIDTH)/2-3,top+ICONWIDTH+ICONWIDTH/2-5,   left+(ICONWIDTH)/2+5,top+ICONWIDTH+ICONWIDTH/2+2,    left+(ICONWIDTH)/2+3,top+ICONWIDTH+ICONWIDTH/2-5};
		setcolor(WHITE);
		setfillstyle(SOLID_FILL,WHITE);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);
		fillpoly(3,utr);
		settextstyle(0,0,2);
		setcolor(BLUE);
		outtextxy(left+(ICONWIDTH/2)-7,top+2+((ICONHEIGHT/2)-(textheight("i")/2)),"i");
		settextstyle(0,0,0);
	}
	void MsgBox::AboutIcon(int left, int top)
	{

		setcolor(3);
		setfillstyle(SOLID_FILL,3);
		fillellipse(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-5,ICONHEIGHT-5);


		setcolor(15);
		setfillstyle(SOLID_FILL,15);
		circle(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-8);
		circle(left+(ICONWIDTH)/2,top+(ICONHEIGHT)/2,ICONWIDTH-9);
		settextstyle(0,0,0);
		outtextxy(left+(ICONWIDTH/2)-7,top+2+((ICONHEIGHT/2)-(textheight("SS")/2)),"SS");

	}

	int MsgBox::TotalLines(int x, int y, int width, char *str)
	{
		char text[2];
		int length,start;
		int X_Pos=x,Y_Pos=y,X_Init=X_Pos;
		int totalLines=1;

		  settextstyle(SMALL_FONT,0,0);

		  length=strlen(str)-1;

		  for(start=0;start<=length;start++)
		  {

			  if(str[start]=='\n'||X_Pos>x+width)
			  {
				Y_Pos+=2*textheight("A");
				X_Pos=X_Init;
				totalLines++;
			  }

			  sprintf(text,"%c",str[start]);
			  X_Pos+=textwidth(text);

		  }


		settextstyle(0,0,0);

		return totalLines;

	}

	void MsgBox::WriteMessage(int x, int y, int width, int fontColor, char *str)
	{
		char text[2];
		int length,start;
		int X_Pos=x,Y_Pos=y,X_Init=X_Pos;


		  settextstyle(SMALL_FONT,0,0);

		  length=strlen(str)-1;

		  for(start=0;start<=length;start++)
		  {

			  if(str[start]=='\n'||X_Pos>x+width)
			  {
				Y_Pos+=2*textheight("A");
				X_Pos=X_Init;
			  }

			  sprintf(text,"%c",str[start]);
			  setcolor(fontColor);
			  outtextxy(X_Pos,Y_Pos,text);
			  X_Pos+=textwidth(text);

		  }
		

		settextstyle(0,0,0);

		

	}

	void MsgBox::SSLogo()
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
	int MsgBox::MessageBox(int left=200, int top=200, char *title="Confirm", char *msgtext="Confirm", int fontColor=BLACK, int btntype=jcOKOnly , int icon=jcNone)
	{
		int mbId=0;
		int totalButtons=0;
		int maxMsgBoxWidth=0;
		int increaseWidth=0;

		Left=left;
		Top=top;
		Width=MSGBOXDEFAULTWIDTH;

		strcpy(Caption,title);
		MsgBtnType=btntype;
		MsgIcon=icon;
		
		settextstyle(SMALL_FONT,0,0);

		if(MsgBtnType==jcAbortRetryIgnore || MsgBtnType==jcYesNoCancel)
		{
			Width+=2*MSGBTNDEFAULTWIDTH+(MSGBTNDEFAULTWIDTH/2);
		}
		else if(MsgBtnType==jcOKCancel || MsgBtnType==jcYesNo || MsgBtnType==jcRetryCancel)
		{
			Width+=MSGBTNDEFAULTWIDTH+(MSGBTNDEFAULTWIDTH/2);
		}

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
		{
			Width+=2*ICONWIDTH;
			Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+2*ICONWIDTH, Top+2*TITLEBARHEIGHT, Width-10-2*ICONWIDTH, msgtext));
		}
		else
		{
			Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext));

		}

		settextstyle(0,0,0);
		if(Width<textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2))
		{
		   int diff;
		   diff= textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2)-Width;
		   Width+=diff+TITLEBARHEIGHT;

		}
		settextstyle(SMALL_FONT,0,0);
		///////////////////////////////////

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
			maxMsgBoxWidth=Width-20-2*ICONWIDTH;
		else
			maxMsgBoxWidth=Width-20;

		 
		if(maxMsgBoxWidth<strlen(msgtext)*textwidth("H"))
		{
			int totalWords=maxMsgBoxWidth/textwidth("H");
			int count=0;

			for(int i=totalWords;i<MAX_WORD_IN_LINE;i++)
			{
				if(maxMsgBoxWidth>=strlen(msgtext)*textwidth("H"))
					break;
				maxMsgBoxWidth+=textwidth("H");
				count++;
			}

			increaseWidth=count*textwidth("H");

		}

		Width+=increaseWidth;


		///////////////////////////////////

		mouse.HideMouse();

		getimage(Left,Top,Left+Width,Top+Height,buffer);

		setfillstyle(SOLID_FILL,LIGHTGRAY);
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
		
		settextstyle(0,0,0);
		setcolor(WHITE);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
		settextstyle(SMALL_FONT,0,0);
		//Icons

		if(MsgIcon==jcCritical)
			CriticalIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else if(MsgIcon==jcQuestion)
			QuestionIcon(Left+10,Top+2*TITLEBARHEIGHT-10);
		else if(MsgIcon==jcExclamation)
			ExclamationIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else if(MsgIcon==jcInformation)
			InformationIcon(Left+10,Top+2*TITLEBARHEIGHT-10);
		else if(MsgIcon==jcAbout)
			AboutIcon(Left+10,Top+2*TITLEBARHEIGHT);
		else
		{
		}



		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
		{

			WriteMessage(Left+2*ICONWIDTH+10, Top+2*TITLEBARHEIGHT, Width-20-2*ICONWIDTH, fontColor, msgtext);
		}
		else
		{
			WriteMessage(Left+10, Top+2*TITLEBARHEIGHT, Width-20, fontColor, msgtext);

		}


		MsgCloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9800);
		MsgCloseBtn->Draw();


		if(MsgBtnType == jcOKOnly)
		{
			MsgBtn[0]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();
			totalButtons=1;
		}
		else if(MsgBtnType == jcOKCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcYesNo)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Yes",jcYes);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"No",jcNo);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcRetryCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Retry",jcRetry);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[1]->Draw();
			totalButtons=2;
		}
		else if(MsgBtnType == jcYesNoCancel)
		{
			MsgBtn[0]= new Button(Left+Width/2-2*MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Yes",jcYes);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"No",jcNo);
			MsgBtn[1]->Draw();
			MsgBtn[2]= new Button(Left+Width/2+MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
			MsgBtn[2]->Draw();
			totalButtons=3;
		}
		else if(MsgBtnType == jcAbortRetryIgnore)
		{
			MsgBtn[0]= new Button(Left+Width/2-2*MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Abort",jcAbort);
			MsgBtn[0]->Draw();
			MsgBtn[1]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Retry",jcRetry);
			MsgBtn[1]->Draw();
			MsgBtn[2]= new Button(Left+Width/2+MSGBTNDEFAULTWIDTH,Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Ignore",jcIgnore);
			MsgBtn[2]->Draw();
			totalButtons=3;
		}
		else
		{
			MsgBtn[0]= new Button(Left+Width/2-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
			MsgBtn[0]->Draw();	
			totalButtons=1;
		}
		settextstyle(0,0,0);
		SSLogo();
		
		mouse.ShowMouse();

		while(1)
		{
			mouse.ShowMouse();
			mouse.GetMouseStatus();
			

			MsgCloseBtn->EnableClickHandler();
			for(int b=0;b<totalButtons;b++)
				MsgBtn[b]->EnableClickHandler();

			mbId=ButtonId;
			ButtonId=0;

			switch(mbId)
			{
				case 9800:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<totalButtons;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
				return 0;
				case jcOK:
				case jcCancel:
				case jcAbort:
				case jcRetry:
				case jcIgnore:
				case jcYes:
				case jcNo:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int k=0;k<totalButtons;k++)
						delete MsgBtn[k];
					delete MsgCloseBtn;
				return mbId;

			}

			while(kbhit()){
				int ch = getch();
				if (ch == 27)  //ESC key pressed
				{
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<totalButtons;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					return 0;
				}
			}
		}

	}
	
	
	
	char * MsgBox::InputBox(int left=200, int top=200, char *title="Input", char *msgtext="Input", int fontColor=BLACK)
	{
		int mbId=0;
		int textboxHeight,textboxLeft,textboxTop,textboxWidth;
		int maxMsgBoxWidth=0;
		int increaseWidth=0;

		Left=left;
		Top=top;
		Width=MSGBOXDEFAULTWIDTH+2*MSGBTNDEFAULTWIDTH;
		
		settextstyle(SMALL_FONT,0,0);
		
		Height = MSGBOXDEFAULTHEIGHT+MSGBTNDEFAULTHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext));
		settextstyle(0,0,0);
		if(Width<textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2))
		{
		   int diff;
		   diff= textwidth(title)+(BORDERWIDTH*2)+(2*TITLEBARHEIGHT+2)-Width;
		   Width+=diff+TITLEBARHEIGHT;

		}
		settextstyle(SMALL_FONT,0,0);
		///////////////////////////////////

		if(MsgIcon==jcCritical||MsgIcon==jcQuestion||MsgIcon==jcExclamation||MsgIcon==jcInformation||MsgIcon==jcAbout)
			maxMsgBoxWidth=Width-20-2*ICONWIDTH;
		else
			maxMsgBoxWidth=Width-20;

		if(maxMsgBoxWidth<strlen(msgtext)*textwidth("H"))
		{
			int totalWords=maxMsgBoxWidth/textwidth("H");
			int count=0;

			for(int i=totalWords;i<MAX_WORD_IN_LINE;i++)
			{
				if(maxMsgBoxWidth>=strlen(msgtext)*textwidth("H"))
					break;
				maxMsgBoxWidth+=textwidth("H");
				count++;
			}

			increaseWidth=count*textwidth("H");

		}

		Width+=increaseWidth;


		///////////////////////////////////

		textboxLeft=Left+10;
		textboxTop=Top+2*TITLEBARHEIGHT+2*(textheight("A")*TotalLines(Left+10, Top+2*TITLEBARHEIGHT, Width-20, msgtext))+20;
		textboxWidth=Width-20;
		textboxHeight=20;

		Height+=2*textboxHeight;

		strcpy(Caption,title);
		MsgBtnType=jcOKCancel;
		
		mouse.HideMouse();

		getimage(Left,Top,Left+Width,Top+Height,buffer);

		setfillstyle(SOLID_FILL,LIGHTGRAY);
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
		
		settextstyle(0,0,0);
		setcolor(WHITE);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		outtextxy(Left+(BORDERWIDTH*2)+TITLEBARHEIGHT+2,Top+(BORDERWIDTH*2)+(TITLEBARHEIGHT/2)-(textheight(Caption)/2),Caption);
		settextstyle(SMALL_FONT,0,0);


			WriteMessage(Left+10, Top+2*TITLEBARHEIGHT, Width-20, fontColor, msgtext);

		


		MsgCloseBtn = new Button(Left+Width-TITLEBARHEIGHT-1, Top+2,TITLEBARHEIGHT-2, TITLEBARHEIGHT-2, "X", 9800);
		MsgCloseBtn->Draw();

		pInputBox = new TextBox(textboxLeft,textboxTop,textboxWidth,textboxHeight,"",LEFT_TEXT,7001);
		pInputBox->Draw();
		
		MsgBtn[0]= new Button(Left+Width/2-MSGBTNDEFAULTWIDTH-(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"OK",jcOK);
		MsgBtn[0]->Draw();
		MsgBtn[1]= new Button(Left+Width/2+(MSGBTNDEFAULTWIDTH/2),Top+Height-MSGBTNDEFAULTHEIGHT-12,MSGBTNDEFAULTWIDTH,MSGBTNDEFAULTHEIGHT,"Cancel",jcCancel);
		MsgBtn[1]->Draw();
			
		settextstyle(0,0,0);
		SSLogo();
		
		mouse.ShowMouse();

		while(1)
		{
			mouse.ShowMouse();
			mouse.GetMouseStatus();
			

			MsgCloseBtn->EnableClickHandler();
			for(int b=0;b<2;b++)
				MsgBtn[b]->EnableClickHandler();
			pInputBox->EnableClickHandler();

			mbId=ButtonId;
			ButtonId=0;

			switch(mbId)
			{
				case 9800:
				case jcCancel:
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<2;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					delete pInputBox;
				return NULL;
				case jcOK:
					char inputText[70];
					strcpy(inputText,pInputBox->GetText());
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int k=0;k<2;k++)
						delete MsgBtn[k];
					delete MsgCloseBtn;
					delete pInputBox;
				return inputText;

			}

			while(kbhit()){
				int ch = getch();
				if (ch == 27)  //ESC key pressed
				{
					mouse.HideMouse();
					flushall();
					putimage(Left,Top,buffer,COPY_PUT);
					mouse.ShowMouse();
					for(int i=0;i<2;i++)
						delete MsgBtn[i];
					delete MsgCloseBtn;
					delete pInputBox;
					return NULL;
				}
			}
		}

	}
MsgBox msgbox;
class CUSTOMER
{
	char Password[50];
public:
	char Username[50];
	//CUSTOMER(char *user,char *pass);
	void inputdata(char *username,char *password);
	int CheckPassword(char *password);


};
int CUSTOMER::CheckPassword(char *password)
{
	if(strcmp(Password,password)==0)
		return 1;
	else{
		return 0;
	}
}
void CUSTOMER::inputdata(char *username,char *password)
{
	strcpy(Username,username);
	strcpy(Password,password);
}
Window *awelcome = new Window(10,10,630,480,"WELCOME");
// Button *standard[5];
// Button *bwelcome[2];
Button *back = new Button(20,400,100,30,"BACK",1);
Button *next = new Button(500,400,100,30,"NEXT",2);
TextBox *pusername = new TextBox(200,200,243,30,"USERNAME",LEFT_TEXT,1);
TextBox *ppassword = new TextBox(200,240,243,30,"PASSWORD",LEFT_TEXT,2);

void welcome();
void Customerlogin();
void Timings()
{

}
void TheatreDetails()
{

}
void FoodCounter()
{

}
void Book()
{

}
void AdminLogin()
{
	cleardevice();
	Window *pLogin = new Window(10,10,630,480,"ADMIN LOGIN");
	pLogin->Draw();
    pusername->Draw();
    ppassword->Draw();
    back->Draw();
    next->Draw();

	// for(int i=1;i<=2;i++)
	// {
	// 	standard[i]->Draw();
	// }
	while(1)
	{
		mouse.ShowMouse(); // To show mouse
        mouse.GetMouseStatus(); // To get position of mouse
        pLogin->EnableClickHandler();
		pusername->EnableClickHandler();
		ppassword->EnableClickHandler();
		ppassword->HideText(true);
		back->EnableClickHandler();
		next->EnableClickHandler();
		// for(int i=1;i<=2;i++)
		// {
		// 	standard[i]->EnableClickHandler();
		// }
		if(ButtonId==1)
	    {
            welcome();
	    }
	} 
}
void CustomerHome()
{
	cleardevice();
	Window *pAHome = new Window(10,10,630,480,"Now Playing");
	Label *timings = new Label(175,80,90,130,"Movie 1",CENTER_TEXT,3);
	Label *theatre = new Label(305,80,90,130,"Movie 2",CENTER_TEXT,4);
	Label *food = new Label(175,250,90,130,"Movie 3",CENTER_TEXT,5);
	Label *book = new Label(305,250,90,130,"Movie 4",CENTER_TEXT,6);
	//Button *home = new Button(20,400,100,30,"Home",LEFT_TEXT,7);
	pAHome->Draw();
	timings->Draw();
	theatre->Draw();
	food->Draw();
	book->Draw();
    back->Draw();
    next->Draw();
	// for(int i=1;i<=2;i++)
    // {
    // 	bwelcome[i]->Draw();
    // }
    while(1)
    {
	mouse.ShowMouse(); // To show mouse
	mouse.GetMouseStatus(); // To get position of mouse
		awelcome->EnableClickHandler();
		timings->EnableClickHandler(2,0,4,8);
		theatre->EnableClickHandler(2,0,4,8);
		food->EnableClickHandler(2,0,4,8);
		book->EnableClickHandler(2,0,4,8);
		back->EnableClickHandler();
		next->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(LabelId==3)//Timings
			Timings();
		else if(LabelId==4)//Details
			TheatreDetails();
		else if(LabelId==5)//Counter
			FoodCounter();
		else if(LabelId==6)//Book A Ticket
		 	Book();
		else if(ButtonId==1)
			Customerlogin();
		else{}

    }
}
void CustomerSignUp()
{
	cleardevice();
	Window *pSignUpWindow = new Window(10,10,630,480,"CUSTOMER SIGN UP");
	pSignUpWindow->Draw();
	pusername->Draw();
    ppassword->Draw();
    back->Draw();
    next->Draw();
    while(1)
    {
    	CUSTOMER Customer;
		mouse.ShowMouse(); // To show mouse
		mouse.GetMouseStatus(); // To get position of mouse
		pSignUpWindow->EnableClickHandler();
		pusername->EnableClickHandler();
		ppassword->EnableClickHandler();
		ppassword->HideText(true);
		back->EnableClickHandler();
		next->EnableClickHandler();

		if(ButtonId==1)
		{
			Customerlogin();
		}
		if(ButtonId==2)
		{
			Customer.inputdata(pusername->GetText(),ppassword->GetText());
			fstream fil;
			fil.open("customer.dat",ios::binary|ios::out);
			fil.close();
			fil.open("customer.dat",ios::binary|ios::app);
			fil.close();
			fil.write((char *)&Customer,sizeof(Customer));
			fil.close();
			Customerlogin();
		}
    }
}
void Customerlogin()
{
	cleardevice();
	Window *pLogin = new Window(10,10,630,480,"CUSTOMER LOGIN");
	Button *pCustomerSignUp = new Button(200,400,243,30,"New Here, SIGN UP",5);
	pLogin->Draw();
    pusername->Draw();
    ppassword->Draw();
    pCustomerSignUp->Draw();
    back->Draw();
    next->Draw();

    while(1)
	{
		CUSTOMER Customer;
		mouse.ShowMouse(); // To show mouse
	mouse.GetMouseStatus(); // To get position of mouse
	pLogin->EnableClickHandler();
		pusername->EnableClickHandler();
		ppassword->EnableClickHandler();
		ppassword->HideText(true);
		pCustomerSignUp->EnableClickHandler();
		back->EnableClickHandler();
		next->EnableClickHandler();
		// for(int i=1;i<=2;i++)
		// {
		// 	standard[i]->EnableClickHandler();
		// }
		if(ButtonId==1)
	    {
	    welcome();
	    }
	    if(ButtonId==2)
	    {
			fstream fil;
			fil.open("customer.dat",ios::binary|ios::in);
			fil.seekg(0,ios::beg);
			while(fil.read((char *)&Customer,sizeof(Customer)))
			{
				if(Customer.CheckPassword(ppassword->GetText()) && strcmp(Customer.Username,pusername->GetText())==0)
				{
					//fil.close();
					CustomerHome();
				}
				else
				{
			   		int msgBtn = msgbox.MessageBox(200,200,"New","Incorrect Password or Username",GREEN,jcRetryCancel,jcCritical);
			   		if(msgBtn=jcRetry){
			   			Customerlogin();
			   			//fil.close();
			   		}
			   		else{welcome();}
				}
			}
			fil.close();
	    }
	    if(ButtonId==5)
	    {
	    	CustomerSignUp();
	    }
	}


}
void welcome()
{
	cleardevice();
	Button *admin = new Button(200,200,243,30,"ADMIN",3);
	Button *customer = new Button(200,240,243,30,"CUSTOMER",4);
	awelcome->Draw();
	admin->Draw();
	customer->Draw();

    // for(int i=1;i<=2;i++)
    // {
    // 	bwelcome[i]->Draw();
    // }
    while(1)
    {
	mouse.ShowMouse(); // To show mouse
	mouse.GetMouseStatus(); // To get position of mouse
		awelcome->EnableClickHandler();
		admin->EnableClickHandler();
		customer->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(ButtonId==3)//Admin
		AdminLogin();
	if(ButtonId==4)//Customer
		Customerlogin();

    }
}

void main()
{
	int gd = DETECT,gm,errorcode;
	char ch;
	initgraph(&gd,&gm,"c://tc//bgi");

		// read result of initialization
		errorcode = graphresult();

		if (errorcode != grOk)// an error occurred
		{
			cout<<"Graphics error :: "<<grapherrormsg(errorcode);
			cout <<"\n press any key to halt: ";
			getch();
			exit(1);// terminate with an error code
		}


    while(true)
    {
    	welcome();
        

		while(kbhit())
		{
		 ch = getch();
		 if(ch==27)
		  exit(0);
		}
    }
    getch();

}