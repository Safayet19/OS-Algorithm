#include <stdio.h>
#include <stdbool.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;

    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

    bool started;
    bool completed;
    bool in_queue;
};

int main() {
    int n, time_quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        p[i].remaining_time = p[i].burst_time;
        p[i].started = false;
        p[i].completed = false;
        p[i].in_queue = false;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int queue[1000];
    int front = 0, rear = 0;

    int current_time = 0;
    int completed = 0;

    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float total_response_time = 0;

    while (completed < n) {

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time &&
                p[i].completed == false &&
                p[i].in_queue == false &&
                p[i].remaining_time > 0) {

                queue[rear++] = i;
                p[i].in_queue = true;
            }
        }

        // If no process is ready, CPU is idle
        if (front == rear) {
            current_time++;
            continue;
        }

        // Dequeue process
        int selected = queue[front++];
        p[selected].in_queue = false;

        // First response time
        if (p[selected].started == false) {
            p[selected].response_time = current_time - p[selected].arrival_time;

            p[selected].started = true;
        }

        // Execute process
        if (p[selected].remaining_time > time_quantum) {
            current_time += time_quantum;
            p[selected].remaining_time -= time_quantum;
        } else {
            current_time += p[selected].remaining_time;
            p[selected].remaining_time = 0;

            p[selected].completion_time = current_time;
            p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;

            p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;

            p[selected].completed = true;
            completed++;

            total_waiting_time += p[selected].waiting_time;
            total_turnaround_time += p[selected].turnaround_time;
            total_response_time += p[selected].response_time;
        }

        // Add processes that arrived while current process was running
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time &&
                p[i].completed == false &&
                p[i].in_queue == false &&
                p[i].remaining_time > 0 &&
                i != selected) {

                queue[rear++] = i;
                p[i].in_queue = true;
            }
        }

        // If selected process is not finished, put it back
        if (p[selected].remaining_time > 0) {
            queue[rear++] = selected;
            p[selected].in_queue = true;
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

    printf("\nAverage Waiting Time = %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time = %.2f", total_turnaround_time / n);
    printf("\nAverage Response Time = %.2f\n", total_response_time / n);

    return 0;
}
