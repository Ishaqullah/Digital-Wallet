#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>


#define ENTER 13 //ASCII value of enter key
#define TAB 9 //ASCII value of tab key
#define BKSP 8 //ASCII value of backspace key
#define SPACE 32 //ASCII value of space key


using namespace std;
//----------------------------------------------------Global Decleration---------------------------------------------------------------//
void title();
void welcomeScreen();  
void loginPage(int);
void gotoxy(int , int);

//===========================================================================CLASSES===========================================================================================

//-----------------------------------------------------------------User interface class------------------------------------------------------------------------------------

class UserInterface{
	public:
		virtual void moneyTransfer(string)=0;                       
		virtual void bill(string)=0;                            
		virtual void easyLoad(string)=0;                   //pure virtual functions
		virtual void deposit(string)=0;
		virtual void menu(string)=0;
};

//-----------------------------------------------------------------Admin interface class------------------------------------------------------------------------------------
class AdminInterface
{
	public:
		virtual void menu()=0;
		virtual void getData()=0;                            //pure virtual functions
		virtual void BanAcc()=0;
		virtual void BonusAmmount()=0;
};

//------------------------------------------------------------------Accounts class------------------------------------------------------------------------------------------
class Accounts
{

	string name,CNIC,contact_no,mpin;
	protected:
	string n[100],cnic[100],con[100],pin[100];
	double bal[100];
	public:
		Accounts(){}                               //default constructor
		Accounts(string name,string CNIC,string contact_no,string mpin)         //parameterized constructor
		{
			this->name=name;
			this->CNIC=CNIC;
			this->contact_no=contact_no;
			this->mpin=mpin;
		}
		friend class  signup;       //making signup and login classes friend of class Accounts
		friend class login;		
};


//------------------------------------------------------------------User class----------------------------------------------------------------------------------------------
class User:public Accounts,public UserInterface    //class User being Inherited publically from Accounts and UserInterface
{
	double balance;
	public:
		User(){}
		//==========menu() will display choices to use=======================//
	void menu(string contact_no){                    
		system("cls");
		title();
		
 		int i, j,choice;
		
		ifstream fout("account.txt",ios::in);
			
			while(!fout.eof())                 //reading data from file "account.txt"
			{
		
			fout>>n[i];     
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==contact_no)
			{
			j=i;
			}
			i++;
			}
		fout.close();
		
		
		cout<<"\n\t\t\t\t\t\t"<<n[j]<<" your current balance is Rs."<<bal[j];
		cout<<"\n\n\n\n\t\t\t\t\t\t1.Deposit\n\n\n\t\t\t\t\t\t2.Money Transfer\n\n\n\t\t\t\t\t\t3.Bill payment\n\n\n\t\t\t\t\t\t4.Easyload\n\n\n\t\t\t\t\t\t5.Exit"<<endl;
		cout<<"\n\n\n\n\n\n\t\t\tEnter your choice: ";
		cin>>choice;
		switch(choice){
		case 1:
			{
			system("cls");	
			deposit(contact_no);          //deposit() called
			break;
			}
		case 2:
			{
			system("cls");	
			moneyTransfer(contact_no);   //moneyTransfer() called  
 			break;
			}
		case 3:
			{
			system("cls");	
			bill(contact_no);            //bill() called  
			break;
			}
		case 4:
			{
			system("cls");	
			easyLoad(contact_no);        //easyLoad() called
			break;	
			}
		case 5:
			{
			system("cls");	
			exit_me();                  //exit_me() called 
			break;
			}	
		default:
			cout<<"Invalid choice!!!"<<endl;
		}
	}	
	
	//===========================Definition of deposit()=====================================//
	void deposit(string contact_no){
		
	int i=0,j;
	title();
	double dep;
		ifstream fout("account.txt",ios::in);
			
			while(!fout.eof())                 //reading data from file "account.txt"
			{
		
			fout>>n[i];     
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==contact_no)
			{
			j=i;
			}
			i++;
			}
		fout.close();	
	cout<<"Enter Amount to deposit: ";
	cin>>dep;
	bal[j]+=dep;
	
		
	ofstream temp("temp1.txt");            //for updation in file creating a temporary file
	int k;	

    	for(k=i-2;k>=0;k--)
    	{
      		if(con[k]==contact_no)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
		}
    
	temp.close();
	remove("account.txt");                   //removing account.txt 
	rename("temp1.txt","account.txt");       //renaming temp1.txt as account.txt
	
		if(j<=i)
			{
				cout<<"\n\n\n\n\t\t\t\t\t\tYour amount has been deposited!! "<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu(contact_no);
			}
		else
		{
			cout<<"\n\n\t\t\t\t\tSorry your account is not found in our database"<<endl;
			getch();
			system("cls");
		}
		
	}
	
	
	
	//======================Definition of moneyTransfer()==================================//
	void moneyTransfer(string contact_no)
	{
		double mon;
		string contact;
		int i=0,j=0,k=200;
		title();
		cout<<"Enter phone number of recipient: ";
		cin>>contact;
		ifstream fout("account.txt",ios::in);
			
			while(!fout.eof())                    //reading data from file "account.txt"
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==contact_no)
			{
			j=i;
			
			}
			if(con[i]==contact)
			k=i;
			
			i++;
			}
		fout.close();
			
		
		if(j<=i && k<=i)
		{
		cout<<"Enter amount you want to transfer: "<<endl;
		cin>>mon;
		if(bal[j]>=mon)
		{
		
		bal[j]-=mon;
		bal[k]+=mon;
		
		ofstream temp("temp1.txt");              //for updation in file creating a temporary file
	int l;	

    	for(l=i-2;l>=0;l--)
    	{
      		if(con[l]==contact_no)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else if(con[l]==contact)
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
      		else
      		temp<<n[l]<<" "<<cnic[l]<<" "<<con[l]<<" "<<pin[l]<< " "<<bal[l]<<endl;
		}
		
	temp.close();
	remove("account.txt");                   //removing account.txt
	rename("temp1.txt","account.txt");       //renaming temp1.txt as account.txt 
		
			
				cout<<"\n\n\n\n\t\t\t\t\t\tYour amount has been transferred to "<<contact<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu(contact_no);
			
			
		}
		
	else
		{
			cout<<"\n\n\t\t\t\t\tYou have insufficient balance.Please try again";
			getch();
			menu(contact_no);
		}		
		}
	else if(k>i)
	{
		cout<<"\n\n\n\n\t\t\t\t\t\tRecipent Account is not found "<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu(contact_no);
	}	
	}
	//definition of details()... this will be used in bill() so we'll just simply call this func rather than writing entire code of filing================//
	void details(string contact_no)
		{
			int i,j;
			double bill;
			ifstream fout("account.txt",ios::in);
			
			while(!fout.eof())              //reading data from file
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==contact_no)
			{
			j=i;
			}
			i++;
			}
		fout.close();	
	
	if(j<=i)
	{
	cout<<"\n\n\n\n\t\t\t\t\t\tEnter Amount to pay: ";
	cin>>bill;
	
	if(bal[j]>=bill)
	{
	bal[j]-=bill;
	
		
	ofstream temp("temp1.txt");            //for updation creating a temporary file
	int k;	

    	for(k=i-2;k>=0;k--)
    	{
      		if(con[k]==contact_no)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
		}
    
	temp.close();
	remove("account.txt");
	rename("temp1.txt","account.txt");
	cout<<"\n\n\n\n\t\t\t\t\t\tYour bill has been paid!! "<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu(contact_no);
	}
	else
	{
		cout<<"\n\n\t\t\t\t\tYou have insufficient balance.Please try again";
			getch();
			system("cls");
			menu(contact_no);
	}
		
				
	}
		else
		{
			cout<<"\n\n\t\t\t\t\tSorry your account is not found in our database "<<endl;
			getch();
			system("cls");
			menu(contact_no);
		}
	}
	//====================================Definition of bill()====================================//
	void bill(string contact_no){
		string account_no;
		double bill;
		int choice;
		title();
		cout<<"\n\n\n\n\t\t\t\t\t\tSelect the bill type "<<endl;
		cout<<"\n\n\n\n\t\t\t\t\t\t1.K-Electric\n\n\n\t\t\t\t\t\t2.SSGC\n\n\n\t\t\t\t\t\t3.KWSB\n\n\n\t\t\t\t\t\t4.PTCL"<<endl<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter your 13 digit KESC account number: ";
					cin>>account_no;
					details(contact_no);
					break;
				}
			case 2:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter your 10 digit SSGC customer number: ";
					cin>>account_no;
					details(contact_no);
					break;
				}
			case 3:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter your 11 KWSB consumer number: ";
					cin>>account_no;
					details(contact_no);
					break;
				}
			case 4:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter PTCL Landline Account ID: ";
					cin>>account_no;
					details(contact_no);
					break;
				}
			default:
				cout<<"n\n\n\n\t\t\t\t\tSorry invalid choice ";	
				break;			
		}
		
	}
	//======================================definition of Details()... this will be used in easyLoad================================//
	void details(string contact_no,string load_contact)
		{
			int i,j;
			double easyLoad;
			ifstream fout("account.txt",ios::in);           //reading data from file
			
			while(!fout.eof())
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==contact_no)
			{
			j=i;
			}
			i++;
			}
		fout.close();	
	
	if(j<=i)
	{
	cout<<"\n\n\n\n\t\t\t\t\t\tEnter amount you want to load to: "<<load_contact<<" ";
	cin>>easyLoad;
	
	if(bal[j]>=easyLoad)
	{
	bal[j]-=easyLoad;
	
		
	ofstream temp("temp1.txt");                   //for updation creating a temporary file
	int k;	

    	for(k=i-2;k>=0;k--)
    	{
      		if(con[k]==contact_no)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
		}
    
	temp.close();
	remove("account.txt");                        //removing account.txt 
	rename("temp1.txt","account.txt");            //renaming temp1.txt as account.txt
	cout<<"\n\n\n\n\t\t\t\t\t\tThe mobile number "<<load_contact<<" has been credited with "<<easyLoad<<" Rs"<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu(contact_no);
	}
	else
	{
		cout<<"\n\n\t\t\t\t\tYou have insufficient balance.Please try again";
			getch();
			menu(contact_no);
	}
		
				
	}
		else
		{
			cout<<"\n\n\t\t\t\t\tSorry your account is not found in our database "<<endl;
			getch();
			system("cls");
			menu(contact_no);
		}
	}
//====================================definition of easyLoad()=======================================//
	void easyLoad(string contact_no)
	{
		string load_contact;
		double amount;
		int choice;
		title();
		cout<<"\n\n\n\n\t\t\t\t\t\tSelect your mobile network "<<endl;
		cout<<"\n\n\n\n\t\t\t\t\t\t1.U-fone\n\n\n\t\t\t\t\t\t2.Telenor\n\n\n\t\t\t\t\t\t3.Jazz\n\n\n\t\t\t\t\t\t4.Zong"<<endl<<endl;
		cout<<"\n\n\n\t\t\t\t\t\tEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter the contact number on which you want to load: ";
					cin>>load_contact;
					details(contact_no,load_contact);
					break;
				}
			case 2:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter the contact number on which you want to load: ";
					cin>>load_contact;
					details(contact_no,load_contact);
					break;
				}
			case 3:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter the contact number on which you want to load: ";
					cin>>load_contact;
					details(contact_no,load_contact);
					break;
				}
			case 4:
				{
					system("cls");
					cout<<"\n\n\n\n\t\t\t\t\t\tEnter the contact number on which you want to load: ";
					cin>>load_contact;
					details(contact_no,load_contact);
					break;
				}
			default:
				cout<<"n\n\n\n\t\t\t\t\tSorry invalid choice ";	
				break;			
		}
	
}


//====================Definition of exit_me()=================================================//
void exit_me()                         
{
	gotoxy(50,10);
	cout<<"THANKS FOR USING MSI PAISA!!!";	
}	
};

//------------------------------------------------------------------Admin Class---------------------------------------------------------------------------------------------

class Admin:public Accounts,public AdminInterface             //class Admin being inherited publically from class Accounts and AdminInterface
{
	public:
		void menu()
		{
		system("cls");
		title();
		int choice;
		
		//=========================================Giving choices to admin=========================================//
		
		cout<<"\n\n\n\n\t\t\t\t\t\t1.View data of all users\n\n\n\t\t\t\t\t\t2.Ban Account\n\n\n\t\t\t\t\t\t3.Add a bonus amount to any user\n\n\n\t\t\t\t\t\t4.Exit"<<endl;
		cout<<"\n\n\n\n\n\n\t\t\tEnter your choice: ";
		cin>>choice;
		switch(choice){
		case 1:
			{
			system("cls");	
			getData();             //getData() called
			break;
			}
		case 2:
			{
			system("cls");	
			BanAcc();              //BanAcc() called
			break;
			}
		case 3:
			{
			system("cls");	
			BonusAmmount();        //BonusAmmount() called
			break;
			}
		case 4:
			{
			system("cls");	
			exit_me();            //exit_me() called
			break;	
			}	
		
		default:
			cout<<"Invalid choice!!!"<<endl;
		}
	}
	
	//===============================Definition of getData()=========================================//
	void getData()
	{
			title();
			int i,j,k=9;
			ifstream fout("account.txt",ios::in);        //reading data from file
			
			while(!fout.eof())
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			i++;
			}
		fout.close();
			//======================Using gotoxy() to set cursor position=========================//	
			gotoxy(30,7);
			cout<<"Name";
			gotoxy(50,7);
			cout<<"CNIC";
			gotoxy(70,7);
			cout<<"Contact No";
			gotoxy(90,7);
			cout<<"Balance";
			gotoxy(30,8);
			cout<<"====================================================================\n";
		
		for(j=i-2;j>=0;j--)
		{
			if(n[j]!="Banned")
			{
			gotoxy(30,k);
			cout<<n[j];
			gotoxy(50,k);
			cout<<cnic[j];
			gotoxy(70,k);
			cout<<con[j];
			gotoxy(90,k);
			cout<<bal[j];
			k++;
		    }
		}
		
		getch();
		system("cls");
		menu();		
	}
	
	//=================================Definition of BanAcc()=======================================//
	void BanAcc()
	{
		string num;
		int i, j=1000;
		
		title();
		
		
		cout<<"Enter Phone Number of the Account you want to Ban: ";
		cin>>num;
		
		ifstream fout("account.txt",ios::in);                //reading data from file
			
			while(!fout.eof())
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==num)
			{
			j=i;
			}
			i++;
			}
		fout.close();
		
		if(j>i)
		{
			cout<<"\n\n\t\t\t\t\tSorry this account is not found in our database!!!"<<endl;
			getch();
			system("cls");
			menu();
		}
		
		else
		{
		n[j]="Banned";
	    }
		ofstream temp("temp1.txt");              //for updation creating a temporary file
	    int k;	

    	for(k=i-2;k>=0;k--)
    	{
      		if(con[k]==num)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
		}
    
	temp.close();      
	remove("account.txt");                  //removing account.txt
	rename("temp1.txt","account.txt");      //renaming temp1.txt as account.txt
	
		if(j<=i)
			{
				cout<<"\n\n\n\n\t\t\t\t\t\tAccount Banned Successfully!! "<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu();
			}
		else
		{
			cout<<"\n\n\t\t\t\t\tSorry this account is not found in our database "<<endl;
			getch();
			system("cls");
			menu();
		}
		
	}
	//==================================definition of BonusAmmount()==========================================//	
	void BonusAmmount()
	{
		string number;
		int i, j=1000;
		double a;
		
		title();
		
		
		cout<<"Enter Phone Number of the Account you want to Add Bonus: ";
		cin>>number;
		
		cout<<"Enter the Bonus Amount: ";
		cin>>a;
		
		ifstream fout("account.txt",ios::in);             //reading data from file
			
			while(!fout.eof())
			{
		
			fout>>n[i];
			fout>>cnic[i];
			fout>>con[i];
			fout>>pin[i];
			fout>>bal[i];
			
			if(con[i]==number)
			{
			j=i;
			}
			i++;
			}
		fout.close();
		
		if(j>i)
		{
			cout<<"\n\n\t\t\t\t\tSorry this account is not found in our database!!!"<<endl;
			getch();
			system("cls");
			menu();
		}
		
		else if(n[j]=="Banned")
		{
			cout<<"\n\n\n\n\t\t\t\t\t\tSorry this Account has been Banned!!!"<<endl;
			cout<<"\n\n\n\n\t\t\t\t\t\tPress any key to continue ";
			system("cls");
		    getch();
		    menu();
		}
		else
		bal[j]+=a;
		
		ofstream temp("temp1.txt");               //for updation creating a temporary file
	    int k;	

    	for(k=i-2;k>=0;k--)
    	{
      		if(con[k]==number)
      		temp<<n[j]<<" "<<cnic[j]<<" "<<con[j]<<" "<<pin[j]<< " "<<bal[j]<<endl;
      		else
      		temp<<n[k]<<" "<<cnic[k]<<" "<<con[k]<<" "<<pin[k]<< " "<<bal[k]<<endl;
		}
    
	temp.close();
	remove("account.txt");                      //removing account.txt
	rename("temp1.txt","account.txt");          //renaming temp1.txt as account.txt
	
		if(j<=i)
			{
				cout<<"\n\n\n\n\t\t\t\t\t\tBonus Added Successfully!! "<<endl;
				cout<<"\n\n\t\t\t\t\tPress any key to continue!! "<<endl;
				getch();
				system("cls");
				menu();
			}
		else
		{
			cout<<"\n\n\t\t\t\t\tSorry this account is not found in our database "<<endl;
			getch();
			system("cls");
			menu();
		}
		
	}	
	//=============================================Definition of exit_me()=============================================//
	void exit_me()                  
{
	gotoxy(50,10);
	cout<<"THANKS FOR USING MSI PAISA!!!";	
}
			
};

//------------------------------------------------------------------Signup Class---------------------------------------------------------------------------------------------

class signup{
	
	public:
		
		void details()
	{
		
		User temp;
		double amount=50;
		cout<<"Enter your First Name: "<<endl;
		cin>>temp.name;
		cout<<"Enter your CNIC Number: "<<endl;
		cin>>temp.CNIC;
		cout<<"Enter Contact Number "<<endl;
		cin>>temp.contact_no;
		cout<<"Enter MPIN Number: "<<endl;
		cin>>temp.mpin;
		
		
		ofstream fin("account.txt",ios::app);         //writing data in file
		
		
			
		fin<<temp.name<<" "<<temp.CNIC<<" "<<temp.contact_no<<" "<<temp.mpin<< " "<<amount<<endl;
		fin.close();
	
		
		
		temp.menu(temp.contact_no);
		


	}
};

//------------------------------------------------------------------Login Class---------------------------------------------------------------------------------------------

class Login{
	string contact_no;
	char mpin[25],ch;
	string n[100],cnic[100],con[100],pin[100],bal[100];
	int i,j,k,l;
	public:
		void details()
		{
			User temp;
			A:
				i=0;j=0;k=0;l=0;
				system("cls");
				title();
				cout<<"\n\n\n\n\t\t\t\t\t\tEnter your contact no: ";
				cin>>contact_no;
				cout<<"\n\n\n\n\t\t\t\t\t\tEnter your pin number: ";
			while(1)
				    {
				    	//============================Masking for Passwords==================================//
				    	
				    	
					   ch = getch(); // Here we are reading charachter from a user by getch() and that charachter is stored in var ch
					   if(ch==ENTER)
					{
					   mpin[k]='\0';
					   break;   
				    }
				    else if(ch==BKSP)
					{
						if(k>0)
						{
							k--;
							cout<<"\b \b";
						}
					}
					else if(ch == TAB||ch == SPACE)
					{
						continue;
					}
					else
					{
						mpin[k]=ch;
						k++;
						cout<<"*";
					}
				}
					string pinNo(mpin);                       //Conversion of char array into string using prameterized contructor
				ifstream fout("account.txt",ios::in);        //reading data from file
				while(!fout.eof())
				{
					
				fout>>n[i];
				fout>>cnic[i];
				fout>>con[i];
				fout>>pin[i];
				fout>>bal[i];
				i++;
				}
				fout.close();
				for(i=0;i<100;i++)
				{
					
				if(contact_no==con[i] && pinNo==pin[i])
				{
					if(n[i]=="Banned")
					{
						cout<<"\n\n\n\n\t\t\t\t\t\tThis Account has been Banned!!!"<<endl;
					    cout<<"\n\n\n\n\t\t\t\t\t\tPress any key to continue ";
					    getch();
					    goto A;
					}
					else
					temp.menu(contact_no);
			    }
				else
				j++;
				}
				if(j>=100)
				{
					cout<<"\n\n\n\n\t\t\t\t\t\tSorry invalid entry"<<endl;
					cout<<"\n\n\n\n\t\t\t\t\t\tPress any key to continue ";
					getch();
					goto A;
				}
				
			}
		
};




//=====================================================================Definition of global functions===============================================================================

//--------------------------------------------------------Definition of Welcome screen----------------------------------------------------

void welcomeScreen()
{
	cout<<"\n\n\t\t\t\t\t *****************************************\n";
	cout<<"\t\t\t\t\t\t      Developed By\n";
	cout<<"\t\t\t\t\t        Ishaqullah Siddiqui (20K-0148)\n";
	cout<<"\t\t\t\t\t        Sarim Latif Khan (20K-1644)\n";
	cout<<"\t\t\t\t\t        Syed Muhib Ahmed (20K-0405)\n";
	cout<<"\t\t\t\t\t *****************************************\n";
	cout<<"\n\n\n\n\n\n\t\t\t\t\t  **************************************************";
	cout<<"\n\t\t\t\t\t  #\t\t WELCOME TO MSI PAISA\t\t   #";
	cout<<"\n\t\t\t\t\t  #\t  Pakistan's most popular digital wallet   #";
	cout<<"\n\t\t\t\t\t  **************************************************";

  //========================Giving choice whether to select admin panel or user panel====================================//

	int choice;	
	cout<<"\n\n\n\n\t\t\t\t\t   For User Panel press 1\n\t\t\t\t\t   For Admin Panel press 2\n";
	cout<<"\n\n\t\t\t\t\t   Enter your Choice: ";   
	cin>>choice;
	switch(choice)
	{
		case 1:
		{
		system("cls");
		loginPage(0);
		break;
		}
		case 2:
		{	
		system("cls");
		loginPage(1);
		break;
		
		}
		default:
		cout<<"Sorry Invalid Entry!!";
		break;
	}
}

//------------------------------------------------------------------Definition of Title------------------------------------------------------------------
void title()
{
    cout<<"\t\t\t\t\t\t***********************\n";
	cout<<"\t\t\t\t\t\t      MSI PAISA\n";
	cout<<"\t\t\t\t\t\t***********************\n";
}

//------------------------------------------------------------------Definition of Login Page------------------------------------------------------------------

void loginPage(int m)
{
	int choice;
	title();
	if(m==0)
	{
	cout<<"\n\n\n\n\t\t\t\t\t\t1.Login\n\n\n\t\t\t\t\t\t2.Signup"<<endl;
	cout<<"\n\n\n\t\t\t\t\t\tEnter your Choice: ";
	cin>>choice;
	switch(choice)
	{
		case 1:
			{
				Login obj;
				obj.details();
				break;
			}
		case 2:
			{
				signup obj1;
				obj1.details();
				break;
			}
		default:
			{
				cout<<"Invalid entry!!!";	
				break;
			}
	}
	}
	else if(m==1)
	{
		string ID,password;
		cout<<"\n\n\n\n\t\t\t\t\t\tEnter admin ID (admin): ";
		cin>>ID;
		cout<<"\n\n\n\n\t\t\t\t\t\tEnter password (admin): ";
		cin>>password;
		if(ID=="admin" && password=="admin")
		{
			Admin obj;
			obj.menu();
		}
	}
}

//------------------------------------------------------------------Definition of Gotoxy------------------------------------------------------------------
void gotoxy(int x, int y) {
COORD c ; 
c.X=x;
c.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


//=======================================================================MAIN================================================================================================


int main()
{
system("color F0");
welcomeScreen();                 //welcomeScreen() called
}
