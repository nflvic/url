### example

```c


char *str = "http://hello.world:3000/foo?bar=foo#bar";

url *u = url_parse(url);

#include <assert.h>
#include <string.h>

if(u == NULL) {
    /* invalid url */
    exit(1);
}

assert(strcmp("http", u->scheme) == 0);

assert(strcmp("hello.world", u->address) == 0);

assert(strcmp("foo", u->path) == 0);

assert(strcmp("foo", map_get(u->params, "bar")) == 0);

assert(strcmp("bar", string_array_list_get(u->flags, 0)) == 0);

```