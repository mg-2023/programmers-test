#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// order_len은 배열 order의 길이입니다.
int solution(int order[], size_t order_len) {
    int answer = 0;
    int next = 1;

    // 간이 스택
    int *stack = malloc(sizeof(int) * order_len);
    int top = -1;
    for (size_t i=0; i<order_len; i++) {
        if (order[i] >= next) {
            while (order[i] > next) {
                stack[++top] = next;
                next++;
            }

            answer++;
            next++;
            continue;
        }

        else {
            if (stack[top] == order[i]) {
                top--;
                answer++;
                continue;
            }

            else {
                break;
            }
        }
    }
    
    free(stack);
    return answer;
}

int main(void) {
    int n;

    scanf("%d", &n);
    int *order = malloc(sizeof(int) * n);
    for (int i=0; i<n; i++) {
        scanf(" %d", &order[i]);
    }

    printf("Ans: %d\n", solution(order, n));
    free(order);

    return 0;
}
