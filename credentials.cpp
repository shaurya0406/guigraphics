#include <fstream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
class CUSTOMER
{
	char Password[50];
public:
	char Username[50];
	CUSTOMER(char *username,char *password);
	//bool CheckPassword(char *password);

};
CUSTOMER::CUSTOMER(char username[],char password[])
{
	Username=username;
	Password=password;
}
// CUSTOMER::CheckPassword(char *password)
// {
// 	if(password==Password)
// 		return true;
// 	else{
// 		return false;
// 	}
// }
void main()
{
	CUSTOMER Customer[20];
	char username[50],password[50];
	bool exists=false;
	int i=0;
	fstream fil;
	fil.open("CUSTOMER.dat",ios::binary|ios::in|ios::out);
	Customer[0]("Shaurya","lallu");
	Customer[1]("Rishit","ghonchu");
	fil.write((char *)&Customer,sizeof(Customer))
	while(fil.read((char *)&Customer,sizeof(Customer)))
	{
		char *user=Customer.Username;
		for(;i<strlen(user);i++)
			username[i]=user[i];
		username[i]=','

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


}