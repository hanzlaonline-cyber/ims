#ifndef INVENTORYSECTION_H
#define INVENTORYSECTION_H

#include "Product.h"

// InventorySection COMPOSES Product pointers (owns them)
class InventorySection {
private:
    int      aisleNumber;
    int      capacity;
    Product** products;    // dynamic array of Product*
    int      count;

    // Bubble-sort products array by productID (ascending)
    void bubbleSort() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (products[j]->id() > products[j + 1]->id()) {
                    Product* tmp   = products[j];
                    products[j]   = products[j + 1];
                    products[j + 1] = tmp;
                }
            }
        }
    }

public:
    InventorySection(int aisle = 0, int cap = 10)
        : aisleNumber(aisle), capacity(cap), count(0)
    {
        products = new Product*[capacity];
        for (int i = 0; i < capacity; i++) products[i] = nullptr;
    }

    // Deep copy constructor
    InventorySection(const InventorySection& other)
        : aisleNumber(other.aisleNumber), capacity(other.capacity), count(other.count)
    {
        products = new Product*[capacity];
        for (int i = 0; i < capacity; i++)
            products[i] = other.products[i];   // shallow copy of pointers (aggregation view)
    }

    // Copy assignment
    InventorySection& operator=(const InventorySection& other) {
        if (this != &other) {
            delete[] products;
            aisleNumber = other.aisleNumber;
            capacity    = other.capacity;
            count       = other.count;
            products    = new Product*[capacity];
            for (int i = 0; i < capacity; i++)
                products[i] = other.products[i];
        }
        return *this;
    }

    ~InventorySection() {
        // Section owns the products (composition) — delete them
        for (int i = 0; i < count; i++) {
            delete products[i];
            products[i] = nullptr;
        }
        delete[] products;
    }

    // Setters
    void setAisleNumber(int a) { aisleNumber = a; }

    // Getters
    int getAisleNumber() const { return aisleNumber; }
    int getCapacity()    const { return capacity;    }
    int getCount()       const { return count;       }

    bool addStock(Product* p) {
        if (count >= capacity) {
            std::cout << "Aisle " << aisleNumber << " is full.\n";
            return false;
        }
        products[count++] = p;
        return true;
    }

    void sortByID() {
        bubbleSort();
        std::cout << "Aisle " << aisleNumber << " sorted by product ID.\n";
    }

    double totalSectionValue() const {
        double total = 0.0;
        for (int i = 0; i < count; i++)
            total += products[i]->calculateValue();
        return total;
    }

    // operator[] for shelf access by index
    Product* operator[](int index) {
        if (index < 0 || index >= count) {
            std::cout << "Index " << index << " out of range for aisle " << aisleNumber << "\n";
            return nullptr;
        }
        return products[index];
    }

    const Product* operator[](int index) const {
        if (index < 0 || index >= count) {
            std::cout << "Index " << index << " out of range for aisle " << aisleNumber << "\n";
            return nullptr;
        }
        return products[index];
    }

    // operator+ merges two sections into a new one (caller owns result)
    InventorySection operator+(const InventorySection& other) const {
        int newCap = capacity + other.capacity;
        InventorySection merged(aisleNumber, newCap);
        // Shallow-copy pointers only (merged is an aggregated view)
        for (int i = 0; i < count; i++)
            merged.products[merged.count++] = products[i];
        for (int i = 0; i < other.count; i++)
            merged.products[merged.count++] = other.products[i];
        return merged;
    }

    void displayAll() const {
        std::cout << "--- Aisle " << aisleNumber
                  << " (" << count << "/" << capacity << " slots) ---\n";
        for (int i = 0; i < count; i++)
            products[i]->displayStatus();
    }

    friend std::ostream& operator<<(std::ostream& os, const InventorySection& sec) {
        os << "Aisle " << sec.aisleNumber
           << " | Capacity: " << sec.capacity
           << " | Items: " << sec.count
           << " | Value: $" << sec.totalSectionValue();
        return os;
    }
};

#endif // INVENTORYSECTION_H
