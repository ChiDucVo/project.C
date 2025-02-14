#ifndef DATATYPE_H
#define DATATYPE_H

// Struct luu tru ngày tháng nam
struct Date {
    int day, month, year;
};

// Struct luu tru thông tin sách
struct Book {
    char bookId[10];
    char title[30];
    char author[20];
    int quantity;
    int price;
    struct Date publication;
};

#endif
