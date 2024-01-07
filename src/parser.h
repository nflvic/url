#pragma once 

#include <math.h>
#include "array_list.h"
#include "map.h"
#include "utils.h"
#include "_string.h"
#include <stdbool.h>
#include <regex.h>

typedef struct url url;

struct url {
    char *raw_url;
    char *scheme;
    char *path;
    char *port;
    char *address;
    map_t *params;
    strAL *flags;
};


url *url_parse(char *url);

bool verify_url(char *url);