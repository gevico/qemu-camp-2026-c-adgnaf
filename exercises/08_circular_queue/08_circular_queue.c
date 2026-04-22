#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    q.head = 0;
    q.tail = total_people - 1;
    q.count = total_people;

    for (int i = 0; i < total_people; i++) {
        q.data[i].id = i + 1;
    }

    while (q.count > 1) {
        for (int i = 1; i < report_interval; i++) {
            q.tail++;
            if (q.tail == MAX_PEOPLE) {
                q.tail = 0;
            }
            q.data[q.tail] = q.data[q.head];

            q.head++;
            if (q.head == MAX_PEOPLE) {
                q.head = 0;
            }
        }

        printf("淘汰: %d\n", q.data[q.head].id);
        q.head++;
        if (q.head == MAX_PEOPLE) {
            q.head = 0;
        }
        q.count--;
    }

    
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}