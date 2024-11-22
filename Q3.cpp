#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

using namespace std;

class BankAccount {
public:
    int accountNumber;
    double balance;
    mutex mtx;  // Mutex to ensure thread-safe access to balance

    BankAccount(int accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    void deposit(double amount) {
        lock_guard<mutex> lock(mtx);  // Automatically locks and unlocks the mutex
        balance += amount;
    }

    void withdraw(double amount) {
        lock_guard<mutex> lock(mtx);  // Automatically locks and unlocks the mutex
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient funds for withdrawal of $" << amount << endl;
        }
    }

    double getBalance() {
        lock_guard<mutex> lock(mtx);
        return balance;
    }
};

// Function to simulate deposit operations (thread1)
void depositFunds(BankAccount& account, double amount, int numDeposits) {
    for (int i = 0; i < numDeposits; ++i) {
        account.deposit(amount);
        cout << "Deposited $" << amount << ", New balance: $" << account.getBalance() << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate some delay
    }
}

// Function to simulate withdrawal operations (thread2)
void withdrawFunds(BankAccount& account, double amount, int numWithdrawals) {
    for (int i = 0; i < numWithdrawals; ++i) {
        account.withdraw(amount);
        cout << "Withdrew $" << amount << ", New balance: $" << account.getBalance() << endl;
        this_thread::sleep_for(chrono::milliseconds(100));  // Simulate some delay
    }
}

int main() {
    // Create a bank account with an initial balance of $1000
    BankAccount account(123456, 1000.0);

    // Create two threads: one for depositing and one for withdrawing
    thread depositThread(depositFunds, ref(account), 200.0, 5);  // Deposit $200, 5 times
    thread withdrawThread(withdrawFunds, ref(account), 150.0, 5); // Withdraw $150, 5 times

    // Wait for both threads to finish
    depositThread.join();
    withdrawThread.join();

    // Final balance after all transactions
    cout << "Final balance: $" << account.getBalance() << endl;

    return 0;
}