# LINKED_LIST_TUTORIAL

Program Overview:

This tutorial program shows all functions required for working with single-linked lists.

A single-linked list is a data structure consisting of elements of the same type that are interconnected sequentially by means of pointers. Each element in the list has a pointer to the next element. The last element (tail) of the list points to NULL. Element without a pointer to it is the first (head) element of the list.

As an example, here is a ranking list of students with the following fields: student's first name, student's last name, student's rating.

         Overview of the function:

1) Add to head:
A new element is created and then placed at the top of the list.

2) Add to tail:
A new element is created and then placed at the end of the list.

3) Add to the place:
It creates a new element that fits in a specific place in the list.
Numbering starts at 0.
If the number is larger for the size of the list, an error message is displayed.

4) Sort the list:
The list is sorted by descending of the student rating field.

5) Swap two elements:
Swaps positions of two given elements.
Numbering starts at 0.
If the number is larger for the size of the list, an error message is displayed.

6) Search for an item in the list by last name:
Enter the student's last name you want to find. If a element with matching last name field is found in the list, it is displayed on the screen.

7) Search for an item in the list by location:
Enter the position of the student in the list of which you want to find. If a student is found in the list at such a place - it is displayed on the screen.
Numbering starts at 0.
If the number is larger for the size of the list, an error message is displayed.

8) Show the list on the screen:
Full list is displayed on the screen.

9) Rating account:
Enter rating. The function counts the number of students whose rating is higher than the entered.

10) Element change:
The student's last name is entered, and then his new rating. Function changes the rating of the given student to the entered number.

11) Removal from the head:
The first element in the list is deleted.

12) Removal from the tail:
The last element in the list is deleted.

13) Removal from the given position:
Removes the list element which position number was entered.
Numbering starts at 0.
If the number is larger for the size of the list, an error message is displayed.

14) Deletion by rating:
All students whose rating is lower than the entered are removed from the list.

15) The entire list is deleted completely (it also happens when you exit to the main menu).

16) Write to file:
A file is created to which the existing list is written.
