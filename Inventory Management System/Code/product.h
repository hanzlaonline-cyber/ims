#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <cstring>

class Product {
private:
    int    productID;
    double price;
    int    quantity;

protected:
    // Allow subclasses to read these
    int    getProductID() const { return productID; }
    double getPrice()     const { return price;     }
    int    getQuantity()  const { return quantity;  }

public:
    Product(int id = 0, double p = 0.0, int qty = 0)
        : productID(id), price(p), quantity(qty) {}

    virtual ~Product() {}

    // Setters with basic validation
    void setProductID(int id)    { if (id >= 0) productID = id; }
    void setPrice(double p)      { if (p >= 0)  price = p;      }
    void setQuantity(int qty)    { if (qty >= 0) quantity = qty; }

    // Public read accessors
    int    id()  const { return productID; }
    double cost() const { return price;   }
    int    qty()  const { return quantity; }

    virtual void   displayStatus()    const = 0;
    virtual double calculateValue()   const { return price * quantity; }
    virtual double calculateRisk()    const { return 0.0; }
    virtual void   applyDiscount(double pct) {
        if (pct > 0 && pct < 100) price -= price * (pct / 100.0);
    }

    // operator== compares by productID
    bool operator==(const Product& other) const {
        return productID == other.productID;
    }

    // operator<< for report generation
    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        os << "[Product ID: " << p.productID
           << " | Price: $" << p.price
           << " | Qty: "    << p.quantity << "]";
        return os;
    }
};

#endif // PRODUCT_H
