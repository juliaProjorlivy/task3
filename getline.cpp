#include "getline.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

ssize_t getline(char **line, size_t *n, FILE *stream)
{
    assert(line != NULL);
    assert(n != NULL);

    if(*line == NULL)
    {
        *line = (char *)calloc(*n, sizeof(char));
    }

    ssize_t i = 0;
    char c = fgetc(stream);
    const int multiplayer = 2;
    while(c != EOF)
    {
        (*line)[i] = c;
        if(c == '\n')
        {
            break;
        }
        i++;

        if(i > *n)
        {
            *n *= multiplayer;
            *line = (char *)realloc(*line, *n);
        }
        c = fgetc(stream);
    }
    if(c == EOF)
    {
        return -1;
    }

    return i;
}
    