                         // Shop Management System


#include <iostream>
#include <vector>

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