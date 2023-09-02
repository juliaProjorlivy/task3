#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_ROWS 20

// выводит строки из массива
void print_rectangle(const char **data, size_t rows)
{
    for(size_t row = 0; row < rows; row++)
    {
        printf("%s\n", *(data + row));
    }
}

// выводит строки, записанные в файле и переданные в массив указателей data
void print_rectangle_file(const char **data, size_t rows)
{
    for(size_t row = 0; row < rows; row++)
    {
        printf("%s", *(data + row));
    }
    printf("\n");
}

// выводит треугольный массив
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

// заполняет массив указателей data указателями на строки, считанные из напрямую из файла stream
// возвращает количество строк
size_t get_data(char **data, FILE *stream)
{
    const int max_strlen = 20;
    int i = 0;
    char line[max_strlen] = {};
    while(!feof(stream))
    {
        if(fgets(line, max_strlen, stream) != NULL)
        {
            *(data + i) = strdup(line);
            i++;
        }
    }
    return i;
}

// разбивает буфер src на отдельные строки и передает указатель на них в массив указателей
// возвращает количество строк
int split_string(char **dest, char *src, size_t size)
{
    int i = 0;
    int len = 0; //длина строки
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

void clean_data(char **data, size_t data_size)
{
    for(int i = 0; i < data_size; i++)
    {
        free(*(data + i));
    }
}

void first_example()
{
    FILE *file = fopen("data.txt", "r");
    char **data = (char **)calloc(sizeof(char *), MAX_ROWS);
    size_t data_size = get_data(data, file); // data_size - количиство строк
    print_rectangle_file((const char **)data, data_size);

    clean_data(data, data_size);
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

    clean_data(data_dest, (size_t)str_count);
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
    // firste example print data from file using get_data function
    first_example();

    //second example print data from file useing struct stat and fread
    second_example();

    // third example print data using arr
    third_example();

    // forth print data using struct stat and puts
    forth_example();
    
    // fifth print triangle array data
    fifth_example();
    
}