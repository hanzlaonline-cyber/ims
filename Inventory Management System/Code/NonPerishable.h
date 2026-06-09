#ifndef NONPERISHABLE_H
#define NONPERISHABLE_H

#include "GroceryProduct.h"

class NonPerishable : public GroceryProduct {
private:
    int    shelfLifeYears;
    double preservativeLevel;   // percentage (0-100)

public:
    NonPerishable(int id = 0, double price = 0.0, int qty = 0,
                  int cal = 0, bool halal = true,
                  int shelfLife = 1, double preservative = 0.0)
        : GroceryProduct(id, price, qty, cal, halal),
          shelfLifeYears(shelfLife), preservativeLevel(preservative) {}

    virtual ~NonPerishable() {}

    // Setters
    void setShelfLife(int s)          { if (s >= 0) shelfLifeYears = s;              }
    void setPreservativeLevel(double p) {
        if (p >= 0.0 && p <= 100.0) preservativeLevel = p;
    }

    // Getters
    int    getShelfLife()         const { return shelfLifeYears;    }
    double getPreservativeLevel() const { return preservativeLevel; }

    void getStorageInstructions() const {
        std::cout << "Non-Perishable ID " << id()
                  << " | Shelf Life: " << shelfLifeYears << " yr(s)"
                  << " | Preservative: " << preservativeLevel << "%"
                  << " | Store in cool, dry place.\n";
    }

    virtual double calculateRisk() const override {
        // Higher preservative = slightly elevated health risk score
        return GroceryProduct::calculateRisk() + preservativeLevel * 0.1;
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [NonPerishable | ShelfLife: " << shelfLifeYears
                  << " yr(s) | Preservative: " << preservativeLevel
                  << "% | Risk: " << calculateRisk() << "]\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const NonPerishable& n) {
        os << static_cast<const GroceryProduct&>(n)
           << " [ShelfLife: " << n.shelfLifeYears
           << "yr | Pres: " << n.preservativeLevel << "%]";
        return os;
    }
};

#endif // NONPERISHABLE_H
