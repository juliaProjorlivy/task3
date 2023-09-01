#include <stdio.h>

void printRectangle(const char *data[], size_t rows)
{
    for(size_t row = 0; row < rows; row++)
    {
        printf("%s", *(data + row));
        printf("\n");
    }
}

void printTriangle(const char *data, int n)
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

int main()
{
    const char *data2[] = {"hay", "please", "free", "super", "run"};
    printRectangle(data2, 5);
    const char data[] = {   1,
                            2, 3, 
                            4, 5, 6,
                            7, 8, 9, 10};
    printTriangle(data, 4);
}