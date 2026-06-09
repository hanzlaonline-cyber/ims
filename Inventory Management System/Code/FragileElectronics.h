#ifndef FRAGILEELECTRONICS_H
#define FRAGILEELECTRONICS_H

#include "ElectronicProduct.h"

class FragileElectronics : public ElectronicProduct {
private:
    int  fragilityRating;   // 1 (low) to 10 (extreme)
    char packagingType[50];

public:
    FragileElectronics(int id = 0, double price = 0.0, int qty = 0,
                       double volt = 0.0, int warranty = 0,
                       const char* brand = "Unknown",
                       int fragility = 5,
                       const char* packaging = "Standard")
        : ElectronicProduct(id, price, qty, volt, warranty, brand),
          fragilityRating(fragility)
    {
        strncpy(packagingType, packaging, 49);
        packagingType[49] = '\0';
    }

    // Copy constructor
    FragileElectronics(const FragileElectronics& other)
        : ElectronicProduct(other), fragilityRating(other.fragilityRating)
    {
        strncpy(packagingType, other.packagingType, 49);
        packagingType[49] = '\0';
    }

    // Copy assignment
    FragileElectronics& operator=(const FragileElectronics& other) {
        if (this != &other) {
            ElectronicProduct::operator=(other);
            fragilityRating = other.fragilityRating;
            strncpy(packagingType, other.packagingType, 49);
            packagingType[49] = '\0';
        }
        return *this;
    }

    virtual ~FragileElectronics() {}

    // Setters
    void setFragilityRating(int r) {
        if (r >= 1 && r <= 10) fragilityRating = r;
    }
    void setPackagingType(const char* p) {
        strncpy(packagingType, p, 49);
        packagingType[49] = '\0';
    }

    // Getters
    int         getFragilityRating() const { return fragilityRating; }
    const char* getPackagingType()   const { return packagingType;   }

    double calculateShippingRisk() const {
        return fragilityRating * 10.0 + ElectronicProduct::calculateRisk();
    }

    // Override polymorphic methods
    virtual double calculateRisk() const override {
        return calculateShippingRisk();
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [FragileElectronics | Fragility: " << fragilityRating
                  << "/10 | Packaging: " << packagingType
                  << " | Shipping Risk: " << calculateShippingRisk() << "]\n";
    }

    virtual void applyDiscount(double pct) override {
        // Fragile items get an extra 2% off for handling inconvenience
        ElectronicProduct::applyDiscount(pct + 2.0);
    }

    friend std::ostream& operator<<(std::ostream& os, const FragileElectronics& f) {
        os << static_cast<const ElectronicProduct&>(f)
           << " [Fragility: " << f.fragilityRating
           << " | Pkg: " << f.packagingType << "]";
        return os;
    }
};

#endif // FRAGILEELECTRONICS_H
