#include "pch.h"
#include <conio.h>
#include <iostream>
#include <windows.h>           

#pragma warning(disable : 4996)
using namespace std;


#define KEY_ARROW_UP    72
#define KEY_ARROW_RIGHT 77
#define KEY_ARROW_DOWN  80
#define KEY_ARROW_LEFT  75
#define ATTR1           240
#define ATTR3           243


struct Student {
	char  name[15];
	char  surname[25];
	float rating;
};


struct Node {
	Student a;
	Node   *next;
};


char menu[20][35] = { "1 -> ADD ELEMENT:", "	a) To head", "	b) To tail", "	c) Into place", "2 -> SORT LIST", "3 -> SWAP k-i and j-i ELEMENTS", "4 -> FIND ELEMENT BY:",
					"	a) Surname", "	b) Place", "4 -> PRINT THE LIST ON THE SCREEN", "5 -> COUNTING", "6 -> EDIT ELEMENT", "7 -> DELETE ELEMENT:", "	a) From head", 
					"	b) From tail", "	c) From place","	d) Rating < N", "8 -> DELETE LIST", "9 -> WRITE TO .txt FILE", "\n10 -> END"};


Node  *create_list(char name[], char surname[], float rating);
Node  *add_to_head(Node *head, char name[], char surname[], float rating);
void   add_to_tail(Node *head, char name[], char surname[], float rating);
Node  *add_into_place(Node *head, int position);
void   swap_elements(Node **head, int K, int J);
Node  *sort(Node *head);
void   find_surname(Node *head, HANDLE h);
Node  *find_place(Node *head);
void   print_list(Node *head, HANDLE h);
int    counting(Node *head, float max);
void   edit_element(Node *head, char surname[]);
Node  *delete_from_head(Node **head);
Node  *delete_from_tail(Node **head);
Node  *delete_from_place(Node **head, int position);
void   delete_min(Node **head, float min);
void   delete_all_list(Node  **head);
void   create_txt_file(Node*head);

void draw_menu(HANDLE h, COORD c, int k, int n);


int list_main() {
	Node   *head = 0, *temp=0;
	char   name[15], surname[25];
	float  rating, min, max;

	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 240);

	COORD c = { 0, 2 };
	int fl = 1, ch, k = 0, n = 20, position, K, J;

	draw_menu(h, c, k, n);

	while (fl) {

		if (_kbhit()) {

			ch = getch();

			switch (ch) {

				case 27: {
					fl = 0;
					SetConsoleTextAttribute(h, 240);
					system("cls");

					delete_all_list(&head);

					SetConsoleTextAttribute(h, 240);
					system("cls");
					break;
				}

				case 13: {
					switch (k) {

						case 1: {								                 //  add_to_head
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter student name: " << endl;
							cin >> name;
							cout << "Enter student's last name: " << endl;
							cin >> surname;
							cout << "Enter student rating: " << endl;

							while (!(cin >> rating)) {
								cout << "ERROR! Please, enter student rating again:\n";

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}
								//cin.clear();
								//cin.ignore();
							}

							head = add_to_head(head, name, surname, rating);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 2: {												//add_to_tail
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter student name: " << endl;
							cin >> name;
							cout << "Enter student's last name: " << endl;
							cin >> surname;
							cout << "Enter student rating: " << endl;

							while (!(cin >> rating)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}

								//cin.clear();
								//cin.ignore();
								cout << "ERROR! Please, enter student rating again:\n";
							}

							if (head) {
								add_to_tail(head, name, surname, rating);
								}
							else {
								head = add_to_head(head, name, surname, rating);
							}

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 3: {															//add_into_place
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter position [0,1,2...]: " << endl;
							while (!(cin >> position)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}

								//cin.clear();
								//cin.ignore();
								cout << "ERROR! Please, enter again:\n";
							}

							head = add_into_place(head, position);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 4: {                                                        //sort
							SetConsoleTextAttribute(h, 240);
							system("cls");

							head = sort(head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 5: {                                                        //swap
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter k[0,1,2...] and j[0,1,2...] elements: \n";

							while (!(cin >> K >> J)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}

								//cin.clear();
								//cin.ignore();
								cout << "ERROR! Please, enter again:\n";
							}

							swap_elements(&head, K, J);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 7: {                                                //find by surname
							SetConsoleTextAttribute(h, 240);
							system("cls");

							find_surname(head, h);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
							
						case 8: {												// find by place
							SetConsoleTextAttribute(h, 240);
							system("cls");

							temp = find_place(head);

							if (temp) {

								cout << "\nAt this point in the list is an element: " << endl;
								SetConsoleCursorPosition(h, { 0,4 });
								for (int j = 0; j < 51; j++) {
									cout << "-";
								}

								SetConsoleCursorPosition(h, { 0, 5 });
								cout << "|" << temp->a.name << endl;
								SetConsoleCursorPosition(h, { 15, 5 });
								cout << "|" << temp->a.surname << endl;
								SetConsoleCursorPosition(h, { 40,  5 });
								cout << "|" << temp->a.rating << endl;
								SetConsoleCursorPosition(h, { 50, 5 });
								cout << "|" << endl;
								SetConsoleCursorPosition(h, { 0, 6 });

								for (int j = 0; j < 51; j++) {
									cout << "-";
								}
								
								SetConsoleCursorPosition(h, { 0, 8 });
								system("pause");
							}

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 9: {													//PRINT	
							SetConsoleTextAttribute(h, 240);
							system("cls");

							print_list(head, h);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 10: {																		//counting
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter rating:" << endl;

							while (!(cin >> max)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}
								//cin.clear();
								//cin.ignore();
								cout << "ERROR! Please, enter again:\n";
							}

							if (counting(head, max)) {

								cout << "\nStudents with a rating higher than(or equals) " << max << " : " << counting(head, max) <<".\n" <<  endl;
								system("pause");
							}

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 11: {													//EDIT
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter the last name of the student whose rating you want to change: " << endl;
							cin >> surname;

							edit_element(head, surname);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 13: {											//delete_from_head
							SetConsoleTextAttribute(h, 240);
							system("cls");

							head = delete_from_head(&head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 14: {													//delete_from_tai
							SetConsoleTextAttribute(h, 240);
							system("cls");

							head = delete_from_tail(&head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 15: {												//delete_from_place							 
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter position [0,1,2...]:" << endl;
							cin >> position;

							while (!(cin >> position)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}

								cout << "ERROR! Please, enter again:\n";
							}

							head = delete_from_place(&head, position);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
	
						case 16: {												//delete_min							 
							SetConsoleTextAttribute(h, 240);
							system("cls");

							cout << "Enter min rating:" << endl;
							cin >> min;

							while (!(cin >> min)) {

								if (!cin) {
									cin.clear();
									while (cin.get() != '\n');
								}

								cout << "ERROR! Please, enter again:\n";
							}

							delete_min(&head, min);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}
						
						case 17: {														//delete_all_list
							SetConsoleTextAttribute(h, 240);
							system("cls");

							delete_all_list(&head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 18: {                                                 // txt file
							SetConsoleTextAttribute(h, 240);
							system("cls");

							create_txt_file(head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							break;
						}

						case 19: {															//END
							SetConsoleTextAttribute(h, 240);
							system("cls");

							delete_all_list(&head);

							SetConsoleTextAttribute(h, 240);
							system("cls");
							return 0;
						}
					}
				}

				case 80: {
					if (k == n - 1) {
						draw_menu(h, c, k, n);
						break;
					}

					else {
						k++;
						draw_menu(h, c, k, n);
						break;
					}
				}

				case 72: {
					if (k == 0) {
						draw_menu(h, c, k, n);
						break;
					}

					else {
						k--;
						draw_menu(h, c, k, n);
						break;
					}
				}
			}
		}
	}

	SetConsoleTextAttribute(h, 240);
	return 0;
} 


void draw_menu(HANDLE h, COORD c, int k, int n) {
	SetConsoleTextAttribute(h, 240);
	SetConsoleCursorPosition(h, { 0,0 });
	cout << "\tFUNCTIONS : " << endl;
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
		cc.Y = c.Y + i;
		SetConsoleCursorPosition(h, cc);
		cout << menu[i];
	}

	cc.Y = c.Y + k;
	SetConsoleTextAttribute(h, ATTR3);
	SetConsoleCursorPosition(h, cc);
	cout << menu[k];
}


Node *create_list(char name[], char surname[], float rating) {
	Node *curr = new Node;

	if (curr)
		cout << "\nMemory for the new object has been successfully allocated.\n";
	else
		cout << "\nMemory for the new object hasn`t been  allocated.\n";

	strcpy(curr->a.name, name);
	strcpy(curr->a.surname, surname);
	curr->a.rating = rating;
	curr->next = NULL;

	cout << "Object successfully created.\n\n";
	system("pause");

	return curr;
}


Node *add_to_head(Node *head, char name[], char surname[], float rating) {
	if (!head) {
		head = create_list(name, surname, rating);
		return head;
	}

	Node *curr = new Node;
	curr = create_list(name, surname, rating);
	curr->next = head;

	return curr;
}


void add_to_tail(Node *head, char name[], char surname[], float rating) {
	Node *curr = head;

	if(curr)
		cout << "\nMemory for the new object has been successfully allocated.\n";
	else
		cout << "\nMemory for the new object hasn`t been  allocated.\n";

	if (!curr) {
		head = create_list(name, surname, rating);
		return;
	}

	while (curr->next) {
		curr = curr->next;
	}

	Node *curr1 = new Node;
	strcpy(curr1->a.name, name);
	strcpy(curr1->a.surname, surname);
	curr1->a.rating = rating;
	curr1->next = NULL;
	curr->next = curr1;

	cout << "Object successfully created.\n\n";
	system("pause");

	return;
}


Node  *add_into_place(Node *head, int position) {
	Node *curr = head;
	Node *curr2 = head;
	int size=0, i=0;
	char   name[15], surname[25];
	float  rating;

	while (curr) {
		curr = curr->next;
		size++;
	}

	if (position < 0 || position > size) {
		cout << "Wrong number entered.\n" << endl;
		system("pause");
		return head;
	}

	cout << "Enter student name: " << endl;
	cin >> name;
	cout << "Enter student's last name: " << endl;
	cin >> surname;
	cout << "Enter student rating: " << endl;

	while (!(cin >> rating)) {

		if (!cin) {
			cin.clear();
			while (cin.get() != '\n');
		}

		//cin.clear();
		//cin.ignore();
		cout << "ERROR! Please, enter student rating again:\n";
	}

	if (!position) {
		head = add_to_head(head, name, surname, rating);
		return head;
	}

	if (position == size) {
		add_to_tail(head, name, surname, rating);
		return head;
	}

	while (i < position - 1 && curr2 != 0) {
		curr2 = curr2->next;
		i++;
	}

	Node *temp = new Node;

	if (curr)
		cout << "\nMemory for the new object has been successfully allocated.\n";
	else
		cout << "\nMemory for the new object hasn`t been  allocated.\n";

	if (curr2) {
		strcpy(temp->a.name, name);
		strcpy(temp->a.surname, surname);
		temp->a.rating = rating;

		temp->next = curr2->next;
		curr2->next = temp;
	}

	cout << "Object successfully created.\n\n";
	system("pause");

	return head;
}


Node *sort(Node *head){
	Node *curr = NULL;

	while (head != NULL){
		Node *temp = head;
		head = head->next;

		if (curr == NULL || temp->a.rating > curr->a.rating){
			temp->next = curr;
			curr = temp;
		}

		else{
			Node *curr2 = curr;

			while (curr2->next != NULL && !(temp->a.rating > curr2->next->a.rating)){
				curr2 = curr2->next;
			}

			temp->next = curr2->next;
			curr2->next = temp;
		}
	}

	cout << "List successfully sorted.\n\n" << endl;
	system("pause");

	return curr;
}


void swap_elements(Node **head, int K, int J) {
	int  i_1 = 0, i_2 = 0, size=0;
	Node *curr_1 = *head, *curr_2 = *head, *prev_1 = NULL, *prev_2 = NULL, *curr_test = *head;

	while (curr_test) {
		curr_test = curr_test->next;
		size++;
	}

	if (K < 0 || J < 0 || K >= size || J >= size) {
		cout << "Wrong number entered.\n" << endl;
		system("pause");
		return;
	}

	if (K == J) {
		return;
	}

	while (curr_1 && (i_1 < K)) {
		prev_1 = curr_1;
		curr_1 = curr_1->next;
		i_1++;
	}

	while (curr_2 && (i_2 < J)) {
		prev_2 = curr_2;
		curr_2 = curr_2->next;
		i_2++;
	}

	if (curr_1 == NULL || curr_2 == NULL) {
		return;
	}

	if (prev_1 != NULL) {
		prev_1->next = curr_2;
	}

	else {
		*head = curr_2;
	}

	if (prev_2 != NULL) {
		prev_2->next = curr_1;
	}

	else {
		*head = curr_1;
	}

	Node *temp = curr_2->next;

	curr_2->next = curr_1->next;
	curr_1->next = temp;

	cout << "Elements K and J successfully swaped.\n\n" << endl;
	system("pause");

	return;
}

void   find_surname(Node *head, HANDLE h) {
	short i = 4;
	char surname[25];
	Node  *curr = head;

	if (!curr) {
		SetConsoleCursorPosition(h, { 55,0 });
		cout << "LIST IS EMPTY.\n" << endl;

		system("pause");
		return;
	}

	cout << "Enter student's last name: " << endl;
	cin >> surname;

	cout << "\nList of students with the last name "<< surname <<" : " << endl;
	while (curr) {
		if (!strcmp(surname, curr->a.surname)) {

			SetConsoleCursorPosition(h, { 0,i });
			for (int j = 0; j < 51; j++) {
				cout << "-";
			}

			SetConsoleCursorPosition(h, { 0,i+1 });
			cout << "|" << curr->a.name << endl;
			SetConsoleCursorPosition(h, { 15,i+1});
			cout << "|" << curr->a.surname << endl;
			SetConsoleCursorPosition(h, { 40, i+1});
			cout << "|" << curr->a.rating << endl;
			SetConsoleCursorPosition(h, { 50, i + 1 });
			cout << "|" << endl;
			SetConsoleCursorPosition(h, { 0,i+2});

			for (int j = 0; j < 51; j++) {
				cout << "-";
			}

			i+=2;
		}

		curr = curr->next;
	}

	SetConsoleCursorPosition(h, { 0, i + 2 });
	system("pause");
	return;
}


Node   *find_place(Node *head) {
	Node  *curr = head;
	int place, size=0, i=0;

	if (!curr) {
		cout << "LIST IS EMPTY.\n" << endl;

		system("pause");
		return NULL;
	}


	cout << "Enter place[0,1,2...]: " << endl;

	while (!(cin >> place)) {

		if (!cin) {
			cin.clear();
			while (cin.get() != '\n');
		}

		//cin.clear();
		//cin.ignore();
		cout << "ERROR! Please, enter again:\n";
	}

	while (curr) {
		curr = curr->next;
		size++;
	}

	curr = head;
	if (place >= size || place < 0) {
		cout << "Wrong number entered\n" << endl;
		system("pause");
		return NULL;
	}

	while (i < place) {
		curr = curr->next;
		i++;
	}

	return curr;
}

int counting(Node *head, float max){
	int i = 0;
	Node  *curr = head;

	if (!curr) {
		cout << "LIST IS EMPTY.\n" << endl;

		system("pause");
		return 0 ;
	}

	while (curr) {
		if (curr->a.rating >= max) {
			i++;
			
		}
		curr = curr->next;
	}
	return i;
}

void   edit_element(Node *head, char surname[]) {
	Node  *curr = head;
	float rating_2=-1;

	if (!curr) {
		cout << "\nNo such student found.\n" << endl;

		system("pause");
		return;
	}

	while (curr) {
		if (!strcmp(surname, curr->a.surname)) {
			cout << "Enter new student rating: " << endl;
			cin >> rating_2;
			curr->a.rating = rating_2;
			//break;
		}

		curr = curr->next;
	}

	if (rating_2 == -1) {
		cout << "\nNo such student found.\n" << endl;

		system("pause");
		return;
	}

	cout << "\nRating successfully changed.\n\n" << endl;
	system("pause");
	return;
}


void print_list(Node *head, HANDLE h) {
	Node  *curr = head;

	if (!curr) {
		SetConsoleCursorPosition(h, { 55,0 });
		cout << "LIST IS EMPTY.\n" << endl;

		system("pause");
		return;
	}

	SetConsoleCursorPosition(h, { 35, 0 });

	for (int j = 0; j < 50; j++) {
		cout << "-";
	}

	SetConsoleCursorPosition(h, { 35,1 });
	cout << "|NAME " << endl;
	SetConsoleCursorPosition(h, { 50,1 });
	cout << "|SURNAME " << endl;
	SetConsoleCursorPosition(h, { 75, 1});
	cout << "|RATING  |" << endl;
	SetConsoleCursorPosition(h, { 35,2 });

	for (int j = 0; j < 50; j++) {
		cout << "-";
	}

	SetConsoleCursorPosition(h, { 60,3 });
	cout << "HEAD" << endl;

	short i = 4;
	while (curr) {
		Sleep(350);

		SetConsoleCursorPosition(h, { 35,i });
		for (int j = 0; j < 50; j++) {
			cout << "-";
		}

		SetConsoleCursorPosition(h, { 35, i+1 });
		cout << "|" << curr->a.name << endl;
		SetConsoleCursorPosition(h, { 50, i+1 });
		cout << "|" << curr->a.surname << endl;
		SetConsoleCursorPosition(h, { 75, i+1 });
		cout << "|" << curr->a.rating << endl;
		SetConsoleCursorPosition(h, { 84, i+1 });
		cout << "|" << endl;

		SetConsoleCursorPosition(h, { 35, i + 2 });
		for (int j = 0; j < 50; j++) {
			cout << "-";
		}

		SetConsoleCursorPosition(h, { 61, i + 3 });
		cout << "|" << endl;
		SetConsoleCursorPosition(h, { 61, i + 4 });
		cout << "V" << endl;

		curr = curr->next;
		i += 5;
	}

	SetConsoleCursorPosition(h, { 60, i});

	cout << "NULL\n" << endl;;
	system("pause");
	return;
}


Node *delete_from_head(Node **head) {
	Node *temp = *head;

	if (!*head) {
		return NULL;
	}

	if (temp->next != 0) {
		temp = temp->next;

		delete *head;
		cout << "Object successfully destroyed.\n" << endl;;
		*head = temp; 
		
		system("pause");
		return *head;
	}

	
	delete *head;

	cout << "Object successfully destroyed.\n" << endl;;
	system("pause");

	return NULL;
}


Node *delete_from_tail(Node **head) {
	if (!*head) {
		return NULL;
	}

	Node *temp = *head;

	if (!(temp->next)) {
		delete *head;

		cout << "Object successfully destroyed.\n" << endl;
		system("pause");

		return NULL;
	}
	

	while (temp->next->next) {
		temp = temp->next;
	}

	delete temp->next;
	temp->next = NULL;

	cout << "Object successfully destroyed.\n" << endl;
	system("pause");

	return *head;
}


Node  *delete_from_place(Node **head, int position) {
	Node *curr = *head;
	Node *curr2 = *head;
	int size = 0, i = 0;

	while (curr) {
		curr = curr->next;
		size++;
	}

	if (position < 0 || position > size-1) {
		cout << "Wrong number entered.\n" << endl;
		system("pause");

		return *head;
	}

	if (!position) {
		curr2 = delete_from_head(head);
		return curr2;
	}

	if (position == size-1) {
		curr2 = delete_from_tail(head);
		return curr2;
	}

	curr = curr2;
	while (i < position) {
		curr = curr2;
		curr2 = curr2->next;
		i++;
	}

	curr->next = curr2->next;
	curr2->next = NULL;
	delete curr2;

	cout << "\nObject successfully destroyed.\n" << endl;
	system("pause");

	return *head;
}

void   delete_min(Node **head, float min) {
	Node  *curr = *head, *prev = *head;

	while (curr != NULL) {

		if (curr->a.rating < min) {

			if (curr == *head) {
				curr = curr->next;
				delete *head;
				cout << "\nObject successfully destroyed.\n" << endl;
				*head = curr;
				prev = curr;
			}

			else {
				prev->next = curr->next;
				delete curr;
				cout << "\nObject successfully destroyed.\n" << endl;;
				curr = prev->next;
			}
		}

		else {
			prev = curr;
			curr = curr->next;
		}
	}

	system("pause");
	return;
}


void delete_all_list(Node **head) {
	Node *temp = *head;
	int k = 0;

	while (temp) { 
		k = 1;
		temp = temp->next;
		delete *head;
		cout << "Object successfully destroyed.\n";
		*head = temp;
	}

	if (k) {
		system("pause");
	}

	return;
}

void   create_txt_file(Node *head) {
	char name_txt[20];
	Node *curr = head;
	FILE *file;

	cout << "Enter a name of txt-file(Name.txt): " << endl;
	cin >> name_txt;

	if (!(file = fopen(name_txt, "w+"))) {
		printf("CANNOT OPEN THE FILE!\n");
		system("pause");

		return;
	}

	while (curr) {
		fprintf(file, "%s %s : %0.3f\n", curr->a.name, curr->a.surname, curr->a.rating);
		curr = curr->next;
	}
													
	cout << "\nData successfully entered into file " << name_txt << endl;

	system("pause");
	fclose(file);

	return;
}
