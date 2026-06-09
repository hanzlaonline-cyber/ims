#ifndef GROCERYPRODUCT_H
#define GROCERYPRODUCT_H

#include "Product.h"

class GroceryProduct : public Product {
private:
    int  calories;
    bool isHalal;

public:
    GroceryProduct(int id = 0, double price = 0.0, int qty = 0,
                   int cal = 0, bool halal = true)
        : Product(id, price, qty), calories(cal), isHalal(halal) {}

    virtual ~GroceryProduct() {}

    // Setters
    void setCalories(int c) { if (c >= 0) calories = c; }
    void setHalal(bool h)   { isHalal = h;               }

    // Getters
    int  getCalories() const { return calories; }
    bool getIsHalal()  const { return isHalal;  }

    void checkSafety() const {
        std::cout << "Safety check for grocery ID " << id()
                  << " | Calories: " << calories
                  << " | Halal: " << (isHalal ? "Yes" : "No") << "\n";
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [Grocery | Cal: " << calories
                  << " | Halal: " << (isHalal ? "Yes" : "No") << "]\n";
    }

    virtual double calculateRisk() const override {
        // Non-perishable grocery has minimal risk
        return 1.0;
    }

    friend std::ostream& operator<<(std::ostream& os, const GroceryProduct& g) {
        os << static_cast<const Product&>(g)
           << " [Cal: " << g.calories
           << " | Halal: " << (g.isHalal ? "Yes" : "No") << "]";
        return os;
    }
};

#endif // GROCERYPRODUCT_H
