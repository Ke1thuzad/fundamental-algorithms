#include "mail.h"

int is_num(int x) {
    return x >= '0' && x <= '9';
}

int compare_mail(const void *a, const void *b) {
    Mail *mail1 = (Mail *) a;
    Mail *mail2 = (Mail *) b;

    String index1 = mail1->address.post_index;
    String index2 = mail2->address.post_index;
    if (!equiv_str(index1, index2))
        return compare_str(index1, index2);

    return compare_str(mail1->id, mail2->id);
}

int parse_time(const String *str, Time *time) {
    int day, month, year, hour, minute, second;
    if (sscanf(str->val, "%d:%d:%d %d:%d:%d", &day, &month, &year, &hour, &minute, &second) != 6) {
        return 1;
    }

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0 ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59) {
        return 1;
    }

    time->day = day;
    time->month = month;
    time->year = year;
    time->hour = hour;
    time->minute = minute;
    time->second = second;

    return 0;
}

int compare_time(const void *a, const void *b) {
    String *time1 = (String *) a;
    String *time2 = (String *) b;

    Time t1, t2;
    if (!parse_time(time1, &t1) || !parse_time(time2, &t2)) {
        return 0;
    }

    if (t1.year != t2.year) return t1.year - t2.year;

    if (t1.month != t2.month) return t1.month - t2.month;

    if (t1.day != t2.day) return t1.day - t2.day;

    if (t1.hour != t2.hour) return t1.hour - t2.hour;

    if (t1.minute != t2.minute) return t1.minute - t2.minute;

    return t1.second - t2.second;
}

int create_address(Address *addr, char *post_index, char *building, char *city, char *street, unsigned int apartment,
                   unsigned int house) {
    addr = (Address *) malloc(sizeof(Address));
    if (!addr)
        return throw_err(MEMORY_NOT_ALLOCATED);

    int err = create_str(&addr->post_index, post_index);
    if (err)
        return err;

    err = create_str(&addr->building, building);
    if (err)
        return err;

    err = create_str(&addr->city, city);
    if (err)
        return err;

    err = create_str(&addr->street, street);
    if (err)
        return err;

    addr->apartment = apartment;
    addr->house = house;

    if (addr->post_index.length != 6 || addr->building.length == 0 || addr->city.length == 0 ||
        addr->street.length == 0 || apartment < 1 || house < 1)
        return throw_err(INCORRECT_INPUT_DATA);

    return 0;
}

void print_address(Address addr) {
    printf("Address:\n\tPost Index: %s\n\tCity: %s\n\tStreet: %s\n\tBuilding: %s\n\tHouse: %u\n\tApartment: %u\n",
           addr.post_index.val, addr.city.val, addr.street.val, addr.building.val, addr.house, addr.apartment);
}

void destroy_address(Address *addr) {
    destroy_str(&addr->post_index);
    destroy_str(&addr->street);
    destroy_str(&addr->city);
    destroy_str(&addr->building);

    addr->house = 0;
    addr->apartment = 0;
}

int create_mail(Mail *mail, Address addr, float weight, char *id, char *creation_date, char *delivery_date) {
    mail = (Mail *) malloc(sizeof(Mail));
    if (!mail)
        return throw_err(MEMORY_NOT_ALLOCATED);

    int err = create_str(&mail->id, id);
    if (err)
        return err;

    err = create_str(&mail->creation_date, creation_date);
    if (err)
        return err;

    err = create_str(&mail->delivery_date, delivery_date);
    if (err)
        return err;

    mail->address = addr;
    mail->weight = weight;

    Time t1;

    if (mail->id.length != 14 || parse_time(&mail->creation_date, &t1) || parse_time(&mail->delivery_date, &t1) ||
        weight < 0)
        return throw_err(INCORRECT_INPUT_DATA);

    int k = 0;

    for (int i = 0; i < mail->id.length; ++i) {
        if (!is_num(mail->id.val[i])) {
            k = 1;
            break;
        }
    }

    if (k)
        return throw_err(INCORRECT_INPUT_DATA);

    return 0;
}

void print_mail(Mail mail) {
    printf("Mail:\n\tWeight: %f\n\tID: %s\n\tCreation date: %s\n\tDelivery date: %s\n\t", mail.weight, mail.id.val,
           mail.creation_date.val, mail.delivery_date.val);
    print_address(mail.address);
}

void destroy_mail(Mail *mail) {
    destroy_address(&mail->address);
    destroy_str(&mail->id);
    destroy_str(&mail->delivery_date);
    destroy_str(&mail->creation_date);

    mail->weight = 0;
}

int create_post(Post *post, Address *addr) {
    post = (Post *) malloc(sizeof(Post));
    if (!post)
        return throw_err(MEMORY_NOT_ALLOCATED);

    if (!addr)
        return throw_err(INCORRECT_INPUT_DATA);

    post->address = addr;

    post->mails = (Mail *) malloc(sizeof(Mail) * STANDARD_CAPACITY);
    if (!post->mails)
        return throw_err(MEMORY_NOT_ALLOCATED);

    return 0;
}

int resize_post(Post *post, int size_delta) {
    Mail *new_addr = (Mail *) realloc(post->mails, post->capacity + size_delta);

    if (!new_addr) {
        free(post->mails);
        return throw_err(MEMORY_NOT_ALLOCATED);
    }

    post->mails = new_addr;
    post->capacity += size_delta;

    return 0;
}

int extend_post(Post *post) {
    return resize_post(post, post->capacity);
}

int append_post(Post *post, Mail mail) {
    int err;

    if (post->length + 1 >= post->capacity) {
        err = extend_post(post);
        if (err)
            return err;
    }

    post->mails[post->length++] = mail;

    return 0;
}

int search_mail(Post *post, String mail_id, Mail **found, int *index) {
    for (int i = 0; i < post->length; ++i) {
        if (equiv_str(post->mails->id, mail_id)) {
            *found = &post->mails[i];
            *index = i;
            return 0;
        }
    }

    return 1;
}

int delete_post_mail(Post *post, String mail_id) {
    Mail *mail;
    int index;

    if (search_mail(post, mail_id, &mail, &index)) {
        destroy_mail(mail);
        return 0;
    }

    for (int i = index; i < post->length - 1; ++i) {
        post->mails[i] = post->mails[i + 1];
    }

    post->length--;

    return 1;
}

void destroy_post(Post *post) {
    if (post->mails) {
        for (int i = 0; i < post->length; ++i) {
            destroy_mail(&post->mails[i]);
        }

        free(post->mails);

        post->mails = NULL;
    }

    destroy_address(post->address);

    post->length = 0;
    post->capacity = 0;
}

