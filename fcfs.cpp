#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id;
    int at, bt;
    int st, ct, tat, wt, rt;
};

// Sort by arrival time; if same arrival time, sort by process ID
bool compare(Process a, Process b) {
    if (a.at == b.at)
        return a.id < b.id;   
    return a.at < b.at;
}

int main() {
    int n;
    cout << "Enter the total process: ";
    cin >> n;

    vector<Process> p(n);
    vector<Process> order;

    float total_tat = 0;
    float total_wt = 0;
    float total_rt = 0;
    float busy_time = 0;

    //take input
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        cout << "Enter arrival time and burst time of Process - " << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;

        busy_time += p[i].bt;
    }

    order = p;

    // Sort processes by arrival time for FCFS execution
    sort(order.begin(), order.end(), compare);

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        int id = order[i].id - 1;

        if (current_time < order[i].at) {
            current_time = order[i].at;
        }

        order[i].st = current_time;

        // CT = ST + BT
        order[i].ct = order[i].st + order[i].bt;

        // TAT = CT - AT
        order[i].tat = order[i].ct - order[i].at;

        // WT = TAT - BT
        order[i].wt = order[i].tat - order[i].bt;

        // RT = ST - AT
        order[i].rt = order[i].st - order[i].at;

        current_time = order[i].ct;

        p[id] = order[i];

        total_tat += p[id].tat;
        total_wt += p[id].wt;
        total_rt += p[id].rt;
    }

    int total_time = current_time;

    // Print serially: P1, P2, P3...
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << endl;
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Response Time = %.2f", total_rt / n);

    printf("\nCPU Utilization = %.2f%%", (busy_time / total_time) * 100);
    printf("\nThroughput = %.2f\n", (float)n / total_time);

    //  Gantt Chart
    cout << "\nGantt Chart:\n";

    for (int i = 0; i < n; i++) {
        if (i == 0 && order[i].st > 0) {
            cout << "| Idle ";
        }
        else if (i > 0 && order[i].st > order[i - 1].ct) {
            cout << "| Idle ";
        }

        cout << "|  P" << order[i].id << "  ";
    }

    cout << "|\n";

    cout << 0;

    for (int i = 0; i < n; i++) {
        if (i == 0 && order[i].st > 0) {
            cout << "\t" << order[i].st;
        }
        else if (i > 0 && order[i].st > order[i - 1].ct) {
            cout << "\t" << order[i].st;
        }

        cout << "\t" << order[i].ct;
    }

    return 0;
}

/*
Enter the total process: 5
Enter arrival time and burst time of Process - 1: 3 1
Enter arrival time and burst time of Process - 2: 4 5
Enter arrival time and burst time of Process - 3: 0 2
Enter arrival time and burst time of Process - 4: 3 7
Enter arrival time and burst time of Process - 5: 5 5

Process AT      BT      CT      TAT     WT      RT
P1      3       1       4       1       0       0
P2      4       5       16      12      7       7
P3      0       2       2       2       0       0
P4      3       7       11      8       1       1
P5      5       5       21      16      11      11

Average Turnaround Time = 7.80
Average Waiting Time = 3.80
Average Response Time = 3.80
CPU Utilization = 95.24%
Throughput = 0.24

Gantt Chart:
|  P3  | Idle |  P1  |  P4  |  P2  |  P5  |
0       2       3       4       11      16      21
*/