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
            *(data + i) = strdup(line);
            i++;
        }
    }
    return i;
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

void first_example()
{
    FILE *file = fopen("data.txt", "r");
    char **data = (char **)calloc(sizeof(char *), MAX_ROWS);
    size_t len = get_data(data, file);
    print_rectangle_file((const char **)data, len);
    fclose(file);
    free(data);
    puts("first example completed");
    puts("--------😎--------");
}

void second_example()
{
    FILE *file = fopen("data.txt", "r");
    char **data_dest = (char **)calloc(sizeof(char *), MAX_ROWS);

    struct stat buf;
    stat("data.txt", &buf);

    size_t data_size = buf.st_size;

    char *data_src = (char *)calloc(data_size, sizeof(char));

    fread(data_src, sizeof(char), data_size, file);

    int str_count = split_string(data_dest, data_src, data_size);
    print_rectangle_file((const char **)data_dest, str_count);

    fclose(file);
    free(data_src);
    free(data_dest);
    puts("second example completed");
    puts("--------😎--------");
}

void third_example()
{
    const char *data2[] = {"hay", "please", "free", "super", "run"};
    print_rectangle(data2, 5);
    puts("third example completed");
    puts("--------😎--------");
}

void forth_example()
{
    FILE *file = fopen("data.txt", "r");
    struct stat buf;
    stat("data.txt", &buf);

    size_t data_size = buf.st_size;

    char *data = (char *)calloc(data_size, sizeof(char));

    fread(data, sizeof(char), data_size, file);
    puts(data);

    fclose(file);
    free(data);
    puts("forth example completed");
    puts("--------😎--------");
}

void fifth_example()
{
     const char data3[] = {   1,
                            2, 3, 
                            4, 5, 6,
                            7, 8, 9, 10};
    print_triangle(data3, 4);
    puts("fifth example completed");
    puts("--------😎--------");
}

int main()
{
    // firste example print data from file using fread
    first_example();

    //second example print data from file useing struct stat
    second_example();

    // third example print data using arr
    third_example();

    // forth print data using only struct stat
    forth_example();
    
    // fifth print triangle array data
    fifth_example();
    
}