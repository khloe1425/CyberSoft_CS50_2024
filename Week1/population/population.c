#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int initial_population, new_births, new_deaths, years = 0;
    // TODO: Prompt for start size
    do {
        printf("Nhap quan the ban dau (lon hon 9): ");
        scanf("%d", &initial_population);
    } while (initial_population <= 9);

    // TODO: Prompt for end size
    do {
        printf("Nhap quan the ket thuc (lon hon hoac bang quan the ban dau): ");
        scanf("%d", &new_births);
    } while (new_births < initial_population);
    // TODO: Calculate number of years until we reach threshold
    while (initial_population < new_births) {
        initial_population += initial_population/3 - initial_population/4;
        years++;
    }
    // TODO: Print number of years
    printf("So nam can thiet: %d\n", years);

    return 0;
}
