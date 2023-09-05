#include "getline.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t my_getline(char **line, size_t *n, FILE *stream)
{
    assert(line != NULL);
    assert(n != NULL);

    if(*line == NULL)
    {
        *line = (char *)calloc(*n, sizeof(char));
    }

    ssize_t i = 0;
    char c = (char)fgetc(stream);
    const int multiplier = 2;
    while(c != '\n')
    {
        (*line)[i] = c;
        if(c == EOF)
        {
            return -1;
        }
        i++;

        if((size_t)i > *n)
        {
            *n *= multiplier;
            *line = (char *)realloc(*line, *n);
        }
        c = (char)fgetc(stream);
    }

    return i;
}
    