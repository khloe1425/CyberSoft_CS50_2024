#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Số lượng ứng cử viên tối đa
#define MAX_CANDIDATES 9

// Khai báo cấu trúc để lưu trữ thông tin của ứng cử viên
struct Candidate {
    char name[50];
    int votes;
};

// Khai báo biến toàn cục để lưu trữ danh sách các ứng cử viên
struct Candidate candidates[MAX_CANDIDATES];
int numCandidates = 0;
int maxVotes = 0;

// Hàm để bầu cử cho ứng cử viên theo tên
int vote(const char *name) {
    for (int i = 0; i < numCandidates; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            candidates[i].votes++;
            if (candidates[i].votes > maxVotes) {
                maxVotes = candidates[i].votes;
            }
            return 1; // Lá phiếu thành công
        }
    }
    return 0; // Lá phiếu không hợp lệ
}

// Hàm để in ra ứng cử viên chiến thắng
void print_winner() {
    printf("Kết quả bầu cử:\n");
    for (int i = 0; i < numCandidates; i++) {
        if (candidates[i].votes == maxVotes) {
            printf("%s\n", candidates[i].name);
        }
    }
}

int main() {
    int numVoters;

    // Nhập số lượng ứng cử viên
    printf("Nhập số lượng ứng cử viên: ");
    scanf("%d", &numCandidates);

    // Kiểm tra số lượng ứng cử viên có vượt quá giới hạn không
    if (numCandidates > MAX_CANDIDATES) {
        printf("Số lượng ứng cử viên tối đa là %d\n", MAX_CANDIDATES);
        return 1;
    }

    // Nhập danh sách các ứng cử viên
    printf("Nhập danh sách ứng cử viên:\n");
    for (int i = 0; i < numCandidates; i++) {
        printf("Tên ứng cử viên %d: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0;
    }

    // Nhập số lượng cử tri
    printf("Nhập số lượng cử tri: ");
    scanf("%d", &numVoters);

    // Bắt đầu bỏ phiếu
    printf("Bắt đầu bỏ phiếu:\n");
    for (int i = 0; i < numVoters; i++) {
        char voterChoice[50];
        printf("Lá phiếu của cử tri %d: ", i + 1);
        scanf("%s", voterChoice);

        int result = vote(voterChoice);
        if (result) {
            printf("Lá phiếu của cử tri %d đã được tính.\n", i + 1);
        } else {
            printf("Lá phiếu của cử tri %d không hợp lệ.\n", i + 1);
        }
    }

    // In kết quả bầu cử
    print_winner();

    return 0;
}
