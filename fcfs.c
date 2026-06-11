#include<stdio.h>

struct process {
    int pid;

    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;

    int start_time;
    int response_time;
};

int main()
{

    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i=0; i<n; i++){
        p[i].pid = i+1;
        printf("Enter arrival time and burst time for pid: %d: ", i+1);

        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    // sort by arrival time by bubble sort
    for(int i=0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].arrival_time > p[j+1].arrival_time){
                struct process temp;
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int current_time = 0;
    float total_waiting_time = 0;
    float total_turnaround_time = 0;
    float total_response_time = 0;

    for(int i=0; i<n; i++){
        if(current_time < p[i].arrival_time){
            current_time = p[i].arrival_time;
        }
        p[i].start_time = current_time;

        p[i].completion_time = current_time + p[i].burst_time; // the core logic
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        current_time = p[i].completion_time;

        total_waiting_time+=p[i].waiting_time;
        total_turnaround_time+=p[i].turnaround_time;
        total_response_time+=p[i].response_time;

    }
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