#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Word count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Chuyển từ thành chữ thường để so sánh không phân biệt chữ hoa chữ thường
    char lower_word[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';

    // Tính toán vị trí trong bảng băm
    unsigned int index = hash(lower_word);

    // Duyệt qua danh sách liên kết tại bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, lower_word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Tính toán hash bằng cách sử dụng tổng của mã ASCII các ký tự, rồi lấy modulo N
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = (hash * 31 + tolower(word[i])) % N;
    }
    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Mở tệp từ điển
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Cấp phát bộ nhớ cho từ tạm thời
    char word[LENGTH + 1];

    // Khởi tạo bảng băm
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Đọc từng từ trong tệp
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Cấp phát bộ nhớ cho một node mới
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dict);
            unload();
            return false;
        }

        // Tính toán vị trí trong bảng băm
        unsigned int index = hash(word);

        // Ghi từ vào node
        strcpy(n->word, word);

        // Thêm node vào bảng băm
        n->next = table[index];
        table[index] = n;

        // Tăng số lượng từ
        word_count++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        table[i] = NULL;
    }
    return true;
}

