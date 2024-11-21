#include <iostream>
using namespace std;

class Process {
    public:
    int pid, arrival, burst, priority, waiting, turnaround;
    int remaining;
};

void priorityPreemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    int executionSequence[1000], seqLength = 0;

// (a)
    for (int i = 0; i < n; i++) processes[i].remaining = processes[i].burst;

// (b)
    while (completed < n) {
        int highestPriority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                if (highestPriority == -1 || processes[i].priority < processes[highestPriority].priority) {
                    highestPriority = i;
                }
            }
        }

        // (c)
        if (highestPriority == -1) {
            time++;
            continue;
        }

        // (d)
        executionSequence[seqLength++] = processes[highestPriority].pid;
        processes[highestPriority].remaining--;

        if (processes[highestPriority].remaining == 0) {
            completed++;
            processes[highestPriority].turnaround = time + 1 - processes[highestPriority].arrival;
            processes[highestPriority].waiting = processes[highestPriority].turnaround - processes[highestPriority].burst;
        }
        time++;
    }

    cout << "\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    double totalWait = 0;
    for (int i = 0; i < n; i++) {
        totalWait += processes[i].waiting;
        cout << "P" << processes[i].pid << "\t" << processes[i].arrival << "\t"
             << processes[i].burst << "\t" << processes[i].priority << "\t\t"
             << processes[i].waiting << "\t" << processes[i].turnaround << endl;
    }

    cout << "\nAverage Waiting Time: " << totalWait / n << endl;
    cout << "\nExecution Sequence: ";
    for (int i = 0; i < seqLength; i++) {
        cout << "P" << executionSequence[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time, burst time, and priority for process P" << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
    }

    priorityPreemptive(processes, n);
    return 0;
}
