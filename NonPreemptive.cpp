#include <iostream>
using namespace std;

// priority is highest for 1 and least for 3 

class Process {
    public:
    int pid, arrival, burst, priority, waiting, turnaround;
    bool completed = false;
};

void priorityNonPreemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    int executionSequence[n], seqLength = 0;


    while (completed < n) {
        int highestPriority = -1;

        for (int i = 0; i < n; i++) {
            // if("process is not completed" && "process is ready")
            if (!processes[i].completed && processes[i].arrival <= time) {
                if (highestPriority == -1 || processes[i].priority < processes[highestPriority].priority) {
                    highestPriority = i;
                }
            }
        }

        if (highestPriority == -1) {
            time++;
            continue;
        }

        executionSequence[seqLength++] = processes[highestPriority].pid;
        processes[highestPriority].waiting = time - processes[highestPriority].arrival;
        processes[highestPriority].turnaround = processes[highestPriority].waiting + processes[highestPriority].burst;
        time += processes[highestPriority].burst;
        processes[highestPriority].completed = true;
        completed++;
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

    priorityNonPreemptive(processes, n);
    return 0;
}
