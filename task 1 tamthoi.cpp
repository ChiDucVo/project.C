#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[50]; // tieu de
    char author[30]; // tac gia
    char isbn[20]; // id sach
    int quantity; // so luong
};

struct Book books[MAX_BOOKS];
int bookCount = 0;

void displayBooks() {
    printf("\n**** All Books ****\n");
    printf("=======================================================================\n");
    printf("| %-5s | %-30s | %-20s | %-15s | %-5s |\n", "ID", "Title", "Author", "ISBN", "Qty");
    printf("=======================================================================\n");
    for (int i = 0; i < bookCount; i++) {
        printf("| %-5d | %-30s | %-20s | %-15s | %-5d |\n",
               books[i].id, books[i].title, books[i].author, books[i].isbn, books[i].quantity);
    }
    printf("=======================================================================\n");
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full!\n");
        return;
    }
    struct Book newBook;
    newBook.id = bookCount + 1;
    printf("Enter Title: "); getchar(); fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;
    printf("Enter Author: "); fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;
    printf("Enter ISBN: "); scanf("%s", newBook.isbn);
    printf("Enter Quantity: "); scanf("%d", &newBook.quantity);
    books[bookCount++] = newBook;
    printf("Book added successfully!\n");
}

void menu() {
    int choice;
    do {
        printf("\n**** Book Management System ****\n");
        printf("1. Display Books\n");
        printf("2. Add Book\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: displayBooks(); break;
            case 2: addBook(); break;
            case 3: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

int main() {
    menu();
    return 0;
}
