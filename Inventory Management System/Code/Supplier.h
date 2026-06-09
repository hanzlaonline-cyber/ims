#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <cstring>

class Supplier {
private:
    int  supplierID;
    char supplierName[100];
    char contractTerms[200];

public:
    Supplier(int id = 0,
             const char* name  = "Unknown Supplier",
             const char* terms = "Standard 30-day net")
        : supplierID(id)
    {
        strncpy(supplierName,  name,  99);  supplierName[99]  = '\0';
        strncpy(contractTerms, terms, 199); contractTerms[199] = '\0';
    }

    // Setters
    void setSupplierID(int id)           { if (id >= 0) supplierID = id; }
    void setSupplierName(const char* n) {
        strncpy(supplierName, n, 99); supplierName[99] = '\0';
    }
    void setContractTerms(const char* t) {
        strncpy(contractTerms, t, 199); contractTerms[199] = '\0';
    }

    // Getters
    int         getSupplierID()    const { return supplierID;    }
    const char* getSupplierName()  const { return supplierName;  }
    const char* getContractTerms() const { return contractTerms; }

    void orderRestock(int productID, int quantity) const {
        std::cout << "Supplier [" << supplierName << "] restocking Product ID "
                  << productID << " with quantity " << quantity << "\n";
    }

    void generateInvoice(int productID, double unitPrice, int quantity) const {
        std::cout << "=== INVOICE ===\n"
                  << "Supplier  : " << supplierName << " (ID: " << supplierID << ")\n"
                  << "Product ID: " << productID << "\n"
                  << "Qty       : " << quantity << "\n"
                  << "Unit Price: $" << unitPrice << "\n"
                  << "Total     : $" << unitPrice * quantity << "\n"
                  << "Terms     : " << contractTerms << "\n"
                  << "===============\n";
    }

    bool operator==(const Supplier& other) const {
        return supplierID == other.supplierID;
    }

    friend std::ostream& operator<<(std::ostream& os, const Supplier& s) {
        os << "[Supplier ID: " << s.supplierID
           << " | Name: " << s.supplierName
           << " | Terms: " << s.contractTerms << "]";
        return os;
    }
};

#endif // SUPPLIER_H
