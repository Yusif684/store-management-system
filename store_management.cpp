#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int stock;
};

void showMenu() {
    cout << "\n=== STORE MANAGEMENT SYSTEM ===\n";
    cout << "1. Add Product\n";
    cout << "2. Process Sale\n";
    cout << "3. View Inventory\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

void addProduct(vector<Product>& inventory) {
    Product p;
    cout << "\nEnter Product ID: ";
    cin >> p.id;
    cin.ignore();

    cout << "Enter Product Name: ";
    getline(cin, p.name);

    cout << "Enter Price: ";
    cin >> p.price;

    cout << "Enter Stock Quantity: ";
    cin >> p.stock;

    if (p.price < 0 || p.stock < 0) {
        cout << "Error: Price and stock cannot be negative.\n";
        return;
    }

    inventory.push_back(p);
    cout << "Product added successfully.\n";
}

void processSale(vector<Product>& inventory) {
    if (inventory.empty()) {
        cout << "\nInventory is empty. Add products first.\n";
        return;
    }

    int id, quantity;
    cout << "\nEnter Product ID to sell: ";
    cin >> id;

    for (size_t i = 0; i < inventory.size(); ++i) {
        if (inventory[i].id == id) {
            cout << "Selected: " << inventory[i].name
                 << " | Available Stock: " << inventory[i].stock
                 << " | Price: " << fixed << setprecision(2) << inventory[i].price << "\n";
            cout << "Enter quantity to sell: ";
            cin >> quantity;

            if (quantity <= 0) {
                cout << "Invalid quantity.\n";
                return;
            }
            if (quantity > inventory[i].stock) {
                cout << "Insufficient stock! Only " << inventory[i].stock << " left.\n";
                return;
            }

            inventory[i].stock -= quantity;
            double total = quantity * inventory[i].price;
            cout << "Sale completed! Total amount: " << fixed << setprecision(2) << total << "\n";
            return;
        }
    }

    cout << "Product with ID " << id << " not found.\n";
}

void viewInventory(const vector<Product>& inventory) {
    if (inventory.empty()) {
        cout << "\nNo products in inventory.\n";
        return;
    }

    cout << "\n--- CURRENT INVENTORY ---\n";
    cout << left << setw(8) << "ID"
         << setw(22) << "Name"
         << setw(12) << "Price"
         << setw(10) << "Stock" << "\n";
    cout << string(52, '-') << "\n";

    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << left << setw(8) << inventory[i].id
             << setw(22) << inventory[i].name
             << setw(12) << fixed << setprecision(2) << inventory[i].price
             << setw(10) << inventory[i].stock << "\n";
    }
}

int main() {
    vector<Product> inventory;
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addProduct(inventory);
                break;
            case 2:
                processSale(inventory);
                break;
            case 3:
                viewInventory(inventory);
                break;
            case 0:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
