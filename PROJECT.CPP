/********************************************
 This is the Library management system
    project made by Vaibhav Anuragi
********************************************/

//Required Headers files
#include<iostream>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iomanip>

//Required class in program
class book
{	char bno[6];
	char bname[50];
	char aname[20];
public:
	void create_book()
	{
		cout << "\n.....NEW BOOK ENTRY.....";
		cout << "\nEnter Book Number ";
		cin >> bno;
		cout << "\nEnter The Name of the Book ";
		gets(bname);
		cout << "\nEnter The Name of its Author ";
		gets(aname);
		cout << "\n\nBOOK CREATED ";
	}
	void show_book()
	{
		cout << "\nBook Number : " << bno;
		cout << "\nBook Name : ";
		puts(bname);
		cout << "Author Name ; ";
		puts(aname);
	}
	void modify_book()
	{
		cout << "\nBook Number " << bno;
		cout << "\nModify Book Name ";
		gets(bname);
		cout << "\nModify Name of The Book Author ";
		gets(aname);
	}
	char *retbno()
	{
		return bno;
	}
	void report()
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
};                    //End of the Class

class student
{	char admno[6];
	char name[30];
	char stbno[6];
	int card;
public:
	void create_student()
	{
		clrscr();
		cout << "\n.....NEW STUDENT ENTERY.....";
		cout << "\nEnter The Admission number of the Student ";
		gets(admno);
		cout << "Enter The Name of the Student ";
		gets(name);
		card = 0;
		stbno[0] = '/0';
		cout << "\n\nSTUDENT RECORD CREATED ";
	}
	void show_student()
	{
		cout << "\nAdmission number : " << admno;
		cout << "\nStudent name : ";
		puts(name);
		cout << "\nNumber of books issued : " << card;
		if (card == 0)
			cout << "\nBook Number " << stbno;
	}
	void modify_student()
	{	cout << "\nAdmission Number " << admno;
		cout << "\nModify Student name ";
		gets(name);
	}
	char *retadmno()
	{
		return admno;
	}
	char *retstbno()
	{
		return stbno;
	}
	int retcard()
	{
		return card;
	}
	void addcard()
	{
		card = 1;
	}
	void resetcard()
	{
		card = 0;
	}
	void getstbno(char s[])
	{
		strcpy(stbno, s);
	}
	void report()
	{
		cout << "\t" << admno << setw(20) << name << setw(30) << card << "\n";
	}
};		    //End of the Class

//Global declaration of stream object
fstream fp, f;
student st;
book bk;

//Function to write in file
void write_book()
{
	char ch;
	fp.open("Book.dat", ios::out | ios::app);
	do
	{
		clrscr();
		bk.create_book();
		fp.write((char*)&bk, sizeof(book));
		cout << "\n\nDo you want to add more records?.....(Y/N) ";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	fp.close();
}
void write_student()
{
	char ch;
	fp.open("Student.dat", ios::out | ios::app);
	do
	{
		st.create_student();
		fp.write((char*)&st, sizeof(student));
		cout << "\n\nDo you want to add more records?.....(Y/N) ";
		cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	fp.close();
}
//Function to read specific record from file
void display_spb(char n[])
{
	cout << "\n\tBOOK DETAILS\n ";
	int flag = 0;
	fp.open("Book.dat", ios::in);
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) == 0)
		{
			bk.show_book();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "Book NOT FOUND ";
	getch();
}
void display_sps(char n[])
{
	cout << "\n\tSTUDENT DEATILS\n";
	int flag = 0;
	fp.open("Student.dat", ios::in);
	while (fp.read((char*)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) == 0)
		{
			st.show_student();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "Student NOT FOUND ";
	getch();
}
//Function to modify record of file
void modify_book()
{
	char n[6];
	int found = 0;
	clrscr();
	cout << "\n\n\t.....MODIFY BOOK RECORD.....";
	cout << "\n\n\tEnter The book number ";
	cin >> n;
	fp.open("Book.dat", ios::in | ios::out);
	while (fp.read((char*)&bk, sizeof(book)) && found == 0)
	{
		if (strcmpi(bk.retbno(), n) == 0)
		{
			bk.show_book();
			cout << "\nEnter The new details of book \n";
			bk.modify_book();
			int pos = -1 * sizeof(bk);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&bk, sizeof(book));
			cout << "\n\n\t Record Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << "Record NOT FOUND";
	getch();
}
void modify_student()
{
	char n[6];
	int found = 0;
	clrscr();
	cout << "\n\n\t.....MODIFY STUDENT RECORD.....";
	cout << "\n\n\tEnter The admission number of the student ";
	cin >> n;
	fp.open("Student.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), n) == 0)
		{
			st.show_student();
			cout << "\nEnter The new details of student \n";
			st.modify_student();
			int pos = -1 * sizeof(st);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&st, sizeof(student));
			cout << "\n\n\tRecord Updated";
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
		cout << "\n\nRecord NOT FOUND";
	getch();
}

//Function to delete record of file
void delete_student()
{
	char n[6];
	int flag = 0;
	clrscr();
	cout << "\n\n\t.....DELETE STUDENT.....";
	cout << "\n\n\tEnter The admission number of Student whose record you want to Delete : ";
	cin >> n;
	fp.open("Student.dat", ios::in | ios::out);
	fstream f0;
	f0.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&st, sizeof(student)))
	{
		if (strcmpi(st.retadmno(), n) != 0)
			f0.write((char*)&st, sizeof(student));
		else
			flag = 1;
	}
	f0.close();
	fp.close();
	remove("Student.dat");
	rename("Temp.dat", "Student.dat");
	if (flag == 1)
		cout << "\n\n\tRecord Deleted ";
	else
		cout << "\n\nRecord NOT FOUND";
	getch();
}
void delete_book()
{
	char n[6];
	clrscr();
	cout << "\n\n\n\t.....DELETE BOOK.....";
	cout << "\n\nEnter The Book number whose record you want to Delete : ";
	cin >> n;
	fp.open("Book.dat", ios::in | ios::out);
	fstream f0;
	f0.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (strcmpi(bk.retbno(), n) != 0);
		{
			f0.write((char*)&bk, sizeof(book));
		}
	}
	f0.close();
	fp.close();
	remove("Book.dat");
	rename("Temp.dat", "Book.dat");
	cout << "\n\n\tRecord Deleted ";
	getch();
}

//Function to display All Students list
void display_alls()
{
	clrscr();
	fp.open("Student.dat", ios::in);
	if (!fp)
	{
		cout << "ERROR!! File could not be open ";
		getch();
		exit(0);
	}
	cout << "\n\n\t\t\t STUDENT LIST\n\n";
	cout << "================================================================\n";
	cout << "Admission number " << setw(20) << "Name " << setw(28) << "Book Issued\n";
	cout << "================================================================\n";
	while (fp.read((char*)&st, sizeof(student)))
	{
		st.report();
	}
	fp.close();
	getch();
}

//Function to display Books list
void display_allb()
{
	clrscr();
	fp.open("Book.dat", ios::in);
	if (!fp)
	{	cout << "ERROR!! File could not be open ";
		getch();
		exit(0);
	}
	cout << "\n\n\t\t\t Book List\n\n";
	cout << "================================================================\n";
	cout << "Book number " << setw(20) << "Book name " << setw(33) << "Author\n";
	cout << "================================================================\n";
	while (fp.read((char*)&bk, sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	getch();
}

//Function to issue book
void book_issue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	clrscr();
	cout << "\n\n\t.....BOOK ISSUE.....";
	cout << "\n\n\tEnter The admission number of the student ";
	cin >> sn;
	fp.open("Student.dat", ios::in | ios::out);
	f.open("Book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.retcard() == 0)
			{
				cout << "\n\n\tEnter the book number ";
				cin >> bn;
				while (f.read((char*)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), bn) == 0)
					{
						bk.show_book();
						flag = 1;
						st.addcard();
						st.getstbno(bk.retbno());
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\t Book issued successfully";
						cout << "\n\n NOTE: Write the current date of book issue on the backside of the Book, ";
						cout << "\n       And submit it within 15 days because after the given period of ";
						cout << "\n       time there will a fine of Rs.1 for each day";
					}
				}
				if (flag == 0)
					cout << "Book NOT FOUND";
			}
			else
				cout << "You have not returned the last book! ";
		}
	}
	if (found == 0)
		cout << "Student record NOT FOUND ";
	getch();
	fp.close();
	f.close();
}

//Function to deposit book
void book_deposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	clrscr();
	cout << "\n\n\t.....BOOK DEPOSIT.....";
	cout << "\n\n\tEnter The admission number of the student ";
	cin >> sn;
	fp.open("Student.dat", ios::in | ios::out);
	f.open("Book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.retcard() == 1)
			{
				while (f.read((char*)&bk, sizeof(book)) && flag == 0)
				{
					if (strcmpi(bk.retbno(), st.retstbno()) == 0)
					{
						bk.show_book();
						flag = 1;
						cout << "\n\nBook deposited in How many days? ";
						cin >> day;
						if (day > 15)
						{
							fine = 1 * (day - 15);
							cout << "\n\nFine of Rs." << fine << " has to be deposited ";
						}
						st.resetcard();
						int pos = -1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\t Book deposited successfully ";
					}
				}
				if (flag == 0)
					cout << "Book number does not exist";

			}
			else
				cout << "No book is issued..Please check!!";
		}
	}
	if (found == 0)
		cout << "Student NOT FOUND ";
	getch();
	fp.close();
	f.close();
}

//Function for Introduction
void intro()
{
	clrscr();
	//Pattern to introduce the user
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 80; j++)
			{
				if (i == 3 && j == 35)
				{	cout << " #LIBRARY ";
					j = j + 7;
				}
				else if (i == 4 && j == 32)
				{	cout << " MANAGEMENT ";
					j = j + 9;
				}
				else if (i == 5 && j == 32)
				{	cout << " SYSTEM ";
					j = j + 11;
				}
				else if ((i == 2 && j == 38) || (i == 6 && j == 38))
				{	cout << "    ";
					j = j + 3;
				}
				else if ((i == 1 && j == 39) || (i == 7 && j == 39))
				{	cout << "  ";
					j = j + 1;
				}
				else
					cout << "*";
			}
	}
	cout << "\n\n\t\t\t    Made By: VAIBHAV ANURAGI ";
	cout << "\n\n\t\t\t   School: KENDRIYA VIDYALAYA ";
	getch();
}

//Administrator Menu Function
void admin_menu()
{
	clrscr();
	int x;
	cout << "\n\n\n\t+++++Administrator Menu+++++";
	cout << "\n\n\t1) Create student Record";
	cout << "\n\n\t2) Display All Students Record";
	cout << "\n\n\t3) Display Specific Student Record";
	cout << "\n\n\t4) Modify Student Record";
	cout << "\n\n\t5) Delete Student Record";
	cout << "\n\n\t6) Create Book";
	cout << "\n\n\t7) Display All Books";
	cout << "\n\n\t8) Display Specific Book";
	cout << "\n\n\t9) Modify Book";
	cout << "\n\n\t10) Delete Book";
	cout << "\n\n\t11) Back to Main menu";
	cout << "\n\n\tPLEASE ENTER YOUR CHOICE (1-11) ";
	cin >> x;

	switch (x)
	{
	case 1: clrscr();
		write_student();
		break;
	case 2: display_alls();
		break;
	case 3: {
		clrscr();
		char num[6];
		cout << "\n\n\tPlease Enter the Admission number ";
		cin >> num;
		display_sps(num);
		break;
	}
	case 4: modify_student();
		break;
	case 5: delete_student();
		break;
	case 6: clrscr();
		write_book();
		break;
	case 7: display_allb();
		break;
	case 8: {
		clrscr();
		char num[6];
		cout << "\n\n\tPlease Enter the Book number ";
		cin >> num;
		display_spb(num);
		break;
	}
	case 9: modify_book();
		break;
	case 10: delete_book();
		break;
	case 11: return;
	default: cout << "\a";
	}
	admin_menu();
}

//The Main Function of the program
void main()
{
	char ch;
	intro();
	do
	{
		clrscr();
		cout << "\n\n\n\t******MAIN MENU******";
		cout << "\n\n\t(1) Book Issue";
		cout << "\n\n\t(2) Book Deposite";
		cout << "\n\n\t(3) Administrator Menu";
		cout << "\n\n\t(4) Exit";
		cout << "\n\n\tPLEASE SELECT YOUR CHOICE (1-4) ";
		ch = getche();
		switch (ch)
		{
		case '1': clrscr();
			book_issue();
			break;
		case '2': book_deposit();
			break;
		case '3': admin_menu();
			break;
		case '4': exit(0);
		default: cout << "\a";
		}
	} while (ch != '4');
}

/********************************************
	 END OF THE PROJECT
 ********************************************/
