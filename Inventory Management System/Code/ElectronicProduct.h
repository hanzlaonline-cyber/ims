#ifndef ELECTRONICPRODUCT_H
#define ELECTRONICPRODUCT_H

#include "Product.h"

class ElectronicProduct : public Product {
private:
    double  voltage;
    int     warrantyYears;
    char*   brandName;      // pointer member -> Rule of 3

public:
    ElectronicProduct(int id = 0, double price = 0.0, int qty = 0,
                      double volt = 0.0, int warranty = 0,
                      const char* brand = "Unknown")
        : Product(id, price, qty), voltage(volt), warrantyYears(warranty)
    {
        brandName = new char[strlen(brand) + 1];
        strcpy(brandName, brand);
    }

    // Copy constructor (Rule of 3)
    ElectronicProduct(const ElectronicProduct& other)
        : Product(other), voltage(other.voltage), warrantyYears(other.warrantyYears)
    {
        brandName = new char[strlen(other.brandName) + 1];
        strcpy(brandName, other.brandName);
    }

    // Copy assignment (Rule of 3)
    ElectronicProduct& operator=(const ElectronicProduct& other) {
        if (this != &other) {
            Product::operator=(other);
            voltage      = other.voltage;
            warrantyYears = other.warrantyYears;
            delete[] brandName;
            brandName = new char[strlen(other.brandName) + 1];
            strcpy(brandName, other.brandName);
        }
        return *this;
    }

    // Destructor (Rule of 3)
    virtual ~ElectronicProduct() {
        delete[] brandName;
    }

    // Setters
    void setVoltage(double v)       { if (v > 0) voltage = v;            }
    void setWarranty(int w)         { if (w >= 0) warrantyYears = w;     }
    void setBrand(const char* b) {
        delete[] brandName;
        brandName = new char[strlen(b) + 1];
        strcpy(brandName, b);
    }

    // Getters
    double      getVoltage()  const { return voltage;       }
    int         getWarranty() const { return warrantyYears; }
    const char* getBrand()    const { return brandName;     }

    void testHardware() const {
        std::cout << "Testing hardware for brand: " << brandName
                  << " | Voltage: " << voltage << "V"
                  << " | Warranty: " << warrantyYears << " yr(s)\n";
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [Electronic | Brand: " << brandName
                  << " | Voltage: " << voltage << "V"
                  << " | Warranty: " << warrantyYears << " yr(s)]\n";
    }

    virtual double calculateRisk() const override {
        // Base risk for electronics: higher voltage = more risk
        return voltage * 0.05;
    }

    friend std::ostream& operator<<(std::ostream& os, const ElectronicProduct& e) {
        os << static_cast<const Product&>(e)
           << " [Brand: " << e.brandName << "]";
        return os;
    }
};

#endif // ELECTRONICPRODUCT_H
