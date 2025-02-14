#ifndef DATATYPE_H
#define DATATYPE_H

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

#endif
