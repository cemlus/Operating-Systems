#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <semaphore.h>
#include <cstring>

using namespace std;

#define SHARED_MEM_NAME "/shared_mem_cpp"
#define BUFFER_SIZE 1024

struct SharedMemory {
    char buffer[BUFFER_SIZE];
    sem_t empty;
    sem_t full;
};

int main() {
    pid_t pid;
    int shm_fd;
    SharedMemory *shm;

    // Step 1: Create or open a shared memory segment
    shm_fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        cerr << "Failed to create shared memory\n";
        return 1;
    }

    // Step 2: Set the size of the shared memory segment
    ftruncate(shm_fd, sizeof(SharedMemory));

    // Step 3: Map the shared memory segment into the process's address space
    shm = static_cast<SharedMemory *>(mmap(nullptr, sizeof(SharedMemory),
                                            PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0));
    if (shm == MAP_FAILED) {
        cerr << "Mapping failed\n";
        return 1;
    }

    // Step 4: Initialize semaphores in shared memory
    sem_init(&shm->empty, 1, 1); // "empty" semaphore starts at 1 (buffer is empty)
    sem_init(&shm->full, 1, 0);  // "full" semaphore starts at 0 (buffer has no data)

    pid = fork();
    if (pid == 0) { // Child process: Consumer
        while (true) {
            sem_wait(&shm->full); // Wait until there is data in the buffer
            cout << "Consumer received: " << shm->buffer << "\n";
            sem_post(&shm->empty); // Signal that the buffer is empty
            sleep(1);
        }
    } else if (pid > 0) { // Parent process: Producer
        while (true) {
            sem_wait(&shm->empty); // Wait until the buffer is empty
            cout << "Producer: Enter data: ";
            cin.getline(shm->buffer, BUFFER_SIZE);
            sem_post(&shm->full); // Signal that the buffer is full
            sleep(1);
        }
    } else {
        cerr << "Fork failed\n";
        return 1;
    }

    return 0;
}
