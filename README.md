# Enterprise Inventory Management System

A fully object‑oriented C++ application that simulates a large‑scale warehouse managing **electronics, groceries, and apparel**. Built as an open‑ended lab project for an OOP course.

## 🧠 Key OOP Features

- **Deep inheritance** – 3+ levels (`Product` → `ElectronicProduct` → `FragileElectronics`, etc.)
- **Polymorphism** – virtual dispatch for `displayStatus()`, `checkRisk()`, `applyDiscount()`, `saveToFile()`, `clone()`
- **Encapsulation** – all data private/protected, validated setters
- **Composition** – `InventorySection` owns and deletes its `Product*` array
- **Aggregation** – `Warehouse` holds sections with optional ownership
- **Rule of Three** – implemented in `ElectronicProduct` (char* brand) and `InventorySection` (Product**)
- **Operator overloading** – `[]`, `+` (merge warehouses), `<<` for reports
- **Templates** – `TransactionLog<T>` for audit trails (string, Supplier)
- **Manual memory management** – raw pointers, `new`/`delete`, no STL containers
- **File persistence** – saves/loads inventory to `inventory_data.txt`

## 📁 Project Structure
