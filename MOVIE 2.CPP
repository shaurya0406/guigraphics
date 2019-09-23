#include <gui.h>
class MOVIE
{
	public:
	char MovieName[50],Timing[5];
	float Price;
	char* Mn()
	{return MovieName;}

};
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
void CustomerTime();
int CheckFile(char *username,char *password=" ")
{
	CUSTOMER Customer;
	fstream fil;
	int exists=0;
	fil.open("customer.dat",ios::binary|ios::in);
	while(fil.read((char *)&Customer,sizeof(Customer)))
	{
		if(strcmp(Customer.Username,username)==0 && Customer.CheckPassword(password))
			exists=1;
		else if(strcmp(Customer.Username,username)==0)
			exists=2;
		
	}

	fil.close();
	return exists;
}
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
	MOVIE Movie;
	Window *pAHome = new Window(10,10,630,480,"Now Playing");
	Label *m1 = new Label(175,80,90,130,"Movie 1",CENTER_TEXT,15,8,3);
	Label *m2 = new Label(305,80,90,130,"Movie 2",CENTER_TEXT,15,8,4);
	Label *m3 = new Label(175,250,90,130,"Movie 3",CENTER_TEXT,15,8,5);
	Label *m4 = new Label(305,250,90,130,"Movie 4",CENTER_TEXT,15,8,6);
	//Button *home = new Button(20,400,100,30,"Home",LEFT_TEXT,7);
	pAHome->Draw();
	m1->Draw();
	m2->Draw();
	m3->Draw();
	m4->Draw();
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
		m1->EnableClickHandler(2,0,15,8);
		m2->EnableClickHandler(2,0,15,8);
		m3->EnableClickHandler(2,0,15,8);
		m4->EnableClickHandler(2,0,15,8);
		back->EnableClickHandler();
		next->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(LabelId==3)
			strcpy(Movie.MovieName,m1->GetText());
		else if(LabelId==4)
			strcpy(Movie.MovieName,m2->GetText());
		else if(LabelId==5)
			strcpy(Movie.MovieName,m3->GetText());
		else if(LabelId==6)
			strcpy(Movie.MovieName,m4->GetText());
		
		else if(ButtonId==1){
			int msgBtn = msgbox.MessageBox(200,200,"HOME","Are you sure you want to \n  Log Out",BLUE,jcYesNo,jcCritical);
				if(msgBtn=jcYes)
				{
					Customerlogin();	
				}
				else{CustomerHome();}
			
		}
		else if(ButtonId==2)
			CustomerTime();	
		else{}

    }
}
void CustomerTime()
{
	cleardevice();
	MOVIE Movie;
	Window *pAHome = new Window(10,10,630,480,"Show Timings");
	Label *t1 = new Label(130,80,100,80,"Time",CENTER_TEXT,15,8,3);
	Label *t2 = new Label(235,80,100,80,"Time",CENTER_TEXT,15,8,4);
	Label *t3 = new Label(340,80,100,80,"Time",CENTER_TEXT,15,8,5);
	Label *t4 = new Label(130,180,100,80,"Time",CENTER_TEXT,15,8,6);
	Label *t5 = new Label(235,180,100,80,"Time",CENTER_TEXT,15,8,7);
	Label *t6 = new Label(340,180,100,80,"Time",CENTER_TEXT,15,8,8);
	Label *t7 = new Label(130,280,100,80,"Time",CENTER_TEXT,15,8,9);
	Label *t8 = new Label(235,280,100,80,"Time",CENTER_TEXT,15,8,10);

	//Button *home = new Button(20,400,100,30,"Home",LEFT_TEXT,7);
	pAHome->Draw();
	t1->Draw();
	t2->Draw();
	t3->Draw();
	t4->Draw();
    t5->Draw();
	t6->Draw();
	t7->Draw();
	t8->Draw();
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
		t1->EnableClickHandler(2,0,15,8);
		t2->EnableClickHandler(2,0,15,8);
		t3->EnableClickHandler(2,0,15,8);
		t4->EnableClickHandler(2,0,15,8);
		t5->EnableClickHandler(2,0,15,8);
		t6->EnableClickHandler(2,0,15,8);
		t7->EnableClickHandler(2,0,15,8);
		t8->EnableClickHandler(2,0,15,8);
		back->EnableClickHandler();
		next->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(LabelId==3)
			strcpy(Movie.Timing,t1->GetText());
		else if(LabelId==4)
			strcpy(Movie.Timing,t2->GetText());
		else if(LabelId==5)
			strcpy(Movie.Timing,t3->GetText());
		else if(LabelId==6)
			strcpy(Movie.Timing,t4->GetText());
		else if(LabelId==7)
			strcpy(Movie.Timing,t5->GetText());
		else if(LabelId==8)
			strcpy(Movie.Timing,t6->GetText());
		else if(LabelId==9)
			strcpy(Movie.Timing,t7->GetText());
		else if(LabelId==10)
			strcpy(Movie.Timing,t8->GetText());
		else if(ButtonId==1)
			CustomerHome();
		else if(ButtonId==2)
			CustomerTime();

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
			CUSTOMER Customer;
			Customer.inputdata(pusername->GetText(),ppassword->GetText());
			if(CheckFile(pusername->GetText())==2)
			{
				int msgBtn = msgbox.MessageBox(200,200,"Sign Up","User Exists. Please Login!",BLUE,jcOKOnly,jcCritical);
					if(msgBtn=jcOK)
					{
						Customerlogin();
						//fil.close();
					}
			}
			else
			{
				fstream fil;
				fil.open("customer.dat",ios::binary|ios::app);
				fil.write((char *)&Customer,sizeof(Customer));
				fil.close();
				Customerlogin();
			}
			
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
			if(CheckFile(pusername->GetText(),ppassword->GetText())==1)
				CustomerHome();
			else
			{
				int msgBtn = msgbox.MessageBox(200,200,"New","Incorrect Password or Username",BLUE,jcRetryCancel,jcCritical);
					if(msgBtn=jcRetry){
						Customerlogin();
						//fil.close();
					}
			}
			
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
	clrscr();
	int gd = DETECT,gm,errorcode;
	char ch;
	initgraph(&gd,&gm,"C:\\tc\\bgi");

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
