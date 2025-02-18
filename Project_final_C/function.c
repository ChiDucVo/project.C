#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "function.h"
#define MAX_BOOKS 100
#define FILE_NAME "data/book.bin"
#define MAX_MEMBERS 100
#define MEMBER_FILE "data/member.bin"

struct Book books[MAX_BOOKS];
int bookCount = 0;

struct Member members[MAX_MEMBERS];
int memberCount = 0;

// Ðoc du lieu sach tu file
void loadBooksFromFile() {
    FILE *file = fopen("book.bin", "rb");
    
    if (file == NULL) {
        printf("Warning: No existing book data found. Creating a new file...\n");
        file = fopen("data/book.bin", "wb"); // Tao file moi neu chua co
        if (file == NULL) {
            printf("Error: Cannot create book data file.\n");
            return;
        }
        fclose(file);
        return;
    }
    bookCount = fread(books, sizeof(struct Book), MAX_BOOKS, file);
    fclose(file);
    if (bookCount == 0) {
        printf("No books available.\n");
    } else {
        printf("Loaded %d books from file.\n", bookCount);
    }
}
// Ghi du lieu sach vào file
void saveBooksToFile() {
    FILE *file = fopen("book.bin", "wb");
    if (file == NULL) {
        printf("Error: Unable to save book data.\n");
        return;
    }		
    fwrite(books, sizeof(struct Book), bookCount, file);
    fclose(file);
    printf("Book data saved successfully.\n");
}

// Hien thi menu quan ly khach hang
void showMemberMenu() {
    int choice;
    do {
       
        printf("\n========== MEMBER MANAGEMENT ==========\n");
        printf("[1] Display Members\n");
        printf("[2] Add Member\n");
        printf("[3] Edit Member\n");
        printf("[0] Back to Main Menu\n");
        printf("=======================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1:
                system("cls");
                displayMembers();
                break;
            case 2:
                system("cls");
                addMember();
                break;
            case 3:
                system("cls");
                editMember();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
        printf("\nPress Enter to return to the menu...");
        getchar();
    } while (choice != 0);
}

// Hien thi danh sach khach hang
void displayMembers() {
    if (memberCount == 0) {
    printf("No members available.\n");
    } else {
        printf("\n**** Member List ****\n");
        printf("+------------+----------------------+---------------+--------+\n");
        printf("| %-10s | %-20s | %-13s | %-6s |\n", "Member ID", "Name", "Phone", "Status");
        printf("+------------+----------------------+---------------+--------+\n");
        for (int i = 0; i < memberCount; i++) {
            printf("| %-10s | %-20s | %-13s | %-6s |\n",
                members[i].memberId, members[i].name, members[i].phone,
                members[i].status ? "Active" : "Locked");
        }
        printf("+------------+----------------------+---------------+--------+\n");
    }
    printf("\nPress ENTER to return to the menu...");
    getchar();
}

// Kiem tra trung lap ID khach hang
int isDuplicateMemberId(const char *memberId) {
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, memberId) == 0) {
            printf("Error: Member ID '%s' already exists. Please enter a different ID.\n", memberId);
            return 1;
        }
    }
    return 0;
}

// Them khach hang moi
void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Cannot add more members.\n");
        return;
    }
    struct Member newMember;
    char choice;
    do {
        printf("\n*** ADD NEW MEMBER ***\n");
        do {
            printf("Enter Member ID: ");
            scanf("%s", newMember.memberId);
            getchar();
        } while (isDuplicateMemberId(newMember.memberId));

        printf("Enter Name: ");
        fgets(newMember.name, sizeof(newMember.name), stdin);
        newMember.name[strcspn(newMember.name, "\n")] = 0;

        printf("Enter Phone: ");
        scanf("%s", newMember.phone);
        getchar();

        newMember.status = true; // M?c d?nh tr?ng thái Active

        members[memberCount++] = newMember;
        printf("fwtfcghhhhhhhhhhhhhhhhhhhe");
        saveBooksToFile();
        printf("Member added successfully!\n");

        printf("\nDo you want to add another member? (Y/N): ");
        scanf(" %c", &choice);
        getchar();
    } while (choice == 'Y' || choice == 'y');
    printf("Returning to Member Management Menu...\n");
}

// Chinh sua thong tin khach hang
void editMember() {
    char memberId[10];
    printf("Enter the Member ID to edit (or '0' to cancel): ");
    scanf("%s", memberId);
    getchar();
    if (strcmp(memberId, "0") == 0) return;

    int index = -1;
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].memberId, memberId) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Member ID not found.\n");
        return;
    }

    printf("\nEditing member: %s\n", members[index].name);
    
    printf("Enter New Name: ");
    fgets(members[index].name, sizeof(members[index].name), stdin);
    members[index].name[strcspn(members[index].name, "\n")] = 0;

    printf("Enter New Phone: ");
    scanf("%s", members[index].phone);
    getchar();

    printf("Set Status (1: Active, 0: Locked): ");
    int status;
    scanf("%d", &status);
    members[index].status = status;

    printf("Member updated successfully!\n");
    printf("\nPress ENTER to return to the menu...");
    getchar();
    
}


// Menu chinh

void showMainMenu() {
    int choice;
    do {
          
        printf("\n*** LIBRARY MANAGEMENT ***\n");
        printf("[1] Manage Books\n");
        printf("[2] Manage Members\n"); 
        printf("[0] Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                showBookMenu();
                break;
            case 2:
                showMemberMenu();  // Goi menu quan ly khach hang
                break;
            case 0:
                printf("Exiting program...\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);
}
// Hien thi danh sach sach 
void displayBooks() {
    if (bookCount == 0) {
        printf("No books available.\n");
    } else {
        printf("\n**** All Books ****\n");
        printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
        printf("| %-10s | %-28s | %-20s | %-8s | %-6s | %-10s |\n", 
            "Book ID", "Title", "Author", "Quantity", "Price", "Pub Date");
        printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
        for (int i = 0; i < bookCount; i++) {
            printf("| %-10s | %-28s | %-20s | %-8d | %-6d | %02d/%02d/%04d |\n",
                books[i].bookId, books[i].title, books[i].author, books[i].quantity, 
                books[i].price, books[i].publication.day, books[i].publication.month, books[i].publication.year);
            printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
        }
    }
    printf("\nPress ENTER to return to the menu...");
    getchar();
}
// Kiem tra xem sach co bi trung ID, tiêu de hoac tac gi không
int isDuplicateBookId(const char *bookId) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, bookId) == 0) {
            printf("Error: Book ID '%s' already exists. Please enter a different ID.\n", bookId);
            return 1;
        }
    }
    return 0;
}
// Them sach moi ( dong thoi kiem tra trung lap )

// Kiem tra trung lap tieu de sach
int isDuplicateTitle(const char *title) {
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].title, title) == 0) {
            printf("Error: The book title '%s' already exists. Please enter a different title.\n", title);
            return 1;  // Tra ve 1 neu trung lap
        }
    }
    return 0;  // Tra ve 0 neu khong trung lap
}
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Cannot add more books.\n");
        return;
    }
    struct Book newBook;
    char choice;
    do {
        printf("\n*** ADD NEW BOOK ***\n");
        // Kiem tra trung lap ID
        do {
            printf("Enter Book ID: ");
            scanf("%s", newBook.bookId);
            getchar();
        } while (isDuplicateBookId(newBook.bookId));

        // Kiem tra trung lap tieu de
        do {
            printf("Enter Title: ");
            fgets(newBook.title, sizeof(newBook.title), stdin);
            newBook.title[strcspn(newBook.title, "\n")] = 0;
        } while (isDuplicateTitle(newBook.title));  // Kiem tra trung lap title

        printf("Enter Author: ");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = 0;
        printf("Enter Quantity: ");
        scanf("%d", &newBook.quantity);
        printf("Enter Price: ");
        scanf("%d", &newBook.price);
        printf("Enter Publication Date (DD MM YYYY): ");
        scanf("%d %d %d", &newBook.publication.day, &newBook.publication.month, &newBook.publication.year);
        
        books[bookCount++] = newBook;
        saveBooksToFile();
        printf("Book added successfully!\n");
        
        // Quay lai menu hay tiep tuc them sach
        printf("\nDo you want to add another book? (Y/N): ");
        scanf(" %c", &choice);
        getchar();
    } while (choice == 'Y' || choice == 'y');
    printf("Returning to Book Management Menu...\n");
}
// Sua thong tin sach
void editBook() {
    char bookId[10];
    printf("Enter the Book ID to edit (or '0' to cancel): ");
    scanf("%s", bookId);
    getchar();
    if (strcmp(bookId, "0") == 0) return;
    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, bookId) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Error: Book ID not found.\n");
        return;
    }
    printf("Editing book: %s\n", books[index].title);
    
    printf("Enter New Title: ");
    fgets(books[index].title, sizeof(books[index].title), stdin);
    books[index].title[strcspn(books[index].title, "\n")] = 0;
    printf("Enter New Author: ");
    fgets(books[index].author, sizeof(books[index].author), stdin);
    books[index].author[strcspn(books[index].author, "\n")] = 0;
    printf("Enter New Quantity: ");
    scanf("%d", &books[index].quantity);
    printf("Enter New Price: ");
    scanf("%d", &books[index].price);
    printf("Enter New Publication Date (DD MM YYYY): ");
    scanf("%d %d %d", &books[index].publication.day, &books[index].publication.month, &books[index].publication.year);
    printf("Book updated successfully!\n");
    printf("\nPress ENTER to return to the menu...");
    getchar();
    getchar();
    void saveBooksToFile();
}

// Xoa sach theo ID
void deleteBook() {
    char bookId[10];
    printf("Enter the Book ID to delete (or '0' to cancel): ");
    scanf("%s", bookId);
    getchar();
    if (strcmp(bookId, "0") == 0) return;
    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].bookId, bookId) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Error: Book ID not found.\n");
        return;
    }
    printf("Are you sure you want to delete this book? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();
    if (confirm == 'y' || confirm == 'Y') {
        for (int i = index; i < bookCount - 1; i++) {
            books[i] = books[i + 1];
        }
        bookCount--;
        printf("Book deleted successfully!\n");
    } else {
        printf("Deletion canceled.\n");
    }
    printf("\nPress ENTER to return to the menu...");
    getchar();
    void saveBooksToFile();
}

// Sap xep sach theo gia tien
void sortBooksByPrice() {
    if (bookCount == 0) {
        printf("No books available to sort.\n");
        return;
    }
    int choice;
    do {
        printf("\n*** SORT BOOKS BY PRICE ***\n");
        printf("[1] Ascending Order\n");
        printf("[2] Descending Order\n");
        printf("[0] Back to Book Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        if (choice == 0) return;  // Quay lai menu quan ly sach
        for (int i = 0; i < bookCount - 1; i++) {
            for (int j = i + 1; j < bookCount; j++) {
                if ((choice == 1 && books[i].price > books[j].price) ||
                    (choice == 2 && books[i].price < books[j].price)) {
                    struct Book temp = books[i];
                    books[i] = books[j];
                    books[j] = temp;
                }
            }
        }
        printf("Books sorted successfully!\n");
        displayBooks();
        printf("\nPress ENTER to return to sorting menu...");
        getchar();
    } while (choice != 0);
}
// Tim kiem sach theo ten
void searchBookByTitle() {
    if (bookCount == 0) {
        printf("No books available to search.\n");
        return;
    }
    char keyword[30];
    printf("Enter book title to search (or '0' to cancel): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;  // Looi bo ky tu xuong dong
    if (strcmp(keyword, "0") == 0) return;  // Quay lai menu quan ly sách
    int found = 0;
    printf("\n**** Search Results ****\n");
    printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
    printf("| %-10s | %-28s | %-20s | %-8s | %-6s | %-10s |\n", 
           "Book ID", "Title", "Author", "Quantity", "Price", "Pub Date");
    printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword)) {
            printf("| %-10s | %-28s | %-20s | %-8d | %-6d | %02d/%02d/%04d |\n",
                   books[i].bookId, books[i].title, books[i].author, books[i].quantity, 
                   books[i].price, books[i].publication.day, books[i].publication.month, books[i].publication.year);
            printf("+------------+------------------------------+----------------------+----------+--------+------------+\n");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching '%s'.\n", keyword);
    }
    printf("\nPress ENTER to return to search menu...");
    getchar();
}

// Kiem tra du lieu sach hop le
int isValidBook(struct Book *book) {
    if (strlen(book->bookId) == 0 || strlen(book->title) == 0 || strlen(book->author) == 0) {
        printf("Error: Book ID, Title, and Author cannot be empty.\n");
        return 0;
    }
    if (book->quantity < 0 || book->price < 0) {
        printf("Error: Quantity and Price must be non-negative.\n");
        return 0;
    }
    if (book->publication.day < 1 || book->publication.day > 31 ||
        book->publication.month < 1 || book->publication.month > 12 ||
        book->publication.year < 1000 || book->publication.year > 9999) {
        printf("Error: Invalid publication date.\n");
        return 0;
    }
    return 1;
}
void showBookMenu() {
    int choice;
    system ("cls");
    do {
        printf("\n========== BOOK MANAGEMENT ==========\n");
        printf("[1] Display Books\n");
        printf("[2] Add Book\n");
        printf("[3] Edit Book\n");
        printf("[4] Delete Book\n");
        printf("[5] Sort Books by Price\n");
        printf("[6] Search Book by Title\n");
        printf("[0] Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1:
                system("cls");
                printf("\n==== DISPLAY BOOKS ====\n");
                displayBooks();
                break;
            case 2:
                system("cls");
                printf("\n==== ADD BOOK ====\n");
                addBook();
                break;
            case 3:
                system("cls");
                printf("\n==== EDIT BOOK ====\n");
                editBook();
                break;
            case 4:
                system("cls");
                printf("\n==== DELETE BOOK ====\n");
                deleteBook();
                break;
            case 5:
                system("cls");
                printf("\n==== SORT BOOKS ====\n");
                sortBooksByPrice();
                break;
            case 6:
                system("cls");
                printf("\n==== SEARCH BOOK ====\n");
                searchBookByTitle();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
        printf("\nPress Enter to return to the menu...");
        getchar();
    } while (choice != 0);
}
