#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    int id;
    char title[50];
    char author[30];
    char isbn[20];
    int quantity;
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

void editBook() {
    int id, found = 0;
    printf("Enter Book ID to edit: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            found = 1;
            printf("Current Information:\n");
            printf("Title: %s, Author: %s, ISBN: %s, Quantity: %d\n", books[i].title, books[i].author, books[i].isbn, books[i].quantity);
            printf("Enter New Title: "); getchar(); fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = 0;
            printf("Enter New Author: "); fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;
            printf("Enter New ISBN: "); scanf("%s", books[i].isbn);
            printf("Enter New Quantity: "); scanf("%d", &books[i].quantity);
            printf("Book information updated successfully!\n");
            return;
        }
    }
    if (!found) {
        printf("Book ID not found!\n");
    }
}

void menu() {
    int choice;
    do {
        printf("\n**** Book Management System ****\n");
        printf("1. Display Books\n");
        printf("2. Add Book\n");
        printf("3. Edit Book\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: displayBooks(); break;
            case 2: addBook(); break;
            case 3: editBook(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 4);
}

int main() {
    menu();
    return 0;
}
