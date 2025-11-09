#include <iostream>
#include <string>
#include <ctime>
using namespace std;
const int MAX_HISTORY = 10;
const int MAX_ACCOUNTS = 5; 
class Transaction {
private:
    string type;
    double amount;
    string timestamp;
public:
    Transaction() : type("N/A"), amount(0.0) {}
    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);
        timestamp = ctime(&now); 
        if (!timestamp.empty() && timestamp.back() == '\n') {
            timestamp.pop_back(); 
        }
    }
    void printDetails() const {
        cout << "[" << timestamp << "] " << type << ": $";
        cout << amount; 
    }
};
class Account {
private:
    long accountNumber;
    string customerName;
    double balance;
    Transaction history[MAX_HISTORY]; 
    int historyCount;
    void logTransaction(const string& type, double amount) {
        if (historyCount < MAX_HISTORY) {
            history[historyCount++] = Transaction(type, amount);
        } else {
            cout << "(Note: History full, " << type << " not logged)\n";
        }
    }
public:
    Account() : accountNumber(0), customerName(""), balance(0.0), historyCount(0) {}
    Account(long accNum, string name, double initialBalance = 0.0) : accountNumber(accNum), customerName(name), balance(initialBalance), historyCount(0) {
            cout << "Account created for " << customerName << " (Acc: " << accountNumber << ") with initial balance: $" << balance << "\n";
            if (initialBalance > 0) {
                logTransaction("Initial Deposit", initialBalance);
            }
        }
    void deposit(double amount) {
        if (amount > 0) {
            balance = balance + amount;
            logTransaction("Deposit", amount);
            cout << "Deposit successful. New balance: $" << balance << "\n";
        } else {
            cout << "Deposit failed: Amount must be positive.\n";
        }
    }
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal failed: Amount must be positive.\n";
            return false;
        }
        if (balance >= amount) {
            balance -= amount;
            logTransaction("Withdrawal", amount);
            cout << "Withdrawal successful. New balance: $" << balance << "\n";
            return true;
        } else {
            cout << "Withdrawal failed: Insufficient funds. Balance: $" << balance << "\n";
            return false;
        }
    }
    void viewTransactionDetails() const {
        cout << "\n--- History for Account " << accountNumber << " (" << customerName << ") ---\n";
        if (historyCount == 0) {
            cout << "No transactions recorded yet.\n";
            return;
        }
        for (int i = 0; i < historyCount; ++i) {
            cout << "-> ";
            history[i].printDetails();
            cout << "\n";
        }
        cout << "Current Balance: $" << balance << "\n";
    }
    long getAccountNumber() const { return accountNumber; }
    string getCustomerName() const { return customerName; }
    double getBalance() const { return balance; }
    friend void fundTransfer(Account& source, Account& destination, double amount);
};
void fundTransfer(Account& source, Account& destination, double amount) {
    cout << "\n--- Initiating Transfer ---\n";
    if (source.withdraw(amount)) {
        destination.deposit(amount);
        source.logTransaction("Transfer OUT to Acc " + to_string(destination.getAccountNumber()), amount);
        destination.logTransaction("Transfer IN from Acc " + to_string(source.getAccountNumber()), amount);
                cout << "Transfer completed successfully.\n";
    } else {
        cout << "Transfer failed due to insufficient funds in source account!\n";
    }
}
Account* findAccount(Account accounts[], int count, long accNum) {
    for (int i = 0; i < count; ++i) {
        if (accounts[i].getAccountNumber() == accNum) {
            return &accounts[i];
        }
    }
    return nullptr;
}
int main() {
    Account bankAccounts[MAX_ACCOUNTS]; 
    int accountCount = 0;
    long nextAccountNumber = 1001;
    int choice;
    do {
        cout << "\n========================================\n";
        cout << "          C++ Banking System\n";
        cout << "========================================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        long accNum, destAccNum;
        double amount;
        Account *sourceAcc, *destAcc;
        string name;
        double initialBalance;
        cin.ignore(1000, '\n'); 
        switch (choice) {
            case 1:
                if (accountCount >= MAX_ACCOUNTS) {
                    cout << "ERROR: Maximum number of accounts reached (" << MAX_ACCOUNTS << ").\n";
                    break;
                }
                cout << "Enter Customer Name: ";
                getline(cin, name);
                cout << "Enter Initial Deposit Amount: $";
                cin >> initialBalance;
                bankAccounts[accountCount] = Account(nextAccountNumber++, name, initialBalance);
                accountCount++;
                break;
            case 2:
                cout << "Enter Account Number to Deposit to: ";
                cin >> accNum;
                sourceAcc = findAccount(bankAccounts, accountCount, accNum);
                if (!sourceAcc) {
                    cout << "ERROR: Account not found.\n";
                    break;
                }
                cout << "Enter Deposit Amount: $";
                cin >> amount;
                sourceAcc->deposit(amount);
                break;
            case 3:
                cout << "Enter Account Number to Withdraw from: ";
                cin >> accNum;
                sourceAcc = findAccount(bankAccounts, accountCount, accNum);
                if (!sourceAcc) {
                    cout << "ERROR: Account not found!\n";
                    break;
                }
                cout << "Enter Withdrawal Amount: $";
                cin >> amount;
                sourceAcc->withdraw(amount);
                break;
            case 4: {
                cout << "Enter Source Account Number: ";
                cin >> accNum;
                sourceAcc = findAccount(bankAccounts, accountCount, accNum);
                if (!sourceAcc) {
                    cout << "ERROR: Source Account not found!\n";
                    break;
                }
                cout << "Enter Destination Account Number: ";
                cin >> destAccNum;
                destAcc = findAccount(bankAccounts, accountCount, destAccNum);
                if (!destAcc) {
                    cout << "ERROR: Destination Account not found!\n";
                    break;
                }
                if (sourceAcc == destAcc) {
                     cout << "ERROR: Cannot transfer funds to the same account!\n";
                     break;
                }
                cout << "Enter Transfer Amount: $";
                cin >> amount;
                fundTransfer(*sourceAcc, *destAcc, amount);
                break;
            }
            case 5:
                cout << "Enter Account Number to view History: ";
                cin >> accNum;
                sourceAcc = findAccount(bankAccounts, accountCount, accNum);
                if (!sourceAcc) {
                    cout << "ERROR: Account not found.\n";
                    break;
                }
                sourceAcc->viewTransactionDetails();
                break;
            case 6:
                cout << "Thank you! Exiting the C++ Banking System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << "Invalid input type! Please re-enter the data.\n";
        }
    } while (choice != 6);
    return 0;
}