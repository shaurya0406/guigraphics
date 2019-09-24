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
	char Name[50], EMail[25];
	char Phone[10];

	//CUSTOMER(char *user,char *pass);
	void inputdata(char *name, char *username,char *password, char *email, char *phone);
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
void CUSTOMER::inputdata(char *name, char *username,char *password, char *email, char *phone)
{
	strcpy(Name,name);
	strcpy(Username,username);
	strcpy(Password,password);
	strcpy(EMail,email);
	strcpy(Phone,phone);
}
Window *awelcome = new Window(10,10,630,480,"WELCOME");
// Button *standard[5];
// Button *bwelcome[2];
Button *back = new Button(20,400,100,30,"BACK",1);
Button *next = new Button(500,400,100,30,"NEXT",2);
//TextBox *pusername = new TextBox(200,200,243,30,"USERNAME",LEFT_TEXT,1);
//TextBox *ppassword = new TextBox(200,240,243,30,"PASSWORD",LEFT_TEXT,2);
int LoginStatus=0;
void Customerlogin();
/*int CheckLoginStatus()
{
	if(LoginStatus==0)
		return 0;
	else
		return 1;
}*/
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
void AdminHome()
{
	cleardevice();
	Window *pAHome = new Window(10,10,630,480,"Admin Home");
	Button *t1 = new Button(75,80,100,130,"1",3);
	Button *t2 = new Button(205,80,100,130,"2",4);
	Button *t3 = new Button(335,80,100,130,"3",5);
	Button *t4 = new Button(465,80,100,130,"4",6);
	Button *t5 = new Button(75,250,100,130,"5",7);
	Button *t6 = new Button(205,250,100,130,"6",8);
	Button *t7 = new Button(335,250,100,130,"7",9);
	Button *t8 = new Button(465,250,100,130,"8",10);
	Button *t9 = new Button(510,420,100,30,"Sign Out",11);

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
	t9->Draw();
	// for(int i=1;i<=2;i++)
    // {
    // 	bwelcome[i]->Draw();
    // }
    while(1)
    {
		int Chk=LoginStatus;
		mouse.ShowMouse(); // To show mouse
		mouse.GetMouseStatus(); // To get position of mouse
		awelcome->EnableClickHandler();
		t1->EnableClickHandler();
		t2->EnableClickHandler();
		t3->EnableClickHandler();
		t4->EnableClickHandler();
		t5->EnableClickHandler();
		t6->EnableClickHandler();
		t7->EnableClickHandler();
		t8->EnableClickHandler();
		t9->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
	       /*	if(ButtonId==1)
			CustomerHome();
		else if(ButtonId==3&&Chk==1)
			strcpy(Movie.Timing,t1->GetText());
		else if(ButtonId==4&&Chk==1)
			strcpy(Movie.Timing,t2->GetText());
		else if(ButtonId==5&&Chk==1)
			strcpy(Movie.Timing,t3->GetText());
		else if(ButtonId==6&&Chk==1)
			strcpy(Movie.Timing,t4->GetText());
		else if(ButtonId==7&&Chk==1)
			strcpy(Movie.Timing,t5->GetText());
		else if(ButtonId==8&&Chk==1)
			strcpy(Movie.Timing,t6->GetText());
		else if(ButtonId==9&&Chk==1)
			strcpy(Movie.Timing,t7->GetText());
		else if(ButtonId==10&&Chk==1)
			strcpy(Movie.Timing,t8->GetText());
		else if(ButtonId==3||ButtonId==4||ButtonId==5||ButtonId==6||ButtonId==7||ButtonId==8||ButtonId==9||ButtonId==10&&Chk==0)
		{

			int msgBtn = msgbox.MessageBox(200,200,"Credentials Needed","Please Login to Proceed",BLUE,jcOKOnly,jcCritical);
			if(msgBtn=jcOK)
			{
				Customerlogin();
			}

		}*/

		}

}

void AdminLogin()
{
	cleardevice();
	Window *pLogin = new Window(10,10,630,480,"ADMIN LOGIN");
	pLogin->Draw();
	TextBox *pusername = new TextBox(200,200,243,30,"USERNAME",LEFT_TEXT,1);
	TextBox *ppassword = new TextBox(200,240,243,30,"PASSWORD",LEFT_TEXT,2);
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
	    else if(ButtonId==2)
		AdminHome();
	}
}
void CustomerHome()
{
	cleardevice();
	MOVIE Movie;
	Window *pAHome = new Window(10,10,630,480,"Now Playing");
	Button *m1 = new Button(175,80,90,130,"Movie 1",3);
	Button *m2 = new Button(305,80,90,130,"Movie 2",4);
	Button *m3 = new Button(175,250,90,130,"Movie 3",5);
	Button *m4 = new Button(305,250,90,130,"Movie 4",6);
	//Button *home = new Button(20,400,100,30,"Home",LEFT_TEXT,7);
	pAHome->Draw();
	m1->Draw();
	m2->Draw();
	m3->Draw();
	m4->Draw();
    back->Draw();
	// for(int i=1;i<=2;i++)
    // {
    // 	bwelcome[i]->Draw();
    // }
    while(1)
    {
		mouse.ShowMouse(); // To show mouse
		mouse.GetMouseStatus(); // To get position of mouse
		awelcome->EnableClickHandler();
		m1->EnableClickHandler();
		m2->EnableClickHandler();
		m3->EnableClickHandler();
		m4->EnableClickHandler();
		back->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(ButtonId==3)
		{
			strcpy(Movie.MovieName,m1->GetText());
			CustomerTime();
		}
		else if(ButtonId==4)
		{
			strcpy(Movie.MovieName,m2->GetText());
			CustomerTime();
		}
		else if(ButtonId==5)
		{
			strcpy(Movie.MovieName,m3->GetText());
			CustomerTime();
		}
		else if(ButtonId==6)
		{
			strcpy(Movie.MovieName,m4->GetText());
			CustomerTime();
		}

		else if(ButtonId==1&&LoginStatus==1)
		{
			int msgBtn = msgbox.MessageBox(200,200,"HOME","Are you sure you want to \n  Log Out",BLUE,jcYesNo,jcCritical);
				if(msgBtn=jcYes)
				{
					LoginStatus=0;
					Customerlogin();

				}
				else{CustomerHome();}

		}
		else if(ButtonId==1&&LoginStatus==0)
		{
			welcome();
		}
		else
		{
		}



    }
}
void CustomerTime()
{
	cleardevice();
	MOVIE Movie;
	Window *pAHome = new Window(10,10,630,480,"Show Timings");
	Button *t1 = new Button(130,80,100,80,"Time",3);
	Button *t2 = new Button(235,80,100,80,"Time",4);
	Button *t3 = new Button(340,80,100,80,"Time",5);
	Button *t4 = new Button(130,180,100,80,"Time",6);
	Button *t5 = new Button(235,180,100,80,"Time",7);
	Button *t6 = new Button(340,180,100,80,"Time",8);
	Button *t7 = new Button(130,280,100,80,"Time",9);
	Button *t8 = new Button(235,280,100,80,"Time",10);

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
	// for(int i=1;i<=2;i++)
    // {
    // 	bwelcome[i]->Draw();
    // }
    while(1)
    {
		int Chk=LoginStatus;
		mouse.ShowMouse(); // To show mouse
		mouse.GetMouseStatus(); // To get position of mouse
		awelcome->EnableClickHandler();
		t1->EnableClickHandler();
		t2->EnableClickHandler();
		t3->EnableClickHandler();
		t4->EnableClickHandler();
		t5->EnableClickHandler();
		t6->EnableClickHandler();
		t7->EnableClickHandler();
		t8->EnableClickHandler();
		back->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(ButtonId==1)
			CustomerHome();
		else if(ButtonId==3&&Chk==1)
			strcpy(Movie.Timing,t1->GetText());
		else if(ButtonId==4&&Chk==1)
			strcpy(Movie.Timing,t2->GetText());
		else if(ButtonId==5&&Chk==1)
			strcpy(Movie.Timing,t3->GetText());
		else if(ButtonId==6&&Chk==1)
			strcpy(Movie.Timing,t4->GetText());
		else if(ButtonId==7&&Chk==1)
			strcpy(Movie.Timing,t5->GetText());
		else if(ButtonId==8&&Chk==1)
			strcpy(Movie.Timing,t6->GetText());
		else if(ButtonId==9&&Chk==1)
			strcpy(Movie.Timing,t7->GetText());
		else if(ButtonId==10&&Chk==1)
			strcpy(Movie.Timing,t8->GetText());
		else if(ButtonId==3||ButtonId==4||ButtonId==5||ButtonId==6||ButtonId==7||ButtonId==8||ButtonId==9||ButtonId==10&&Chk==0)
		{

			int msgBtn = msgbox.MessageBox(200,200,"Credentials Needed","Please Login to Proceed",BLUE,jcOKOnly,jcCritical);
			if(msgBtn=jcOK)
			{
				Customerlogin();
			}

		}

		}

}
void CustomerSignUp()
{
	cleardevice();
	Window *pSignUpWindow = new Window(10,10,630,480,"CUSTOMER SIGN UP");
	Label *page = new Label(200,70,243,30,"Customer Sign Up",CENTER_TEXT);
	TextBox *pname = new TextBox(200,130,243,30,"NAME",LEFT_TEXT,1);
	TextBox *pusername = new TextBox(200,180,243,30,"USERNAME",LEFT_TEXT,2);
	TextBox *ppassword = new TextBox(200,230,243,30,"PASSWORD",LEFT_TEXT,3);
	TextBox *pphone = new TextBox(200,280,243,30,"PHONE NUMBER",LEFT_TEXT,4);
	TextBox *pemail = new TextBox(200,330,243,30,"EMAIL ID",LEFT_TEXT,5);

	pSignUpWindow->Draw();
	page->Draw();
	pname->Draw();
	pusername->Draw();
	ppassword->Draw();
	pphone->Draw();
	pemail->Draw();

    back->Draw();
    next->Draw();
    while(1)
    {

		mouse.ShowMouse(); // To show mouse
		mouse.GetMouseStatus(); // To get position of mouse
		pSignUpWindow->EnableClickHandler();
		ppassword->EnableClickHandler();
		pname->EnableClickHandler();
		pusername->EnableClickHandler();
		ppassword->HideText(true);
		pphone->EnableClickHandler();
		pemail->EnableClickHandler();

		back->EnableClickHandler();
		next->EnableClickHandler();

		if(ButtonId==1)
		{
			Customerlogin();
		}
		if(ButtonId==2)
		{
			CUSTOMER Customer;

			Customer.inputdata(pname->GetText(),pusername->GetText(),ppassword->GetText(),pemail->GetText(),pphone->GetText());
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
	TextBox *pusername = new TextBox(200,200,243,30,"USERNAME",LEFT_TEXT,2);
	TextBox *ppassword = new TextBox(200,240,243,30,"PASSWORD",LEFT_TEXT,3);
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
			{
				LoginStatus=1;
				CustomerHome();
			}
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
	Button *admin = new Button(200,180,243,30,"ADMIN",3);
	Button *customer = new Button(200,220,243,30,"CUSTOMER",4);
	Button *guest = new Button(200,260,243,30,"GUEST",5);
	awelcome->Draw();
	admin->Draw();
	guest->Draw();
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
		guest->EnableClickHandler();
   //  	for(int i=1;i<=2;i++)
			// bwelcome[i]->EnableClickHandler();
		if(ButtonId==3)//Admin
			AdminLogin();
		else if(ButtonId==4)//Customer
			Customerlogin();
		else if(ButtonId==5)
			CustomerHome();


    }
}

void main()
{
	clrscr();
	int gd = DETECT,gm,errorcode;
	char ch;
	initgraph(&gd,&gm,"C:\\turboc3\\bgi");

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
