#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_numeric(string s);

int main(int argc, string argv[])
{
    // Kiểm tra xem người dùng có cung cấp đúng số lượng đối số dòng lệnh không
    if (argc != 2 || !is_numeric(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Chuyển đối số dòng lệnh thành số nguyên
    int key = atoi(argv[1]);

    // Kiểm tra xem khóa có phải là số dương không
    if (key < 0)
    {
        printf("Key must be a positive integer.\n");
        return 1;
    }

    // Yêu cầu người dùng nhập văn bản gốc
    string plaintext = get_string("plaintext: ");

    // Khởi tạo một chuỗi cho văn bản mã hóa
    printf("ciphertext: ");

    // Mã hóa từng ký tự của văn bản gốc
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        // Kiểm tra nếu là chữ cái viết hoa
        if (isupper(c))
        {
            // Xoay ký tự trong phạm vi A-Z
            printf("%c", (c - 'A' + key) % 26 + 'A');
        }
        // Kiểm tra nếu là chữ cái viết thường
        else if (islower(c))
        {
            // Xoay ký tự trong phạm vi a-z
            printf("%c", (c - 'a' + key) % 26 + 'a');
        }
        // Nếu không phải chữ cái, giữ nguyên ký tự đó
        else
        {
            printf("%c", c);
        }
    }

    // Xuống dòng sau khi in ra văn bản mã hóa
    printf("\n");

    return 0;
}

// Hàm kiểm tra xem một chuỗi có phải là số hay không
bool is_numeric(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}
