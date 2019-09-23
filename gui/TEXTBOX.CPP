


	  
	#ifndef TEXTBOX_CPP
	#define TEXTBOX_CPP 
	
	#include <textbox.h>
	#include <graphics.h>
	#include <string.h>
	#include <conio.h>
	#include <ctype.h>


  
      
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
   
   #endif //TEXTBOX_CPP
   
		


















	

 
