#pragma once 

#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct string_t string_t;

struct string_t {
    char *ptr;

    // position of null ptr
    size_t len;

    // allocated size
    size_t size;
};

string_t *string_create();

string_t *string_create_size(size_t size);

void string_append(string_t *s, char c);

void string_concat(string_t *s, char *str);

void string_destroy(string_t *s);

void string_expand(string_t *s, size_t capacity);