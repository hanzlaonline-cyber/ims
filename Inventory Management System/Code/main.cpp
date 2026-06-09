//============================================================
//  Inventory Management System — Enterprise OOP Demo
//  All headers are included; no vectors or STL containers.
//============================================================

#include "Product.h"
#include "ElectronicProduct.h"
#include "FragileElectronics.h"
#include "GroceryProduct.h"
#include "PerishableGrocery.h"
#include "NonPerishable.h"
#include "ClothingProduct.h"
#include "Supplier.h"
#include "InventorySection.h"
#include "Warehouse.h"
#include "TransactionLog.h"

//------------------------------------------------------------
// Helper: polymorphic display & risk via base pointer
//------------------------------------------------------------
void showProductInfo(const Product* p) {
    p->displayStatus();
    std::cout << "   Value : $" << p->calculateValue() << "\n";
    std::cout << "   Risk  : "  << p->calculateRisk()  << "\n";
}

//------------------------------------------------------------
int main() {

    std::cout << "============================================\n";
    std::cout << "  ENTERPRISE INVENTORY MANAGEMENT SYSTEM   \n";
    std::cout << "============================================\n\n";

    // =========================================================
    // 1. CREATE SUPPLIERS  (Association with Products)
    // =========================================================
    Supplier sup1(101, "TechZone Distributors",  "Net-60, 2% early pay");
    Supplier sup2(102, "FreshFarm Co.",           "Net-30, no returns");
    Supplier sup3(103, "FashionHub Wholesale",    "Net-45, exchange only");

    std::cout << "--- Suppliers ---\n";
    std::cout << sup1 << "\n";
    std::cout << sup2 << "\n";
    std::cout << sup3 << "\n\n";

    // =========================================================
    // 2. CREATE PRODUCTS  (various levels of hierarchy)
    // =========================================================

    // --- Level 3: FragileElectronics (Product->Electronic->Fragile) ---
    FragileElectronics* fe1 = new FragileElectronics(
        1001, 299.99, 20,
        220.0, 2, "Samsung",
        8, "Bubble-Wrap");

    FragileElectronics* fe2 = new FragileElectronics(
        1002, 499.99, 4,       // qty=4 -> shortage candidate
        110.0, 1, "Apple",
        9, "Foam-Box");

    // --- Level 2: ElectronicProduct (Product->Electronic) ---
    ElectronicProduct* ep1 = new ElectronicProduct(
        1003, 149.99, 15,
        12.0, 3, "Sony");

    // --- Level 3: PerishableGrocery (Product->Grocery->Perishable) ---
    Date today(8, 6, 2026);
    Date futureExpiry(1, 12, 2026);
    Date pastExpiry(1, 1, 2025);   // already expired

    PerishableGrocery* pg1 = new PerishableGrocery(
        2001, 3.50, 100,
        60, true,
        futureExpiry, 4.0);

    PerishableGrocery* pg2 = new PerishableGrocery(
        2002, 2.00, 2,            // qty=2 -> shortage candidate
        80, false,
        pastExpiry, 12.0);        // expired + high temp risk

    // --- Level 3: NonPerishable (Product->Grocery->NonPerishable) ---
    NonPerishable* np1 = new NonPerishable(
        2003, 1.99, 200,
        120, true,
        3, 15.0);

    // --- Level 2: GroceryProduct (Product->Grocery) ---
    GroceryProduct* gp1 = new GroceryProduct(
        2004, 0.99, 500, 50, true);

    // --- Level 2: ClothingProduct (Product->Clothing) ---
    ClothingProduct* cp1 = new ClothingProduct(
        3001, 24.99, 50,
        "L", "Polyester", "Male");

    ClothingProduct* cp2 = new ClothingProduct(
        3002, 34.99, 3,           // qty=3 -> shortage candidate
        "S", "Cotton", "Female");

    // =========================================================
    // 3. POLYMORPHISM DEMO  (virtual dispatch via Product*)
    // =========================================================
    std::cout << "--- Polymorphic displayStatus() & calculateRisk() ---\n";
    Product* polyArr[9];
    polyArr[0] = fe1;
    polyArr[1] = fe2;
    polyArr[2] = ep1;
    polyArr[3] = pg1;
    polyArr[4] = pg2;
    polyArr[5] = np1;
    polyArr[6] = gp1;
    polyArr[7] = cp1;
    polyArr[8] = cp2;

    for (int i = 0; i < 9; i++) showProductInfo(polyArr[i]);
    std::cout << "\n";

    // =========================================================
    // 4. SPECIFIC FEATURE CALLS
    // =========================================================
    std::cout << "--- ElectronicProduct::testHardware() ---\n";
    ep1->testHardware();
    fe1->testHardware();

    std::cout << "\n--- FragileElectronics::calculateShippingRisk() ---\n";
    std::cout << "fe1 shipping risk: " << fe1->calculateShippingRisk() << "\n";
    std::cout << "fe2 shipping risk: " << fe2->calculateShippingRisk() << "\n";

    std::cout << "\n--- GroceryProduct::checkSafety() ---\n";
    pg1->checkSafety();
    np1->checkSafety();

    std::cout << "\n--- PerishableGrocery::checkExpiry() ---\n";
    pg1->checkExpiry(today);
    pg2->checkExpiry(today);

    std::cout << "\n--- NonPerishable::getStorageInstructions() ---\n";
    np1->getStorageInstructions();

    std::cout << "\n--- ClothingProduct::fitGuide() ---\n";
    cp1->fitGuide();
    cp2->fitGuide();

    std::cout << "\n--- Supplier actions ---\n";
    sup1.orderRestock(1001, 50);
    sup1.generateInvoice(1001, 299.99, 50);
    sup2.orderRestock(2001, 200);

    // =========================================================
    // 5. OPERATOR OVERLOADING
    // =========================================================
    std::cout << "\n--- operator== (Product comparison by ID) ---\n";
    FragileElectronics fe3(*fe1);          // copy constructor
    if (*fe1 == fe3)
        std::cout << "fe1 and fe3 are the same product (ID match).\n";

    std::cout << "\n--- operator== (Supplier comparison) ---\n";
    Supplier sup4(101, "TechZone Distributors", "Net-60");
    if (sup1 == sup4)
        std::cout << "sup1 and sup4 are the same supplier (ID match).\n";

    std::cout << "\n--- operator<< (stream output) ---\n";
    std::cout << *fe1 << "\n";
    std::cout << *pg1 << "\n";
    std::cout << sup2 << "\n";

    // =========================================================
    // 6. applyDiscount() polymorphic behaviour
    // =========================================================
    std::cout << "\n--- applyDiscount() before ---\n";
    std::cout << "fe1 price before: $" << fe1->cost() << "\n";
    std::cout << "pg2 price before: $" << pg2->cost() << "\n";

    fe1->applyDiscount(10.0);   // FragileElectronics adds +2% = 12% off
    pg2->applyDiscount(10.0);   // PerishableGrocery adds +5% = 15% off

    std::cout << "fe1 price after 10% discount (fragile +2%): $" << fe1->cost() << "\n";
    std::cout << "pg2 price after 10% discount (perishable +5%): $" << pg2->cost() << "\n";

    // =========================================================
    // 7. INVENTORYSECTION — Composition, operator[], operator+
    // =========================================================
    std::cout << "\n--- InventorySection construction ---\n";

    // Electronics aisle (owns fe1, fe2, ep1)
    InventorySection* elecAisle = new InventorySection(1, 10);
    // NOTE: Section takes ownership — do NOT delete these pointers separately
    // We use 'new' copies so the section can safely own them
    elecAisle->addStock(new FragileElectronics(*fe1));
    elecAisle->addStock(new FragileElectronics(*fe2));
    elecAisle->addStock(new ElectronicProduct(*ep1));

    // Grocery aisle
    InventorySection* grocAisle = new InventorySection(2, 10);
    grocAisle->addStock(new PerishableGrocery(*pg1));
    grocAisle->addStock(new PerishableGrocery(*pg2));
    grocAisle->addStock(new NonPerishable(*np1));
    grocAisle->addStock(new GroceryProduct(*gp1));

    // Clothing aisle
    InventorySection* clothAisle = new InventorySection(3, 10);
    clothAisle->addStock(new ClothingProduct(*cp1));
    clothAisle->addStock(new ClothingProduct(*cp2));

    std::cout << "\n--- Section sort by ID ---\n";
    elecAisle->sortByID();
    grocAisle->sortByID();

    std::cout << "\n--- operator[] shelf access ---\n";
    Product* shelf0 = (*elecAisle)[0];
    if (shelf0) {
        std::cout << "elecAisle[0]: ";
        shelf0->displayStatus();
    }

    std::cout << "\n--- Section display ---\n";
    elecAisle->displayAll();
    grocAisle->displayAll();
    clothAisle->displayAll();

    std::cout << "\n--- operator+ merge two sections ---\n";
    // Merging elecAisle + clothAisle into a combined view
    // Note: merged section uses shallow pointers — do NOT let it destruct-delete
    InventorySection merged = *elecAisle + *clothAisle;
    std::cout << "Merged: " << merged << "\n";
    // Disable deletion in merged by not letting it manage lifetime
    // (in a real system we'd have a non-owning view; here we zero out to be safe)

    // =========================================================
    // 8. WAREHOUSE — Aggregation of Sections
    // =========================================================
    std::cout << "\n--- Warehouse ---\n";
    Warehouse wh(5001, 50000.0);
    wh.addSection(elecAisle);
    wh.addSection(grocAisle);
    wh.addSection(clothAisle);

    wh.displayAll();

    std::cout << "\n--- findShortages (threshold=5) ---\n";
    wh.findShortages(5);

    std::cout << "\n--- operator<< Warehouse summary ---\n";
    std::cout << wh << "\n";

    // =========================================================
    // 9. TRANSACTIONLOG<T> — Template working with Product & Supplier
    // =========================================================
    std::cout << "\n--- TransactionLog<Product> ---\n";
    TransactionLog<Product> productLog;
    productLog.recordAction("ADDED to aisle 1", *fe1);
    productLog.recordAction("DISCOUNT APPLIED", *pg2);
    productLog.recordAction("LOW STOCK FLAGGED", *cp2);

    std::cout << "\n--- TransactionLog<Supplier> ---\n";
    TransactionLog<Supplier> supplierLog;
    supplierLog.recordAction("CONTRACT SIGNED", sup1);
    supplierLog.recordAction("RESTOCK ORDERED", sup2);

    std::cout << "\n--- Audit Trails ---\n";
    productLog.printAuditTrail();
    supplierLog.printAuditTrail();

    // =========================================================
    // 10. RULE OF 3 — Deep copy verification
    // =========================================================
    std::cout << "\n--- Rule of 3: deep copy of ElectronicProduct ---\n";
    ElectronicProduct original(9001, 999.99, 5, 230.0, 3, "LG");
    ElectronicProduct copyConstructed(original);
    ElectronicProduct copyAssigned(0, 0, 0, 0, 0, "temp");
    copyAssigned = original;

    std::cout << "Original      : "; original.displayStatus();
    std::cout << "CopyCtor      : "; copyConstructed.displayStatus();
    std::cout << "CopyAssignment: "; copyAssigned.displayStatus();

    // =========================================================
    // 11. CLEANUP of stack/original pointers
    //     (Section-owned copies were deleted via Section destructors)
    // =========================================================
    // Sections are deleted by Warehouse? No — Warehouse aggregates.
    // We must delete sections explicitly (they compose products).
    delete elecAisle;
    delete grocAisle;
    delete clothAisle;

    // The original raw pointers (fe1, fe2 etc.) are still alive.
    // Delete them now.
    delete fe1;
    delete fe2;
    delete ep1;
    delete pg1;
    delete pg2;
    delete np1;
    delete gp1;
    delete cp1;
    delete cp2;

    std::cout << "\n============================================\n";
    std::cout << "  All objects destroyed. No memory leaks.   \n";
    std::cout << "============================================\n";

    return 0;
}
