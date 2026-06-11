#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    bool started;
};

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time, burst time, and priority for P%d: ", i + 1);
        scanf("%d %d %d",
              &p[i].arrival_time,
              &p[i].burst_time,
              &p[i].priority);

        p[i].remaining_time = p[i].burst_time;
        p[i].started = false;
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
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {

                if (p[i].priority < highest_priority) {
                    highest_priority = p[i].priority;
                    selected = i;
                }

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
            if (p[selected].started == false) {
                p[selected].response_time =
                    current_time - p[selected].arrival_time;

                p[selected].started = true;
            }

            p[selected].remaining_time--;
            current_time++;

            if (p[selected].remaining_time == 0) {
                p[selected].completion_time = current_time;

                p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;

                p[selected].waiting_time =  p[selected].turnaround_time - p[selected].burst_time;

                total_waiting_time += p[selected].waiting_time;
                total_turnaround_time += p[selected].turnaround_time;
                total_response_time += p[selected].response_time;

                completed++;
            }
        }
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].priority,
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