#ifndef FUNDAMENTAL_ALGORITHMS_MAIL_H
#define FUNDAMENTAL_ALGORITHMS_MAIL_H

#include "../../utility/error_handler.h"
#include "mystring.h"

typedef struct Address {
    String city;
    String street;
    unsigned int house;
    String building;
    unsigned int apartment;
    String post_index;
} Address;

typedef struct Mail {
    float weight;
    String id;
    String creation_date;
    String delivery_date;
} Mail;

typedef struct Post {
    Address *address;
    Mail *mails;
} Post;

#endif //FUNDAMENTAL_ALGORITHMS_MAIL_H
