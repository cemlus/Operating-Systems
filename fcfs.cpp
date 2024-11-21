#include <iostream>
using namespace std;

class Process {
    public:
    int pid, arrival, burst, waiting, turnaround;
};

void fcfs(Process processes[], int n) {
    int time = 0;
    double totalWait = 0;

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    // if any process doesn't start at arrival time of t = 0 then:
    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrival) {
            time = processes[i].arrival; 
            // time is set to last process's arrival time
        }

        processes[i].waiting = time - processes[i].arrival;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
        totalWait += processes[i].waiting;

        cout << "P" << processes[i].pid << "\t" << processes[i].arrival << "\t"
             << processes[i].burst << "\t" << processes[i].waiting << "\t"
             << processes[i].turnaround << endl;

        time += processes[i].burst;
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

    fcfs(processes, n);
    return 0;
}


/*
// 
#include <iostream>
using namespace std;

class Process{
    public: 
    int pid, arrival, waiting, turnaround, burst;
    // bool isCompleted = false;
};

void fcfs(Process processes[], int n){
    int time = 0;
    double totalWait = 0;
    
    cout << "Processes\tAt\tBt" << endl;
    for(int i = 0 ; i < n ; i++){
        // checking if a process has arrived at the time of running this iteration, and if it hasn't then we increment time upto the point of its arrival.
        
        if(time < processes[i].arrival){
            time = processes[i].arrival;
        }
        // further we add the burst time of the ongoing process into the time variable; later we also add the waiting time for both variable into the totalWait variable to find the average waiting time for each process.
        
        
        cout << "P " << processes[i].pid << " : \t" << "\t" << processes[i].arrival << "\t" << processes[i].burst << endl;
        
        processes[i].waiting = time - processes[i].arrival;
        processes[i].turnaround = processes[i].waiting + processes[i].burst;
        totalWait += processes[i].waiting;
    
        time += processes[i].burst;             // incrementing the time as soon as the ongoing process has been terminated.
    }
    cout << "average waiting time: " << totalWait / n << endl;
}

int main() {
    int n;
    cout << "enter number of processes needed: " ;
    cin >> n;
    
    Process processes[n];
    for(int i = 0 ; i < n ; i++){
        processes[i].pid = i + 1;
        cout << "enter the arrival and burst time for process" << processes[i].pid << ": ";
        cin >> processes[i].arrival >> processes[i].burst ;
    }

    fcfs(processes, n);
    return 0;
}

*/
