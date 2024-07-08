
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<windows.h>
using namespace std;
//======================================================================================================================\\

// make every class in sepearated file and includ header file like ( #include "DataBase.h")

// write report and take screenshots of run




//========================================================================================================================\\

class DataBase {
protected:
    ifstream Diamond;
    ifstream Gold;
    ifstream Silver;

public:
    ~DataBase() {
        Diamond.close();
        Gold.close();
        Silver.close();
    }
    void LinkDataBase(string DIAMOND, string GOLD, string SILVER) {
        Diamond.open(DIAMOND + ".txt");
        Gold.open(GOLD + ".txt");
        Silver.open(SILVER + ".txt");
        if (!Diamond || !Gold || !Silver) {
            cerr << "Error opening files!" << endl;
            exit(1);
        }
    }
};
//======================================================================================================================\\

// Data Base class






//========================================================================================================================\\

class Account : public DataBase {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    Account(int accountNumber, string accountHolderName, double balance)
            : accountNumber(accountNumber), accountHolderName(accountHolderName), balance(balance) {}

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else
        {
            cout << "Withdrawal exceeds balance." << endl;
            return false;
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void displayInfo() const {
        cout << "=================^^^============ " << endl;
        cout << "  Account Name Is  : ( " << accountHolderName << "  )" << endl;
        cout << "=================^^^============ " << endl << endl;
        cout << "  Account Number Is  : ( " << accountNumber << "  )" << endl;
        cout << "=================^^^============ " << endl << endl;
        cout << "  Account Balance Is  : ( " << balance << "  )" << endl;
     cout<<"=================^^^============ "<<endl<< endl;
    }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(int accountNumber, string accountHolderName, double balance, double overdraftLimit)
            : Account(accountNumber, accountHolderName, balance), overdraftLimit(overdraftLimit) {}

    bool withdraw(double amount) {
        if (balance + overdraftLimit >= amount) {
            balance -= amount;
            cout << "Withdrew " << amount << ", new balance: " << balance << endl;
            return true;
        } else {
            cout << "Insufficient balance or overdraft limit exceeded." << endl;
            return false;
        }
    }
};
//======================================================================================================================\\




//========================================================================================================================\\

class Bank : public DataBase {
private:
    Account **accounts;
    int numAccounts;
    int capacity;

    void displayOperationMenu()
    {
        cout << " ********************************* " << endl;
        cout << " *    Sahm Bank Operations        * " << endl;
        cout << " ********************************* " << endl;
        cout << " *                                * " << endl;
        cout << " *    1-Deposite                  * " << endl;
        cout << " *    2-WithdDraw                 * " << endl;
        cout << " *    3-Transfer Between Acoounts * " << endl;
        cout << " *    4-Transfer Money            * " << endl;
        cout << " *    5-Cahout (Remove Acoount)   * " << endl;
        cout << " *    6- Search For Account       * " << endl;
        cout << " *    7- EXIT                     * " << endl;
        cout << " ********************************* " << endl;
    }

    int getOperationChoice() {
        int choice;
        cout << "Enter your choice (1-7): ";
        cin >> choice;
        return choice;
    }

    void makeDeposit(Account *account) {
        double amount;
        cout << "Enter deposit amount: ";
        cin >> amount;
        account->deposit(amount);
        cout << "Deposited successfully. New balance: " << account->getBalance() << endl;
    }

    void makeWithdraw(Account *account) {
        double amount;
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        if (account->withdraw(amount)) {
            cout << "Withdrawn successfully. New balance: " << account->getBalance() << endl;
        } else {
            cout << "Withdrawal failed. Insufficient funds." << endl;
        }
    }

    void cashOut(int accountNumber) {
        Account *account = findAccount(accountNumber);
        if (account != nullptr) {
            double balance = account->getBalance();
            // Remove the account from the array (assuming the account is permanently deleted)
            removeAccount(accountNumber);
            cout << "Cashout successful. Withdrawn " << balance << ". Account deleted." << endl;
        } else {
            cout << "Account not found." << endl;
        }
    }

    void transferCoins(Account *senderAccount) {
        double amount;
        cout << "Enter transfer amount: ";
        cin >> amount;

        if (senderAccount->withdraw(amount)) {
            cout << "Transfer successful. Transferred " << amount << ". New balance: " << senderAccount->getBalance() << endl;
        } else {
            cout << "Transfer failed. Insufficient funds." << endl;
        }
    }

    void transferBetweenAccounts(Account *senderAccount) {
        int recipientAccountNumber;
        cout << "Enter recipient account number: ";
        cin >> recipientAccountNumber;

        Account *recipientAccount = findAccount(recipientAccountNumber);
        if (recipientAccount != nullptr) {
            double amount;
            cout << "Enter transfer amount: ";
            cin >> amount;

            if (senderAccount->withdraw(amount)) {
                recipientAccount->deposit(amount);
                cout << "Transfer successful. Transferred " << amount << " to account " << recipientAccountNumber << "." << endl;
            } else {
                cout << "Transfer failed. Insufficient funds." << endl;
            }
        } else {
            cout << "Recipient account not found." << endl;
        }
    }

    void searchAccount() {
        int accountNumber;
        cout << "Enter account number to search: ";
        cin >> accountNumber;

        Account *account = findAccount(accountNumber);
        if (account != nullptr) {
            cout << "Account found." << endl;
            account->displayInfo();
        } else {
            cout << "Account not found." << endl;
        }
    }

public:
    Bank(int initialCapacity = 10) : accounts(new Account *[initialCapacity]), numAccounts(0),
                                     capacity(initialCapacity) {}

    ~Bank() {
        for (int i = 0; i < numAccounts; ++i) {
            delete accounts[i];
        }
        delete[] accounts;
    }

    void createAccount() {
        int accountNumber;
        string accountHolderName;
        double initialBalance;
        string accountType;

//        cout << "Enter account number: ";
DisplayUIAccountNumber();
        cin >> accountNumber;

//        cout << "Enter account holder name: ";
DisplayUIAccountName();
        cin.ignore(); // Consume the newline character left in the buffer

//        cout << "Enter account holder name: ";

        getline(cin, accountHolderName);
//        cin >> accountHolderName;

      //  cout << "Enter initial balance: ";
DisplayUIAccountBalacne();
        cin >> initialBalance;

     //   cout << "Choose account type (Diamond, Gold, Silver): ";
       DisplayUIAccounType();
        cin >> accountType;

        Account *newAccount = nullptr;
        if (accountType == "Diamond" || accountType == "Gold" || accountType == "Silver") {
            if (accountType == "Diamond") {
                newAccount = new Account(accountNumber, accountHolderName, initialBalance);
            } else if (accountType == "Gold") {
                newAccount = new Account(accountNumber, accountHolderName, initialBalance);
            } else {
                newAccount = new Account(accountNumber, accountHolderName, initialBalance);
            }
        } else {
            newAccount = new CheckingAccount(accountNumber, accountHolderName, initialBalance, 500);
        }

        // Save account data to the appropriate file
        ofstream outFile(accountType + ".txt", ios::app);  // Append to the file
        outFile << accountNumber << endl;

        // Check capacity and resize if needed
        if (numAccounts == capacity) {
            capacity *= 2;
            Account **newAccounts = new Account *[capacity];
            for (int i = 0; i < numAccounts; ++i) {
                newAccounts[i] = accounts[i];
            }
            delete[] accounts;
            accounts = newAccounts;
        }
        accounts[numAccounts++] = newAccount;

        cout << "Account created successfully." << endl;
    }
    void outro()
    {
        cout <<"Thank You For Choosing Our Bank We Hope That You Have A good Expirense \n";
        cout <<"Have A Nice Time SIR Take This Cadeu From Our Team \n";
        cout << "\n";
        cout << "     .----------------. .----------------. .----------------. .----------------. .----------------. " << endl;
        cout << "     | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "     | |   ____   | || |   ____   | || |   ____   | || |   ____   | || |   ____   | |" << endl;
        cout << "     | |  / _ \ |  | || |  / _ \ |  | || |  / _ \ |  | || |  / _ \ |  | || |  / _ \ |  | |" << endl;
        cout << "     | |  | (_) |  | || |  | (_) |  | || |  | (_) |  | || |  | (_) |  | || |  | (_) |  | |" << endl;
        cout << "     | |  | _ \ |  | || |  | _ \ |  | || |  | _ \ |  | || |  | _ \ |  | || |  | _ \ |  | |" << endl;
        cout << "     | |  | (_) |  | || |  | (_) |  | || |  | (_) |  | || |  | (_) |  | || |  | (_) |  | |" << endl;
        cout << "     | |   \___/ |  | || |   \___/ |  | || |   \___/ |  | || |   \___/ |  | || |   \___/ |  | |" << endl;
        cout << "     | |       | || |       | || |       | || |       | || |       | || |       | |" << endl;
        cout << "     | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |" << endl;
        cout << "     '----------------' '----------------' '----------------' '----------------' '----------------' "  << endl;
        cout << "     .----------------. .----------------. .----------------. .----------------. .----------------. " << endl;
        cout << "     | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "     | |   S  A  H  M  | || |   G  R  O  U  P  | || |   S  A  H  M  | || |   G  R  O  U  P  | |" << endl;
        cout << "     | |   S  A  H  M  | || |   G  R  O  U  P  | || |   S  A  H  M  | || |   G  R  O  U  P  | |" << endl;
        cout << "     | |   S  A  H  M  | || |   G  R  O  U  P  | || |```";
        cout << "          .----------------.  .----------------.  .----------------.  .----------------.  .----------------. " << endl;
        cout << "      | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |" << endl;
        cout << "      | |    ______    | || |  _______     | || |     ____     | || | _____  _____ | || |   ______     | |" << endl;
        cout << "      | |  .' ___  |   | || | |_   __ \\    | || |   .'    `.   | || ||_   _||_   _|| || |  |_   __ \\   | |" << endl;
        cout << "      | | / .'   \_|    | || |   | |__) |   | || |  /  .--.  \\  | || |  | |    | |  | || |    | |__) |  | | " << endl;
        cout << "      | | | |    ____  | || |   |  __ /    | || |  | |    | |  | || |  | '    ' |  | || |    |  ___/   | | " << endl;
        cout << "      | | \ `.___]  _|  | || |  _| |  \\ \\_  | || |  \\  `--'  /  | || |   \\ `--' /   | || |   _| |_      | |" << endl;
        cout << "      | |  `._____.'   | || | |____| |___| | || |   `.____.'   | || |    `.__.'    | || |  |_____|     | | " << endl;
        cout << "      | |              | || |              | || |              | || |              | || |              | | " << endl;
        cout << "      | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' | " << endl;
        cout << "          '----------------'  '----------------'  '----------------'  '----------------'  '----------------' " << endl;
    }
    void viewAccountDetails(int accountNumber) {
        Account *account = findAccount(accountNumber);
        if (account != nullptr) {
            account->displayInfo();
        } else {
            cout << "Account not found." << endl;
        }
    }

    void makeTransaction() {
        int accountNumber;
        cout << "Enter account number: ";
        cin >> accountNumber;

        Account *account = findAccount(accountNumber);
        if (account != nullptr) {
            int operationChoice;
            do {
                displayOperationMenu();
                operationChoice = getOperationChoice();

                switch (operationChoice) {
                    case 1:
                        makeDeposit(account);
                        break;
                    case 2:
                        makeWithdraw(account);
                        break;
                    case 3:
                        transferBetweenAccounts(account);
                        break;
                    case 4:
                        transferCoins(account);
                        break;
                    case 5:
                        cashOut(accountNumber);
                        break;
                    case 6:
                        searchAccount();
                        break;
                    case 7:
                        break; // Exit the operation menu
                    default:
                        cout << "Invalid choice. Please enter a valid option." << endl;
                }
            } while (operationChoice != 7);
        } else {
            cout << "Account not found." << endl;
        }
    }
    void intro()
    {
        //system("cls");

        cout << " ********************************* " << endl;
        cout << " *    Sahm ---> Team Bank      * " << endl;
        cout << " *************-******************** " << endl;
        cout << " *            |                  * " << endl;
        cout << " *            |                  * " << endl;
        cout << " *            ^                  * " << endl;
        cout << " *    1-Crate Account            * " << endl;
        cout << " *    2-View Account Details     * " << endl;
        cout << " *    3-Make Operation           * " << endl;
        cout << " *    4-Exit                     * " << endl;
        cout << " *                               * " << endl;
        cout << " ********************************* " << endl;


    }
    void Sahm()
    {
cout<<"============|||||||||||=========================================================================================\n";
cout << "                  |||||||||||" << endl;
cout << "                  |||||||||||" << endl;
cout << "                  |||||||||||" << endl;
cout << "                  |||||||||||" << endl;
cout << "                  |||||||||||" << endl;
cout << "             /____________________\\ " << endl;
cout << "              \\   S  A             / " << endl;
cout << "               \\   A  N           / " << endl;
cout << "                \\   H   B       / " << endl;
cout << "                 \\   M   A     / " << endl;
cout << "                  \\   T   N   / " << endl;
cout << "                   \\   E  K  / " << endl;
cout << "                    \\------/ " << endl;
cout << "                     \\    / " << endl;
cout << "                      \\  / " << endl;
cout << "                       \\/ " << endl;
    }
    void DisplayUIAccountName()
    {
     //   system("cls");
        cout << " ********************************* " << endl;
        cout << " *                               * " << endl;
        cout << " *      Enter Yor Account Name   * "<<endl ;
        cout << " ********************************* " << endl;
    }
    void DisplayUIAccountNumber()
    {
     //   system("cls");
        cout << " ********************************* " << endl;
        cout << " * - Enter Your Account Number - * " << endl;
        cout << " *                               * " << endl;
        cout << " ********************************* " << endl;
    }
    void DisplayUIAccountBalacne()
    {
        //system("cls");
        cout << " ********************************* " << endl;
        cout << " * - Enter Your Account Balance -* " << endl;
        cout << " *                               * " << endl;
        cout << " ********************************* " << endl;
    }

void DisplayUIAccounType() {
   // system("cls");
    cout << " ********************************* " << endl;
    cout << " *   Sahm Bank Account Types --> * " << endl;
    cout << " ********************************* " << endl;
    cout << " *                               * " << endl;
    cout << " *    1-Diamod                   * " << endl;
    cout << " *    2-Gold                     * " << endl;
    cout << " *    3-Silver                   * " << endl;
    cout << " *                               * " << endl;
    cout << " ********************************* " << endl;
}
private:
    Account *findAccount(int accountNumber) {
        for (int i = 0; i < numAccounts; ++i) {
            if (accounts[i]->getAccountNumber() == accountNumber) {
                return accounts[i];
            }
        }
        return nullptr; // Account not found
    }

    void removeAccount(int accountNumber) {
        for (int i = 0; i < numAccounts; ++i) {
            if (accounts[i]->getAccountNumber() == accountNumber) {
                // Delete the account and shift the remaining accounts in the array
                delete accounts[i];
                for (int j = i; j < numAccounts - 1; ++j) {
                    accounts[j] = accounts[j + 1];
                }
                numAccounts--;
                return;
            }
        }
    }
};
//======================================================================================================================\\








//========================================================================================================================\\

int main() {
    cout<<"  Welcome to Sahm Team Bank System ;)\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    Bank bank;
    int choice;
    DataBase dataBase;
    dataBase.LinkDataBase("Diamond", "Gold", "Silver");
    do {
        bank.intro();

        cout << "Enter your choice (1-4): ";

        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                bank.Sahm();
                break;
            case 2: {
                int accountNumber;
                bank.Sahm();
                bank.DisplayUIAccountNumber();
                cin >> accountNumber;
                bank.viewAccountDetails(accountNumber);
                bank.Sahm();
                break;
            }
            case 3:
                bank.Sahm();
                bank.makeTransaction();
                break;
            case 4:
               bank.outro();
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

    } while (choice != 4);

    return 0;
}
