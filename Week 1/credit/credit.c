#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long long CardNumber;
    do {
        CardNumber = get_long("Nhap so the tin dung: ");
    } while (CardNumber <= 0);

    int sum = 0;
    long long tempNumber = CardNumber;
    int count = 0;

    while (tempNumber > 0) {
        int digit = tempNumber % 10;
        if (count % 2 == 1) {
            int doubled = digit * 2;
            while (doubled > 0) {
                sum += doubled % 10;
                doubled /= 10;
            }
        } else {
            sum += digit;
        }
        tempNumber /= 10;
        count++;
    }
    if (sum % 10 == 0) {
        if ((CardNumber >= 340000000000000 && CardNumber < 350000000000000) ||
            (CardNumber >= 370000000000000 && CardNumber < 380000000000000)) {
            printf("AMEX\n");
        } else if (CardNumber >= 5100000000000000 && CardNumber < 5600000000000000) {
            printf("MASTERCARD\n");
        } else if ((CardNumber >= 4000000000000 && CardNumber < 5000000000000) ||
                   (CardNumber >= 4000000000000000 && CardNumber < 5000000000000000)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
    return 0;
}
