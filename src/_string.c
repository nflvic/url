#include "_string.h"

string_t *string_create() {

    string_t *st = malloc(sizeof(string_t));

    if(st) {

        char *tmp = malloc(1);

        if(tmp) {
            st->len = 0;
            st->size = 1;
            st->ptr = tmp;

            return st;
        }

        /*memory err*/
        return NULL;
    }

    return NULL;
    /*memory err*/
}

string_t *string_create_size(size_t size){

    if(size == 0)
        return string_create();

    string_t *st = malloc(sizeof(string_t));

    if(st) {

        char *tmp = malloc(size);

        if(tmp) {
            st->len = 0;
            st->size = size;
            st->ptr = tmp;

            return st;
        }

        /*memory err*/
        return NULL;
    }

    return NULL;
    /*memory err*/
}

void string_append(string_t *s, char c) {
    if(s->size-1 == s->len) {
        s->ptr = realloc(s->ptr, s->size + 2);

        if(s->ptr) {
            s->size++;
        }
        /*else malloc() err*/
    }

    s->ptr[s->len] = c;
    s->len++;
    s->ptr[s->len] = '\0';
}


void string_concat(string_t *s, char *str) {

    size_t f = strlen(str);
    size_t rem_space = s->size - s->len;

    if(rem_space > f) {

        size_t indx = 0;

        for(size_t i = s->len; indx < f; i++) {
            s->ptr[i] = str[indx];
            indx++;
        }

    } else {

        size_t space_needed = (f - rem_space) + 1;

        s->ptr = realloc(s->ptr, s->size + space_needed);
        s->size += space_needed;

        size_t indx = 0;

        for(size_t i = s->len; indx < f; i++) {
            s->ptr[i] = str[indx];
            indx++;
        }
    }

    s->len += f;
    s->ptr[s->len] = '\0';

}

void string_expand(string_t *s, size_t capacity) {
    size_t new_size = s->size + capacity;

    s->ptr = realloc(s->ptr, new_size);

    if(s->ptr) {
        s->size = new_size;
        return;
    }

    /**err*/

}

void string_destroy(string_t *s) {
    if(s) {

        if(s->ptr) {

            free(s->ptr);
        }

        free(s);
    }
}