//**********************************************************
//	Project: Phone Directory
//	Built By: Nishant Srivastava
//**********************************************************

#include <fstream.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void dev()
{
  clrscr();
  gotoxy(35, 19);
  cout << "Developed By...";
  gotoxy(27, 22);
  cout << "Nishant Srivastava";
  getch();
}
long double count = 0;
struct customer
{
  char name[40];
  long double phone;
};
void getdata();
int search_ph(char *s);
int search_nm(long ph);
void mod_data();
void getdata(customer &c)
{
  char ch;
  cin.get(ch);
  clrscr();
  gotoxy(15, 10);
  cout << "Add Customer Data \n";
  gotoxy(17, 12);
  cout << "Record #" << (++count) << endl;
  gotoxy(1, 14);
  for (int i = 0; i < 40; i++)
    c.name[i] = ' ';
  c.phone = 0;
  cout << "Enter name:";
  cin.getline(c.name, 40);
  cout << "\n Enter phone number:";
  cin >> c.phone;
  cout << "\n";
}
void display(customer c)
{
  clrscr();
  gotoxy(15, 10);
  cout << "Customer Details \n";
  gotoxy(1, 12);
  cout << "Name:" << c.name << "\t";
  cout << "Phone:" << c.phone << "\n";
}
void mod_data(customer &c)
{
  char nm[40], cph[8];
  clrscr();
  gotoxy(15, 8);
  cout << "Modify customer data \n"
       << endl;
  char ch = cin.get();
  cout << ch;
  gotoxy(17, 10);
  cout << "Current details \n";
  gotoxy(17, 11);
  cout << "___________ \n\n";
  cout << "Name:" << c.name << "\t Phone:" << c.phone << endl;
  gotoxy(17, 16);
  cout << "Enter new details \n";
  gotoxy(17, 17);
  cout << "___________\n\n";
  gotoxy(10, 24);
  cout << "If you want to retain old name,just Press enter";
  gotoxy(50, 17);
  cout << endl;
  cout << "Name:";
  cin.getline(nm, 40);
  cout << "Phone:";
  cin.getline(cph, 8);
  if (strlen(nm) != 0)
    strcpy(c.name, nm);
  if (strlen(nm) != 0)
    c.phone = atol(cph);
  gotoxy(10, 24);
  clreol();
}
fstream finout;
int main()
{
  clrscr();
  customer cust;
  finout.open("customer.dat", ios::in | ios::out | ios::binary);
  if (!finout)
  {
    cout << "Cannot open file!! \n";
    return 1;
  }
  int choice, mrec, offset;
  long ph;
  char nm[40], ans, ch;
  for (int i = 0; i < 40; i++)
    nm[i] = ' ';
  do
  {
    clrscr();
    cout << "\n\n\t\t\t\t MAIN MENU \n\n";
    cout << "\t\t            \n"
         << endl;
    cout << "\t\t\t 1.Add Record.\n"
         << endl;
    cout << "\t\t\t 2.Modify Record.\n"
         << endl;
    cout << "\t\t\t 3.Search for a name.\n"
         << endl;
    cout << "\t\t\t 4.Search for a phone number.\n"
         << endl;
    cout << "\t\t\t 5.Exit.\n"
         << endl;
  ra:
    cout << "\n\t\t\t Enter Your choice..(1-5)..";
    cin >> choice;
    switch (choice)
    {
    case 1:
      getdata(cust);
      mrec = count;
      offset = ((mrec - 1) * sizeof(customer));
      finout.seekp(offset, ios::beg);
      finout.write((char *)&cust, sizeof(customer));
      break;
    case 2:
      if (!count)
      {
        cout << "No record has been added yet. \n";
        cout << "Please run option 1 first of all \n\n";
        gotoxy(10, 23);
        cout << "Press a key to continue... \n";
        getch();
        break;
      }
      cout << "\n\nModify Which Phone Number?";
      cin >> ph;
      mrec = search_nm(ph);
      if (mrec == 0)
      {
        cout << " \n\n\n No such Phone number exists \n";
        gotoxy(15, 23);
        cout << "Press a key to continue.." << endl;
        getch();
        break;
      }
      else
      {
        offset = (mrec - 1) * sizeof(customer);
        finout.seekg(offset, ios::beg);
        finout.read((char *)&cust, sizeof(customer));
        display(cust);
        cout << "Modify this record?(y/n)..";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
        {
          cout << "Enter new details \n";
          mod_data(cust);
          finout.seekp(offset, ios::beg);
          finout.write((char *)&cust, sizeof(customer));
          cout << "\n Record Modified\n";
          gotoxy(30, 24);
          cout << "Press a key to continue.." << endl;
          getch();
        }
        break;
      }
    case 3:
      if (!count)
      {
        cout << "\n\n\n\nNo Record has been added yet\n";
        cout << "Please run option 1 first of all\n\n";
        gotoxy(10, 23);
        cout << "Press a key to continue...";
        getch();
        break;
      }
      cout << "\n\n Search Which Name ?";
      cin.get(ch);
      cin.getline(nm, 40);
      mrec = search_ph(nm);
      if (mrec == 0)
      {
        cout << "\n\n\n No such Name exists \n";
        gotoxy(15, 23);
      ad:
        cout << "Press a key to continue(y/n)..." << endl;
        char s;
        cin >> s;
        if (s == 'y' || s == 'Y')
        {
          continue;
        }
        else if (s == 'n' || s == 'N')
        {
          break;
        }
        else
        {
          cout << "Invalid input\n";
          goto ad;
        }
        getch();
        break;
      }
      else
      {
        offset = (mrec - 1) * sizeof(customer);
        finout.seekg(offset, ios::beg);
        finout.read((char *)&cust, sizeof(customer));
        display(cust);
        gotoxy(10, 23);
        cout << "Press a key to continue...\n";
        getch();
      }
      break;
    case 4:
      if (!count)
      {
        cout << "\n\n\n\nNo Record has been added yet\n";
        cout << "Please run option 1 first of all\n\n";
        gotoxy(10, 23);
        cout << "Press a key to continue...";
        getch();
        break;
      }
      cout << "\n\n Search Which phone number?";
      cin >> ph;
      mrec = search_nm(ph);
      if (mrec == 0)
      {
        cout << "\n\n\nNo such phone number exists.\n";
        gotoxy(15, 23);
      ab:
        cout << "Press a key to continue(y/n)..." << endl;
        char s;
        cin >> s;
        if (s == 'y' || s == 'Y')
        {
          continue;
        }
        else if (s == 'n' || s == 'N')
        {
          break;
        }
        else
        {
          cout << "Invalid input\n";
          goto ab;
        }
        getch();
        break;
      }
      else
      {
        offset = (mrec - 1) * sizeof(customer);
        finout.seekg(offset, ios::beg);
        finout.read((char *)&cust, sizeof(customer));
        display(cust);
        gotoxy(10, 23);
        cout << "Press a key to continue...\n";
        getch();
      }
      break;
    case 5:
      clrscr();
      cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tTHANKS FOR VISIT";
      getch();
      dev();
      break;
    default:
      cout << "\n\n\n\t\t\tWrong choice!!Valid choices are 1-5.\n";
      goto ra;
      clrscr();
    }
  } while (choice >= 1 && choice <= 3);
  return 0;
}
int search_ph(char *s)
{
  finout.seekg(0);
  int ctr = 0, flag;
  customer cs;
  while (ctr <= count)
  {
    finout.seekg((ctr * sizeof(customer)), ios::beg);
    finout.read((char *)&cs, sizeof(customer));
    ctr++;
    if ((strcmpi(cs.name, s)) == 0)
      return ctr;
  }
  return 0;
}
int search_nm(long ph)
{
  finout.seekg(0);
  int ctr = 0;
  customer cs;
  while (ctr <= count)
  {
    finout.seekg((ctr * sizeof(customer)), ios::beg);
    finout.read((char *)&cs, sizeof(customer));
    ctr++;
    if (cs.phone == ph)
      return ctr;
  }
  return 0;
}
