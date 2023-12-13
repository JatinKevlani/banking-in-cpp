#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

class customer
{
private:
    char accNo[100], name[100];
    double balance;

public:
    int getData();
    void displayData();
    char *getaccNo();
    void depositAmount(char acNo[], double amount);
    void withdrawAmount(char acNo[], double amount);
    int transferAmount();
    void editInfo();
};

int customer::getData()
{
    // -1 for data file opening error.
    // 1 for same account number error.
    // 0 for successfull input.
    ifstream dataFile;
    dataFile.open("data.txt");
    if (!dataFile)
        return -1; // -1 for data file opening error.
    char acno[100];
    cout << "Enter the account number : ";
    cin.ignore();
    cin.getline(acno, 100);
    customer temp;
    while (dataFile.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(acno, temp.getaccNo()) == 0)
            return 1; // 1 for same account number error.
    }
    strcpy(accNo, acno);
    cout << "Enter the name : ";
    cin.getline(name, 100);
    cout << "Enter the intial deposit amount : ";
    cin >> balance;
    dataFile.close();
    return 0; // 0 for successfull input.
}

void customer::displayData()
{
    cout << "Account number : " << accNo << endl;
    cout << "Name : " << name << endl;
    cout << "Balance : " << balance << endl;
}

char *customer::getaccNo()
{
    return accNo;
}

void customer::depositAmount(char acNo[], double amount)
{
    ofstream transactionFile, activityFile;
    transactionFile.open("transaction.txt", ios::app);
    if (!transactionFile)
        throw runtime_error("Transaction file not found!");
    activityFile.open("activity.txt", ios::app);
    if (!activityFile)
        throw runtime_error("Activity file not found!");
    if (amount < 1)
    {
        cout << "Cannot deposit money less than 1 rs." << endl;
        activityFile << "Tried to deposit money but cannot due to amount less than 1 rs." << endl;
    }
    else
    {
        balance += amount;
        cout << "Money deposited successfully!" << endl
             << "Your updated balance is : " << balance << endl;
        transactionFile << "Rs " << amount << " deposited in account number : " << acNo << endl;
        activityFile << "Money deposited in account number : " << acNo << "." << endl;
    }
    transactionFile.close();
    activityFile.close();
}

void customer::withdrawAmount(char acNo[], double amount)
{
    ofstream transactionFile, activityFile;
    transactionFile.open("transaction.txt", ios::app);
    if (!transactionFile)
        throw runtime_error("Transaction file not found!");
    activityFile.open("activity.txt", ios::app);
    if (!activityFile)
        throw runtime_error("Activity file not found!");
    if (amount < 1)
    {
        cout << "Cannot withdraw money less than 1 rs." << endl;
        activityFile << "Tried to withdraw money but cannot due to amount less than 1 rs." << endl;
    }
    else if (balance < amount)
    {
        cout << "Low balance...." << endl
             << "Cannot withdraw money!" << endl;
        activityFile << "Tried to withdraw money but cannot due to low balance." << endl;
    }
    else
    {
        balance -= amount;
        cout << "Money withdrawed successfully!" << endl
             << "Your updated balance is : " << balance << endl;
        transactionFile << "Rs " << amount << " withdrawed from account number : " << acNo << endl;
        activityFile << "Money withdrawn from account number : " << acNo << "." << endl;
    }
    activityFile.close();
    transactionFile.close();
}

int customer::transferAmount()
{
    // -1 for same account transfer error.
    // 0 for successfull transfer.
    // 1 for data file opening error.
    // 2 for temp file opening error.
    // 3 for transaction file opening error.
    // 4 for activity file opening error.
    // 5 for low balance error.
    // 6 for sender not found.
    // 7 for receiver not found.
    // 8 for amount less than 1 rs.
    fstream dataFile, activityFile;
    ofstream tempFile;
    ofstream transactionFile;
    dataFile.open("data.txt", ios::in);
    if (!dataFile)
        return 1; // 1 for data file opening error.
    tempFile.open("temp.txt");
    if (!tempFile)
        return 2; // 2 for temp file opening error.
    transactionFile.open("transaction.txt", ios::app);
    if (!transactionFile)
        return 3; // 3 for transaction file opening error.
    activityFile.open("activity.txt", ios::app);
    if (!activityFile)
        return 4; // 4 for activity file opening error.
    char receiver[100], sender[100];
    bool flagReceiver = false, flagSender = false;
    double amount;
    customer temp;
    cout << "Enter the account number from which you want to transfer the money : ";
    cin.ignore();
    cin.getline(sender, 100);
    while (dataFile.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(sender, temp.getaccNo()) == 0)
        {
            flagSender = true;
            break;
        }
    }
    dataFile.close();
    if (flagSender == false)
        return 6; // 6 for sender not found.
    dataFile.open("data.txt", ios::in);
    if (!dataFile)
        return 1; // 1 for data file opening error.
    cout << "Enter the account number in which you want to transfer the money : ";
    cin.getline(receiver, 100);
    while (dataFile.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(receiver, temp.getaccNo()) == 0)
        {
            flagReceiver = true;
            break;
        }
    }
    dataFile.close();
    if (flagReceiver == false)
        return 7; // 7 for receiver not found.
    if (strcmp(sender, receiver) == 0)
        return -1; // -1 for same account transfer error.
    dataFile.open("data.txt", ios::in);
    if (!dataFile)
        return 1; // 1 for data file opening error.
    cout << "Enter the amount you want to transfer : ";
    cin >> amount;
    if (amount < 1)
        return 8; // 8 for amount less than 1 rs.
    while (dataFile.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(sender, temp.getaccNo()) == 0)
        {
            if (temp.balance < amount)
                return 5; // 5 for low balance error.
            temp.balance -= amount;
        }
        tempFile.write((char *)&temp, sizeof(temp));
    }
    tempFile.close();
    dataFile.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
    dataFile.open("data.txt", ios::in);
    if (!dataFile)
        return 1; // 1 for data file opening error.
    tempFile.open("temp.txt");
    if (!tempFile)
        return 2; // 1 for temp file opening error.
    while (dataFile.read((char *)&temp, sizeof(temp)))
    {
        if (strcmp(receiver, temp.getaccNo()) == 0)
            temp.balance += amount;
        tempFile.write((char *)&temp, sizeof(temp));
    }
    transactionFile << "Rs " << amount << " transfered from account number : " << sender << " to account number : " << receiver << endl;
    dataFile.close();
    tempFile.close();
    remove("data.txt");
    rename("temp.txt", "data.txt");
    transactionFile.close();
    activityFile << "Money transfered from account number : " << sender << " to account number : " << receiver << "." << endl;
    activityFile.close();
    return 0; // 0 for successfull transfer.
}

void customer::editInfo()
{
    cout << "Enter your new name : ";
    cin.getline(name, 100);
    cout << "Information edited successfully!" << endl;
}