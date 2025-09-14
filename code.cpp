#include <bits/stdc++.h>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNum;
    double balance;

public:
    BankAccount(string n, int ac, double bal)
        : name(std::move(n)), accountNum(ac), balance(bal >= 0 ? bal : 0) {
    }

    const string &getName() const { return name; }
    int getAccountNum() const { return accountNum; }
    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "\t\tDeposit amount must be positive!" << endl;
            return false;
        }
        balance += amount;
        cout << "\t\tDeposited " << amount << " | New Balance: " << balance << endl;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "\t\tWithdrawal amount must be positive!" << endl;
            return false;
        }
        if (balance >= amount) {
            balance -= amount;
            cout << "\t\tWithdrawn " << amount << " | New Balance: " << balance << endl;
            return true;
        } else {
            cout << "\t\tInsufficient Balance. Current Balance: " << balance << endl;
            return false;
        }
    }

    void showDetails() const {
        cout << "Name: " << name
                << " | Account Number: " << accountNum
                << " | Balance: " << balance << endl;
    }
};

class BankManagement {
private:
    map<int, BankAccount> accounts;

public:
    bool addAccount(const string &name, int accountNum, double balance) {
        if (accountNum <= 0) {
            cout << "\t\tInvalid account number!" << endl;
            return false;
        }
        if (accounts.find(accountNum) != accounts.end()) {
            cout << "\t\tAccount number already exists!" << endl;
            return false;
        }
        accounts.emplace(accountNum, BankAccount(name, accountNum, balance));
        cout << "\t\tAccount Created Successfully...." << endl;
        return true;
    }

    void showAllAccounts() const {
        if (accounts.empty()) {
            cout << "\t\tNo accounts found." << endl;
            return;
        }
        cout << "\t\tAll Account Holders" << endl;
        for (const auto &pair: accounts) {
            pair.second.showDetails();
        }
    }

    void searchAccount(int accountNum) const {
        auto it = accounts.find(accountNum);
        if (it != accounts.end()) {
            cout << "\t\tAccount Holder" << endl;
            it->second.showDetails();
        } else {
            cout << "\t\tAccount not found!" << endl;
        }
    }

    BankAccount *findAccount(int accountNum) {
        auto it = accounts.find(accountNum);
        return (it != accounts.end()) ? &it->second : nullptr;
    }
};

int main() {
    BankManagement bank;
    int choice;
    char op;

    do {
        cout << "\n\t\t:: Bank Management System ::" << endl;
        cout << "\t\t1. Create New Account" << endl;
        cout << "\t\t2. Show All Accounts" << endl;
        cout << "\t\t3. Search Account" << endl;
        cout << "\t\t4. Deposit Money" << endl;
        cout << "\t\t5. Withdraw Money" << endl;
        cout << "\t\t6. Exit" << endl;
        cout << "\t\t-------------------------------" << endl;
        cout << "\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int accountNum;
                double balance;
                cout << "\t\tEnter Name: ";
                cin >> name;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNum;
                cout << "\t\tEnter Initial Balance: ";
                cin >> balance;
                bank.addAccount(name, accountNum, balance);
                break;
            }
            case 2:
                bank.showAllAccounts();
                break;

            case 3: {
                int accountNum;
                cout << "\t\tEnter Account Number: ";
                cin >> accountNum;
                bank.searchAccount(accountNum);
                break;
            }
            case 4: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Deposit: ";
                cin >> accountNum;
                if (auto *acc = bank.findAccount(accountNum)) {
                    cout << "\t\tEnter Amount: ";
                    cin >> amount;
                    acc->deposit(amount);
                } else {
                    cout << "\t\tAccount Not Found!" << endl;
                }
                break;
            }
            case 5: {
                int accountNum;
                double amount;
                cout << "\t\tEnter Account Number to Withdraw: ";
                cin >> accountNum;
                if (auto *acc = bank.findAccount(accountNum)) {
                    cout << "\t\tEnter Amount: ";
                    cin >> amount;
                    acc->withdraw(amount);
                } else {
                    cout << "\t\tAccount Not Found!" << endl;
                }
                break;
            }
            case 6:
                cout << "\t\tExiting... Goodbye!" << endl;
                return 0;
            default:
                cout << "\t\tInvalid Choice!" << endl;
        }

        cout << "\n\t\tDo you want to continue? (Y/N): ";
        cin >> op;
    } while (op == 'y' || op == 'Y');
}
