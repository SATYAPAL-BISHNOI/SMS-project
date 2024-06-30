                         // Shop Management System


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Product { // Class for prodect
public:
    int id;
    string name;
    double price;
    int quantity;

    Product(int id, string name, double price, int quantity)
        : id(id), name(name), price(price), quantity(quantity) {}
};


// Create Shop Class


class Shop {
private:
    vector<Product> inventory;
    int nextId;

    void loadFromFile() {
        ifstream infile("inventory.txt");
        if (!infile.is_open()) return;

        inventory.clear();
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            int id;
            string name;
            double price;
            int quantity;
            ss >> id >> name >> price >> quantity;
            inventory.emplace_back(id, name, price, quantity);
            if (id >= nextId) nextId = id + 1;
        }
        infile.close();
    }

    void saveToFile() {
        ofstream outfile("inventory.txt");
        for (const auto& product : inventory) {
            outfile << product.id << " " << product.name << " " << product.price << " " << product.quantity << endl;
        }
        outfile.close();
    }

public:
    Shop() : nextId(1) {
        loadFromFile();
    }

    ~Shop() {
        saveToFile();
    }

    void addProduct(string name, double price, int quantity) {
        Product newProduct(nextId++, name, price, quantity);
        inventory.push_back(newProduct);
        cout << "Product added successfully!" << endl;
        saveToFile();
    }

    void displayProducts() {
        cout << "ID\tName\tPrice\tQuantity" << endl;
        for (const auto& product : inventory) {
            cout << product.id << "\t" << product.name << "\t" << product.price << "\t" << product.quantity << endl;
        }
    }

    void updateProduct(int id, string name, double price, int quantity) {
        for (auto& product : inventory) {
            if (product.id == id) {
                product.name = name;
                product.price = price;
                product.quantity = quantity;
                cout << "Product updated successfully!" << endl;
                saveToFile();
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    void deleteProduct(int id) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->id == id) {
                inventory.erase(it);
                cout << "Product deleted successfully!" << endl;
                saveToFile();
                return;
            }
        }
        cout << "Product not found!" << endl;
    }
};


int main() {
    Shop shop;
    int choice;

    while (true) {
        cout << "1. Add Product" << endl;
        cout << "2. Display Products" << endl;
        cout << "3. Update Product" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double price;
            int quantity;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product price: ";
            cin >> price;
            cout << "Enter product quantity: ";
            cin >> quantity;
            shop.addProduct(name, price, quantity);
        } else if (choice == 2) {
            shop.displayProducts();
        } else if (choice == 3) {
            int id;
            string name;
            double price;
            int quantity;
            cout << "Enter product ID to update: ";
            cin >> id;
            cout << "Enter new product name: ";
            cin >> name;
            cout << "Enter new product price: ";
            cin >> price;
            cout << "Enter new product quantity: ";
            cin >> quantity;
            shop.updateProduct(id, name, price, quantity);
        } else if (choice == 4) {
            int id;
            cout << "Enter product ID to delete: ";
            cin >> id;
            shop.deleteProduct(id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
