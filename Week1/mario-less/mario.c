#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    do
    {
        printf("Nhap chieu cao (khong qua 8): ");
        scanf("%d", &h);
    }
    while (h <= 0 || h > 8);
    for (int i = 1; i <= h; i++)
    {
        for (int j = 0; j < h - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}
