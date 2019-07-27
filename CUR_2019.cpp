#include "pch.h"
#include "list.h"
#include <conio.h>
#include <ctime>																	
#include <iostream>
#include <windows.h>


#pragma warning(disable : 4996)
using namespace std;


#define KEY_ARROW_UP    72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN  80
#define KEY_ARROW_LEFT  75
#define ATTR1           240
#define ATTR2           15


char m[4][15] = { "  S T A R T  ", " A B O U T !! ", " H E L P ?? ", "  E X I T  " };


void frame(HANDLE h, COORD frame_begin, COORD frame_end);					 //BUILDING A FRAME
void draw( HANDLE h, COORD c, int k, int n, int len);				 // MENU
void Start(HANDLE h);                                              // START
void About(HANDLE h);												//ABOUT
void Help( HANDLE h);                       //HELP


int main() {
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 240);
	system("cls");
	SetConsoleTitle(L"PACKAGE FUNCTIONS FOR WORKING WITH A SINGLY-LINKED LIST.");

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.X = 10;														// Width of each character in the font
	cfi.dwFontSize.Y = 25;												// Height
	wcscpy(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);


	COORD frame_begin = { 0, 4 };              // BEGIN OF FRAME
	COORD frame_end = { 119, 7 };                                       // END FRAME
	COORD c = { 8, 5 };                       // COODR for key
	int fl = 1, ch, k = 0, n = 4, len = 32;

	draw(h, c, k, n, len);
	frame(h, frame_begin, frame_end);
	

	while (fl) {

		if (_kbhit()) {

			ch = getch();

			switch (ch) {

				case 27: {
					fl = 0;
					SetConsoleTextAttribute(h, 240);          // ESC
					system("cls");
					break;
				}

				case 13: {                            // ENTER
					switch (k) {

						case 0: {
							Start(h);
							break;
						}

						case 1: {
							About(h);
							break;
						}

						case 2: {
							Help(h);
							break;
						}

						case 3: {
							SetConsoleTextAttribute(h, 240);
							fl = 0;
							system("cls");
						}
					}
				}

				case 77: {
					if (k == n - 1) {
						break;
					}

					else {
						k++;
						draw(h, c, k, n, len);
						frame(h, frame_begin, frame_end);
						break;
					}
				}

				case 75: {
					if (k == 0) {
						break;
					}

					else {
						k--;
						draw(h, c, k, n, len);
						frame(h, frame_begin, frame_end);
						break;
					}
				}
			}
		}
	}

	return 0;
}

																						//building a frame
void frame(HANDLE h, COORD frame_begin, COORD frame_end) {
	COORD t = frame_begin;
	int len_x = frame_end.X - t.X - 2;
	int len_y = frame_end.Y - t.Y - 2;

	SetConsoleTextAttribute(h, 240);
	SetConsoleCursorPosition(h, frame_begin);

	cout << char(457);
	for (int i = 0; i < len_x; i++) {
		cout << char(461);
	}

	cout << char(443);
	frame_begin.Y++;
	for (int i = 0; i < len_y; i++, frame_begin.Y++) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}

	SetConsoleCursorPosition(h, frame_begin);
	cout << char(456);
	for (int i = 0; i < len_x; i++) {
		cout << char(461);
	}

	cout << char(444);
	SetConsoleCursorPosition(h, frame_begin);
	frame_begin.X = frame_end.X;
	frame_begin.X--;
	frame_begin.Y--;
	for (int i = 0; i < len_y; i++, frame_begin.Y--) {
		SetConsoleCursorPosition(h, frame_begin);
		cout << char(442);
	}

	SetConsoleTextAttribute(h, 240);
	for (short i = 30; i < 120; i = i + 30) {

		SetConsoleCursorPosition(h, { 4 + i , 4 });
		cout << char(457);

		SetConsoleCursorPosition(h, { 3 + i , 4 });
		cout << char(443);

		SetConsoleCursorPosition(h, { 3 + i , 5 });
		cout << char(442);

		SetConsoleCursorPosition(h, { 4 + i , 5 });
		cout << char(442);

		SetConsoleCursorPosition(h, { 4 + i , 6 });
		cout << char(456);

		SetConsoleCursorPosition(h, { 3 + i , 6 });
		cout << char(444);
	}
	SetConsoleCursorPosition(h, { 113, 10 });
}


void draw(HANDLE h, COORD c, int k, int n, int len) {
	SetConsoleTextAttribute(h, 240);
	time_t sec;
	int kolichestvo_dney;

	SetConsoleCursorPosition(h, { 94, 10 });
	sec = time(NULL);
	kolichestvo_dney = (sec / 3600) / 24;
	cout << asctime(localtime(&sec));

	SetConsoleCursorPosition(h, { 0, 8 });
	cout << "*Before you begin, we recommend that you go through the help tab!!!" << endl;

	SetConsoleCursorPosition(h, { 32,0 });
	cout << "-----------------------------------------------------------" << endl;
	SetConsoleCursorPosition(h, { 32, 1 });
	cout << "| PACKAGE FUNCTIONS FOR WORKING WITH A SINGLY-LINKED LIST |" << endl;
	SetConsoleCursorPosition(h, { 32,2 });
	cout << "|        on the example of a rating list of students.     |" << endl;
	SetConsoleCursorPosition(h, { 32,3 });
	cout << "-----------------------------------------------------------" << endl;

	SetConsoleTextAttribute(h, ATTR1);
	COORD cc = c;

	for (int i = 0; i < n; i++) {
		cc.X = c.X + i * len;
		SetConsoleCursorPosition(h, cc);
		cout << m[i];
	}

	cc.X = c.X + k * len;
	SetConsoleTextAttribute(h, ATTR2);
	SetConsoleCursorPosition(h, cc);
	cout << m[k];
}


void Start(HANDLE h) {
	SetConsoleTextAttribute(h, 240);
	system("cls");
	list_main();
	return;
}


void About(HANDLE h) {
	int ch;
	SetConsoleTextAttribute(h, 249);
	system("cls");
	cout << "\nThis program was created by a student of ....\nVersion 1.0.2\nLicensed product.\n\n\n" << endl;

	cout << "Enter ESC for exit......";


	while (1) {

		ch = getch();

		if (ch == 27) {

			SetConsoleTextAttribute(h, 240);
			system("cls");
			break;
		}
	}

	system("cls");
}


void Help(HANDLE h) {
	int ch;

	SetConsoleTextAttribute(h, 244);
	system("cls");

	cout << "\n________________________________________________________________________________________________________________________\n" << endl;
	SetConsoleTextAttribute(h, 242);
	cout << "\t\t\t\t\tProgram Overview: " << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\n\n This tutorial program shows all functions required for working with single - linked lists." << endl;
	cout << " A SINGLY-LINKED LIST is a data structure consisting of elements of the same type.\n" << endl; 
	cout << " Each element in the list has a pointer to the next element.\n The last element(tail) of the list points to NULL.\n Element without a pointer to it is the first(head) element of the list.\n " << endl;
	cout << " As an example, here is a RANKING LIST OF STUDENTS with the following fields:\n\tstudent's first name, student's last name, student's rating." << endl;
	SetConsoleTextAttribute(h, 244);
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	SetConsoleTextAttribute(h, 242);
	cout << "\n\t\t\t\t\tOverview of the function:\n\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "1) Add to head:\n " << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tA new element is createdand then placed at the top of the list. \n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "2) Add to tail: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tA new element is createdand then placed at the end of the list.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "3) Add to the place:\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tIt creates a new element that fits in a specific place in the list." << endl;
	cout << "\tNumbering starts at 0." << endl;
	cout << "\tIf the number is larger for the size of the list, an error message is displayed.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "4) Sort the list: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tThe list is sorted by descending of the student rating field.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "5) Swap two elements:\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tSwaps positions of two given elements." << endl;
	cout << "\tNumbering starts at 0." << endl;
	cout << "\tIf the number is larger for the size of the list, an error message is displayed.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "6) Search for an item in the list by last name: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tEnter the student's last name you want to find.\n\tIf a element with matching last name field is found in the list, it is displayed on the screen.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "7) Search for an item in the list by location:\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tEnter the position of the student in the list of which you want to find.\n\tIf a student is found in the list at such a place - it is displayed on the screen." << endl;
	cout << "\tNumbering starts at 0." << endl;
	cout << "\tIf the number is larger for the size of the list, an error message is displayed.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "8) Show the list on the screen: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tFull list is displayed on the screen.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "9) Rating account: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tEnter rating.The function counts the number of students whose rating is higher than the entered.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "10) Element change: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tThe student's last name is entered, and then his new rating.\n\tFunction changes the rating of the given student to the entered number.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "11) Removal from the head:\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tThe first element in the list is deleted.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "12) Removal from the tail: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tThe last element in the list is deleted.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "13) Removal from the given position: \n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tRemoves the list element which position number was entered." << endl;
	cout << "\tNumbering starts at 0." << endl;
	cout << "\tIf the number is larger for the size of the list, an error message is displayed.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "14) Deletion by rating:\n" << endl;
	SetConsoleTextAttribute(h, 240);
	cout << "\tAll students whose rating is lower than the entered are removed from the list.\n" << endl;
	SetConsoleTextAttribute(h, 241);
	cout << "15) The entire list is deleted completely(it also happens when you exit to the main menu).\n" << endl;
	cout << "16) Write to file:\n" << endl;	
	SetConsoleTextAttribute(h, 240);
	cout << "\tA file is created to which the existing list is written.\n" << endl;
	SetConsoleTextAttribute(h, 244);
	cout << "________________________________________________________________________________________________________________________\n" << endl;

	SetConsoleCursorPosition(h, { 0, 0 });
	SetConsoleTextAttribute(h, 240);

	cout << "Enter ESC for exit......";


	while (1) {

		ch = getch();

		if(ch ==27){

				SetConsoleTextAttribute(h, 240);
				system("cls");
				break;
			}
	}
}
