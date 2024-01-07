#pragma once
#include "array_list.h"
#include "_string.h"

strAL *split(char *str, char *delim);

char *string_create_copy(char *str);

strAL *split_lim(char *str, char *delim, int lim);

size_t find_first_not_space(char *str);

size_t find_last_not_space(char *str);

char *trim(char *buffer);

char *string_sub(size_t start, size_t stop, char *buffer);