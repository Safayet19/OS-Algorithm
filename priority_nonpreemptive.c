#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    bool completed;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = false;

        printf("Enter arrival time, burst time, and priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
    }

    int current_time = 0;
    int completed = 0;

    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float total_response_time = 0;

    while (completed < n) {
        int selected = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].completed == false) {

                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    selected = i;
                }

                // Tie-breaking: same priority, earlier arrival time
                else if (p[i].priority == highest_priority) {
                    if (p[i].arrival_time < p[selected].arrival_time) {
                        selected = i;
                    }
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {
            p[selected].start_time = current_time;

            p[selected].completion_time = current_time + p[selected].burst_time;

            p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;

            p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;

            p[selected].response_time = p[selected].start_time - p[selected].arrival_time;

            current_time = p[selected].completion_time;

            p[selected].completed = true;
            completed++;

            total_waiting_time += p[selected].waiting_time;
            total_turnaround_time += p[selected].turnaround_time;
            total_response_time += p[selected].response_time;
        }
    }

    printf("\nPID\tAT\tBT\tPR\tST\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].priority,
               p[i].start_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time,
               p[i].response_time);
    }

    printf("\nAverage Waiting Time = %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f", total_turnaround_time / n);
    printf("\nAverage Response Time = %.2f\n", total_response_time / n);

    return 0;
}
