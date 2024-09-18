#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    if(argc!=2)
    {
        fprintf(stderr, "Sử dụng: ./recover infile\n");
        return 1;
    }

    // mở file đầu vào
    FILE* inpt = fopen(argv[1], "r");
    if(inpt == NULL)
    {
        fprintf(stderr, "Không thể mở %s.\n", argv[1]);
        return 2;
    }

    // đặt con trỏ file đầu ra bằng NULL
    FILE* outpt = NULL;

    // tạo một mảng 512 phần tử để lưu 512 byte từ thẻ nhớ
    BYTE buffer[512];

    // đếm số lượng file jpeg tìm thấy
    int jpeg = 0;

    // chuỗi để giữ tên file
    char filename[8] = {0};

    // đọc cho đến khi hết file
    while(fread(buffer, sizeof(BYTE)*512, 1, inpt) == 1)
    {
        // kiểm tra nếu tìm thấy jpeg
        if(buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && (buffer[3] & 0xF0) == 0xE0)
        {
            // đóng outpt nếu jpeg đã được tìm thấy trước đó và ghi vào ___.jpg
            if(outpt != NULL)
            {
                fclose(outpt);
            }
            sprintf(filename, "%03d.jpg", jpeg++);

            // mở một outpt mới để ghi jpeg mới tìm thấy
            outpt = fopen(filename, "w");
        }

        // tiếp tục ghi vào file jpeg nếu không tìm thấy jpeg mới
        if(outpt != NULL)
        {
            fwrite(buffer, sizeof(BYTE)*512, 1, outpt);
        }
    }

    // đóng outpt cuối cùng đã mở
    if (outpt != NULL)
    {
        fclose(outpt);
    }

    // đóng file inpt (hình ảnh pháp y)
    fclose(inpt);

    return 0;
}
