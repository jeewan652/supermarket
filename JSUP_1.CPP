//        ********************************************************
//                     HEADER FILES  USED IN  PROGRAM
//        ********************************************************
#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<process.h>
#include<dos.h>
//        ********************************************************
//                       CLASS  USED IN  PROGRAM
//        ********************************************************
class product
{
int pno;
char name[50];
float price, tax, qty, dis;
public:
void create_product()
   {
cout<<"\t  Enter the product no. of the product: ";
cin>>pno;
cout<<"\t  Enter the name of the product       : ";
gets(name);
cout<<"\t  Enter the price of the product      : ";
cin>>price;
cout<<"\t  Enter the discount                  : ";
cin>>dis;
  }
void show_product()
     {
cout<<"\n\t  Product no. of the product: "<<pno;
cout<<"\n\t  Name of the product       : ";
puts(name);
cout<<"\n\t  Price of the product      : "<<price;
cout<<"\n\t  Discount                  : "<<dis;
      }
int  retpno()
{return pno;}

float retprice()
  {return price;}

char* retname()
  {return name;}

int retdis()
  {return dis;}

 };
//          ********************************************************
//               GLOBAL DECALARATION OF STREAM OBJECT, OBJECT
//          ********************************************************
fstream fp;
product pr;
//          ********************************************************
//                         FUNCTION TO WRITE IN FILE
//          ********************************************************
void write_product()
    {
fp.open("Shop.dat",ios::out|ios::app);
pr.create_product();
fp.write((char*)&pr,sizeof(product));
fp.close();
cout<<"\n\n\t  Product has bean created ";
getch();
    }
//          ********************************************************
//                  FUNCTIONN TO READ ALL RECORDS FROM FILE
//          ********************************************************
void display_all()
    {   clrscr();
	int flag=0;
	cout<<"\n\n\n\t\t  DISPLAY ALL RECORD !!!\n\n";
	fp.open("shop.dat",ios::in);
	while(fp.read((char*)&pr,sizeof(product)))
	    {
	pr.show_product();
	flag=1;
	cout<<"\n�������������������������������������������������������\n";
	getch();
	     }
	fp.close();
	if(flag==0)
	cout<<"\n\n\t Record not exist";
	getch();
      }
//          ********************************************************
//                 FUNCTION TO READ SPECIFIC RECORD FROM FILE
//          ********************************************************

void display_sp(int n)
    {
int flag=0;
fp.open("shop.dat",ios::in);
while(fp.read((char*)&pr,sizeof(product)))
       {
	if(pr.retpno()==n)
	  {
	clrscr();
	pr.show_product();
	flag=1;
	       }
	  }
fp.close();
if(flag==0)
	cout<<"\n\n\t Record not exist";
	getch();
       }
//         ********************************************************
//                    FUNCTION TO MODIFY RECORD OF FILE
//         ********************************************************
void modify_product()
    {
int no,found=0;
clrscr();
cout<<"\n\n\t\t   TO MODIFY:-";
cout<<"\n\t\t  =============";
cout<<"\n\t Enter the product no.: ";
cin>>no;
fp.open("shop.dat",ios::in|ios::out);
while(fp.read((char*)&pr,sizeof(product)) && found==0)
       {
	if(pr.retpno()==no)
	  {
	pr.show_product();
	cout<<"\n\n\t #.ENTER THE NEW DETAILS:- "<<endl;
	pr.create_product();
	int pos=-1*sizeof(pr);
	fp.seekp(pos,ios::cur);
	fp.write((char*)&pr,sizeof(product));
	cout<<"\n\n\t           RECORD UPDATED....";
	found=1;
	    }
	 }
fp.close();
if(found==0)
cout<<"\n\n\t RECORD NOT FOUND ";
getch();
    }
//         ********************************************************
//                    FUNCTION TO DELETE RECORD FROM FILE
//         ********************************************************
void delete_product()
     {
int no;
clrscr();
cout<<"\n\n\n";
cout<<"\n\t\t       +----------------+";
cout<<"\n\t\t       | DELETE REOCORD |";
cout<<"\n\t\t       +----------------+";
cout<<"\n\t   Enter product no. of product to be deleted: ";
cin>>no;
fp.open("shop.dat",ios::in|ios::out);
fstream fp2;
fp2.open("temp.dat",ios::out);
fp.seekg(0, ios::beg);
while(fp.read((char*)&pr,sizeof(product)))
	{
	if(pr.retpno()!=no)
	     {
	fp2.write((char*)&pr,sizeof(product));
	       }
	  }
fp2.close();
fp.close();
remove("shop.dat");
rename("temp.dat","shop.dat");
if(pr.retpno()!=no)
       {
cout<<"\n\n\n\t\t *...RECORD NOT FOUND TO DELETE...*";
       }
else
       {cout<<"\n\n\n\t\t          *.RECORD DELETED.*";
	}
getch();
       }
//        ********************************************************
//               FUNCTION TO DISPLAY ALL PRODUCTS PRICE LIST
//        ********************************************************
void menu()
    {   clrscr();
fp.open("shop.dat",ios::in);
if(!fp)
       {
	cout<<"\n\t ERROR!!! FILE COULD NOT BE OPEN";
	cout<<"\n\t GO TO ADMIN MENU TO CREATE FILE";
	cout<<"\n\n\n\t PROGRAM IS CLOSING.....";
	getch();
	exit(0);
	}
cout<<"\n\n\n";
cout<<"\t         ������������������Ŀ\n";
cout<<"\t         �   PRODUCT MENU   �\n";
cout<<"\t���������������������������������������ͻ\n";
cout<<"\t�  P.No.  �      NAME      �   PRICE    �\n";
cout<<"\t���������������������������������������͹\n";
while(fp.read((char*)&pr,sizeof(product)))
   {
cout<<"\t�"<<pr.retpno()<<"\t"<<pr.retname()<<"\t"<<pr.retprice()<<"\t\t�"<<endl;
	 }
cout<<"\t���������������������������������������ͼ\n";

fp.close();
  }
//       ***********************************************************
//         FUNCTION TO PLACE ORDER & GERNERATING BILL FOR PRODUCT
//       ***********************************************************
void place_order()

{ int choice;
int order_arr[50],quan[50],c=0;
float amt,damt,total=0;
char ch='Y';
menu();
cout<<"\n\n\n";
cout<<"\t\t  #.PRESS '1' TO PROCEED\n";
cout<<"\t\t  #.PRESS '2' TO RETURN BACK TO MENU\n";
cout<<"\n\t\t  Enter your choice (1-2): ";
choice=getch();
switch(choice)
      {
	case '1':cout<<"\n\t\t   �������������������͸";
	cout<<"\n\t\t   � PLACE YOUR ORDER  �";
	cout<<"\n\t\t   �������������������;";
		do
	       {
		cout<<"\n\t\t Enter the product no. : ";
		cin>>order_arr[c];
		cout<<"\t\t Quantity in number    : ";
		cin>>quan[c];
		c++;
		cout<<"\n\n\t\t ORDER MORE PRODUCT..?(y/n): ";
		ch=getch();
		}
	while(ch=='y'|| ch=='Y');
	cout<<"\n\n\t\tTHANK YOU FOR PLACING THE ORDER";

	clrscr();
	cout<<"\n\n\n\n\n\n\n\n\n\t\t\t    LOADING";
	for(int i=1;i<=6;i++)
	{ cout<<".";delay(500);
	  }

	clrscr();
	cout<<" �����������������������������������INVOICE������������������������������������\n";
	cout<<" Pr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after Discount\n";
	for(int x=0;x<=c;x++)
	 {
	fp.open("shop.dat",ios::in);
	fp.read((char*)&pr,sizeof(product));
	while(!fp.eof())
	      {
		if(pr.retpno()==order_arr[x])
		     {
		amt=pr.retprice()*quan[x];
		damt=amt-(amt*pr.retdis()/100);
	cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<" \t"<<quan[x]<<"\t\t"<<pr.retprice()<<" \t"<<amt<<"\t\t"<<damt;
		total+=damt;
		     }
		fp.read((char*)&pr,sizeof(product));
	       }
	fp.close();
	 }
	cout<<"\n\n\t\t\t\t  TOTAL = "<<total;
	cout<<"\n\n\t\t\t  *.THANK YOU VISIT AGAIN.*\n";
		getch();
	break;
	case '2':break;
	default:cout<<"\a";menu();

       }
      }
//         ********************************************************
//                         ADMINSTRATION MENU FUNCTION
//         ********************************************************
void admin_menu()
{
clrscr();
char ch2;
cout<<"\n\n\n";
cout<<"\n\t              �������������������������͸          ";
cout<<"\n\t    ���������͵ *.ADMINISTRATION MENU.* ���������ͻ";
cout<<"\n\t    �         �������������������������;         �";
cout<<"\n\t    �   1.CREATE PRODUCT                          �";
cout<<"\n\t    �   2.DISPLAY ALL PRODUCT                     �";
cout<<"\n\t    �   3.QUERY                                   �";
cout<<"\n\t    �   4.MODIFY PRODUCT                          �";
cout<<"\n\t    �   5.DELETE PRODUCT                          �";
cout<<"\n\t    �   6.VIEW PRODUCT MENU                       �";
cout<<"\n\t    �   7.BACK TO THE MAIN MENU                   �";
cout<<"\n\t    ���������������������������������������������ͼ";
   ch2=getche();
switch(ch2)
   {
case '1': clrscr();
		write_product();
		break;
case '2': display_all();
		break;
case '3':
		int num;
		clrscr();
		cout<<"\n\n\t Enter the product no. ";
		cin>>num;
		display_sp(num);
		break;
case '4': modify_product();
		break;
case '5': delete_product();
		break;
case '6': menu();
		getch();
case '7': break;
default:cout<<"\a";admin_menu();
      }
    }
//        ********************************************************
//                    THE MAIN FUNCTION OF PROGRAM
//        ********************************************************
void main()
{
char ch;
int ro();
char username[10];
int pass;

clrscr();
cout<<"\n\n\n\n";
cout<<"\t����� �   � ����� ������ ������ ��   �� ����� ����� �  � ����� �������"<<endl;
delay(400);
cout<<"\t�     �   � �   � �      �    � � � � � �   � �   � � �  �        �   "<<endl;
delay(400);
cout<<"\t����� �   � ����� ���    ������ �  �  � ����� ����� ��   ���      �   "<<endl;
delay(400);
cout<<"\t    � �   � �     �      ��     �     � �   � ��    � �  �        �   "<<endl;
delay(400);
cout<<"\t����� ����� �     ������ � �    �     � �   � � �   �  � �����    �   "<<endl;
delay(400);
cout<<"\t\t\t\t �  �                 �  �                    "<<endl;
delay(400);
cout<<"\t\t\t\t     �                    �                   "<<endl;
delay(600);
cout<<"\n\n";
cout<<"\t\t\t      BiLLiNG SYSTEM\n";
cout<<"\t\t\t     ����������������\n";
cout<<"\n\n\n\n\n\n\n\t\t\t\t\t\t\t    MADE BY: Jeewan kundu";
cout<<        "\t\t\t\t\t\t\t\t     -----------";
delay(1000);

clrscr();
cout<<"\n\n\n\n\n\n\n\n\n";
cout<<"\t\t\t\tLOGIN\n\n";
cout<<"\t\t\t USERNAME: ";
gets(username);
cout<<"\n\t\t\t PASSWORD: ";
cin>>pass;
if(pass==7509)
      {

clrscr();
cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t     LOADING";
for(int i=0;i<=6;i++)
{ cout<<".";
	delay(300);
	}
clrscr();
cout<<"\n\n\n\n\n\n\n\t\t\t PRESS 'ENTER' TO PROCEED";
      }
else
    {
clrscr();
cout<<"\n\n\n\n\n\n\n\t\t      INVALID USERNAME & PASSWORD...!";
delay(700);
clrscr();
cout<<"\n\n\n\n\n\n\n\n\n\t\t   TAKING YOU OUT FROM THE PROGRAM";
for(int i=0;i<=6;i++)
{  cout<<".";
	delay(900);
	 }
	exit(0);
       }
      do
      {
	clrscr();
	cout<<"\n\n\n\n";
	cout<<"\n\t               ���������������͸";
	cout<<"\n\t      ��������͵ *.MAIN MENU.* ���������ͻ";
	cout<<"\n\t      �        ���������������;         �";
	cout<<"\n\t      �                                  �";
	cout<<"\n\t      �    1.CUSTMER                     �";
	cout<<"\n\t      �    2.AMINISTRATIN                �";
	cout<<"\n\t      �    3.EXIT                        �";
	cout<<"\n\t      �                                  �";
	cout<<"\n\t      ����������������������������������ͼ";
	cout<<"\n\n\t    SELECT YOUR OPTION(1-3): ";
	ch=getche() ;
	switch(ch)
	 {
	case '1': clrscr();
		place_order();
		getch();
		break;
	case '2': admin_menu();
		break;
	case '3': exit(0);
	default:cout<<"\a";
	   }
}while(ch!='3');
}

























