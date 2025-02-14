#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Hien thi menu chinh
void showMainMenu();

// Quan ly sach
void showBookMenu();
void displayBooks();
void addBook();
void editBook();
void deleteBook();
void sortBooksByPrice(); // Them ham sap xep sach theo gia
void searchBookByTitle(); // Chuc nang tim kiem sach theo ten

// Quan ly file (ddc/ghi du lieu sach)
void loadBooksFromFile();  // Them khai bao
void saveBooksToFile();    // Them khai bao


// Kiem tra du lieu hop le
int isValidBook(struct Book *book);

#endif
