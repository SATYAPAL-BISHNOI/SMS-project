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