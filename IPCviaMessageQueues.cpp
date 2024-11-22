#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>

using namespace std;

#define MAX_SIZE 50

struct myMessage {
    long int msg_type;       // Message type
    char msg[MAX_SIZE];      // Message content
};

int main() {
    int running = 1;          // Flag for loops
    int messageId;            // Message queue ID
    myMessage messageText;    // Struct to send/receive messages
    char buffer[MAX_SIZE];    // Buffer for user input

    // Create message queue
    messageId = msgget((key_t)12345, 0666 | IPC_CREAT);
    if (messageId == -1) {
`        cerr << "Message queue creation failed." << endl;
        return 1;
    }

    // Sending messages
    while (running) {
        cout << "Enter a message (type 'end' to stop): ";
        cin.getline(buffer, MAX_SIZE);

        // Prepare the message
        strncpy(messageText.msg, buffer, MAX_SIZE - 1); // Copy input to message
        messageText.msg[MAX_SIZE - 1] = '\0';          // Ensure null termination
        messageText.msg_type = 1;                      // Set message type to 1

        // Send the message
        int isSent = msgsnd(messageId, (void*)&messageText, sizeof(messageText.msg), 0);
        if (isSent == -1) {
            cerr << "Message not sent." << endl;
            return 1;
        }

        // Check for termination keyword
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0; // Exit the loop
        }
    }

    running = 1; // Reset running for receiving messages
    long int msg_to_rec = 1; // Type of message to receive

    // Receiving messages
    while (running) {
        // Receive a message
        int isRecieved = msgrcv(messageId, (void*)&messageText, sizeof(messageText.msg), msg_to_rec, 0);
        if (isRecieved == -1) {
            cerr << "Failed to receive message." << endl;
            return 1;
        }

        // Print the received message
        cout << "Data received: " << messageText.msg << endl;

        // Check for termination keyword
        if (strncmp(messageText.msg, "end", 3) == 0) {
            running = 0; // Exit the loop
        }
    }

    // Clean up: Remove the message queue
    if (msgctl(messageId, IPC_RMID, nullptr) == -1) {
        cerr << "Failed to delete message queue." << endl;
        return 1;
    }

    return 0;
}
