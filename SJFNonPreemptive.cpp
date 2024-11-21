#include <iostream>
using namespace std;

// shortest job first

class Process {
    public:
    int pid, arrival, burst, waiting, turnaround;
    bool completed = false;
};

void sjfNonPreemptive(Process processes[], int n) {
    int time = 0, completed = 0;
    double totalWait = 0;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    while (completed < n) {
        int shortest = -1;

        // find the shortest job first
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= time) {      // either process is not completed or process has arrived while some other is being executed(because only then can the arrivalTime < time)
                if (shortest == -1 || processes[i].burst < processes[shortest].burst) {
            // if the shortest job has been decided yet || shortest job is being calculated
                    shortest = i;   // index of shortest job has been recorded 
                }
            }
        }
        
        if (shortest == -1) {
            time++;
            continue;
        }

        processes[shortest].waiting = time - processes[shortest].arrival;
        processes[shortest].turnaround = processes[shortest].waiting + processes[shortest].burst;
        totalWait += processes[shortest].waiting;

        time += processes[shortest].burst;      // Once selected, the process runs to completion
        processes[shortest].completed = true;

        completed++;        // after the job is completed we incrememnt the completed variable so as to increase the count of it.

        cout << "P" << processes[shortest].pid << "\t" << processes[shortest].arrival << "\t"
             << processes[shortest].burst << "\t" << processes[shortest].waiting << "\t"
             << processes[shortest].turnaround << endl;
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

    sjfNonPreemptive(processes, n);
    return 0;
}

// check while completed < n
    // for int i = 0 ; i < n ; i++
    // if !processes[i].completed && processes[i].arrival <= time
    // if shortest == -1 || processes[i].burst < processes[shortest].burst
    // shortest = i

// if(shortest == -1) time ++

/*
    process[shortest].waiting + =  time - process[shortest].arrival 
    process[shortest].turnaroundTime = process[shortest].waiting + process[shortest].burst
    totalWait += process[shortest].waiting
    time += process[shortest].burst
    process[shortest].completed = true
    completed++
*/