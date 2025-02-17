#ifndef DATATYPE_H
#define DATATYPE_H
#include <stdbool.h>
// Struct luu tru ng�y th�ng nam
struct Date {
    int day, month, year;
};
// Struct luu tru th�ng tin s�ch
struct Book {
    char bookId[10];
    char title[30];
    char author[20];
    int quantity;
    int price;
    struct Date publication;
};

// Cau truc luu thong tin khach hang
struct Member {
    char memberId[10];
    char name[30];
    char phone[15];
    bool status; // 1: Active, 0: Locked
};

#endif
