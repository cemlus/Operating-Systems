#include <iostream>
using namespace std;

struct MemoryBlock {
    int size;        // Size of the memory block
    bool allocated;  // Allocation status
    int allocatedTo; // Process ID allocated to this block (-1 if unallocated)
};

void displayMemoryState(MemoryBlock memory[], int n) {
    cout << "\nCurrent Memory State:\n";
    cout << "Block\tSize\tAllocated\tProcess\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << memory[i].size << "\t";
        cout << (memory[i].allocated ? "Yes" : "No") << "\t\t";
        if (memory[i].allocated) {
            cout << memory[i].allocatedTo;
        } else {
            cout << "-";
        }
        cout << endl;
    }
    cout << endl;
}

void firstFit(MemoryBlock memory[], int n, int processId, int processSize) {
    for (int i = 0; i < n; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            memory[i].allocated = true;
            memory[i].allocatedTo = processId;
            cout << "Process " << processId << " allocated to block " << i + 1 << endl;
            return;
        }
    }
    cout << "Process " << processId << " could not be allocated.\n";
}

void bestFit(MemoryBlock memory[], int n, int processId, int processSize) {
    int bestIdx = -1;
    for (int i = 0; i < n; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (bestIdx == -1 || memory[i].size < memory[bestIdx].size) {
                bestIdx = i;
            }
        }
    }
    if (bestIdx != -1) {
        memory[bestIdx].allocated = true;
        memory[bestIdx].allocatedTo = processId;
        cout << "Process " << processId << " allocated to block " << bestIdx + 1 << endl;
    } else {
        cout << "Process " << processId << " could not be allocated.\n";
    }
}

void worstFit(MemoryBlock memory[], int n, int processId, int processSize) {
    int worstIdx = -1;
    for (int i = 0; i < n; i++) {
        if (!memory[i].allocated && memory[i].size >= processSize) {
            if (worstIdx == -1 || memory[i].size > memory[worstIdx].size) {
                worstIdx = i;
            }
        }
    }
    if (worstIdx != -1) {
        memory[worstIdx].allocated = true;
        memory[worstIdx].allocatedTo = processId;
        cout << "Process " << processId << " allocated to block " << worstIdx + 1 << endl;
    } else {
        cout << "Process " << processId << " could not be allocated.\n";
    }
}

int main() {
    const int MAX_BLOCKS = 10;
    MemoryBlock memory[MAX_BLOCKS];
    int numBlocks, choice, processId = 1;

    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;

    for (int i = 0; i < numBlocks; i++) {
        cout << "Enter size of block " << i + 1 << ": ";
        cin >> memory[i].size;
        memory[i].allocated = false;
        memory[i].allocatedTo = -1;
    }

    while (true) {
        cout << "\nMemory Allocation Menu:\n";
        cout << "1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Display Memory State\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 5) break;

        if (choice >= 1 && choice <= 3) {
            int processSize;
            cout << "Enter size of the process to allocate: ";
            cin >> processSize;

            switch (choice) {
                case 1:
                    firstFit(memory, numBlocks, processId, processSize);
                    break;
                case 2:
                    bestFit(memory, numBlocks, processId, processSize);
                    break;
                case 3:
                    worstFit(memory, numBlocks, processId, processSize);
                    break;
            }
            processId++;                    // this goes to show that each process is put in the switch case individually which makes sense as memory is allocated on an individual basis for the processes
        } else if (choice == 4) {
            displayMemoryState(memory, numBlocks);
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    cout << "Exiting the program.\n";
    return 0;
}
