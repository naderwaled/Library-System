#include "stdafx.h"
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<time.h>
#include<conio.h>
#include<istream>

using namespace std;
// to time
struct tm time1() {
	time_t now;
	struct tm today; //tm include day and month and year and time (seconds , minutes , hours )
	now = time(NULL); //get the time from computer
	today = *localtime(&now);

	return today;
};

struct date {
	string day;
	string month;
	string year;
};

struct books {
	string id_of_book;
	string name_of_book;
	string author;
	string year;
	string status_book;
	string name_of_ismember;
	date start_of_time;
	date end_of_time;
	int numberword = 0;
};

struct members {
	string id_of_member;
	string name_of_member;
	string pass_of_member;
	date date_of_member;
	string status_member;
	int number_isbooks = 0;
};

struct isbooks 
{
	string id_of_book;
	string name_of_book;
	date start_of_time;
	date end_of_time;
};

int error;  //to check valid choice
string arr_of_words[1000][10000];  //to storage text of books
isbooks arr_of_isbooks[1000][5];   //to storage borrowing books

void Input(books arr_of_books[1000], int& book_id, members arr_of_members[1000], int& member_id, string calender1[370][2]);

string readpassword(string pass);

bool loginadmin();

int loginmember(members arr_of_members[1000], int member_id);

void display_books(books arr_of_books[1000], int i);

void display_members(members arr_of_members[1000], int i);

string search_idbook(string id, int book_id, books arr_of_books[1000]);

int addbook(int book_id, books arr_of_books[1000]);

string search_idmember(string id, int member_id, members arr_of_members[1000]);

int addmember(int member_id, members arr_of_members[1000]);

void search_of_book(books arr_of_books[1000], int book_id, string arr_of_words[1000][10000]);

void search_of_member(members arr_of_members[1000], int member_id);

void update_book(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id);

void update_member(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id);

void bowrring_book(books arr_of_books[1000], int book_id, string calender1[370][2], members arr_of_members[1000], int member_id, int rus_member);

void return_book(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id, int rus_member);

void check_today(books arr_of_books[1000], int book_id);

void admin_section(books arr_of_books[1000], int& book_id, members arr_of_members[1000], int& member_id);

void member_section(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id, string calender1[370][2]);

void visitor_section(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id);
//main function
void main()
{
	books arr_of_books[1000];  //to storage data of books
	members arr_of_members[1000];   //to storage data of members
	string calender1[370][2];    //to storage date
	int book_id = 0;            //to count the books
	int member_id = 0;        //to count the members
	tm today;               
	int choice_section;            //Choice of section inside the library (admin/library)                 

	//to getting the all data
	Input(arr_of_books, book_id, arr_of_members, member_id , calender1);

	//start program
	do {

		cin.clear();
		cout << "" << setw(50) << "Welcome to The Library :" << setw(29) << "" << "\n\n";

		cout << "\t 1. Access the Admin Section \t\n\n";
		cout << "\t 2. Access The Member Section \t\n\n";
		cout << "\t 3. Access The Visitor Section \t\n\n";
		cout << "\t 4. Quit Program \t\t\n" << endl;

		do
		{
			error = 0;
			cout << "\n Please Enter Your Selection Between (1-4) : ";
			cin >> choice_section;
			if (cin.fail() && choice_section < 1 || choice_section > 4)
			{
				cout << "\n\tPlease Enter A Valid Input. " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);
		system("cls");

		//if you are admin
		if (choice_section == 1)
		{
			admin_section(arr_of_books, book_id, arr_of_members, member_id);
		}
		//if you are member
		if (choice_section == 2)
		{
			member_section(arr_of_books, book_id, arr_of_members, member_id, calender1);
		}
		//if you are visitor
		if (choice_section == 3)
		{
			visitor_section(arr_of_books, book_id, arr_of_members, member_id);
		}
		//to Quit
	} while (choice_section != 4);
}

void Input(books arr_of_books[1000], int& book_id, members arr_of_members[1000], int& member_id, string calender1[370][2])
{
	//getting the date from the text file .
	ifstream InBook;
	InBook.open("books.txt");   //include all books
	for (int i = 0; InBook.eof() == false; i++)
	{
		getline(InBook, arr_of_books[i].id_of_book, '%');
		// Storing Book name
		getline(InBook, arr_of_books[i].name_of_book, '#');
		//storing author name
		getline(InBook, arr_of_books[i].author, '$');
		//storing year
		getline(InBook, arr_of_books[i].year, '@');
		//storing status
		getline(InBook, arr_of_books[i].status_book, '*');
		if (arr_of_books[i].status_book == "false")
		{
			getline(InBook, arr_of_books[i].name_of_ismember, '|');   //storing member who borrowing book
			getline(InBook, arr_of_books[i].start_of_time.day, '/');   //storing start of time borrowing book
			getline(InBook, arr_of_books[i].start_of_time.month, '/');
			getline(InBook, arr_of_books[i].start_of_time.year, '|');
			getline(InBook, arr_of_books[i].end_of_time.day, '/');      //storing end of time borrowing book
			getline(InBook, arr_of_books[i].end_of_time.month, '/');
			getline(InBook, arr_of_books[i].end_of_time.year, '|');
		}
		book_id += 1;                           //getting the final value of book
	}
	book_id -= 1;
	InBook.close();
	//getting the text from the book's file .
	for (int i = 0; i < book_id; i++)
	{
		fstream check1;
		check1.open(arr_of_books[i].name_of_book + ".txt");
		for (int j = 0; check1.eof() == false; j++)
		{
			getline(check1, arr_of_words[i][j], ' ');
			arr_of_books[i].numberword += 1;
		}
		check1.close();
	}

	ifstream InMember;
	InMember.open("members.txt");    //include all member
	for (int i = 0; !InMember.eof(); i++)
	{
		getline(InMember, arr_of_members[i].id_of_member, '%');
		//getting the date from the text file . Storing member id
		getline(InMember, arr_of_members[i].name_of_member, '#');
		//storing member name
		getline(InMember, arr_of_members[i].pass_of_member, '$');
		//storing member pass
		getline(InMember, arr_of_members[i].date_of_member.day, '/');
		getline(InMember, arr_of_members[i].date_of_member.month, '/');
		getline(InMember, arr_of_members[i].date_of_member.year, '@');
		getline(InMember, arr_of_members[i].status_member, '*');
		//storing member date
		member_id += 1;                         //getting the final value of member
	}
	member_id -= 1;
	InMember.close();
	//storing member borrowed book
	for (int i = 0; i < member_id; i++)
	{
		if (arr_of_members[i].status_member == "false")
		{
			fstream check2;
			check2.open(arr_of_members[i].name_of_member + ".txt");
			for (int j = 0; check2.eof() == false; j++)
			{
				getline(check2, arr_of_isbooks[i][j].id_of_book, '|');
				getline(check2, arr_of_isbooks[i][j].name_of_book, '|');
				getline(check2, arr_of_isbooks[i][j].start_of_time.day, '/');
				getline(check2, arr_of_isbooks[i][j].start_of_time.month, '/');
				getline(check2, arr_of_isbooks[i][j].start_of_time.year, '|');
				getline(check2, arr_of_isbooks[i][j].end_of_time.day, '/');
				getline(check2, arr_of_isbooks[i][j].end_of_time.month, '/');
				getline(check2, arr_of_isbooks[i][j].end_of_time.year, '|');
				arr_of_members[i].number_isbooks += 1;
			}
			arr_of_members[i].number_isbooks -= 1;
			check2.close();
		}
	}
	fstream calender;//for storing date text file
	calender.open("calender.txt");
	for (int i = 0; i < 365; i++)
	{
		getline(calender, calender1[i][0], '/');
		getline(calender, calender1[i][1], ';');
	}
}

void admin_section(books arr_of_books[1000], int& book_id, members arr_of_members[1000], int& member_id)
{
	bool rus_admin;        //to check the admin
	int choice_admin_section;     //Choice of database in the admin section(seeing lists, adding books etc)
	rus_admin = loginadmin();
	if (rus_admin == true)
	{
		// out time to file
		time1();
		do {
			system("cls");
			cout << "" << setw(40) << "Welcome Admin" << setw(29) << "" << endl << endl;
			cout << "\t 1. Add New Book in Book Database\t\n\n";
			cout << "\t 2. Add New Member in Member Database\t\n\n";
			cout << "\t 3. Display All Books\t\n\n";
			cout << "\t 4. Display All Members\t\n\n";
			cout << "\t 5. Search For A Book \t\n\n";
			cout << "\t 6. Search For A Member \t\n\n";
			cout << "\t 7. Update Book Data \t\n\n";
			cout << "\t 8. Update Member Data \t\n\n";
			cout << "\t 9. Check Today \t\n\n";
			cout << "\t 10. Help \t\n\n";
			cout << "\t 11. Return to previous list\t" << endl;

			do
			{
				error = 0;
				cout << "\n Please Enter Your Selsction Between (1-11) : ";
				cin >> choice_admin_section;
				if (cin.fail() && choice_admin_section < 1 || choice_admin_section > 11)
				{
					cout << "\n\tPlease Enter A Valid Input. " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

			system("cls");
			//CALLING FUNCTION ADD BOOK
			if (choice_admin_section == 1)
			{
				book_id = addbook(book_id, arr_of_books);
			}
			//CALLING FUNCTION ADD STUDENT
			if (choice_admin_section == 2)
			{
				member_id = addmember(member_id, arr_of_members);
			}
			//showing all the books
			if (choice_admin_section == 3)
			{
				for (int i = 0; i < book_id; i++)
				{
					display_books(arr_of_books, i);
					if (i == (book_id / 2))
						system("pause");
				}
				system("pause");
			}
			//showing all the member
			if (choice_admin_section == 4)
			{
				for (int i = 0; i < member_id; i++)
				{
					display_members(arr_of_members, i);
					if (i == (member_id / 2))
						system("pause");
				}
				system("pause");
			}
			//search for a books
			if (choice_admin_section == 5)
			{
				search_of_book(arr_of_books, book_id, arr_of_words);
			}
			//search for a member
			if (choice_admin_section == 6)
			{
				search_of_member(arr_of_members, member_id);
			}
			//update the data of books
			if (choice_admin_section == 7)
			{
				update_book(arr_of_books, book_id, arr_of_members, member_id);
			}
			//update the data of members
			if (choice_admin_section == 8)
			{
				update_member(arr_of_books, book_id, arr_of_members, member_id);
			}
			//check today
			if (choice_admin_section == 9)
			{
				check_today(arr_of_books, book_id);
			}
			//help
			if (choice_admin_section == 10)
			{
				cout << "\tthis guide help you to know more about the admin's section." << endl;
				cout << "\t************************************************************\n" << endl;
				cout << "\t\t1. if you want to add a new book to the library datebase, you shoud select (1) \n\t\tyou will add the book by id ,name,year and author.\n" << endl;
				cout << "\t\t2. if you want to add a new member to the library datebase, you should select (2) \n\t\tyou will add the member by id , name, password.\n" << endl;
				cout << "\t\t3. if you want to see all books in the library, you should select (3) \n\t\tyou will see all book`s id, name, year, author.\n" << endl;
				cout << "\t\t4. if oyu wnat to see all member in the library, you should select (4) \n\t\tyou will see all member`s id, name, password and Date Of Registration.\n" << endl;
				cout << "\t\t5. if you want to search for book, you should select (5) \n\t\tyou can search for the book by id, name, year, author and one or two words.\n" << endl;
				cout << "\t\t6. if you want to search for member, you should select (6) \n\t\tyou can search for members by id, name and Date Of Registration.\n" << endl;
				cout << "\t\t7. if you want to update or change the data of the book, you should select (7) \n\t\tyou can update the book's id, the book's name, the book's year and the book's author.\n" << endl;
				cout << "\t\t8. if you want to update or change the data of member, you should select (8) \n\t\tyou can update the member's id, the member's name and the member's password.\n" << endl;
				cout << "\t\t9. if you wnat to see which book will return to day, you should select (9) \n\t\tyou can see which book will return to day.\n" << endl;
				system("pause");
			}
			//to back
			if (choice_admin_section == 11)
			{
				break;
			}
		} while (true);

	}
}

void member_section(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id, string calender1[370][2])
{
	int rus_member;     //to storage the index of member
	int choice_member_section;   //Choice of database in the member section
	rus_member = loginmember(arr_of_members, member_id);     //to check the member
	system("cls");
	if (rus_member >= 0)
	{
		do {
			system("cls");
			cout << "" << setw(40) << "Welcome Member" << setw(29) << "" << endl << endl;
			cout << "\t 1. Display All Books\t\n\n";
			cout << "\t 2. Search For A Book \t\n\n";
			cout << "\t 3. Borrowing A Book \t\n\n";
			cout << "\t 4. Return A Book \t\n\n";
			cout << "\t 5. Help \t\n\n";
			cout << "\t 6. Return to previous list\t" << endl;

			do
			{
				error = 0;
				cout << "\n Please Enter Your Selsction Between (1-6) : ";
				cin >> choice_member_section;
				if (cin.fail() && choice_member_section < 1 || choice_member_section > 6)
				{
					cout << "\n\tPlease Enter A Valid Input. " << endl;
					error = 1;
					cin.clear();
					cin.ignore(80, '\n');
				}
			} while (error == 1);

			system("cls");
			//showing all the books
			if (choice_member_section == 1)
			{
				for (int i = 0; i < book_id; i++)
				{
					display_books(arr_of_books, i);
					if (i == (book_id / 2))
						system("pause");
				}
				system("pause");
			}
			//search for a books
			if (choice_member_section == 2)
			{
				search_of_book(arr_of_books, book_id, arr_of_words);
			}
			//to borrowing the book
			if (choice_member_section == 3)
			{
				bowrring_book(arr_of_books, book_id, calender1, arr_of_members, member_id, rus_member);
			}
			//to return the book 
			if (choice_member_section == 4)
			{
				return_book(arr_of_books, book_id, arr_of_members, member_id, rus_member);
			}
			//help
			if (choice_member_section == 5)
			{
				cout << "\tthis guide help you to know more about the member's section." << endl;
				cout << "\t*************************************************************\n" << endl;
				cout << "\t\t1. if you want to see all books in the library, you should select (1) \n\t\tyou will see all book's id, name, year, author.\n" << endl;
				cout << "\t\t2. if you want to search for book, you should select (2) \n\t\tyou can search for the book by id, name, year, author and one or two words.\n" << endl;
				cout << "\t\t3. if you want to borrow book, you should select (3) \n\t\tyou can enter the book's id you want to borrow or search for book and borrow directily.\n" << endl;
				cout << "\t\t4. if you wnat to return book, you should select (4) \n\t\tyou can return the books that you borrowed before.\n" << endl;
				system("pause");
			}
			//to back
			if (choice_member_section == 6)
			{
				break;
			}
		} while (true);
	}
}

void visitor_section(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id)
{
	int choice_visitor_section;     //Choice of database in the visitor section 
	do {
		system("cls");
		cout << "" << setw(40) << "Welcome Visitor" << setw(29) << "" << endl << endl;
		cout << "\t 1. Display All Books\t\n\n";
		cout << "\t 2. Search For A Book \t\n\n";
		cout << "\t 3. Help \t\n\n";
		cout << "\t 4. Return to previous list\t" << endl;

		do
		{
			error = 0;
			cout << "\n Please Enter Your Selsction Between (1-4) : ";
			cin >> choice_visitor_section;
			if (cin.fail() && choice_visitor_section < 1 || choice_visitor_section > 6)
			{
				cout << "\n\tPlease Enter A Valid Input. " << endl;
				error = 1;
				cin.clear();
				cin.ignore(80, '\n');
			}
		} while (error == 1);

		system("cls");
		//showing all the books
		if (choice_visitor_section == 1)
		{
			for (int i = 0; i < book_id; i++)
			{
				display_books(arr_of_books, i);
				if (i == (book_id / 2))
					system("pause");
			}
			system("pause");
		}
		//search for a book
		if (choice_visitor_section == 2)
		{
			search_of_book(arr_of_books, book_id, arr_of_words);
		}
		//help
		if (choice_visitor_section == 3)
		{
			cout << "\tthis guide help you to know more about the visitor's section." << endl;
			cout << "\t**************************************************************\n" << endl;
			cout << "\t\t1. if you want to see all books in the library, you should select (1) \n\t\tyou will see all book's id, name, year, author.\n" << endl;
			cout << "\t\t2. if you want to search for book, you should select (2) \n\t\tyou can search for the book by id, name, year, author and one or two words.\n" << endl;
			system("pause");
		}
		//to back
		if (choice_visitor_section == 4)
		{
			break;
		}
	} while (true);
}

//to read any password
string readpassword(string pass)
{
	const char BACKSPACE = 8;    // to delete char
	const char RETURN = 13;   //press the key of Enter
	unsigned char ch = 0;
	while ((ch = getch()) != RETURN)
	{
		if (ch == BACKSPACE)
		{
			if (pass.length() != 0)
			{
				cout << "\b \b";
				pass.resize(pass.length() - 1);
			}
		}
		else if (ch == 0 || ch == 224) // handle escape sequences
		{
			getch(); // ignore non printabxle chars
			continue;
		}
		else
		{
			pass += ch;
			cout << '*';
		}
	}
	return pass;
}
// to check is admin
bool loginadmin()
{
	// to read user name && password form text file
	string user1;
	string pass1;
	//to check is admin
	bool isadmin = false;
	// file  
	fstream check;
	// open file
	check.open("admin.txt");
	// read user name amd password from file
	check >> user1 >> pass1;
	check.close();
	//check is admin
	for (int i = 0; i < 3; i++)
	{
		string user;
		string  pass;
		cout << "Enter The Username: ";
		cin >> user;
		cout << "Enter The Password: ";
		pass = readpassword(pass);
		if (user == user1 && pass == pass1)
		{
			isadmin = true;
			break;
		}
		// if wrong password or username
		else
		{
			// to clear the program
			system("cls");
			cout << "Wrong Username or Password." << endl;
		}

	}
	if (isadmin == true)
	{
		//time form function (data type:"struct tm",day as a valible)
		struct tm day = time1();
		//file to add new deta to login
		fstream file("admin.txt", ios_base::app | ios_base::out);
		file << "time : " << day.tm_hour << ':' << day.tm_min << ':' << day.tm_sec << " | ";
		file << "date: " << day.tm_mday << '/' << day.tm_mon + 1 << '/' << day.tm_year + 1900 << endl;
	}
	system("cls");
	return isadmin;
}
// to check is member
int loginmember(members arr_of_members[1000], int member_id)
{
	int j;
	for (int i = 0; i < 3; i++)
	{
		string name;
		string pass;
		cout << "Enter Name : ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter Password : ";
		pass = readpassword(pass);
		bool ismember = false;
		for (j = 0; j < member_id; j++)
		{
			if (name == arr_of_members[j].name_of_member&&pass == arr_of_members[j].pass_of_member)
			{
				ismember = true;
				break;
			}
		}
		system("cls");
		if (ismember == true)
		{
			return j;
		}
		// if wrong password or username
		else
		{
			cout << "Wrong Name Or Password." << endl;
		}
	}
	return -1;
}
//to display any books with book's index
void display_books(books arr_of_books[1000], int i)
{
	cout << "Id : " << arr_of_books[i].id_of_book << endl;
	cout << "Name : " << arr_of_books[i].name_of_book << endl;
	cout << "Author : " << arr_of_books[i].author << endl;
	cout << "Year : " << arr_of_books[i].year << endl;
	if (arr_of_books[i].status_book == "false")
	{
		cout << "Name of Member : " << arr_of_books[i].name_of_ismember << endl;
		cout << "Date of Issue Book : " << arr_of_books[i].start_of_time.day << '/' << arr_of_books[i].start_of_time.month << '/' << arr_of_books[i].start_of_time.year << endl;
		cout << "Date of Return Book : " << arr_of_books[i].end_of_time.day << '/' << arr_of_books[i].end_of_time.month << '/' << arr_of_books[i].end_of_time.year << endl;
	}
	cout << "\n\n";
}
//to display any members with book's member
void display_members(members arr_of_members[1000], int i)
{
	cout << "Id : " << arr_of_members[i].id_of_member << endl;
	cout << "Name : " << arr_of_members[i].name_of_member << endl;
	cout << "Password : " << arr_of_members[i].pass_of_member << endl;
	cout << "Date Of Registration : " << arr_of_members[i].date_of_member.day << '/' << arr_of_members[i].date_of_member.month << '/' << arr_of_members[i].date_of_member.year << endl;

	if (arr_of_members[i].status_member == "false")
	{
		for (int j = 0; j <arr_of_members[i].number_isbooks; j++)
		{
			cout << "ID of Issue Book : " << arr_of_isbooks[i][j].id_of_book << endl;
			cout << "Name of Issue Book : " << arr_of_isbooks[i][j].name_of_book << endl;
			cout << "Date of Issue Book : " << arr_of_isbooks[i][j].start_of_time.day << '/' << arr_of_isbooks[i][j].start_of_time.month << '/' << arr_of_isbooks[i][j].start_of_time.year << endl;
			cout << "Date of Return Book : " << arr_of_isbooks[i][j].end_of_time.day << '/' << arr_of_isbooks[i][j].end_of_time.month << '/' << arr_of_isbooks[i][j].end_of_time.year << endl;
		}
	}
	cout << "\n\n";
}
//to know the id using before and suggest the new id
string search_idbook(string id, int book_id, books arr_of_books[1000])
{
	getline(cin, id);
	while (true) 
	{
		bool isfound = false;
		for (int i = 0; i <book_id; i++)
		{
			if (arr_of_books[i].id_of_book == id)
			{
				isfound = true;
				break;
			}
		}
		if (isfound == false)
		   	break;
		//if id using before
		else 
		{
			cout << "\n\tThe ID is Already Used\nEnter Another ID : (Suggest " << (book_id + 1) << " )";
			getline(cin, id);
		}
	}
	return id;
}

int addbook(int book_id, books arr_of_books[1000])
{
	system("cls");
	books add;
	cout << "\n\tEnter ID : ";
	getline(cin, add.id_of_book);
	add.id_of_book = search_idbook(add.id_of_book, book_id, arr_of_books);
	string name;
	cout << "\n\tEnter Name : ";
	getline(cin, add.name_of_book);
	cout << "\n\tEnter Author : ";
	getline(cin, add.author);
	cout << "\n\tEnter Year : ";
	getline(cin, add.year);
	string text;
	cout << "\n\tEnter Text : ";
	getline(cin, text);
	arr_of_books[book_id].numberword = 1;
	//to know number of word
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == ' ')
		{
			arr_of_books[book_id].numberword++;
		}
	}
	//storage new book in the file 
	fstream InBook("books.txt", ios_base::app);
	InBook << add.id_of_book << '%' << add.name_of_book << '#' << add.author << '$' << add.year << '@' << "true" << '*';
	//storage new book in the array of books 
	arr_of_books[book_id].id_of_book = add.id_of_book;
	arr_of_books[book_id].name_of_book = add.name_of_book;
	arr_of_books[book_id].author = add.author;
	arr_of_books[book_id].year = add.year;
	arr_of_books[book_id].status_book = "true";
	//creat a new file 
	ofstream newfile;
	newfile.open(add.name_of_book + ".txt");
	newfile.close();
	//storage new text in the new file
	ofstream thefile(add.name_of_book + ".txt", ios_base::app);
	thefile << text;
	thefile.close();
	//storage new text in the array of words
	fstream check1;
	check1.open(add.name_of_book + ".txt");
	for (int j = 0; j<arr_of_books[book_id].numberword; j++)
	{
		getline(check1, arr_of_words[book_id][j], ' ');
	}
	check1.close();
	book_id++;
	return book_id;
}
//to know the id using before and suggest the new id
string search_idmember(string id, int member_id, members arr_of_members[1000])
{
	getline(cin, id);
	while (true) {
		bool isfound = false;
		for (int i = 0; i < member_id; i++)
		{
			if (arr_of_members[i].id_of_member == id)
			{
				isfound = true;
				break;
			}
		}
		if (isfound == false)
			break;
		//if id using before
		else
		{
			cout << "\n\tThe ID is Already Used\nEnter Another ID : (Suggest " << (member_id + 1) << " )";
			getline(cin, id);
		}
	}
	return id;
}

int addmember(int member_id, members arr_of_members[1000])
{
	system("cls");
	string id;
	cout << "\n\tenter id : ";
	getline(cin, id);
	id = search_idmember(id, member_id, arr_of_members);
	cout << "\n\tenter name : ";
	string name;
	getline(cin, name);
	cout << "\n\tenter password : ";
	string password;
	getline(cin, password);
	struct tm addday = time1();
	//storage new member in the file
	fstream InMember("members.txt", ios_base::app);
	InMember << id << '%' << name << '#' << password << '$';
	InMember << addday.tm_mday << '/' << addday.tm_mon + 1 << '/' << addday.tm_year + 1900 << '@' << "true*";
	//storage new member in the array of books
	arr_of_members[member_id].id_of_member = id;
	arr_of_members[member_id].name_of_member = name;
	arr_of_members[member_id].pass_of_member = password;
	tm today = time1();
	int Year = today.tm_year + 1900;
	int Month = today.tm_mon + 1;
	int Day = today.tm_mday;
	stringstream year;
	year << Year;
	string Y_O_C = year.str();
	stringstream month;
	month << Month;
	string M_O_C = month.str();
	stringstream day;
	day << Day;
	string D_O_C = day.str();
	arr_of_members[member_id].date_of_member.day = D_O_C;
	arr_of_members[member_id].date_of_member.month = M_O_C;
	arr_of_members[member_id].date_of_member.year = Y_O_C;
	member_id += 1;
	ofstream newfile;   //creat a new file 
	newfile.open(name +".txt");
	return member_id;
}
//to search about any book by any way
void search_of_book(books arr_of_books[1000], int book_id, string arr_of_words[1000][10000])
{
	string search_book;
	char answer;
	int choise_of_search;
	do {
		bool isfound = false;


		cout << "\n\tSelect One Of The Following Options : \n" << endl;
		cout << "\n\t1. Search By Id : \n" << endl;
		cout << "\n\t2. Search By Name : \n" << endl;
		cout << "\n\t3. Search By Author : \n" << endl;
		cout << "\n\t4. Search By Year : \n" << endl;
		cout << "\n\t5. Search By Words : \n" << endl;
		cout << "\n\tEnter Your Selection (1:5) : ";
		cin >> choise_of_search;
		while (cin.fail() && choise_of_search > 5 || choise_of_search < 1)
		{
			cout << "\n\tPlease Enter Your Selection Between (1:5) : ";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> choise_of_search;
		}
		//search by id of books
		if (choise_of_search == 1)
		{
			cout << "\n\tEnter The Book's Id : ";
			cin >> search_book;
			system("cls");
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].id_of_book == search_book)
				{
					display_books(arr_of_books, i);
					isfound = true;
				}
			}
		}
		//search by name of books
		else if (choise_of_search == 2)
		{
			cout << "\n\tEnter The Book's Name : ";
			cin.ignore();
			getline(cin, search_book);
			system("cls");
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].name_of_book.find(search_book) != string::npos)
				{
					display_books(arr_of_books, i);
					isfound = true;
				}
			}
		}
		//search by author of books
		else if (choise_of_search == 3)
		{
			cout << "\n\tEnter The Book's Auther : ";
			cin.ignore();
			getline(cin, search_book);
			system("cls");
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].author.find(search_book) != string::npos)
				{
					display_books(arr_of_books, i);
					isfound = true;
				}
			}

		}
		//search by year of books
		else if (choise_of_search == 4)
		{
			cout << "\n\tEnter The Book's Year : ";
			cin >> search_book;
			system("cls");
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].year == search_book)
				{
					display_books(arr_of_books, i);
					isfound = true;
				}
			}
		}
		//search by word of books
		else if (choise_of_search == 5)
		{
			int m = 0;
			bool swapped;
			bool isword = false;
			int sortad_book[1000][2] = { { 0 } };
			int sum;
			int sort = 0;
			string search_word[2];
			cout << "\n\tEnter The Word of Book : ";
			cin.ignore();
			getline(cin, search_book);
			system("cls");
			//to know the search_book is one word or two word
			for (int i = 0; i < search_book.size(); i++)
			{
				if (search_book[i] == ' ')
				{
					m++;
					isword = true;
					continue;
				}
				search_word[m] += search_book[i];
			}
			//to search
			for (int i = 0; i < book_id; i++)
			{
				sum = 0;
				bool found = false;
				for (int j = 1; j <= arr_of_books[i].numberword; j++)
				{
					if (isword == false)    //to search by one word
					{
						if (search_book == arr_of_words[i][j - 1])
						{
							sum++;
							isfound = true;
							found = true;
						}
					}
					if (isword)    //to search by two words
					{
						if (search_word[0] == arr_of_words[i][j - 1] && search_word[1] == arr_of_words[i][j])
						{
							sum++;
							isfound = true;
							found = true;
						}
					}
				}
				//to storage index and the number of words repeated in the book
				if (found == true)
				{
					sortad_book[sort][0] = i;
					sortad_book[sort][1] = sum;
					sort++;
				}
			}
			//to sort the books According to the number of words repeated in the book
			do
			{
				swapped = false;
				for (int i = 1; i < sort; i++)
				{

					if (sortad_book[i - 1][1] < sortad_book[i][1])
					{
						swap(sortad_book[i - 1], sortad_book[i]);
						swapped = true;
					}
				}
			} while (swapped);
			for (int i = 0; i < sort; i++)
			{
				int n;
				n = sortad_book[i][0];
				display_books(arr_of_books, n);
			}
		}
		//if not found the book 
		if (!isfound)
		{
			cout << "\n\t Not Found This Book" << endl;
		}
		cout << "\n\tDo You Want To Search Again? (Y/N) : ";
		cin >> answer;
		system("cls");
		if (answer == 'N' || answer == 'n')
		{
			break;
		}
		else if (answer == 'y' || answer == 'Y')
		{
			continue;
		}

	} while (true);
	system("cls");
}
//to search about any member by any way
void search_of_member(members arr_of_members[1000], int member_id)
{
	string search_member;
	string search_of_day;
	string search_of_month;
	string search_of_year;
	char answer;
	int choise_of_search;
	int choise2_of_search;
	do {
		bool isfound = false;

		cout << "\n\tSelect One Of The Following Options : \n" << endl;
		cout << "\n\t1. Search By Id : \n" << endl;
		cout << "\n\t2. Search By Name : \n" << endl;
		cout << "\n\t3. Search By date : \n" << endl;
		cout << "\n\tEnter Your Selection (1:3) : ";

		cin >> choise_of_search;
		while (cin.fail()&& choise_of_search<1 || choise_of_search>3)
		{
			cout << "\n\tPlease Enter Your Selection Between (1:3) : ";
			cin.clear();
			cin.ignore(80, '\n');
			cin >> choise_of_search;
		}
		//to search by member's id
		if (choise_of_search == 1)
		{
			cout << "\n\tEnter Your Member's Id : ";
			cin >> search_member;
			system("cls");

			for (int i = 0; i < member_id; i++)
			{
				if (arr_of_members[i].id_of_member == search_member)
				{
					display_members(arr_of_members, i);
					isfound = true;
				}
			}
		}
		//to search by member's name
		else if (choise_of_search == 2)
		{
			cout << "\n\tEnter Your Member's Name : ";
			cin.ignore();
			getline(cin, search_member);
			system("cls");
			for (int i = 0; i < member_id; i++)
			{
				if (arr_of_members[i].name_of_member.find(search_member) != string::npos)
				{
					display_members(arr_of_members, i);
					isfound = true;
				}
			}
		}
		//to search by member's date
		else if (choise_of_search == 3)
		{
			system("cls");
			cout << "\n\tSelect One Of The Following Options : \n" << endl;
			cout << "\n\t1. Search By Day Only : \n" << endl;
			cout << "\n\t2. Search By Month Only : \n" << endl;
			cout << "\n\t3. Search BY Year Only : \n" << endl;
			cout << "\n\t4. Search By All Date : \n" << endl;
			cout << "\n\tEnter Your Selection (1:4) : ";
			cin >> choise2_of_search;
			while (cin.fail() && choise2_of_search < 1 || choise2_of_search>4)
			{
				cout << "\n\tPlease Enter Your Selection Between (1:4) : ";
				cin.clear();
				cin.ignore(80, '\n');
				cin >> choise2_of_search;
			}
			//to search by member's day of date
			if (choise2_of_search == 1)
			{
				cout << "\n\tEnter Your Member's Date (Day) : ";
				cin >> search_member;
				system("cls");

				for (int i = 0; i < member_id; i++)
				{
					if (arr_of_members[i].date_of_member.day == search_member)
					{
						display_members(arr_of_members, i);
						isfound = true;
					}
				}
			}
			//to search by member's month of date
			else if (choise2_of_search == 2)
			{
				cout << "\n\tEnter Your Member's Date (Month) : ";
				cin >> search_member;
				system("cls");

				for (int i = 0; i < member_id; i++)
				{
					if (arr_of_members[i].date_of_member.month == search_member)
					{
						display_members(arr_of_members, i);
						isfound = true;
					}
				}
			}
			//to search by member's year of date
			else if (choise2_of_search == 3)
			{
				cout << "\n\tEnter Your Member's Date (Years) : ";
				cin >> search_member;
				system("cls");

				for (int i = 0; i < member_id; i++)
				{
					if (arr_of_members[i].date_of_member.year == search_member)
					{
						display_members(arr_of_members, i);
						isfound = true;
					}
				}
			}
			//to search by member's all date
			else if (choise2_of_search == 4)
			{
				cout << "\n\tEnter Your Member's All Date : " << endl;
				cout << "\n\tEnter The Member's Day : ";
				cin >> search_of_day;
				cout << "\n\tEnter The Member's Month : ";
				cin >> search_of_month;
				cout << "\n\tEnter The Member's Year : ";
				cin >> search_of_year;
				system("cls");

				for (int i = 0; i < member_id; i++)
				{
					if (arr_of_members[i].date_of_member.day == search_of_day && arr_of_members[i].date_of_member.month == search_of_month && arr_of_members[i].date_of_member.year == search_of_year)
					{
						display_members(arr_of_members, i);
						isfound = true;
					}
				}
			}
		}
		//if not found the member
		if (!isfound)
		{
			cout << "\n\t Not Found This Member " << endl;
		}
		cout << "\n\tDo You Want To Search Again? (Y/N) : ";
		cin >> answer;
		system("cls");
		if (answer == 'N' || answer == 'n')
		{
			break;
		}
		else if (answer == 'y' || answer == 'Y')
		{
			continue;
		}
	} while (true);
}
//to change name of file during updating
void renamefile(string oldname, string newname) 
{
	char old[100] = {};
	oldname += ".txt";
	for (int i = 0; i < oldname.size(); i++) 
	{
		old[i] = oldname[i];
	}
	char newn[100] = {};
	newname += ".txt";
	for (int i = 0; i < newname.size(); i++) 
	{
		newn[i] = newname[i];
	}
	int res;
	res = rename(old, newn);
}
//to change of the data of any books
void update_book(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id)
{
	int choice, ismember;
	bool isfound = false;
	string search, old_name, new_name;
	cout << "\t1.Enter Book's ID\t\n\n";
	cout << "\t2.Search for A Book\t\n\n";
	do
	{
		error = 0;
		cout << "\n Please Enter Your Selsction Between (1-2) : ";
		cin >> choice;
		if (cin.fail() && choice < 1 || choice > 2)
		{
			cout << "\n\tPlease Enter A Valid Input. " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	system("cls");
	if (choice == 1)
	{
		cout << "\tEnter The Book's ID : ";
		cin >> search;
		while (true)
		{
			bool isavailable = false;
			system("cls");
			//to search
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].id_of_book == search)
				{
					display_books(arr_of_books, i);
					system("pause");
					cout << "\n\tEnter ID : ";
					getline(cin, arr_of_books[i].id_of_book);
					arr_of_books[i].id_of_book = search_idbook(arr_of_books[i].id_of_book, book_id, arr_of_books);
					old_name = arr_of_books[i].name_of_book;
					cout << "\n\tEnter Name : ";
					getline(cin, arr_of_books[i].name_of_book);
					new_name = arr_of_books[i].name_of_book;
					cout << "\n\tEnter Author : ";
					getline(cin, arr_of_books[i].author);
					cout << "\n\tEnter Year : ";
					getline(cin, arr_of_books[i].year);
					isavailable = true;
					//if member borrowing the book
					if (arr_of_books[i].status_book == "false")
					{
						for (int k = 0; k < member_id; k++)
						{
							if (arr_of_members[k].status_member == "false")
							{
								for (int j = 0; j < arr_of_members[k].number_isbooks; j++)
								{
									if (arr_of_isbooks[k][j].id_of_book == search)
									{
										arr_of_isbooks[k][j].id_of_book = arr_of_books[i].id_of_book;
										arr_of_isbooks[k][j].name_of_book = arr_of_books[i].name_of_book;
										ismember = k;
										isfound = true;
										break;
									}
								}
								if (isfound)
								{
									break;
								}
							}
						}
					}
					if (isavailable)
					{
						break;
					}
				}
			}
			if (isavailable)
			{
				break;
			}
			//if not found the book			
			else
			{
				cout << "\tThe ID is not Valid\t\n\n";
				cout << "\tEnter The Book's ID : ";
				cin >> search;
			}
		}
		//storage new data in the fils
		fstream file1("books.txt", std::fstream::out | std::fstream::trunc);
		ofstream file2("books.txt", ios_base::app);
		for (int i = 0; i < book_id; i++)
		{
			file2 << arr_of_books[i].id_of_book << "%" << arr_of_books[i].name_of_book << "#" << arr_of_books[i].author << "$" << arr_of_books[i].year << "@" << arr_of_books[i].status_book << "*";
			if (arr_of_books[i].status_book == "false")
			{
				file2 << arr_of_books[i].name_of_ismember << '|';
				file2 << arr_of_books[i].start_of_time.day << '/' << arr_of_books[i].start_of_time.month << '/' << arr_of_books[i].start_of_time.year << '|';
				file2 << arr_of_books[i].end_of_time.day << '/' << arr_of_books[i].end_of_time.month << '/' << arr_of_books[i].end_of_time.year << '|';
			}
		}
		file2.close();
		if (isfound)
		{
			fstream file5(arr_of_members[ismember].name_of_member + ".txt", std::fstream::out | std::fstream::trunc);
			ofstream file6(arr_of_members[ismember].name_of_member + ".txt", ios_base::app);
			for (int i = 0; i < arr_of_members[ismember].number_isbooks; i++)
			{
				file6 << arr_of_isbooks[ismember][i].id_of_book << '|' << arr_of_isbooks[ismember][i].name_of_book << '|';
				file6 << arr_of_isbooks[ismember][i].start_of_time.day << '/' << arr_of_isbooks[ismember][i].start_of_time.month << '/' << arr_of_isbooks[ismember][i].start_of_time.year << '|';
				file6 << arr_of_isbooks[ismember][i].end_of_time.day << '/' << arr_of_isbooks[ismember][i].end_of_time.month << '/' << arr_of_isbooks[ismember][i].end_of_time.year << '|';
			}
			file6.close();
		}
		if (new_name != old_name)
		{
			renamefile(old_name, new_name);
		}
	}
	else if (choice == 2)
	{
		search_of_book(arr_of_books, book_id, arr_of_words);
	}
}
//to change of the data of any member
void update_member(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id)
{
	int choice, ismember;
	bool isfound = false;
	string search, old_name, new_name;
	cout << "\t1.Enter Member's ID\t\n\n";
	cout << "\t2.Search for A Member\t\n\n";
	do
	{
		error = 0;
		cout << "\n Please Enter Your Selsction Between (1-2) : ";
		cin >> choice;
		if (cin.fail() && choice < 1 || choice > 2)
		{
			cout << "\n\tPlease Enter A Valid Input. " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	system("cls");
	if (choice == 1)
	{
		cout << "\tEnter The Member's ID : ";
		cin >> search;
		while (true)
		{
			bool isavailable = false;
			system("cls");
			//to search
			for (int i = 0; i < member_id; i++)
			{
				if (arr_of_members[i].id_of_member == search)
				{
					display_members(arr_of_members, i);
					system("pause");
					cout << "\n\tEnter ID : ";
					getline(cin, arr_of_members[i].id_of_member);
					arr_of_members[i].id_of_member = search_idmember(arr_of_members[i].id_of_member, member_id, arr_of_members);
					old_name = arr_of_members[i].name_of_member;
					cout << "\n\tEnter Name : ";
					getline(cin, arr_of_members[i].name_of_member);
					new_name = arr_of_members[i].name_of_member;
					cout << "\n\tEnter Password : ";
					getline(cin, arr_of_members[i].pass_of_member);
					ismember = i;
					isavailable = true;
					//if the member borrowing book
					if (arr_of_members[i].status_member == "false")
					{
						for (int k = 0; k < book_id; k++)
						{
							if (arr_of_books[k].status_book == "false")
							{
								if (arr_of_books[k].name_of_ismember == old_name)
								{
									arr_of_books[k].name_of_ismember = new_name;
									isfound = true;
									break;
								}
							}
						}
					}
					if (isfound)
					{
						break;
					}
				}
			}
			if (isavailable)
			{
				break;
			}
			//if not found the member
			else
			{
				cout << "\tThe ID is not Valid\t\n\n";
				cout << "\tEnter The Member's ID : ";
				cin >> search;
			}
		}
		//storage new data in the fils
		if (isfound)
		{
			fstream file1("books.txt", std::fstream::out | std::fstream::trunc);
			ofstream file2("books.txt", ios_base::app);
			for (int i = 0; i < book_id; i++)
			{
				file2 << arr_of_books[i].id_of_book << "%" << arr_of_books[i].name_of_book << "#" << arr_of_books[i].author << "$" << arr_of_books[i].year << "@" << arr_of_books[i].status_book << "*";
				if (arr_of_books[i].status_book == "false")
				{
					file2 << arr_of_books[i].name_of_ismember << '|';
					file2 << arr_of_books[i].start_of_time.day << '/' << arr_of_books[i].start_of_time.month << '/' << arr_of_books[i].start_of_time.year << '|';
					file2 << arr_of_books[i].end_of_time.day << '/' << arr_of_books[i].end_of_time.month << '/' << arr_of_books[i].end_of_time.year << '|';
				}
			}
			file2.close();
		}
		fstream file5("members.txt", std::fstream::out | std::fstream::trunc);
		ofstream file6("members.txt", ios_base::app);
		for (int i = 0; i <member_id; i++)
		{
			file6 << arr_of_members[i].id_of_member << '%' << arr_of_members[i].name_of_member << '#';
			file6 << arr_of_members[i].pass_of_member << '$' << arr_of_members[i].date_of_member.day << '/' << arr_of_members[i].date_of_member.month << '/';
			file6 << arr_of_members[i].date_of_member.year << '@' << arr_of_members[i].status_member << '*';
		}
		file6.close();
		if (new_name != old_name)
		{
			renamefile(old_name, new_name);
		}
	}
	else if (choice == 2)
	{
		search_of_member(arr_of_members, member_id);
	}
}
//to bowrrowing the book
void bowrring_book(books arr_of_books[1000], int book_id, string calender1[370][2], members arr_of_members[1000], int member_id, int rus_member)
{
	char answer;
	int choice;
	int position;
	int bboock;
	string search, date, DY, MTH;
	tm today = time1();
	cout << "\t1.Enter Book's ID\t\n\n";
	cout << "\t2.Search for A Book\t\n\n";
	do
	{
		error = 0;
		cout << "\n Please Enter Your Selsction Between (1-2) : ";
		cin >> choice;
		if (cin.fail() && choice < 1 || choice > 2)
		{
			cout << "\n\tPlease Enter A Valid Input. " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	system("cls");
	if (choice == 1)
	{
		cout << "\tEnter The Book's Id : ";
		cin >> search;
		while (true)
		{
			bool isavailable = false;
			system("cls");
			//to search
			for (int i = 0; i < book_id; i++)
			{
				if (arr_of_books[i].id_of_book == search)
				{
					if (arr_of_books[i].status_book == "true")
					{
						//to know the date of today
						int Year = today.tm_year + 1900;
						int Month = today.tm_mon + 1;
						int Day = today.tm_mday;
						stringstream year;
						year << Year;
						string Y_O_C = year.str();
						stringstream month;
						month << Month;
						string M_O_C = month.str();
						stringstream day;
						day << Day;
						string D_O_C = day.str();
						string NY_O_C = Y_O_C;
						position = 0;
						//to calculate the date after 30 days 
						for (position = 0; position < 365; position++)
						{
							if (calender1[position][0] == D_O_C&& calender1[position][1] == M_O_C)
							{
								break;
							}
						}
						if (position >= 335)    //today is after 1 dec 
						{
							stringstream year;
							Year += 1;
							year << Year;
							NY_O_C = year.str();
						}
						bboock = i;
						display_books(arr_of_books, i);
						cout << "The Book is booked for you from : " << today.tm_mday << " / " << today.tm_mon + 1 << " / " << today.tm_year + 1900 << " ";
						cout << "till : " << calender1[(position + 30) % 365][0] << '/' << calender1[(position + 30) % 365][1] << '/' << NY_O_C << '\n' << endl;
						system("pause");
						//to storage the new data in the array of books and array of is book
						arr_of_books[i].status_book = "false";
						arr_of_books[i].name_of_ismember = arr_of_members[rus_member].name_of_member;
						arr_of_books[i].start_of_time.day = D_O_C;
						arr_of_books[i].start_of_time.month = M_O_C;
						arr_of_books[i].start_of_time.year = Y_O_C;
						arr_of_books[i].end_of_time.day = calender1[(position + 30) % 365][0];
						arr_of_books[i].end_of_time.month = calender1[(position + 30) % 365][1];
						arr_of_books[i].end_of_time.year = NY_O_C;
						arr_of_members[rus_member].status_member = "false";
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].id_of_book = arr_of_books[i].id_of_book;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].name_of_book = arr_of_books[i].name_of_book;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].start_of_time.day = arr_of_books[i].start_of_time.day;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].start_of_time.month = arr_of_books[i].start_of_time.month;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].start_of_time.year = arr_of_books[i].start_of_time.year;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].end_of_time.day = arr_of_books[i].end_of_time.day;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].end_of_time.month = arr_of_books[i].end_of_time.month;
						arr_of_isbooks[rus_member][arr_of_members[rus_member].number_isbooks].end_of_time.year = arr_of_books[i].end_of_time.year;
						arr_of_members[rus_member].number_isbooks++;
						isavailable = true;
						break;
					}
					//if the book is borrowed
					else if (arr_of_books[i].status_book == "false")
					{
						cout << "\tThe Book is not Available" << endl;
						isavailable = true;
						break;
					}
				}
			}
			if (isavailable == true)
			{
				break;
			}
			//if the book not found
			else
			{
				cout << "\tThe ID is not Valid\t\n\n";
				cout << "\tEnter The Book's ID : ";
				cin >> search;
			}
		}
		//storage new data in the files
		fstream file1("books.txt", std::fstream::out | std::fstream::trunc);
		ofstream file2("books.txt", ios_base::app);
		for (int i = 0; i < book_id; i++)
		{
			file2 << arr_of_books[i].id_of_book << "%" << arr_of_books[i].name_of_book << "#" << arr_of_books[i].author << "$" << arr_of_books[i].year << "@" << arr_of_books[i].status_book << "*";
			if (arr_of_books[i].status_book == "false")
			{
				file2 << arr_of_books[i].name_of_ismember << '|';
				file2 << arr_of_books[i].start_of_time.day << '/' << arr_of_books[i].start_of_time.month << '/' << arr_of_books[i].start_of_time.year << '|';
				file2 << arr_of_books[i].end_of_time.day << '/' << arr_of_books[i].end_of_time.month << '/' << arr_of_books[i].end_of_time.year << '|';
			}
		}
		file2.close();
		fstream file3("members.txt", std::fstream::out | std::fstream::trunc);
		ofstream file4("members.txt", ios_base::app);
		for (int i = 0; i < member_id; i++)
		{
			file4 << arr_of_members[i].id_of_member << "%" << arr_of_members[i].name_of_member << "#" << arr_of_members[i].pass_of_member << "$";
			file4 << arr_of_members[i].date_of_member.day << '/' << arr_of_members[i].date_of_member.month << '/' << arr_of_members[i].date_of_member.year << '@' << arr_of_members[i].status_member << "*";
		}
		file4.close();
		fstream file(arr_of_members[rus_member].name_of_member + ".txt", ios_base::app | ios_base::out);
		file << arr_of_books[bboock].id_of_book << '|' << arr_of_books[bboock].name_of_book << '|';
		file << arr_of_books[bboock].start_of_time.day << '/' << arr_of_books[bboock].start_of_time.month << '/' << arr_of_books[bboock].start_of_time.year << '|';
		file << arr_of_books[bboock].end_of_time.day << '/' << arr_of_books[bboock].end_of_time.month << '/' << arr_of_books[bboock].end_of_time.year << '|';
		file.close();
	}
	else if (choice == 2)
	{
		search_of_book(arr_of_books, book_id, arr_of_words);
	}
}
//to return the book 
void return_book(books arr_of_books[1000], int book_id, members arr_of_members[1000], int member_id, int rus_member)
{
	int choice;
	string search, date, DY, MTH;
	tm today = time1();
	cout << "\t1.Enter Book's ID\t\n\n";
	cout << "\t2.Search for A Book\t\n\n";
	do
	{
		error = 0;
		cout << "\n Please Enter Your Selsction Between (1-2) : ";
		cin >> choice;
		if (cin.fail() && choice < 1 || choice > 2)
		{
			cout << "\n\tPlease Enter A Valid Input. " << endl;
			error = 1;
			cin.clear();
			cin.ignore(80, '\n');
		}
	} while (error == 1);
	system("cls");
	if (choice == 1)
	{
		cout << "\tEnter The Book's ID : ";
		cin >> search;
		while (true)
		{
			bool isavailable = false;
			system("cls");
			//search in books which the member borrowing
			for (int i = 0; i < arr_of_members[rus_member].number_isbooks; i++)
			{
				if (arr_of_isbooks[rus_member][i].id_of_book == search)
				{
					//swap the array of isbooks
					for (int j = i + 1; j < arr_of_members[rus_member].number_isbooks; j++)
					{
						arr_of_isbooks[rus_member][j - 1].id_of_book == arr_of_isbooks[rus_member][j].id_of_book;
						arr_of_isbooks[rus_member][j - 1].name_of_book == arr_of_isbooks[rus_member][j].name_of_book;
						arr_of_isbooks[rus_member][j - 1].start_of_time.day == arr_of_isbooks[rus_member][j].start_of_time.day;
						arr_of_isbooks[rus_member][j - 1].start_of_time.month == arr_of_isbooks[rus_member][j].start_of_time.month;
						arr_of_isbooks[rus_member][j - 1].start_of_time.year == arr_of_isbooks[rus_member][j].start_of_time.year;
						arr_of_isbooks[rus_member][j - 1].end_of_time.day == arr_of_isbooks[rus_member][j].end_of_time.day;
						arr_of_isbooks[rus_member][j - 1].end_of_time.month == arr_of_isbooks[rus_member][j].end_of_time.month;
						arr_of_isbooks[rus_member][j - 1].end_of_time.year == arr_of_isbooks[rus_member][j].end_of_time.year;
					}
					for (int i = 0; i < book_id; i++)
					{
						if (arr_of_books[i].id_of_book == search)
						{
							display_books(arr_of_books, i);
							cout << "The Book is returned successfully " << endl;
							system("pause");
							//storage new data in array of book and members
							arr_of_books[i].status_book = "true";
						}
					}
					//if the member borrowing 2,3,4,5 books 
					if (arr_of_members[rus_member].number_isbooks > 1)
					{
						arr_of_members[rus_member].status_member = "false";
					}
					//if the member borrowing one book
					else if (arr_of_members[rus_member].number_isbooks == 1)
					{
						arr_of_members[rus_member].status_member = "true";
					}
					arr_of_members[rus_member].number_isbooks--;
					isavailable = true;
					break;
				}
			}
			if (isavailable)
			{
				break;
			}
			//if the book not found
			else if (isavailable == false)
			{
				cout << "\tYou Do Not Have The Book\t\n";
				cout << "\tEnter The Book's ID : ";
				cin >> search;
			}
		}
		//storage new data in files
		fstream file1("books.txt", std::fstream::out | std::fstream::trunc);
		ofstream file2("books.txt", ios_base::app);
		for (int i = 0; i < book_id; i++)
		{
			file2 << arr_of_books[i].id_of_book << "%" << arr_of_books[i].name_of_book << "#" << arr_of_books[i].author << "$" << arr_of_books[i].year << "@" << arr_of_books[i].status_book << "*";
			if (arr_of_books[i].status_book == "false")
			{
				file2 << arr_of_books[i].name_of_ismember << '|';
				file2 << arr_of_books[i].start_of_time.day << '/' << arr_of_books[i].start_of_time.month << '/' << arr_of_books[i].start_of_time.year << '|';
				file2 << arr_of_books[i].end_of_time.day << '/' << arr_of_books[i].end_of_time.month << '/' << arr_of_books[i].end_of_time.year << '|';
			}
		}
		file2.close();
		fstream file3("members.txt", std::fstream::out | std::fstream::trunc);
		ofstream file4("members.txt", ios_base::app);
		for (int i = 0; i < member_id; i++)
		{
			file4 << arr_of_members[i].id_of_member << "%" << arr_of_members[i].name_of_member << "#" << arr_of_members[i].pass_of_member << "$";
			file4 << arr_of_members[i].date_of_member.day << '/' << arr_of_members[i].date_of_member.month << '/' << arr_of_members[i].date_of_member.year << '@' << arr_of_members[i].status_member << "*";
		}
		file4.close();
		fstream file5(arr_of_members[rus_member].name_of_member + ".txt", std::fstream::out | std::fstream::trunc);
		ofstream file6(arr_of_members[rus_member].name_of_member + ".txt", ios_base::app);
		for (int i = 0; i < arr_of_members[rus_member].number_isbooks; i++)
		{
			file6 << arr_of_isbooks[rus_member][i].id_of_book << '|' << arr_of_isbooks[rus_member][i].name_of_book << '|';
			file6 << arr_of_isbooks[rus_member][i].start_of_time.day << '/' << arr_of_isbooks[rus_member][i].start_of_time.month << '/' << arr_of_isbooks[rus_member][i].start_of_time.year << '|';
			file6 << arr_of_isbooks[rus_member][i].end_of_time.day << '/' << arr_of_isbooks[rus_member][i].end_of_time.month << '/' << arr_of_isbooks[rus_member][i].end_of_time.year << '|';
		}
		file6.close();
	}
	else if (choice == 2)
	{
		search_of_book(arr_of_books, book_id, arr_of_words);
	}
}
//to know the book return today
void check_today(books arr_of_books[1000], int book_id)
{
	bool isfound = false;
	tm today = time1();
	int Year = today.tm_year + 1900;
	int Month = today.tm_mon + 1;
	int Day = today.tm_mday;
	stringstream year;
	year << Year;
	string Y_O_C = year.str();
	stringstream month;
	month << Month;
	string M_O_C = month.str();
	stringstream day;
	day << Day;
	string D_O_C = day.str();
	for (int i = 0; i < book_id; i++)
	{
		if (D_O_C == arr_of_books[i].end_of_time.day && M_O_C == arr_of_books[i].end_of_time.month && Y_O_C == arr_of_books[i].end_of_time.year)
		{
			display_books(arr_of_books, i);
			isfound = true;
		}
	}
	//if not found the book
	if (!isfound)
	{
		cout << "\n\n\t No book return today\n";
	}
	system("pause");
}

////////////////////////////////////////////////////////////////////