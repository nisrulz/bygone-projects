//**********************************************************
//	Project: CD Library Management System
//	Built By: Nishant Srivastava
//**********************************************************

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <fstream.h>
#include <process.h>
fstream file1, file2;
struct f11
{
    int sr_no;
    int cas_no;
    char filmname[40];
    char filmtype[20];
    int no_cas;
    int avail;
    int charge;
};
struct f12
{
    int cust_no;
    int cust_code;
    char cust_name[20];
    char cust_addr[40];
    char filmname[40];
    int cas_no;
    int paid;
    long int doi;
};
class vlib
{
  private:
    int srno1, srno2, ccode, cucode, temp1, temp2, cno;
    f11 varf1, tempvf1;
    f12 varf2, tempvf2;
    char filename1[12], filename2[12];
    fstream file1, file2;

  public:
    vlib()
    {
        srno1 = 0;
        srno2 = 0;
        ccode = 101;
        cucode = 1001;
        cno = 0;
        gotoxy(25, 2);
        cout << "CD Library Management System";
        gotoxy(3, 3);
        file_create1();
    }
    void file_create1()
    {
        file1.open("list.dat", ios::out, ios::noreplace | ios::app);
        file1.close();
        file2.open("transrec.dat", ios::out, ios::noreplace | ios::app);
        file2.close();
    }
    void addncas();
    void issue();
    void run();
    void done1();
    void ano();
    void bno();
    void disp_lis();
    void disp_tran();
};
void vlib::addncas()
{
    char ans = 'n';
    do
    {
        clrscr();
        char inp[40], inp2[20];
        gotoxy(25, 2);
        cout << "CD Library Management System";
        gotoxy(3, 3);
        gotoxy(23, 4);
        cout << "Adding a new CD to the Library";
        gotoxy(5, 7);
        varf1.sr_no = srno1 + 1;
        varf1.cas_no = ccode;
        cout << "Film Name :\t";
        gotoxy(35, 7);
        gets(inp);
        strcpy(varf1.filmname, inp);
        gotoxy(5, 9);
        cout << "Film Type : \t";
        gotoxy(35, 9);
        gets(inp2);
        strcpy(varf1.filmtype, inp2);
        gotoxy(5, 11);
        cout << "No. of CD's : \t";
        gotoxy(35, 11);
        cin >> varf1.no_cas;
        gotoxy(5, 13);
        cout << "Rent on CD : \t";
        gotoxy(35, 13);
        cin >> varf1.charge;
        file1.open("list.dat", ios::app);
        file1.seekp(0, ios::end);
        file1.write((char *)&varf1, sizeof(varf1));
        file1.close();
        gotoxy(5, 15);
        cout << "Input More Films(y/n)";
        gotoxy(35, 15);
        cin >> ans;
        srno1++;
        ccode++;
    } while (ans == 'y' || ans == 'y');
}
void vlib::issue()
{
    char ans = 'y';
    file1.open("list.dat", ios::in);
    do
    {
        clrscr();
        char inp[40], inp2[20], inp3[40];
        gotoxy(25, 2);
        cout << "CD Library Management System ";
        gotoxy(27, 4);
        cout << "Film Name : \t";
        gotoxy(35, 7);
        gets(inp);
        char h = 'n';
        int i;
        file1.open("list.dat", ios::in | ios::out);
        file1.seekg(0, ios::beg);
        int j = 0, c = 0;
        while ((file1) && (h != 'y'))
        {
            file1.read((char *)&tempvf1, sizeof(tempvf1));
            c++;
            if ((strcmp(tempvf1.filmname, inp) == 0) && (tempvf1.avail > 0))
            {
                h = 'y';
                j = c;
            }
        }
        if (h == 'y')
        {
            strcpy(varf2.filmname, inp);
            gotoxy(5, 9);
            cout << "Customer Name:";
            gotoxy(35, 9);
            gets(inp2);
            strcpy(varf2.cust_name, inp2);
            gotoxy(5, 11);
            cout << "Customer Address:";
            gotoxy(35, 11);
            gets(inp3);
            strcpy(varf2.cust_name, inp3);
            tempvf1.avail--;
            file1.seekp((j - 1) * sizeof(tempvf1), ios::beg);
            file1.write((char *)&tempvf1, sizeof(tempvf1));
            gotoxy(5, 13);
            cout << "Amount Paid:";
            gotoxy(35, 13);
            cin >> varf2.paid;
            gotoxy(40, 13);
            cout << "Today's Date:";
            cin >> varf2.doi;
            varf2.cust_no = cno + 1;
            varf2.cust_code = cucode;
            varf2.cas_no = tempvf1.cas_no;
            file2.open("transrec.dat", ios::app);
            file2.seekp(0, ios::end);
            file2.write((char *)&varf2, sizeof(varf2));
            file2.close();
            gotoxy(5, 15);
            cout << "Any More CD's(y/n)";
            gotoxy(35, 15);
            cin >> ans;
            cno++;
            cucode++;
            file1.close();
        }
        else
        {
            ano();
            ans = 'n';
        }
    } while (ans == 'y' || ans == 'y');
    file1.close();
}
void vlib::run()
{
    char go = 'y';

    do
    {
        clrscr();
        int fld;
        gotoxy(25, 2);
        cout << "CD Library Management System";
        gotoxy(22, 12);
        cout << "[1] To Add CD's To The Library";
        gotoxy(22, 14);
        cout << "[2] Customer's Request To Library";
        gotoxy(22, 16);
        cout << "[3] CD Returns";
        gotoxy(22, 18);
        cout << "[4] List Of Movies Available";
        gotoxy(22, 20);
        cout << "[5] List Of Movies On Return";
        gotoxy(22, 22);
        cout << "[6] Exit";
        gotoxy(30, 24);
        cout << "Your Choice :  ";
        cin >> fld;
        switch (fld)
        {
        case 1:
            addncas();
            break;
        case 2:
            issue();
            break;
        case 3:
            done1();
            break;
        case 4:
            disp_lis();
            break;
        case 5:
            disp_tran();
            break;
        case 6:
            go = ' ';
            break;
        default:
            gotoxy(22, 12);
            cout << "Invalid Input";
            go = 'y';
            break;
        }
    } while (go == 'y');
}
void vlib::done1()
{
    char ans = 'y';
    do
    {
        clrscr();
        int charge;
        char inp[40], inp2[20], inp3[40], inp4[30], custname[30];
        gotoxy(25, 2);
        cout << "CD Library Management System";
        gotoxy(27, 4);
        cout << " CD Renturn detail ";
        gotoxy(5, 7);
        cout << "Film Name : ";
        gotoxy(35, 7);
        gets(inp);
        gotoxy(5, 9);
        cout << "Customers Name: ";
        gotoxy(35, 9);
        gets(inp4);
        strcpy(custname, inp4);
        char h = 'n';
        file2.open("transrec.dat", ios::in);
        int c = 0, j = 0;
        file2.seekg(0);
        while ((file2) && (h != 'y'))
        {
            file2.read((char *)&tempvf2, sizeof(tempvf2));
            if ((strcmp(tempvf2.filmname, inp) == 0) && (strcmp(tempvf2.cust_name,
                                                                custname) == 0))
            {
                h = 'y';
            }
        }
        if (h == 'y')
        {
            gotoxy(5, 11);
            cout << " Returning Date:";
            gotoxy(35, 11);
            long int date;
            cin >> date;
            date -= tempvf2.doi;
            gotoxy(5, 13);
            cout << "charge";
            gotoxy(35, 13);
            file1.open("list.date", ios::in);
            file1.seekg(0);
            while (file1)
            {
                f11 tempo;
                c++;
                file1.read((char *)&tempo, sizeof(tempo));
                if ((strcmp(tempo.filmname, inp) == 0))
                {
                    charge = tempo.charge * date;
                    j = c;
                }
            }
            cout << " Charge ";
            gotoxy(5, 15);
            cout << "Amount Paid:";
            gotoxy(35, 15);
            cout << tempvf2.paid;
            gotoxy(5, 15);
            cout << "Amount To Be Paid :";
            gotoxy(35, 15);
            cout << (charge - tempvf2.paid);
            tempvf1.avail++;
            file1.seekp((j - 1) * sizeof(tempvf1), ios::beg);
            file1.write((char *)&tempvf1, sizeof(tempvf1));
            gotoxy(5, 15);
            cout << "Any More CD's(Y/N) ";
            gotoxy(35, 15);
            cin >> ans;
        }
        else
        {
            bno();
            ans = 'n';
        }
        file1.close();
    } while (ans == 'y' || ans == 'Y');
    file2.close();
}
void vlib::ano()
{
    gotoxy(22, 12);
    cout << "The Reqested CD's Is Not Available:";
    getch();
}
void vlib::bno()
{
    gotoxy(22, 12);
    cout << "Reqested CD's Is Not Ours";
    getch();
}
void vlib::disp_lis()
{
    f11 displ;
    file1.open("list.dat", ios::in);
    file1.seekg(0, ios::beg);
    cout << "The List Of CD's Available Is:" << endl;
    file1.read((char *)&displ, sizeof(displ));
    while (file1)
    {
        cout << displ.sr_no << '\t' << displ.cas_no;
        cout << '\t' << displ.no_cas << '\t';
        cout << displ.filmname;
        cout << '\t' << displ.filmtype << '\t';
        cout << displ.avail << '\t';
        cout << displ.charge << endl;
        file1.read((char *)&displ, sizeof(displ));
    }
    file1.close();
    getch();
}
void vlib::disp_tran()
{
    f12 disp1;
    file2.open("transrec.dat", ios::in);
    file2.seekg(0, ios::beg);
    cout << "The CD's on Rent Are:  " << endl;
    file2.read((char *)&disp1, sizeof(disp1));
    while (file2)
    {
        cout << disp1.cust_no << '\t';
        cout << disp1.cas_no;
        cout << '\t' << disp1.filmname << '\t';
        cout << disp1.cust_name;
        cout << '\t' << disp1.cust_addr << '\t';
        cout << disp1.doi << endl;
        file2.read((char *)&disp1, sizeof(disp1));
    }
    file2.close();
    getch();
}
void main()
{
    clrscr();
    vlib v1;
    v1.run();
}