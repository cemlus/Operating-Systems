#include <iostream>
using namespace std;

class Process {
    public:
    int pid, arrival, burst, waiting, turnaround, remaining;
    // remaining here is the time remaining for the particular process
};

void sjfPreemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    double totalWait = 0;

    //  (a)
    for (int i = 0; i < n; i++) processes[i].remaining = processes[i].burst;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";

    //  (b)
    while (completed < n) {
        int shortest = -1;

        // finding the shortest process(just like in SJF non-preemptive)
        for (int i = 0; i < n; i++) {
            // checks for any process that has arrived which could possibly have a shorter burst time than the currently running one
            if (processes[i].arrival <= time && processes[i].remaining > 0) {
                // if the condition reaches here it means that there does exist a process that has arrived and is ready with it's remaining time > 0
                if (shortest == -1 || processes[i].remaining < processes[shortest].remaining) {
                    // if the process being iterated has lesser time remaining than the one currently selected, it's swapped out by assigning the variable "shortest" to its index.
                    shortest = i;
                }
            }
        }
    //  (c) If no process is ready, increments time
        if (shortest == -1) {
            time++;
            continue;
        }
        processes[shortest].remaining--;

    //  (d)
        if (processes[shortest].remaining == 0) {
            completed++;
            // remember that the turnaroud time is the total time of process in the cpu
            processes[shortest].turnaround = time + 1 - processes[shortest].arrival;
            processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
            totalWait += processes[shortest].waiting;

            cout << "P" << processes[shortest].pid << "\t" << processes[shortest].arrival << "\t"
                 << processes[shortest].burst << "\t" << processes[shortest].waiting << "\t"
                 << processes[shortest].turnaround << endl;
        }
        // the time keeps on moving forward
        time++;
    }

    cout << "\nAverage Waiting Time: " << totalWait / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time and burst time for process P" << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    sjfPreemptive(processes, n);
    return 0;
}
