#ifndef FUNDAMENTAL_ALGORITHMS_MAIL_H
#define FUNDAMENTAL_ALGORITHMS_MAIL_H

#include "../../utility/error_handler.h"
#include "mystring.h"

#define STANDARD_CAPACITY 5

typedef struct Address {
    String city;
    String street;
    unsigned int house;
    String building;
    unsigned int apartment;
    String post_index;
} Address;

typedef struct Mail {
    Address address;
    float weight;
    String id;
    String creation_date;
    String delivery_date;
} Mail;

typedef struct Post {
    Address *address;
    Mail *mails;
    int length;
    int capacity;
} Post;

typedef struct Time {
    int day;
    int month;
    int year;
    int hour;
    int minute;
    int second;
} Time;

#endif //FUNDAMENTAL_ALGORITHMS_MAIL_H
