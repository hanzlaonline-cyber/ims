#ifndef PERISHABLEGROCERY_H
#define PERISHABLEGROCERY_H

#include "GroceryProduct.h"

// Simple date structure (no <ctime> dependency)
struct Date {
    int day;
    int month;
    int year;

    Date(int d = 1, int m = 1, int y = 2025) : day(d), month(m), year(y) {}

    // Returns true if this date is before the other (i.e., expired relative to 'other')
    bool isBefore(const Date& other) const {
        if (year  != other.year)  return year  < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    void print() const {
        std::cout << day << "/" << month << "/" << year;
    }
};

class PerishableGrocery : public GroceryProduct {
private:
    Date   expiryDate;
    double storageTemp;   // in Celsius

public:
    PerishableGrocery(int id = 0, double price = 0.0, int qty = 0,
                      int cal = 0, bool halal = true,
                      Date expiry = Date(1, 1, 2025),
                      double temp = 4.0)
        : GroceryProduct(id, price, qty, cal, halal),
          expiryDate(expiry), storageTemp(temp) {}

    virtual ~PerishableGrocery() {}

    // Setters
    void setExpiryDate(const Date& d) { expiryDate = d;           }
    void setStorageTemp(double t)     { storageTemp = t;          }

    // Getters
    Date   getExpiryDate()  const { return expiryDate;  }
    double getStorageTemp() const { return storageTemp; }

    // Pass today's date to check expiry
    bool checkExpiry(const Date& today) const {
        if (expiryDate.isBefore(today)) {
            std::cout << "EXPIRED: Product ID " << id() << " expired on ";
            expiryDate.print();
            std::cout << "\n";
            return true;
        }
        std::cout << "Product ID " << id() << " is fresh. Expires on ";
        expiryDate.print();
        std::cout << "\n";
        return false;
    }

    virtual double calculateRisk() const override {
        // Risk rises as storage temp exceeds safe threshold (e.g., 8°C)
        double tempRisk = (storageTemp > 8.0) ? (storageTemp - 8.0) * 5.0 : 0.0;
        return GroceryProduct::calculateRisk() + tempRisk;
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [Perishable | Temp: " << storageTemp << "°C | Expiry: ";
        expiryDate.print();
        std::cout << " | Risk: " << calculateRisk() << "]\n";
    }

    virtual void applyDiscount(double pct) override {
        // Perishables near expiry get larger discount — add 5%
        GroceryProduct::applyDiscount(pct + 5.0);
    }

    friend std::ostream& operator<<(std::ostream& os, const PerishableGrocery& p) {
        os << static_cast<const GroceryProduct&>(p)
           << " [Temp: " << p.storageTemp << "C | Exp: "
           << p.expiryDate.day << "/" << p.expiryDate.month << "/" << p.expiryDate.year << "]";
        return os;
    }
};

#endif // PERISHABLEGROCERY_H
