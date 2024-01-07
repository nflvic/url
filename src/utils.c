#include "utils.h"

strAL *split(char *str, char *delim) {
    strAL *splits = string_array_list_create();
    string_t *x = string_create();

    size_t delim_len = strlen(delim);

    size_t seq = 0;
    
    for(int i = 0; str[i] != '\0'; i++) {

        if(str[i] == delim[seq]) {
            seq++;
        } else {
            seq = 0;
        }

        string_append(x, str[i]);

        if(seq == delim_len) {
            x->ptr[x->size - (seq + 1)] = '\0';
            string_array_list_append_allocated(splits, string_create_copy(x->ptr));

            free(x->ptr);

            x->ptr = malloc(1);
            x->ptr[0] = '\0';
            x->len = 0;
            x->size = 1;
        }

    }

    string_array_list_append_allocated(splits, x->ptr);

    free(x);

    return splits;
}


/**
 * @param lim numbers of pieces to projuce.
*/
strAL *split_lim(char *str, char *delim, int lim) {
    strAL *splits = string_array_list_create();
    string_t *x = string_create();

    size_t delim_len = strlen(delim);

    size_t seq = 0;
    
    int num_f = 0;
    for(int i = 0; str[i] != '\0'; i++) {

        if(str[i] == delim[seq]) {
            seq++;
        } else {
            seq = 0;
        }

        string_append(x, str[i]);

        if(seq == delim_len && num_f < lim - 1) {
            x->ptr[x->size - (seq + 1)] = '\0';
            string_array_list_append_allocated(splits, string_create_copy(x->ptr));

            free(x->ptr);

            x->ptr = malloc(1);
            x->ptr[0] = '\0';
            x->len = 0;
            x->size = 1;

            num_f++;
        }

    }

    string_array_list_append_allocated(splits, x->ptr);

    free(x);

    return splits;
}

char *string_create_copy(char *str)
{
    int len = strlen(str) + 1;
    char *res = malloc(sizeof(char) * len);
    strcpy(res, str);
    return res;
}

char *trim(char *buffer)
{
    int start = find_first_not_space(buffer);
    int stop = find_last_not_space(buffer) + 1;

    return string_sub(start,stop,buffer);
}

size_t find_last_not_space(char *str)
{
    size_t len = strlen(str);
    size_t i;

    for(i = len-1; i ; i--)
    {
        if(str[i] != ' ')
        {
            if(str[i] != '\t')
                break;
        }
    }

    return i;
}

size_t find_first_not_space(char *str)
{
    size_t len = strlen(str);
    size_t i;

    for(i = 0; i < len ; i++)
    {
        if(str[i] != ' ')
        {
            if(str[i] != '\t')
                break;
        }
    }

    return i;
}

char *string_sub(size_t start, size_t stop, char *buffer)
{
    string_t *temp = string_create_size(stop - start + 1);

    for (unsigned int i = 0; i < stop; i++)
    {
        if (i >= start)
        {
            string_append(temp, buffer[i]);
        }

    }

    char *chars = temp->ptr;
    free(temp);
    return chars;
}