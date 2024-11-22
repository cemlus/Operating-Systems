// #include <unistd.h>  // For `fork`, `pipe`, `read`, `write`, `close`
// #include <cstring>   // For `strlen` and `strcpy`
#include <iostream>  // For input/output in C++

// using namespace std;
// int main() {
//     int pipe_fd[2];
//     pid_t pid;
//     char write_msg[] = "Hello from parent!";
//     char read_msg[50];

//     // Step 1: Create a pipe
//     if (pipe(pipe_fd) == -1) {
//         cerr << "Pipe creation failed\n";
//         return 1;
//     }

//     pid = fork();
//     if (pid == 0) { // Child process
//         close(pipe_fd[1]); // Close write end
//         read(pipe_fd[0], read_msg, sizeof(read_msg)); // Read from pipe
//         cout << "Child received: " << read_msg << "\n";
//         close(pipe_fd[0]); // Close read end
//     } else if (pid > 0) { // Parent process
//         close(pipe_fd[0]); // Close read end
//         write(pipe_fd[1], write_msg, strlen(write_msg) + 1); // Write to pipe
//         close(pipe_fd[1]); // Close write end
//     } else {
//         cerr << "Fork failed\n";
//         return 1;
//     }

//     return 0;
// }

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    int fd[2], n;
    char buffer[100];
    pid_t p;
    pipe(fd); // creates a unidirectional pipe with two end fd[0] and fd[1]
    p = fork();
    if (p > 0) // parent
    {
        printf("Parent Passing value to child\n");
        write(fd[1], "hello\n", 6); // fd[1] is the write end of the pipe
        sleep(3);
    }
    else // child
    {
        printf("Child printing received value\n");
        n = read(fd[0], buffer, 100); // fd[0] is the read end of the pipe
        printf("%s", buffer);
        write(1, buffer, n);
    }
}

pid_t pid;
int pipe_fd[2], n;
char writingBuffer[50] = "hola amigo";
char readingBuffer[50];

if(pipe(pipe_fd) == -1){
    cerr << "there was an error" ;
    return -1;
}

pid = fork();


if(pid > 0) {   // parent 
    write(pipe_fd[1], writingBuffer, sizeof(writingBuffer))
    sleep(3);
} else if (pid == 0){       // child
    n = read(pipe_fd[0], readingBuffer, sizeof(readingBuffer));
    cout << n ;
    sleep(3);
} else {
    cerr << "there was an error while forking";
    return -1;
}



