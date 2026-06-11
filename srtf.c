#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
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

    struct process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for P%d: ", i+1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        p[i].remaining_time = p[i].burst_time;
        p[i].started = false;
    }

    int current_time = 0;
    int completed = 0;

    float total_wt = 0, total_tat = 0, total_rt = 0;

    while (completed < n) {
        int selected = -1;
        int min_remaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                if (p[i].remaining_time < min_remaining) {
                    min_remaining = p[i].remaining_time;
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            current_time++;
        } else {

            // First response
            if (!p[selected].started) {
                p[selected].response_time = current_time - p[selected].arrival_time;
                p[selected].started = true;
            }

            // Execute for 1 unit
            p[selected].remaining_time--;
            current_time++;

            // If finished
            if (p[selected].remaining_time == 0) {
                p[selected].completion_time = current_time;
                p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;
                p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;

                total_wt += p[selected].waiting_time;
                total_tat += p[selected].turnaround_time;
                total_rt += p[selected].response_time;

                completed++;
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time,
               p[i].response_time);
    }

    printf("\nAverage WT = %.2f", total_wt / n);
    printf("\nAverage TAT = %.2f", total_tat / n);
    printf("\nAverage RT = %.2f\n", total_rt / n);

    return 0;
}