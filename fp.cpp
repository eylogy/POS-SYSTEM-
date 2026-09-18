#include <iostream>
using namespace std;

const int maxusers = 20;

// Role is one of: "Admin", "Supervisor", "Cashier"
string accountUser[maxusers] = {"admin", "supervisor", "cashier"};
string accountPass[maxusers] = {"Group5", "Group5", "Group5"};
string accountRole[maxusers] = {"Admin", "Supervisor", "Cashier"};
int accountCount = 3;

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

// ADMIN for the inventory system//
void admin(string items[], int inventory[]) {

    int pick;
    char again3;

    do
    {
        cout << "\n===== INVENTORY =====" << endl;
        for (int i = 0; i < 3; i++) {
            cout << (i + 1) << ". " << items[i] <<endl;
        }
        cout << "Check Product: ";
        cin >> pick;

        int idx = pick - 1;
        if (idx >= 0 && idx < 3)
        {
            cout << items[idx] << ": " << inventory[idx] << " Pc(s) remaining." << endl;
        }
        else
        {
            cout << "Invalid Input " << endl;
        }

        cout << "\nCheck another product? (y/n): ";
        cin >> again3;

    } while (again3 == 'y' || again3 == 'Y');
}

// SUPERVISOR for the monitoring system//
void supervisor(string items[], double soldRevenue[], int soldQty[], int totalOrders, double totalSales) {

    cout << "\n===== SALES MONITORING =====" << endl;
    for (int i = 0; i < 3; i++) {
        cout << items[i] << " - Sold: " << soldQty[i] << " pc(s) | Revenue: PHP " << soldRevenue[i] << endl;
    }
    cout << "-----------------------------" << endl;
    cout << "Total Orders Placed: " << totalOrders << endl;
    cout << "Total Sales: PHP " << totalSales << endl;
    cout << "=============================" << endl;
}

// CASHIER for the ordering system //
void cashier(string items[], double prices[], int inventory[], double discRate, double taxRate, int &totalOrders, double &totalSales, int soldQty[], double soldRevenue[]) {

    char orderAgain;

    do
    {
        int order;
        int quantity;
        char discountAnswer;
        string chosenItem = "";
        int index = -1;
        double subtotal = 0;
        double discount = 0;
        double tax = 0;
        double total = 0;
        double amountPaid = 0;
        double change = 0;

        cout << "\n==== MENU ====" << endl;
        for (int i = 0; i < 3; i++) {
            cout << (i + 1) << ". " << items[i] << " - PHP " << prices[i] << endl;
        }

        cout << "Enter your choice: ";
        cin >> order;

        switch (order)
        {
            case 1:
            case 2:
            case 3:
                index = order - 1;
                chosenItem = items[index];
                break;

            default:
                cout << "Invalid item number." << endl;
        }

        if (index != -1)
        {
            cout << "Enter Quantity: ";
            cin >> quantity;

            if (quantity <= 0)
            {
                cout << "Quantity must be more than 0!" << endl;
            }
            else if (quantity > inventory[index])
            {
                cout << "Error: Not enough stock available! Current Stock: " << inventory[index] << endl;
            }
            else
            {
                subtotal = quantity * prices[index];

                cout << "Are you a Senior Citizen/PWD? (y/n): ";
                cin >> discountAnswer;

                if (discountAnswer == 'y' || discountAnswer == 'Y')
                {
                    discount = subtotal * discRate;
                }

                tax = (subtotal - discount) * taxRate;
                total = subtotal - discount + tax;

                cout << "Amount to pay: PHP " << total << endl;
                cout << "Enter amount paid: ";
                cin >> amountPaid;

                if (amountPaid < total)
                {
                    cout << "Insufficient payment!" << endl;
                }
                else
                {
                    change = amountPaid - total;

                    inventory[index] -= quantity;

                    cout << "\n=== ORDER RECEIPT ===" << endl;
                    cout << "Item: " << chosenItem << endl;
                    cout << "Quantity: " << quantity << endl;
                    cout << "Subtotal: PHP " << subtotal << endl;
                    cout << "Discount: PHP " << discount << endl;
                    cout << "Tax (12%): PHP " << tax << endl;
                    cout << "Total: PHP " << total << endl;
                    cout << "Amount Paid: PHP " << amountPaid << endl;
                    cout << "Change: PHP " << change << endl;
                    cout << "Order placed successfully!" << endl;

                    totalOrders++;
                    totalSales = totalSales + total;

                    soldQty[index] = soldQty[index] + quantity;
                    soldRevenue[index] = soldRevenue[index] + total;
                }
            }
        }

        cout << "\nProcess another order? (y/n): ";
        cin >> orderAgain;

    } while (orderAgain == 'y' || orderAgain == 'Y');
}

// Find the index of an employee name in the array. Returns -1 if not found.
int findEmployeeIndex(string usernames[], int usercount, string name)
{
    for (int i = 0; i < usercount; i++)
    {
        if (usernames[i] == name)
            return i;
    }
    return -1;
}

// Find the index of an account by username. Returns -1 if not found.
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
    // Declared here (outside the login loop) so inventory, sales, and
    // employee records persist even after logging out and logging back in.
    string items[] = {"Beef Tapa", "Longganisa", "Corned Beef"};
    double prices[] = {45, 35, 50};
    int inventory[] = {100, 100, 100};

    double discRate = 0.20;
    double taxRate = 0.12;

    int soldQty[] = {0, 0, 0};
    double soldRevenue[] = {0, 0, 0};
    int totalOrders = 0;
    double totalSales = 0;

    char loginAgain = 'y';

    // Keep the whole system running so a new user can log in after someone logs out
    while (loginAgain == 'y' || loginAgain == 'Y')
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

        int choice;

        // Keep this user's session running until they log out
        do
        {
            showMenu(currentRole);
            cin >> choice;

            switch (choice)
            {
            // MONITORING // - Supervisor only
            case 1:
            {
                if (currentRole != "Supervisor")
                {
                    cout << "Access Denied: Supervisors only." << endl;
                    break;
                }

                supervisor(items, soldRevenue, soldQty, totalOrders, totalSales);
                break;
            }

            // VIEW INVENTORY // - Admin only
            case 2:
            {
                if (currentRole != "Admin")
                {
                    cout << "Access Denied: Admins only." << endl;
                    break;
                }

                admin(items, inventory);
                break;
            }

            // ORDER SYSTEM // - Cashier only
            case 3:
            {
                if (currentRole != "Cashier")
                {
                    cout << "Access Denied: Cashiers only." << endl;
                    break;
                }

                cashier(items, prices, inventory, discRate, taxRate, totalOrders, totalSales, soldQty, soldRevenue);
                break;
            }

            // EMPLOYEE MANAGEMENT SYSTEM // - Admin only
            case 4:
            {
                if (currentRole != "Admin")
                {
                    cout << "Access Denied: Admins only." << endl;
                    break;
                }

                int userchoice;

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
                        case 1:
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

                        case 2:
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

                                if (findEmployeeIndex(usernames, usercount, newName) != -1)
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

                        case 3:
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

                                int idx = findEmployeeIndex(usernames, usercount, removeusers);

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

                        case 0:
                            break;

                        default:
                            cout << "Invalid selection." << endl;
                    }

                } while (userchoice != 0);

                break;
            }

            // LOG OUT //
            case 0:
                cout << "Logging out " << currentRole << "...\n";
                break;

            default:
                cout << "Invalid selection." << endl;
        }

        } while (choice != 0);

        cout << "\nLog in as another user? (y/n): ";
        cin >> loginAgain;
    }

    cout << "Exiting POS system. Goodbye!" << endl;
    return 0;
}