#include <cs50.h>
#include <stdio.h>
#include <string.h>

void print_bulb(const char *binary) {
    for (int i = 0; i < 8; i++) {
        if (binary[i] == '0') {
            printf("\U0001F4A1 ");
        } else {
            printf("\U0001F4A1\U0001F31F ");
        }
    }
    printf("\n");
}

int main() {
    char input[256];

    
    printf("Nhập tin nhắn: ");
    scanf("%255s", input);

    int length = strlen(input);

    // Duyệt qua từng ký tự của chuỗi đầu vào và chuyển đổi thành số nhị phân 8 bit
    for (int i = 0; i < length; i++) {
        char binary[9]; // 8 ký tự + null-terminator
        int ascii_value = (int)input[i];

        // Chuyển đổi thành số nhị phân
        for (int j = 7; j >= 0; j--) {
            binary[7 - j] = ((ascii_value >> j) & 1) ? '1' : '0';
        }
        binary[8] = '\0'; // Kết thúc chuỗi số nhị phân

        // In biểu tượng cảm xúc cho ký tự hiện tại
        print_bulb(binary);
    }

    return 0;
}
