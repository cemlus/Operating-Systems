// #include <iostream>

// using namespace std;

// bool isSafe(int processes[], int avail[], int max[][10], int alloc[][10], int need[][10], int n, int m) {
//     int work[10];
//     bool finish[10] = {0}; // Finish array to check if process is finished
//     int safeSeq[10]; // Safe sequence of processes

//     // Initialize work array with available resources
//     for (int i = 0; i < m; i++) {
//         work[i] = avail[i];
//     }

//     int count = 0; // Count of processes in safe sequence

//     while (count < n) {
//         bool found = false;
//         for (int i = 0; i < n; i++) {
//             if (!finish[i]) {
//                 int j;
//                 for (j = 0; j < m; j++) {
//                     if (need[i][j] > work[j])
//                         break;
//                 }

//                 // If all the needed resources can be allocated
//                 if (j == m) {
//                     for (int k = 0; k < m; k++) {
//                         work[k] += alloc[i][k];
//                     }

//                     // Add this process to the safe sequence
    
//                     safeSeq[count++] = i;
//                     finish[i] = true;
//                     found = true;
//                 }
//             }
//         }

//         // If no process was found, the system is not in a safe state
//         if (!found) {
//             cout << "System is not in a safe state!" << endl;
//             return false;
//         }
//     }

//     // If system is in a safe state, print the safe sequence
//     cout << "System is in a safe state.\nSafe Sequence: ";
//     for (int i = 0; i < n; i++) {
//         cout << "P" << safeSeq[i];
//         if (i != n - 1)
//             cout << " -> ";
//     }
//     cout << endl;

//     return true;
// }

// int main() {
//     int n, m;
//     cout << "Enter number of processes: ";
//     cin >> n;
//     cout << "Enter number of resource types: ";
//     cin >> m;

//     int processes[10];        // Array of processes
//     int alloc[10][10];        // Allocation matrix
//     int max[10][10];          // Maximum matrix
//     int avail[10];            // Available resources
//     int need[10][10];         // Need matrix

//     // Initialize processes
//     for (int i = 0; i < n; i++) {
//         processes[i] = i;
//     }

//     cout << "Enter allocation matrix:\n";
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cin >> alloc[i][j];
//         }
//     }

//     cout << "Enter maximum matrix:\n";
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cin >> max[i][j];
//         }
//     }

//     cout << "Enter available resources:\n";
//     for (int i = 0; i < m; i++) {
//         cin >> avail[i];
//     }

//     // Calculate the need matrix: need = max - allocation
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             need[i][j] = max[i][j] - alloc[i][j];
//         }
//     }

//     // Check if the system is in a safe state
//     isSafe(processes, avail, max, alloc, need, n, m);

//     return 0;
// }


#include <iostream>
using namespace std;

const int PROCESSES = 3;  // Number of processes
const int RESOURCES = 4;  // Number of resource types

bool isSafe(int available[], int allocation[][RESOURCES], int max[][RESOURCES], int n, int m) {
    int need[n][m];             // the minimum amount of resources each process needs to execute
    bool finished[n] = {false};  // Mark all processes as not finished/imcomplete from the start
    int work[m];            // stores the current availability of the resources during the time of execution
    int safeSequence[n];  // Store the safe sequence
    int index = 0;

    // Calculate the Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work vector with available resources (so that we dont have to make changes to the original available matrix and at the same time can compare the resources with the work matrix)
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Find the safe sequence
    for (int count = 0; count < n; count++) {                      // this will run as many times, as the processes are there in the system.
        bool found = false;                                        // by default setting the safesequence found to "false"
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {             // finished was set to false for all processes by default at the start itself
                bool canAllocate = true;    // since the resources are available they can be allocated to the necessary process
                for (int j = 0; j < m; j++) {  
                    if (need[i][j] > work[j]) {         // if for i'th process, the need is > availability => as a result the process cannot be executed/ reosurces cannot be allocated
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {                      // in case the resources for the current task is available then we can allocate it to them and then the process can be executed successfully.
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];        // as a result, the allocated resources to the current process are freed and they are now available for the use of other processes.
                    }
                    safeSequence[index++] = i;              // we can now add the processId to the safeSequence
                    finished[i] = true;                     // now that the process execution is complete, the respective processId is now set to "finished" 
                    found = true;                           // safe place for the process is now found 
                }
            }
        }
        if (!found) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    // Display the safe sequence
    cout << "System is in a safe state.\nSafe sequence is: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSequence[i] << (i == n - 1 ? "\n" : " -> ");
    }
    return true;
}

void simulateBankersAlgorithm() {
    int available[RESOURCES] = {3, 3, 2, 2};  // Available resources
    int allocation[PROCESSES][RESOURCES] = {
        {0, 1, 0, 0},  // P0
        {2, 0, 0, 1},  // P1
        {3, 0, 2, 1}   // P2
    };
    int max[PROCESSES][RESOURCES] = {
        {7, 5, 3, 4},  // P0
        {3, 2, 2, 2},  // P1
        {9, 0, 2, 2}   // P2
    };

    cout << "Case 1: Safe State\n";
    isSafe(available, allocation, max, PROCESSES, RESOURCES);

    // Simulate a case where the system is not in a safe state
    int unsafeAllocation[PROCESSES][RESOURCES] = {
        {0, 1, 0, 0},  // P0
        {2, 0, 0, 1},  // P1
        {4, 0, 2, 1}   // P2
    };

    cout << "\nCase 2: Unsafe State\n";
    isSafe(available, unsafeAllocation, max, PROCESSES, RESOURCES);
}

int main() {
    simulateBankersAlgorithm();
    return 0;
}
