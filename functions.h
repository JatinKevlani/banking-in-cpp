void printMenu();
void clearScreen();
void pressEnterToContinue(bool);

void printMenu()
{
    cout << "Enter 0 to exit." << endl;
    cout << "Enter 1 to create new account." << endl;
    cout << "Enter 2 to get information of all customers." << endl;
    cout << "Enter 3 to get information of particular customer." << endl;
    cout << "Enter 4 to deposit money." << endl;
    cout << "Enter 5 to withdraw money." << endl;
    cout << "Enter 6 to transfer money." << endl;
    cout << "Enter 7 to get transaction history." << endl;
    cout << "Enter 8 to edit customer information." << endl;
    cout << "Enter 9 to delete your account." << endl;
}

void clearScreen()
{
    system("cls");
}

void pressEnterToContinue(bool exit = false)
{
    if (exit == true)
        cout << "Press ENTER to exit...";
    else
        cout << "Press ENTER to continue...";
    cin.ignore();
    cin.get();
}