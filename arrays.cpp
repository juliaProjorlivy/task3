#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define MAX_STRLEN 20
#define MAX_ROWS 20

void print_rectangle(const char **data, size_t rows)
{
    for(size_t row = 0; row < rows; row++)
    {
        printf("%s\n", *(data + row));
    }
}

void print_rectangle_file(const char **data, size_t rows)
{
    for(size_t row = 0; row < rows; row++)
    {
        printf("%s", *(data + row));
    }
}

void print_triangle(const char *data, int n)
{
    for(int rows = 1; rows < n + 1; rows++)
    {
        for(int cols = 0; cols < rows; cols++)
        {
            printf("%d ", *(data + (int)(rows * (rows - 1) / 2)) + cols);
        }
        printf("\n");
    }
}

size_t get_data(char **data, FILE *stream)
{
    int i = 0;
    char line[MAX_STRLEN] = {};
    while(!feof(stream))
    {
        if(fgets(line, MAX_STRLEN, stream) != NULL)
        {
            printf("str = %s\n", line);
            *(data + i) = strdup(line);
            i++;
        }
    }
    return i;
}

void get_data2(char *data)
{
    puts(data);
}

int split_string(char **dest, char *src, size_t size)
{
    int i = 0;
    int len = 0;
    int str_count = 0;
    while(i < (int)size)
    {
        if(src[i] == '\n')
        {
            *(dest + str_count) = strndup(src + i - len, len);
            str_count++;
            len = 0;
        }
        len++; //длина строки без учета \n
        i++;

    }
    return str_count;
}


int main()
{
    // firste example print data from file using fread
    FILE *file = fopen("data.txt", "r");
    char **data = (char **)calloc(sizeof(char *), MAX_ROWS);
    size_t len = get_data(data, file);

    // first example print data from file useing struct stat
    FILE *file = fopen("data.txt", "r");
    
    char **data = (char **)calloc(sizeof(char *), MAX_ROWS);

    // size_t len = getdata(data, file);

    struct stat buf;
    stat("data.txt", &buf);
    char *data4 = (char *)calloc(buf.st_size, sizeof(char));
    fread(data4, sizeof(char), buf.st_size, file);
    // getdata2(data4);
    // free(data4);
    int str_count = split_string(data, data4, buf.st_size);
    print_rectangle((const char **)data, str_count);

    fclose(file);
    // printRectangle((const char **)data, len);
    free(data4);
    free(data);

    const char *data2[] = {"hay", "please", "free", "super", "run"};
    print_rectangle(data2, 5);
    // const char data3[] = {   1,
    //                         2, 3, 
    //                         4, 5, 6,
    //                         7, 8, 9, 10};
    // printTriangle(data3, 4);
    
}