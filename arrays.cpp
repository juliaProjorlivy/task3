#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_ROWS 20

// выводит строки из массива
void print_rectangle(const char **data, size_t rows, int is_file)
{
    assert(*data != NULL);
    assert(isfinite(rows));
    assert(isfinite(is_file));

    if(is_file)
    {
        for(size_t row = 0; row < rows; row++)
        {
            printf("%s", *(data + row));
        }
        printf("\n");
    }
    else
    {
        for(size_t row = 0; row < rows; row++)
        {   
            printf("%s\n", *(data + row));
        }
    }
}

// выводит треугольный массив
void print_triangle(const char *data, int n)
{
    assert(data != NULL);
    assert(isfinite(n));
    for(int rows = 1; rows < n + 1; rows++)
    {
        for(int cols = 0; cols < rows; cols++)
        {
            printf("%d ", *(data + rows * (rows - 1) / 2) + cols);
        }
        printf("\n");
    }
}

// заполняет массив указателей data указателями на строки, считанные из напрямую из файла stream
// возвращает количество строк
size_t get_data(char **data, FILE *stream)
{
    assert(data != NULL);
    assert(stream != NULL);

    const int max_strlen = 20;
    size_t i = 0;
    char line[max_strlen] = {};
    while(!feof(stream))
    {
        if(fgets(line, max_strlen, stream) != NULL)
        {
            if((*(data + i) = strdup(line)) == NULL)
            {
                printf("memory allocation error");
                break;
            }
            i++;
        }
    }
    return i;
}

// разбивает буфер src на отдельные строки и передает указатель на них в массив указателей
// возвращает количество строк
size_t split_string(char **dest, char *src, size_t size)
{
    assert(dest != NULL);
    assert(src != NULL);
    assert(isfinite(size));

    size_t i = 0;
    size_t len = 0; //длина строки
    size_t str_count = 0;
    while(i < size)
    {
        if(src[i] == '\n')
        {
            if((*(dest + str_count) = strndup(src + i - len, len)) == NULL)
            {
                printf("memory allocation error");
            }
            str_count++;
            len = 0;
        }
        len++; //длина строки без учета \n
        i++;

    }
    return str_count;
}

void clean_data(char **data, size_t data_size)
{
    assert(data != NULL);
    assert(isfinite(data_size));

    for(int i = 0; i < data_size; i++)
    {
        free(*(data + i));
    }
}

void first_example()
{
    FILE *file = fopen("data.txt", "r");
    char **data = (char **)calloc(sizeof(char *), MAX_ROWS);

    if(data != NULL)
    {
        size_t data_size = get_data(data, file); // data_size - количиство строк
        print_rectangle((const char **)data, data_size, 1);

        clean_data(data, data_size);
        fclose(file);
        free(data);
    }

    else
    {
        puts("memory allocation failure");
    }
    puts("first example completed");
    puts("--------😎--------");
}

void second_example()
{
    FILE *file = fopen("data.txt", "r");
    char **data_dest = (char **)calloc(sizeof(char *), MAX_ROWS);

    if(data_dest != NULL)
    {
        struct stat buf;
        stat("data.txt", &buf);

        size_t data_size = buf.st_size;

        char *data_src = (char *)calloc(data_size, sizeof(char));

        if(data_src != NULL && data_size == fread(data_src, sizeof(char), data_size, file))
        {
            size_t str_count = split_string(data_dest, data_src, data_size);
            print_rectangle((const char **)data_dest, str_count, 1);
            clean_data(data_dest, str_count);
            free(data_src);
        }
        else
        {
            puts("memory allocation failure");
        }

        free(data_dest);
    }
    else
    {
        puts("memory allocation failure\n");
    }

    fclose(file);
    puts("second example completed");
    puts("--------😎--------");
}

void third_example()
{
    const char *data2[] = {"hay", "please", "free", "super", "run"};
    print_rectangle(data2, 5, 0);
    puts("third example completed");
    puts("--------😎--------");
}

void forth_example()
{
    FILE *file = fopen("data.txt", "r");
    struct stat buf;
    stat("data.txt", &buf);

    size_t data_size = buf.st_size;

    char *data = (char *)calloc(data_size + 1, sizeof(char));

    if(data != NULL)
    {
        if(data_size == fread(data, sizeof(char), data_size, file))
        {
            data[data_size] = '\0';
            puts(data);
        }
        else
        {
            puts("memory allocation failure");
        }

        free(data);
    }
    
    fclose(file);
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
    // firste example print data from file using get_data function
    first_example();

    //second example print data from file useing struct stat and fread
    second_example();

    // third example print data from array
    third_example();

    // forth print data using struct stat and puts
    forth_example();
    
    // fifth print triangle array data
    fifth_example();
    
}