#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool is_parked;
    int temp_in_time;
    int total_time;
} Parkings;

int calc_fee(int *fees, int time) {
    int add_time = time - fees[0];
    int base_fee = fees[1];
    if (add_time <= 0) {
        return base_fee;
    }

    else {
        int add_time_unit = (add_time / fees[2]);
        int add_fee_unit = fees[3];
        if (add_time % fees[2] > 0) {
            add_time_unit++;
        }

        return base_fee + add_time_unit * add_fee_unit;
    }
}

int parse_time(char *time) {
    time[2] = '\0';
    int hour = atoi(time);
    int min = atoi(time + 3);
    time[2] = ':';

    return hour * 60 + min;
}

void parse_log(char *log, Parkings *pks) {
    char *part;
    char *time, *num, *inout;
    int segment = 1;

    for (part = strtok(log, " "); part != NULL; part = strtok(NULL, " ")) {
        switch (segment) {
            case 1:
            time = part;
            break;

            case 2:
            num = part;
            break;

            case 3:
            inout = part;
            break;
        }

        segment++;
    }

    int car_num = atoi(num);
    if (!strcmp(inout, "IN")) {
        pks[car_num].is_parked = true;
        pks[car_num].temp_in_time = parse_time(time);
    }

    else if (!strcmp(inout, "OUT")) {
        int out_time = parse_time(time);
        pks[car_num].is_parked = false;
        pks[car_num].total_time += (out_time - pks[car_num].temp_in_time);
    }
}

// fees_len은 배열 fees의 길이입니다.
// records_len은 배열 records의 길이입니다.
// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
int* solution(int fees[], size_t fees_len, const char* records[], size_t records_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    Parkings *pks = malloc(10000 * sizeof(Parkings));
    char tmp_record[50];

    for (int i=0; i<10000; i++) {
        pks[i].is_parked = false;
        pks[i].temp_in_time = -1;
        pks[i].total_time = 0;
    }

    for (size_t i=0; i<records_len; i++) {
        strcpy(tmp_record, records[i]);
        parse_log(tmp_record, pks);
    }

    int cars = 0;
    for (int i=0; i<10000; i++) {
        if (pks[i].temp_in_time != -1) {
            cars++;
            if (pks[i].is_parked) {
                pks[i].total_time += (1439 - pks[i].temp_in_time);
            }
        }
    }

    int* answer = malloc(cars * sizeof(int));
    int j = 0;
    for (int i=0; i<10000; i++) {
        if (pks[i].temp_in_time != -1) {
            answer[j++] = calc_fee(fees, pks[i].total_time);
        }
    }

    free(pks);
    return answer;
}

int main(void) {
    int fees[4] = {180, 5000, 10, 600};
    const char *records[9] = { "05:34 5961 IN", "06:00 0000 IN", "06:34 0000 OUT", "07:59 5961 OUT",
                         "07:59 0148 IN", "18:59 0000 IN", "19:09 0148 OUT", "22:59 5961 IN",
                         "23:00 5961 OUT" };
    
    int *answer = solution(fees, 4, records, 9);
    for (int i=0; i<3; i++) {
        printf("%d ", answer[i]);
    }

    puts("");
    free(answer);

    return 0;
}
