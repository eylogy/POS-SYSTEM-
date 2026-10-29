#include <iostream>
#include <string>
using namespace std;

const int maxusers = 20;

// Role is one of: "Admin", "Supervisor", "Cashier"
string accountUser[maxusers] = {"admin", "supervisor", "cashier"};
string accountPass[maxusers] = {"Group5", "Group5", "Group5"};
string accountRole[maxusers] = {"Admin", "Supervisor", "Cashier"};
int accountCount = 3;

// Prints a number with 2 decimal places
void printMoney(double amount)
{
    int pesos = amount;
    int centavos = (amount - pesos) * 100 + 0.5;

    if (centavos == 100)
    {
        pesos++;
        centavos = 0;
    }

    cout << pesos << ".";

    if (centavos < 10)
    cout << "0";

    cout << centavos;
}

int readNumber(int max)
{
    string digit[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    string text;
    cin >> text;

    for (int n = 0; n <= max; n++)
    {
        string numberText = "";
        int temp = n;

        if (n == 0)
        {
            numberText = "0";
        }

        while (temp > 0)
        {
            numberText = digit[temp % 10] + numberText;
            temp = temp / 10;
        }

        if (text == numberText)
        {
            return n;
        }
    }

    return -1;  
}

 // POS MONITORING SYSTEM //
void showMenu(string role) {

    cout << "\nPOS SYSTEM GROUP 5 (" << role << ")" << endl;
    cout << "====================" << endl;

    if (role == "Supervisor")
        cout << "Monitoring [1]" << endl;

    if (role == "Admin")
        cout << "Inventory [2]" << endl;

    if (role == "Cashier")
        cout << "Order [3]" << endl;

    if (role == "Admin")
        cout << "Manage Employees [4]" << endl;

    cout << "Exit [0]" << endl;
    cout << "Select: ";
}

// Shows everything currently in the order and returns the subtotal
double showOrder(string items[], double prices[], int cartQty[])
{
    double subtotal = 0;

    cout << "\n--- CURRENT ORDER ---" << endl;
    for (int i = 0; i < 13; i++)
    {
        if (cartQty[i] > 0)
        {
            cout << items[i] << " x" << cartQty[i] << " = PHP ";
            printMoney(cartQty[i] * prices[i]);
            cout << endl;
            subtotal = subtotal + cartQty[i] * prices[i];
        }
    }
    cout << "Subtotal: PHP ";
    printMoney(subtotal);
    cout << endl;

    return subtotal;
}

int findAccountIndex(string usernames[], int count, string name)
{
    for (int i = 0; i < count; i++)
    {
        if (usernames[i] == name)
            return i;
    }
    return -1;
}

int main()
{
    // Employee list (separate from login accounts) //
    string usernames[maxusers] = {"Admin" , "Supervisor", "Cashier"};
    int usercount = 3;

    // POS MONITORING SYSTEM //
    string items[] = {"Beef Tapa", "Longganisa", "Corned Beef", "Bistek", "Menudo", "Torta", "Rice", "Fried Rice", "Java Rice", "Soup", "Nestea", "Coke", "Water"};
    double prices[] = {45.00, 35.00, 50.00, 65.00, 55.00, 30.00, 15.00, 25.00, 20.00, 10.00, 20.00, 25.00, 10.00};
    int inventory[] = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

    double discRate = 0.20;
    double taxRate = 0.12;

    int soldQty[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
    double soldRevenue[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int cartQty[13] = {0};   // saved order: how many of each item is in it
    int totalOrders = 0;
    double totalSales = 0;

    string loginAgain = "y";

    // Keep the whole system running so a new user can log in after someone logs out
    while (loginAgain == "y" || loginAgain == "Y" || loginAgain == "yes" || loginAgain == "YES" || loginAgain == "Yes")
    {
        // LOGIN SYSTEM //
        string username, password;
        string currentRole = "";
        bool loggedIn = false;

        for (int attempts = 1; attempts <= 3; attempts++) {

            cout << "\nLOGIN SYSTEM\n";
            cout << "Attempt: " << attempts << " of 3\n";

            cout << "Please enter your username: ";
            cin >> username;

            cout << "Please enter your password: ";
            cin >> password;

            int idx = findAccountIndex(accountUser, accountCount, username);

            if (idx != -1 && accountPass[idx] == password) {
                currentRole = accountRole[idx];
                cout << "\nLogin successful! Welcome, " << currentRole << ".\n";
                loggedIn = true;
                break;
            }
            else {
                cout << "Incorrect Username and Password\n";
            }
        }

        // If login failed after 3 attempts //
        if (!loggedIn) {
            cout << "\nToo many failed attempts. Access denied.\n";
            cout << "\nTry logging in again? (y/n): ";
            cin >> loginAgain;
            continue;
        }

        char choice;

        // Keep this user's session running until they log out
        do
        {
            showMenu(currentRole);
            cin >> choice;

            switch (choice)
            {
            // MONITORING // - Supervisor only
            case '1':
            {
                if (currentRole != "Supervisor")
                {
                    cout << "Access Denied: Supervisors only." << endl;
                    break;
                }

                cout << "\n===== SALES MONITORING =====" << endl;
                for (int i = 0; i < 13; i++) {
                    cout << items[i] << " - Sold: " << soldQty[i] << " pc(s) | Revenue: PHP ";
                    printMoney(soldRevenue[i]);
                    cout << endl;
                }
                cout << "-----------------------------" << endl;
                cout << "Total Orders Placed: " << totalOrders << endl;
                cout << "Total Sales: PHP ";
                printMoney(totalSales);
                cout << endl;
                cout << "=============================" << endl;
                break;
            }

            // VIEW INVENTORY // - Admin only
            case '2':
            {
                if (currentRole != "Admin")
                {
                    cout << "Access Denied: Admins only." << endl;
                    break;
                }

                int pick;
                string again3;

                do
                {
                    cout << "\n===== INVENTORY =====" << endl;
                    for (int i = 0; i < 13; i++) {
                        cout << (i + 1) << ". " << items[i] <<endl;
                    }
                    cout << "Check Product: ";
                    pick = readNumber(13);

                    int idx = pick - 1;
                    if (idx >= 0 && idx < 13)
                    {
                        cout << items[idx] << ": " << inventory[idx] << " Pc(s) remaining." << endl;
                    }
                    else
                    {
                        cout << "Invalid Input " << endl;
                    }

                    cout << "\nCheck another product? (y/n): ";
                    cin >> again3;

                } while (again3 == "y" || again3 == "Y" || again3 == "yes" || again3 == "YES" || again3 == "Yes");

                break;
            }

            // ORDER SYSTEM // - Cashier only
            case '3':
            {
                if (currentRole != "Cashier")
                {
                    cout << "Access Denied: Cashiers only." << endl;
                    break;
                }

                string orderAgain;
                string payNow;

                // Check if there is an unfinished order from before
                bool hasItems = false;
                for (int i = 0; i < 13; i++)
                {
                    if (cartQty[i] > 0)
                        hasItems = true;
                }
                // addItems decides if we show the menu to add items, or go straight to payment
                bool addItems = true;

                if (hasItems)
                {
                    string addMore;
                    cout << "\nYou have an unfinished order." << endl;
                    showOrder(items, prices, cartQty);

                    cout << "Add more items? (y/n): ";
                    cin >> addMore;

                    if (!(addMore == "y" || addMore == "Y" || addMore == "yes" || addMore == "YES" || addMore == "Yes"))
                    {
                        addItems = false;   // go straight to payment
                    }
                }
                // ===== ADD ITEMS =====
                if (addItems)
                {
                    do
                    {
                        int order;
                        int quantity;

                        cout << "\n==== MENU ====" << endl;
                        for (int i = 0; i < 6; i++) {
                            cout << (i + 1) << ". " << "A" << (i + 1) << " " << items[i] << " - PHP " << prices[i] << ".00 " << endl;
                        }

                        cout << "\n === ADD ONS === " << endl;
                        for (int j = 6; j < 13; j++)
                        {
                            cout << (j + 1) << ". " << "A" << (j + 1) << " " << items[j] << " - PHP " << prices[j] << ".00 " << endl;
                        }

                        cout << "Enter your choice: ";
                        order = readNumber(13);

                        if (order >= 1 && order <= 13)
                        {
                            int index = order - 1;

                            cout << "Enter Quantity: ";
                            quantity = readNumber(999);

                            if (quantity <= 0)
                            {
                                cout << "Quantity must be more than 0!" << endl;
                            }
                            else if (quantity + cartQty[index] > inventory[index])
                            {
                                cout << "Error: Not enough stock! Available: " << (inventory[index] - cartQty[index]) << endl;
                            }
                            else
                            {
                                cartQty[index] = cartQty[index] + quantity;
                                cout << items[index] << " added to the order." << endl;
                            }
                        }
                        else
                        {
                            cout << "Invalid item number." << endl;
                        }

                        showOrder(items, prices, cartQty);

                        cout << "\nProcess another order? (y/n): ";
                        cin >> orderAgain;

                    } while (orderAgain == "y" || orderAgain == "Y" || orderAgain == "yes" || orderAgain == "YES" || orderAgain == "Yes");
                }
                // AFTER "n"
                // Check again if there is anything in the order. If nothing, there is nothing to pay.
                hasItems = false;
                for (int i = 0; i < 13; i++)
                {
                    if (cartQty[i] > 0)
                        hasItems = true;
                }
                if (hasItems)
                {
                    cout << "Pay now? (y/n): ";
                    cin >> payNow;

                    if (!(payNow == "y" || payNow == "Y" || payNow == "yes" || payNow == "YES" || payNow == "Yes"))
                    {
                        cout << "Order saved. Choose Order [3] again to continue it." << endl;
                    }
                    else
                    {
                        // ===== CHECKOUT =====
                        string discountAnswer;
                        double appliedDisc = 0;
                        double subtotal = showOrder(items, prices, cartQty);

                        cout << "Are you a Senior Citizen/PWD? (y/n): ";
                        cin >> discountAnswer;

                        if (discountAnswer == "y" || discountAnswer == "Y" || discountAnswer == "yes" || discountAnswer == "YES" || discountAnswer == "Yes")
                        {
                            appliedDisc = discRate;
                        }

                        double discount = subtotal * appliedDisc;
                        double tax = (subtotal - discount) * taxRate;
                        double total = subtotal - discount + tax;

                        cout << "\nVAT 12% added ";
                        printMoney(tax);

                        cout << "\nAmount to pay: PHP ";
                        printMoney(total);
                        cout << endl;

                        double amountPaid = 0;
                        bool cancelled = false;
                        bool firstTry = true;
                        int paidCentavos = 0;
                        int totalCentavos = (int)(total * 100 + 0.5);   // total in centavos, e.g. 71.68 becomes 7168
                        string paidText;

                        do
                        {
                            if (firstTry)
                            {
                                cout << "Enter amount paid: ";
                            }
                            else
                            {
                                cout << "Insufficient payment! Your order is still saved." << endl;
                                cout << "Enter amount paid again (0 to cancel): ";
                            }
                            firstTry = false;

                            cin >> paidText;

                            // Read the typed amount as centavos. Invalid input stays at -1.
                        int dots = 0;
                        bool valid = (paidText != "");
                        for (int k = 0; paidText[k] != '\0'; k++)
                        {
                            if (paidText[k] == '.')
                                dots++;
                            else if (paidText[k] < '0' || paidText[k] > '9')
                                valid = false;
                        }
                        if (dots > 1 || paidText == ".")
                            valid = false;

                        paidCentavos = -1;
                        if (valid)
                        {
                            int whole = 0;
                            int cents = 0;
                            int centDigits = 0;
                            bool afterDot = false;

                            for (int k = 0; paidText[k] != '\0'; k++)
                            {
                                if (paidText[k] == '.')
                                    afterDot = true;
                                else if (!afterDot)
                                    whole = whole * 10 + (paidText[k] - '0');
                                else if (centDigits < 2)
                                {
                                    cents = cents * 10 + (paidText[k] - '0');
                                    centDigits++;
                                }
                            }
                            if (centDigits == 1)
                                cents = cents * 10;   // "71.6" means 60 centavos


                            paidCentavos = whole * 100 + cents;
                        }

                        if (paidCentavos == 0)
                        {
                            cancelled = true;
                            break;
                        }

                        if (paidCentavos >= totalCentavos)
                        {
                            amountPaid = paidCentavos / 100.0;
                            break;
                        }
                    } while (true);

                        // Only print the receipt if the payment was not cancelled
                        if (cancelled == false)
                        {
                            double change = amountPaid - total;

                            cout << "\n=== ORDER RECEIPT ===" << endl;
                            for (int i = 0; i < 13; i++)
                            {
                                if (cartQty[i] > 0)
                                {
                                    cout << items[i] << " x" << cartQty[i] << endl;

                                    // Take the stock out and record the sale
                                    inventory[i] = inventory[i] - cartQty[i];
                                    soldQty[i] = soldQty[i] + cartQty[i];

                                    double lineSub = cartQty[i] * prices[i];
                                    double lineTotal = (lineSub - lineSub * appliedDisc) * (1 + taxRate);
                                    soldRevenue[i] = soldRevenue[i] + lineTotal;

                                    cartQty[i] = 0;   // clear the order
                                }
                            }

                            cout << "Subtotal: PHP ";
                            printMoney(subtotal);
                            cout << endl;

                            cout << "Discount: PHP ";
                            printMoney(discount);
                            cout << endl;

                            cout << "Tax (12%): PHP ";
                            printMoney(tax);
                            cout << endl;

                            cout << "Total: PHP ";
                            printMoney(total);
                            cout << endl;

                            cout << "Amount Paid: PHP ";
                            printMoney(amountPaid);
                            cout << endl;

                            cout << "Change: PHP ";
                            printMoney(change);
                            cout << endl;

                            cout << "Order placed successfully!" << endl;

                            totalOrders++;
                            totalSales = totalSales + total;
                        }
                    }
                }
                break;
            }
            // EMPLOYEE MANAGEMENT SYSTEM // - Admin only
            case '4':
            {
                if (currentRole != "Admin")
                {
                    cout << "Access Denied: Admins only." << endl;
                    break;
                }
                char userchoice;

                do
                {
                    cout << "\n===== USER MANAGEMENT SYSTEM =====" << endl;
                    cout << "1. View Users" << endl;
                    cout << "2. Add User" << endl;
                    cout << "3. Remove User" << endl;
                    cout << "0. Back to Main Menu" << endl;
                    cout << "Select: ";
                    cin >> userchoice;

                    switch (userchoice)
                    {
                        case '1':
                        {
                            cout << "\n===== EMPLOYEE LIST =====" << endl;
                            if (usercount == 0)
                            {
                                cout << "No users on file." << endl;
                            }
                            for (int i = 0; i < usercount; i++)
                            {
                                cout << (i + 1) << ". " << usernames[i] << endl;
                            }
                            cout << "--------------------------" << endl;
                            break;
                        }

                        case '2':
                        {
                            if (usercount >= maxusers)
                            {
                                cout << "User list is full. Cannot add more." << endl;
                            }
                            else
                            {
                                string newName;
                                cout << "Enter new user's name: ";
                                cin >> newName;

                                if (findAccountIndex(usernames, usercount, newName) != -1)
                                {
                                    cout << "That user already exists." << endl;
                                }
                                else
                                {
                                    usernames[usercount] = newName;
                                    usercount++;
                                    cout << "User added successfully!" << endl;
                                }
                            }
                            break;
                        }

                        case '3':
                        {
                            if (usercount == 0)
                            {
                                cout << "No users to remove." << endl;
                            }
                            else
                            {
                                string removeusers;
                                cout << "\n===== EMPLOYEE LIST =====" << endl;
                                for (int i = 0; i < usercount; i++)
                                {
                                    cout << (i + 1) << ". " << usernames[i] << endl;
                                }
                                cout << "Enter the name of the user to remove: ";
                                cin >> removeusers;

                                int idx = findAccountIndex(usernames, usercount, removeusers);

                                if (idx == -1)
                                {
                                    cout << "No such user found." << endl;
                                }
                                else
                                {
                                    // Shift everything after idx back by one to fill the gap
                                    // idx = index of the user to remove
                                    for (int i = idx; i < usercount - 1; i++)
                                    {
                                        usernames[i] = usernames[i + 1];
                                    }
                                    usercount--;
                                    cout << "User removed successfully!" << endl;
                                }
                            }
                            break;
                        }

                        case '0':
                            break;

                        default:
                            cout << "Invalid selection." << endl;
                    }
                } while (userchoice != '0');
                break;
            }
            // LOG OUT //
            case '0':
                cout << "Logging out " << currentRole << "...\n";
                break;

            default:
                cout << "Invalid selection." << endl;
        }

        } while (choice != '0');

        cout << "\nLog in as another user? (y/n): ";
        cin >> loginAgain;
    }

    cout << "Exiting POS system. Goodbye!" << endl;
    return 0;
}
