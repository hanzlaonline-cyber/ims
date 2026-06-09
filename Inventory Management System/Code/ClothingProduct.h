#ifndef CLOTHINGPRODUCT_H
#define CLOTHINGPRODUCT_H

#include "Product.h"

class ClothingProduct : public Product {
private:
    char size[10];      // S, M, L, XL, etc.
    char fabric[50];
    char gender[15];    // Male, Female, Unisex

public:
    ClothingProduct(int id = 0, double price = 0.0, int qty = 0,
                    const char* sz = "M",
                    const char* fab = "Cotton",
                    const char* gen = "Unisex")
        : Product(id, price, qty)
    {
        strncpy(size,   sz,  9);  size[9]   = '\0';
        strncpy(fabric, fab, 49); fabric[49] = '\0';
        strncpy(gender, gen, 14); gender[14] = '\0';
    }

    virtual ~ClothingProduct() {}

    // Setters
    void setSize(const char* s)   { strncpy(size,   s,  9);  size[9]   = '\0'; }
    void setFabric(const char* f) { strncpy(fabric, f, 49); fabric[49] = '\0'; }
    void setGender(const char* g) { strncpy(gender, g, 14); gender[14] = '\0'; }

    // Getters
    const char* getSize()   const { return size;   }
    const char* getFabric() const { return fabric; }
    const char* getGender() const { return gender; }

    void fitGuide() const {
        std::cout << "Fit Guide for ID " << id()
                  << " | Size: " << size
                  << " | Fabric: " << fabric
                  << " | Gender: " << gender << "\n";
    }

    virtual void displayStatus() const override {
        std::cout << *this
                  << " [Clothing | Size: " << size
                  << " | Fabric: " << fabric
                  << " | Gender: " << gender << "]\n";
    }

    virtual double calculateRisk() const override {
        return 0.5;   // clothing has minimal inventory risk
    }

    friend std::ostream& operator<<(std::ostream& os, const ClothingProduct& c) {
        os << static_cast<const Product&>(c)
           << " [Size: " << c.size
           << " | Fabric: " << c.fabric
           << " | Gender: " << c.gender << "]";
        return os;
    }
};

#endif // CLOTHINGPRODUCT_H
