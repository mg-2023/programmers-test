#include <stdio.h>
#include <string.h>

char next_vowel(char cur_vowel) {
    switch (cur_vowel) {
        case 'A':
            return 'E';
        case 'E':
            return 'I';
        case 'I':
            return 'O';
        case 'O':
            return 'U';
        case 'U':
            return 0;
        default:
            return 0;
    }
}

void next(char *entry, int *nth) {
    for (int i=4; i>=0; i--) {
        if (entry[i] == '\0') {
            if (entry[i-1] == '\0') {
                continue;
            }
            
            else {
                entry[i] = 'A';
                goto done;
            }
        }
        
        else if (entry[i] == 'A' || entry[i] == 'E'
              || entry[i] == 'I' || entry[i] == 'O') {
            entry[i] = next_vowel(entry[i]);
            goto done;
        }
        
        else if (entry[i] == 'U') {
            entry[i] = next_vowel(entry[i]);
            continue;
        }
    }

done:
    if (nth != NULL)
        (*nth)++;
}

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int solution(const char* word) {
    int answer = 1;
    char entry[6] = {'A', 0, 0, 0, 0, 0};
    while (strcmp(word, entry)) {
        next(entry, &answer);
    }
    
    return answer;
}

int main(void) {
    char order[6];
    scanf("%s", order);

    printf("%d\n", solution(order));
    return 0;
}
