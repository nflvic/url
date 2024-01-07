#include "parser.h"

int min(int a, int b) {
    if(a < b) {
        return a;
    } else {
        return b;
    }
}

// http://localhost:3000;
url *url_parse(char *str) {

    if(!verify_url(str)) {
        return NULL;
    }

    url *parsed = malloc(sizeof(url));

    char *u = trim(str);

    parsed->raw_url = u;

    char *s = strstr(u, "://");

    if(s) {
        char  *ret = string_sub(0, s - u, u);
        parsed->scheme = ret;
    } else {
        parsed->scheme = NULL;
    }

    s = s + 3;
    char *sl = NULL;

    {
        sl = strstr(s + 3, "/");

        char *ret = NULL;

        if(sl) {
           ret = string_sub(0, sl - s, s);
        } else {
            ret = string_sub(0, strlen(s), s);
            parsed->path = string_create_copy("/");
        }

        {
            strAL *addr_splits = split_lim(ret, ":", 2);
            parsed->port = 
            addr_splits->size == 2 ? string_array_list_get(addr_splits, 1) : NULL;

            parsed->address = string_array_list_get(addr_splits, 0);

            free(addr_splits);
            free(addr_splits->list);
        }


        free(ret);

    }

    char *p_start = NULL;
    {
        if(sl) {
             p_start = strchr(sl, '?');
        }
    }
            //parsed->path = p_start ? string_sub(0, p_start - sl, sl) : string_create_copy(sl);
    char *frag_start = NULL;

    if(sl) {
        frag_start = strchr(sl, '#');

        if(frag_start) {
            parsed->flags = split(frag_start + 1, "#");
        }
    }

    char *param_string = NULL;
    int p2f, p2p;
    if(p_start && frag_start) {
        p2f = frag_start - sl;
        p2p = p_start - sl;
        
        int path_size = min(p2f, p2p);

        parsed->path = string_sub(0,path_size, sl);
        
        assert(path_size == p2p);

        param_string = string_sub(0, frag_start - p_start - 1, p_start + 1);

    } else if(p_start && !frag_start) {
        parsed->path = string_sub(0, p_start - sl, sl);
        param_string = string_create_copy(p_start + 1);
    } else if(!p_start && frag_start) {
        parsed->path = string_sub(0, frag_start - sl, sl);
    } else {
         parsed->path = string_create_copy(sl);
    }

    if(p_start) {
        strAL *p_splits = split(param_string, "&");

        parsed->params = map_create();

        for(size_t i = 0; i < p_splits->size; i++) {
            strAL *pspt = split_lim(string_array_list_get(p_splits, i), "=",2);

            assert(pspt->size == 2);

            map_put(parsed->params, string_array_list_get(pspt, 0), string_array_list_get(pspt, 1));

            string_arraylist_destroy(&pspt);
        }

        string_arraylist_destroy(&p_splits);
    }

    //free(u);
    return parsed;

}

bool verify_url(char *url)
{
    regex_t regex;
    int reti;
    bool out = false;

    reti = regcomp(&regex, "((http|https)://)[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)", REG_EXTENDED);
    if (reti) {
        return false;
    }

    reti = regexec(&regex, url, 0, NULL, 0);
    if (!reti) {
        out = true;
    }

    regfree(&regex);

    return out;

}
