#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "InventorySection.h"

#define MAX_SECTIONS 20

// Warehouse AGGREGATES InventorySection objects (does NOT own/delete them)
class Warehouse {
private:
    int               locationID;
    double            totalSquareFootage;
    InventorySection* sections[MAX_SECTIONS];
    int               sectionCount;

public:
    Warehouse(int locID = 0, double sqft = 0.0)
        : locationID(locID), totalSquareFootage(sqft), sectionCount(0)
    {
        for (int i = 0; i < MAX_SECTIONS; i++) sections[i] = nullptr;
    }

    // No deep copy needed — Warehouse aggregates (does not own) sections
    ~Warehouse() {
        // Do NOT delete sections here — they are aggregated, not composed
    }

    // Setters
    void setLocationID(int id)          { locationID = id;           }
    void setSquareFootage(double sqft)  { if (sqft >= 0) totalSquareFootage = sqft; }

    // Getters
    int    getLocationID()       const { return locationID;         }
    double getSquareFootage()    const { return totalSquareFootage; }
    int    getSectionCount()     const { return sectionCount;       }

    bool addSection(InventorySection* sec) {
        if (sectionCount >= MAX_SECTIONS) {
            std::cout << "Warehouse " << locationID << ": max sections reached.\n";
            return false;
        }
        sections[sectionCount++] = sec;
        return true;
    }

    // Total value of all products across all sections
    double getGlobalValue() const {
        double total = 0.0;
        for (int i = 0; i < sectionCount; i++)
            total += sections[i]->totalSectionValue();
        return total;
    }

    // Flag sections where stock is below threshold
    void findShortages(int threshold = 5) const {
        std::cout << "=== Shortage Report (threshold=" << threshold << ") ===\n";
        bool found = false;
        for (int i = 0; i < sectionCount; i++) {
            for (int j = 0; j < sections[i]->getCount(); j++) {
                const Product* p = (*sections[i])[j];
                if (p && p->qty() < threshold) {
                    std::cout << "LOW STOCK -> ";
                    p->displayStatus();
                    found = true;
                }
            }
        }
        if (!found) std::cout << "No shortages detected.\n";
        std::cout << "=============================================\n";
    }

    // Display every section
    void displayAll() const {
        std::cout << "=== Warehouse " << locationID
                  << " (" << totalSquareFootage << " sqft) ===\n";
        for (int i = 0; i < sectionCount; i++) {
            sections[i]->displayAll();
        }
        std::cout << "Total Inventory Value: $" << getGlobalValue() << "\n";
        std::cout << "=============================================\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Warehouse& w) {
        os << "[Warehouse ID: " << w.locationID
           << " | " << w.totalSquareFootage << " sqft"
           << " | Sections: " << w.sectionCount
           << " | Global Value: $" << w.getGlobalValue() << "]";
        return os;
    }
};

#endif // WAREHOUSE_H
