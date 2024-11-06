#ifndef FUNDAMENTAL_ALGORITHMS_MAIL_H
#define FUNDAMENTAL_ALGORITHMS_MAIL_H

#include "../../utility/error_handler.h"
#include "mystring.h"

#include <time.h>

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

#ifndef LAB1T1_ARRAY_H

int is_num(int x);

#endif

int compare_mail(const void *a, const void *b);
int parse_time(const String *str, Time *time);
int compare_creation_date(const void *a, const void *b);
int compare_time_str(const void *a, const void *b);
int compare_time(const void *a, const void *b);

int create_address(Address *addr, char *post_index, char *building, char *city, char *street, int apartment,
                   int house);
int copy_address(Address *dst, const Address *src);
void print_address(Address addr);
void destroy_address(Address *addr);

int create_mail(Mail *mail, Address addr, float weight, char *id, char *creation_date, char *delivery_date);
void print_mail(Mail mail);
void destroy_mail(Mail *mail);

int create_post(Post *post, Address *addr);
int resize_post(Post *post, int size_delta);
int extend_post(Post *post);
int append_post(Post *post, Mail mail);
int delete_post_mail(Post *post, String mail_id);
void destroy_post(Post *post);

int search_mail_id(Post *post, String mail_id, Mail **found, int *index);
int search_mail_in_time(Post *post, Mail *found, int *index);
int search_mail_delayed(Post *post, Mail *found, int *index);

#endif //FUNDAMENTAL_ALGORITHMS_MAIL_H
