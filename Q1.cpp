#include <iostream>
#include <pthread.h>
#include <vector>
#include <climits>

using namespace std;

// Shared data and results
vector<int> data = {10, 20, 5, 8, 99, 56, 12, 45, 78, 3};
int sum = 0, max_value = INT_MIN, min_value = INT_MAX;

// Thread functions
void* calculate_sum(void*) {
    for (int num : :: data) sum += num;
    return nullptr;
}

void* find_maximum(void*) {
    for (int num : :: data) max_value = max(max_value, num);
    return nullptr;
}

void* find_minimum(void*) {
    for (int num : :: data) min_value = min(min_value, num);
    return nullptr;
}

int main() {
    pthread_t threads[3];

    // Create threads
    pthread_create(&threads[0], nullptr, calculate_sum, nullptr);
    pthread_create(&threads[1], nullptr, find_maximum, nullptr);
    pthread_create(&threads[2], nullptr, find_minimum, nullptr);

    // Wait for threads to finish
    for (int i = 0; i < 3; i++) pthread_join(threads[i], nullptr);

    // Print results
    cout << "Sum: " << sum << endl;
    cout << "Max: " << max_value << endl;
    cout << "Min: " << min_value << endl;

    return 0;
}

// #include <iostream>
// #include <pthread.h>
// #include <vector>
// #include <climits>

// using namespace std;

// // Shared data
// vector<int> data = {10, 20, 5, 8, 99, 56, 12, 45, 78, 3};

// // Results for threads
// int sum = 0;
// int max_value = INT_MIN;
// int min_value = INT_MAX;

// // Thread function to calculate the sum
// void* calculate_sum(void* arg) {
//     for (int num : ::data) {
//         sum += num;
//     }
//     pthread_exit(NULL);
// }

// // Thread function to find the maximum value
// void* find_maximum(void* arg) {
//     for (int num : ::data) {
//         if (num > max_value) {
//             max_value = num;
//         }
//     }
//     pthread_exit(NULL);
// }

// // Thread function to find the minimum value
// void* find_minimum(void* arg) {
//     for (int num : ::data) {
//         if (num < min_value) {
//             min_value = num;
//         }
//     }
//     pthread_exit(NULL);
// }

// int main() {
//     pthread_t thread1, thread2, thread3;

//     // Create threads
//     pthread_create(&thread1, NULL, calculate_sum, NULL);
//     pthread_create(&thread2, NULL, find_maximum, NULL);
//     pthread_create(&thread3, NULL, find_minimum, NULL);

//     // Wait for threads to finish
//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);
//     pthread_join(thread3, NULL);

//     // Print results
//     cout << "Sum of elements: " << sum << endl;
//     cout << "Maximum value: " << max_value << endl;
//     cout << "Minimum value: " << min_value << endl;

//     return 0;
// }