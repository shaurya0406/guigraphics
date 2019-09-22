#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
enum bool{false,true};
class CUSTOMER
{
	char Password[50];
public:
	char Username[50];
	//CUSTOMER(char *user,char *pass);
	int CheckPassword(char *password);

};
// CUSTOMER::CUSTOMER(char user[],char pass[])
// {
// 	Username=user;
// 	Password=pass;
// }
int CUSTOMER::CheckPassword(char *password)
{
	if(password==Password)
		return 1;
	else{
		return 0;
	}
}
void main()
{
	CUSTOMER Customer[20];
	CUSTOMER Customer1;
	char username[50],password[50],user[50];;
	bool exists=false;
	int i=0;
	fstream fil;
	fil.open("CUSTOMER.dat",ios::binary|ios::in|ios::out);
    strcpy(Customer[0].Username,"Shaurya");
	strcpy(Customer[1].Username,"Rishit");
	fil.write((char *)&Customer,sizeof(Customer));
	while(fil.read((char *)&Customer1,sizeof(Customer1)))
	{
		strcpy(user,Customer1.Username);
		for(;i<strlen(user);i++)
			username[i]=user[i];
		username[i]=',';


	}
	cout<<username;
	// cout<<"enter username : ";
	// gets(username);
	// while(fil.read((char *)&Customer,sizeof(Customer)))
	// {
	// 	char *user=Customer.Username;
	// 	if(strcmp(user,username))
	// 	{
	// 		exists=true;
	// 	}

	// }
	// cout<<"enter username : ";
	// gets(username);
	// cout<<"hi "<<username<<endl;
	// cout<<"enter password : ";
	// gets(password);
	// Customer[0](username,password);
    fil.close();
    getch();
}