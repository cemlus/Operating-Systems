#include <iostream>
#include <thread>
#include <semaphore> // For std::binary_semaphore

using namespace std;

// Shared resources
int counter = 0;

// Semaphore for mutual exclusion
std::binary_semaphore semaphore(1); // Initialized to 1 (allow one thread to enter)

void thread_function(const string& thread_name) {
    for (int i = 0; i < 5; ++i) {
        // Acquire the semaphore before entering the critical section
        semaphore.acquire();

        // Critical section
        cout << thread_name << " entering critical section." << endl;
        ++counter; // Update the shared variable
        cout << thread_name << " updated counter to " << counter << endl;

        // Simulate some work
        this_thread::sleep_for(chrono::milliseconds(100));

        cout << thread_name << " leaving critical section." << endl;

        // Release the semaphore after exiting the critical section
        semaphore.release();

        // Simulate non-critical work
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

int main() {
    // Create two threads
    thread thread1(thread_function, "Thread 1");
    thread thread2(thread_function, "Thread 2");

    // Wait for threads to finish
    thread1.join();
    thread2.join();

    cout << "Final value of counter: " << counter << endl;

    return 0;
}