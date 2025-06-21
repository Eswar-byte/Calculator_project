#include <bits/stdc++.h>
using namespace std;

class BankAccount {
private:
    string name;
    int accountNumber;
    string pin;
    double balance;

public:
    BankAccount(string name, int accNo, string pin, double balance = 0.0)
        : name(name), accountNumber(accNo), pin(pin), balance(balance) {}

    string getName() const { return name; }
    int getAccountNumber() const { return accountNumber; }
    string getPin() const { return pin; }
    double getBalance() const { return balance; }

    void deposit(double amount) { balance += amount; }
    void withdraw(double amount) {
        if (amount <= balance) balance -= amount;
        else cout << "Insufficient funds.\n";
    }

    void displayInfo() const {
        cout << "\n--- Account Info ---\n";
        cout << "Name: " << name << "\nAccount No: " << accountNumber << "\nBalance: ₹" << balance << endl;
    }

    void saveToFile(ofstream& fout) const {
        fout << name << " " << accountNumber << " " << pin << " " << balance << endl;
    }
};

// Load all accounts from file
vector<BankAccount> loadAccounts() {
    vector<BankAccount> users;
    ifstream fin("accounts.txt");
    string name, pin;
    int accNo;
    double balance;

    while (fin >> name >> accNo >> pin >> balance) {
        users.emplace_back(name, accNo, pin, balance);
    }

    return users;
}

// Save all accounts to file
void saveAccounts(const vector<BankAccount>& users) {
    ofstream fout("accounts.txt");
    for (const auto& user : users)
        user.saveToFile(fout);
}

// Generate unique account number
int generateAccountNumber(const vector<BankAccount>& users) {
    int base = 1001;
    if (!users.empty())
        base = users.back().getAccountNumber() + 1;
    return base;
}

// Signup flow
void signup(vector<BankAccount>& users) {
    string name, pin;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Choose a 4-digit PIN: ";
    cin >> pin;

    int accNo = generateAccountNumber(users);
    BankAccount newUser(name, accNo, pin);
    users.push_back(newUser);
    saveAccounts(users);

    cout << "Account created successfully!\n";
    cout << "Your account number is: " << accNo << endl;
}

// Login flow
void login(vector<BankAccount>& users) {
    int accNo;
    string pin;
    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter PIN: ";
    cin >> pin;

    for (auto& user : users) {
        if (user.getAccountNumber() == accNo && user.getPin() == pin) {
            cout << "\nWelcome, " << user.getName() << "!\n";
            int choice;
            do {
                cout << "\n1. Deposit\n2. Withdraw\n3. Balance\n4. Account Info\n0. Logout\nChoice: ";
                cin >> choice;
                if (choice == 1) {
                    double amt;
                    cout << "Enter amount to deposit: ";
                    cin >> amt;
                    user.deposit(amt);
                } else if (choice == 2) {
                    double amt;
                    cout << "Enter amount to withdraw: ";
                    cin >> amt;
                    user.withdraw(amt);
                } else if (choice == 3) {
                    cout << "Balance: ₹" << user.getBalance() << endl;
                } else if (choice == 4) {
                    user.displayInfo();
                }
            } while (choice != 0);

            saveAccounts(users);
            return;
        }
    }

    cout << "Invalid account number or PIN.\n";
}

int main() {
    vector<BankAccount> users = loadAccounts();
    int option;

    cout << "=== Bank Management System ===\n";
    do {
        cout << "\n1. Signup\n2. Login\n0. Exit\nChoose option: ";
        cin >> option;
        if (option == 1) signup(users);
        else if (option == 2) login(users);
    } while (option != 0);

    cout << "Thank you for using the system!\n";
    return 0;
}
