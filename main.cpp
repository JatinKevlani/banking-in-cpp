#include "class_customer.h"
#include "functions.h"

int main()
{
    fstream dataFile;
    dataFile.open("data.txt");
    if (!dataFile)
        throw runtime_error("Data file not found!");
    dataFile.close();
    ofstream tempFile;
    tempFile.open("temp.txt");
    if (!tempFile)
        throw runtime_error("Temp file not found!");
    tempFile.close();
    remove("temp.txt");
    fstream transactionFile;
    transactionFile.open("transaction.txt", ios::app);
    if (!transactionFile)
        throw runtime_error("Transaction file not found!");
    transactionFile.close();
    fstream activityFile;
    activityFile.open("activity.txt", ios::app);
    if (!activityFile)
        throw runtime_error("Activity file not found!");
    activityFile << "New session started." << endl;
    activityFile.close();
    customer customers;
    int flag = 0, checkInput, checkTransfer, lineCounter = 1, activityCounter = 0;
    char acno[100], choice, transactionHistory[100], activityHistory[100];
    double amount;
    do
    {
        clearScreen();
        printMenu();
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case '0':
            clearScreen();
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            if (activityCounter == 0)
                activityFile << "Exited without doing anything." << endl;
            activityFile << "Session ended." << endl;
            cout << "Bye!" << endl;
            activityFile.close();
            pressEnterToContinue(true);
            break;

        case '1':
            activityCounter++;
            clearScreen();
            dataFile.open("data.txt", ios::out | ios::app | ios::binary);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            checkInput = customers.getData();
            // -1 for data file opening error.
            // 1 for same account number error.
            // 0 for successfull input.
            if (checkInput == -1)
                throw runtime_error("Data file not found!");
            else if (checkInput == 1)
            {
                cout << "Cannot create account of same account number!" << endl;
                activityFile << "Unable to create account due to same account number error." << endl;
                activityFile.close();
            }
            else
            {
                cout << "Customer added successfully!" << endl;
                activityFile << "New customer added." << endl;
                activityFile.close();
            }
            dataFile.write((char *)&customers, sizeof(customers));
            dataFile.close();
            activityFile.close();
            pressEnterToContinue();
            break;

        case '2':
            activityCounter++;
            clearScreen();
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            if (dataFile.peek() == ifstream::traits_type::eof())
            {
                cout << "No data found!" << endl;
            }
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                customers.displayData();
            }
            activityFile << "Viewed inforamtion of all customer." << endl;
            activityFile.close();
            dataFile.close();
            pressEnterToContinue();
            break;

        case '3':
            activityCounter++;
            clearScreen();
            flag = 0;
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            cout << "Enter the account number : ";
            cin.ignore();
            cin.getline(acno, 100);
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                if (strcmp(acno, customers.getaccNo()) == 0)
                {
                    customers.displayData();
                    flag = 1;
                    activityFile << "Searched information for account number : " << acno << "." << endl;
                    activityFile.close();
                    break;
                }
            }
            dataFile.close();
            if (flag == 0)
            {
                cout << "No such account number found!" << endl;
                activityFile << "Tried to search information but account not found." << endl;
                activityFile.close();
            }
            pressEnterToContinue();
            break;

        case '4':
            activityCounter++;
            clearScreen();
            flag = 0;
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            tempFile.open("temp.txt");
            if (!tempFile)
                throw runtime_error("Temp file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            cout << "Enter the account number : ";
            cin.ignore();
            cin.getline(acno, 100);
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                if (strcmp(acno, customers.getaccNo()) == 0)
                {
                    cout << "Enter the amount you want to deposit : ";
                    cin >> amount;
                    customers.depositAmount(acno, amount);
                    flag = 1;
                }
                tempFile.write((char *)&customers, sizeof(customers));
            }
            dataFile.close();
            tempFile.close();
            if (flag == 0)
            {
                cout << "No such account number found!" << endl;
                activityFile << "Tried to deposit money but account not found." << endl;
            }
            activityFile.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            pressEnterToContinue();
            break;

        case '5':
            activityCounter++;
            clearScreen();
            flag = 0;
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            tempFile.open("temp.txt");
            if (!tempFile)
                throw runtime_error("Temp file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            cout << "Enter the account number : ";
            cin.ignore();
            cin.getline(acno, 100);
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                if (strcmp(acno, customers.getaccNo()) == 0)
                {
                    cout << "Enter the amount you want to withdraw : ";
                    cin >> amount;
                    customers.withdrawAmount(acno, amount);
                    flag = 1;
                }
                tempFile.write((char *)&customers, sizeof(customers));
            }
            dataFile.close();
            tempFile.close();
            if (flag == 0)
            {
                cout << "No such account number found!" << endl;
                activityFile << "Tried to withdraw money but account not found." << endl;
                activityFile.close();
            }
            activityFile.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            pressEnterToContinue();
            break;

        case '6':
            activityCounter++;
            clearScreen();
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            checkTransfer = customers.transferAmount();
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
            if (checkTransfer == -1)
            {
                cout << "Cannot transfer money to the same account!" << endl;
                activityFile << "Tried to transfer money but cannot tranfer due to same account number in sender and receiver both." << endl;
                activityFile.close();
            }
            else if (checkTransfer == 0)
                cout << "Money transfered successfully!" << endl;
            else if (checkTransfer == 1)
                throw runtime_error("Data file not found!");
            else if (checkTransfer == 2)
                throw runtime_error("Temp file not found!");
            else if (checkTransfer == 3)
                throw runtime_error("Transaction file not found!");
            else if (checkTransfer == 4)
                throw runtime_error("Activity file not found!");
            else if (checkTransfer == 5)
            {
                cout << "Low balance..." << endl
                     << "Cannot transfer money!" << endl;
                activityFile << "Tried to transfer money but cannot transfer due to low balance." << endl;
                activityFile.close();
            }
            else if (checkTransfer == 6)
            {
                cout << "Sender not found!" << endl;
                activityFile << "Tried to transfer money but sender not found." << endl;
                activityFile.close();
            }
            else if (checkTransfer == 7)
            {
                cout << "Receiver not found!" << endl;
                activityFile << "Tried to transfer money but receiver not found." << endl;
                activityFile.close();
            }
            else
            {
                cout << "Cannot transfer money less than 1 rs." << endl;
                activityFile << "Tried to transfer money but cannot due to amount less than 1 rs." << endl;
                activityFile.close();
            }
            activityFile.close();
            pressEnterToContinue();
            break;

        case '7':
            activityCounter++;
            clearScreen();
            lineCounter = 1;
            transactionFile.open("transaction.txt", ios::in);
            if (!transactionFile)
                throw runtime_error("Transaction file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            if (transactionFile.peek() == ifstream::traits_type::eof())
            {
                cout << "No history found!" << endl;
            }
            else
            {
                cout << "Transaction history : " << endl;
                while (transactionFile.getline(transactionHistory, 100))
                {
                    cout << lineCounter << ". " << transactionHistory << endl;
                    lineCounter++;
                }
            }
            activityFile << "Viewed transaction history." << endl;
            activityFile.close();
            transactionFile.close();
            pressEnterToContinue();
            break;

        case '8':
            activityCounter++;
            clearScreen();
            flag = 0;
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            tempFile.open("temp.txt");
            if (!tempFile)
                throw runtime_error("Temp file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            cout << "Enter the account number in which you want to edit your information : ";
            cin.ignore();
            cin.getline(acno, 100);
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                if (strcmp(acno, customers.getaccNo()) == 0)
                {
                    customers.editInfo();
                    flag = 1;
                    activityFile << "Information edited of account number : " << acno << "." << endl;
                    activityFile.close();
                }
                tempFile.write((char *)&customers, sizeof(customers));
            }
            if (flag == 0)
            {
                cout << "No such account number found!" << endl;
                activityFile << "Tried to edit information but account not found." << endl;
                activityFile.close();
            }
            activityFile.close();
            dataFile.close();
            tempFile.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            pressEnterToContinue();
            break;

        case '9':
            activityCounter++;
            clearScreen();
            flag = 0;
            dataFile.open("data.txt", ios::in);
            if (!dataFile)
                throw runtime_error("Data file not found!");
            tempFile.open("temp.txt");
            if (!tempFile)
                throw runtime_error("Temp file not found!");
            activityFile.open("activity.txt", ios::app);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            cout << "Enter the account number you want to delete : ";
            cin.ignore();
            cin.getline(acno, 100);
            while (dataFile.read((char *)&customers, sizeof(customers)))
            {
                if (strcmp(acno, customers.getaccNo()) != 0)
                {
                    tempFile.write((char *)&customers, sizeof(customers));
                }
                else
                {
                    flag = 1;
                    cout << "Account deleted successfully!" << endl;
                    activityFile << "Customer account deleted." << endl;
                    activityFile.close();
                }
            }
            if (flag == 0)
            {
                cout << "No such account number found!" << endl;
                activityFile << "Tried to delete account but account not found." << endl;
                activityFile.close();
            }
            activityFile.close();
            dataFile.close();
            tempFile.close();
            remove("data.txt");
            rename("temp.txt", "data.txt");
            pressEnterToContinue();
            break;

        case 'a':
            activityCounter++;
            clearScreen();
            lineCounter = 1;
            activityFile.open("activity.txt", ios::in);
            if (!activityFile)
                throw runtime_error("Activity file not found!");
            if (activityFile.peek() == ifstream::traits_type::eof())
            {
                cout << "No history found!" << endl;
                activityFile.close();
            }
            else
            {
                cout << "Activity history : " << endl;
                while (activityFile.getline(activityHistory, 100))
                {
                    cout << lineCounter << ". " << activityHistory << endl;
                    lineCounter++;
                }
                activityFile.close();
            }
            activityFile.open("activity.txt", ios::app);
            activityFile << "Viewed activity history." << endl;
            activityFile.close();
            pressEnterToContinue();
            break;

        default:
            cout << "Invalid choice!" << endl;
            pressEnterToContinue();
        }
    } while (choice != '0');

    return 0;
}