/*************************************************************************
			     ELECTRIC BILL
**************************************************************************/

#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<iomanip.h>

 class bill
   {
     char ph_no[10];
     char name[100],add[100];
     int uni_code;
     int reading,total,unit_charge;
    public:
     void get_data();
     void display();
     int get_unicode()
      {
	return uni_code;
      }
   }s;

 void bill::get_data()
   {
     cout<<"\n\t Enter your name : ";
      gets(name);
     cout<<"\n\t Enter your unique code : ";
      cin>>uni_code;
     cout<<"\n\t Enter phone no. : ";
      gets(ph_no);
     cout<<"\n\t Enter adderess : ";
      gets(add);
     cout<<"\n\n\t Enter unit consume : ";
     cin>>reading;
   }
 void bill::display()
   {
     getch();
     clrscr();
     int rs;
     cout<<"\n\n\t name : "<<name<<endl;
     cout<<"\n\t custemer code : "<<uni_code<<endl;
     cout<<"\n\t phone no : "<<ph_no<<endl;
     cout<<"\n\t adderess : "<<add;
     cout<<"\n\n\t=> units : "<<reading<<endl;
     if(reading<50)
      {
	rs=100+reading*3.05;
	cout<<"\n********************************************************\n";
	cout<<"\n\t                     bill : "<<rs<<" Rs";
	cout<<"\n********************************************************\n";
      }
     else if (reading>50 || reading<100)
      {
	rs=100+reading*3.15;
	cout<<"\n*******************************************************\n";
	cout<<"\n\t                   bill : "<<rs<<" Rs";
	cout<<"\n*******************************************************\n";
      }
     else if (reading>100 || reading<200)
      {
	rs=100+reading*4.15;         //BASE PRICE = 100//
	cout<<"\n*******************************************************\n";
	cout<<"\n\t                   bill : "<<rs<<" Rs";
	cout<<"\n*******************************************************\n";
      }
     else if (reading<200 || reading>250)
      {
	rs=100+reading*4.25;
	cout<<"\n********************************************************\n";
	cout<<"\n\t                   bill : "<<rs<<" Rs";
	cout<<"\n********************************************************\n";
      }
     else
      {
	rs=100+reading*5.2;
	cout<<"\n********************************************************\n";
	cout<<"\n\t                   bill : "<<rs<<" Rs";
	cout<<"\n********************************************************\n";
      }
       cout<<endl;
   }

  void option();
  void menu();
  void add();
  void display_all();
  void search_uni_code();
  void modify();
  void delete1();

 //DISPLAY
 void option()
   {
     cout<<"=============================================================================\n";
     cout<<"******************************* WELLCOME ***********************************\n";
     cout<<"=============================================================================\n";
     cout<<"\n\n\t 1. add ";
     cout<<"\n\n\t 2. display ";
     cout<<"\n\n\t 3. search by unique no ";
     cout<<"\n\n\t 4. modify data ";
     cout<<"\n\n\t 5. delete ";
     cout<<"\n\n\t 6. Exit ";
     cout<<endl;
     cout<<"\n\n\n\t=> Enter your choice : ";
   }

 //MENU
 void menu()
   {
     int ch;
     option();
     cin>>ch;
     while(ch)
      {
       switch(ch)
	{
	 case 1:add();
	  break;
	 case 2:display_all();
	  break;
	 case 3:search_uni_code();
	  break;
	 case 4:modify();
	  break;
	 case 5:delete1();
	  break;
	 case 6:exit(0);
	  break;
	 default:cout<<"\n Wrong choice ";
	 cout<<"\n Enter correct input ";
	  break;
	}
       clrscr();
       option();
       cin>>ch;
      }
   }

 //TO ADD DATA
 void add()
   {
     clrscr();
     ofstream fout;
     char ch='y';
     fout.open("elec.dat",ios::out|ios::app|ios::binary);
     while(ch=='y'||ch=='Y')
      {
       s.get_data();
       fout.write((char*)&s,sizeof(s));
       cout<<"\n Want to add more data "<<endl;
       cin>>ch;
      }
     cout<<" Data has been writen ";
     fout.close();
   }

 //TO DISPLAY INFO
 void display_all()
    {
      ifstream fin;
      fin.open("elec.dat",ios::in|ios::binary);
      while(fin.read((char*)&s,sizeof(s)))
       {
	s.display();
       }
       fin.close();
       getch();
    }

 //TO SEARCH INFO USING UNIQUE CODE
 void search_uni_code()
   {
     int cus_code;
     ifstream fin;
     char ch='n';
     cout<<"\n Enter 6 digit unique code ";
     cin>>cus_code;
     fin.open("elec.dat",ios::in|ios::binary);
     while(fin.read((char*)&s,sizeof(s)))
      {
       if(s.get_unicode()==cus_code)
	{
	 s.display();
	 ch='y';
	}
      }
     if(ch=='n'||ch=='N')
      {
       cout<<cus_code<<" ...not found...";
      }
      fin.close();
      getch();
   }

 //TO MODIFY DATA USING UNI CODE
 void modify()
   {
     clrscr();
     int uni_code1,loc;
     char found='n';
     fstream fio;
     fio.open("elec.dat",ios::in|ios::out|ios::binary);
     cout<<"\n Enter the unique code whose deteils has to be modified ";
     cin>>uni_code1;
     while(fio)
      {
       loc=fio.tellg();
       fio.read((char*)&s,sizeof(s));
       if(s.get_unicode()==uni_code1)
	{
	 s.get_data();
	 found='y';
	 fio.seekg(loc);
	 fio.write((char*)&s,sizeof(s));
	 cout<<"\n\t The record of unique code "<<uni_code1<<" is modified...";
	 break;
	}
      }
       if(found=='n'||found=='N')
	{
	 cout<<"unique code "<<uni_code1<<" not found ";
	}
       fio.close();
   }

 //TO DELETE DATA
 void delete1()
   {
     int uni_code;
     char found;
     fstream fio;
     fio.open("elec.dat",ios::in | ios::out | ios::binary);
     ofstream new1;
     new1.open("elec1.dat",ios::out | ios::binary);
     ofstream out;
     out.open("elec2.dat",ios::out | ios::binary);
     cout<<"enter unique code to be deleted : ";
     cin>>uni_code;
     while(fio.read((char*)&s,sizeof(s)));
      {
       if(s.get_unicode()==uni_code)
	{
	 out.write((char*)&s,sizeof(s));
	 cout<<uni_code<<" is deleted"<<endl;
	 found='y';
	}
       else
	{
	 new1.write((char*)&s,sizeof(s));
	}
      }
       if(found=='n')
	{
	 cout<<uni_code<<" not found";
	}
	fio.close();
	new1.close();
	remove("elec.dat");
	rename("elec1.dat","elec.dat");
	cout<<"record is deleted ";
	getch();
   }

 void main()
   {
     clrscr();
     fstream fio;
     fio.open("elec.dat",ios::in|ios::out|ios::binary);
     menu();
     getch();
   }

			  //   THE  END  //
