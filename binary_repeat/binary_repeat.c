#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 0을 모두 없애고 0의 개수를 반환
int remove_zeros(char *s) {
    int zeros = 0;
    size_t s_len = strlen(s);
    char *s_copy = calloc(s_len+1, sizeof(char));

    int j = 0;
    for (size_t i=0; i<s_len; i++) {
        if (s[i] == '1') {
            s_copy[j++] = '1';
        }

        else if (s[i] == '0') {
            zeros++;
        }
    }
    strcpy(s, s_copy);
    free(s_copy);

    return zeros;
}

int get_bits(size_t n) {
    int bits = 0;
    while (n != 0) {
        n >>= 1;
        bits++;
    }

    return bits;
}

// 인자로 주어진 문자열의 길이를 이진수로 변환해서 s에 복사
void convert_len_to_bin(char *s) {
    size_t s_len = strlen(s);
    char *s_copy = calloc(s_len+1, sizeof(char));
    int bits = get_bits(s_len);
    for (int i=bits-1; i>=0; i--) {
        s_copy[i] = (s_len & 1) + '0';
        s_len >>= 1;
    }

    strcpy(s, s_copy);
    free(s_copy);
}

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int* solution(const char* s) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = malloc(sizeof(int) * 2);
    answer[0] = 0;
    answer[1] = 0;

    char *s_copy = calloc(strlen(s) + 1, sizeof(char));
    memcpy(s_copy, s, strlen(s) + 1);
    while (strcmp(s_copy, "1")) {
        answer[1] += remove_zeros(s_copy);
        convert_len_to_bin(s_copy);
        answer[0] += 1;
    }

    return answer;
}

int main(void) {
    char *s = calloc(150001, sizeof(char));
    scanf("%s", s);

    int *res = solution(s);
    printf("result: [%d, %d]\n", res[0], res[1]);

    free(s);
    free(res);
    return 0;
}