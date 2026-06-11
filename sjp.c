#include<stdio.h>
#include<climits>

struct process{
    int pid;

    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int response_time;

    bool completed;
    int start_time;

};

int main()
{
    int n; // number of processes
    printf("Enter number of Processes: ");
    scanf("%d", &n);

    struct process p[n];

    int i=0;
    for(i=0; i<n; i++){
        p[i].pid = i+1;
        p[i].completed = false;
        printf("Enter arrival time of pid %d: ", i+1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    }

    int current_time = 0;
    int complete = 0; // number of completed processes

    float total_turnaround_time=0;
    float total_waiting_time = 0;
    float total_response_time =0;

    while(complete < n){
        int selected = -1;
        int min_burst = INT_MAX;
        i=0;
        for(i=0; i<n; i++){
            if(p[i].arrival_time <= current_time && p[i].completed==false){
                if(p[i].burst_time < min_burst){
                    min_burst = p[i].burst_time;
                    selected = i;
                }
            }
        }

        if(selected == -1){
            current_time++;
        }
        else {
            p[selected].start_time = current_time;

            p[selected].completion_time = current_time+p[selected].burst_time;
            p[selected].turnaround_time = p[selected].completion_time - p[selected].arrival_time;
            p[selected].waiting_time = p[selected].turnaround_time - p[selected].burst_time;
            p[selected].response_time = p[selected].start_time - p[selected].arrival_time;

            current_time = p[selected].completion_time;
            p[selected].completed = true;
            complete++;

            total_turnaround_time += p[selected].turnaround_time;
            total_response_time += p[selected].response_time;
            total_waiting_time += p[selected].waiting_time;
        }
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