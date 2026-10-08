#include<iostream>
#include<string>
#include<vector>
using namespace std;

// =============================================================
//  FOREIGNS & LOCALS WAREHOUSE MANAGEMENT SYSTEM
//  Days 1-3 Complete:
//   Day 1 — Product class + auto ID generation
//   Day 2 — InventoryItem hierarchy + Person hierarchy
//   Day 3 — Order hierarchy (CustomerOrder + ReturnOrder)
// =============================================================


// =============================================================
// CLASS 1: Product
// Responsibility: store product details & auto-generate an ID
// OOP: Encapsulation — generateID() is private, price/flags hidden
// =============================================================
class Product {
private:
    string product_ID;
    string product_name;
    string product_type;
    string size;
    string color;
    double price;
    bool isHazardous;
    bool isPerishable;
    bool isFragile;

    // Private helper — ID logic hidden from outside (Encapsulation)
    string generateID() {
        string flags = "";
        if (isHazardous)  flags += "H";
        if (isPerishable) flags += "P";
        if (isFragile)    flags += "F";
        if (flags == "")  flags = "STD";
        return product_type + "-" + size + "-" + color + "-" + flags;
    }

public:
    Product(string name, string type, string s, string c,
            double p, bool hazardous, bool perishable, bool fragile) {
        product_name  = name;
        product_type  = type;
        size          = s;
        color         = c;
        price         = p;
        isHazardous   = hazardous;
        isPerishable  = perishable;
        isFragile     = fragile;
        product_ID    = generateID();
    }

    string getProductID()   const { return product_ID;   }
    string getProductName() const { return product_name; }
    string getProductType() const { return product_type; }
    double getPrice()       const { return price;        }

    void display() const {
        cout << "Product ID:    " << product_ID    << endl;
        cout << "Product Name:  " << product_name  << endl;
        cout << "Product Type:  " << product_type  << endl;
        cout << "Product Size:  " << size          << endl;
        cout << "Product Color: " << color         << endl;
        cout << "Product Price: $" << price        << endl;
    }
};


// =============================================================
// CLASS 2: InventoryItem  (Abstract Base Class)
// OOP: Abstraction — getItemType() is pure virtual, cannot
//      instantiate InventoryItem directly
// =============================================================
class InventoryItem {
protected:
    string product_ID;
    string product_name;
    int    quantity;
    string location;
    string size;
    bool   isHazardous;
    bool   isPerishable;
    bool   isFragile;

public:
    InventoryItem(string id, string name, int q, string loc,
                  string s, bool hazardous, bool perishable, bool fragile) {
        product_ID   = id;
        product_name = name;
        quantity     = q;
        location     = loc;
        size         = s;
        isHazardous  = hazardous;
        isPerishable = perishable;
        isFragile    = fragile;
    }

    // Pure virtual — Abstraction: forces subclasses to identify themselves
    virtual string getItemType() const = 0;

    // Virtual display — Polymorphism: each subclass overrides this
    virtual void displayItem() const {
        cout << "-----Inventory Status-----" << endl;
        cout << "Type:       " << getItemType() << endl;
        cout << "Name:       " << product_name  << endl;
        cout << "ID:         " << product_ID    << endl;
        cout << "Stock:      " << quantity      << endl;
        cout << "Location:   " << location      << endl;
        cout << "Size:       " << size          << endl;
        cout << "Hazardous:  " << (isHazardous  ? "Yes" : "No") << endl;
        cout << "Perishable: " << (isPerishable ? "Yes" : "No") << endl;
        cout << "Fragile:    " << (isFragile    ? "Yes" : "No") << endl;
    }

    string getID()        const { return product_ID;   }
    string getProductID() const { return product_ID;   }
    string getName()      const { return product_name; }
    int    getQuantity()  const { return quantity;     }
    void   setQuantity(int q)   { quantity = q;        }

    virtual ~InventoryItem() {}
};


// =============================================================
// CLASS 3: PerishableItem  (Child of InventoryItem)
// OOP: Inheritance — reuses InventoryItem, adds expiry date
// =============================================================
class PerishableItem : public InventoryItem {
private:
    string expiration_date;

public:
    PerishableItem(string id, string name, int q, string loc,
                   string s, bool hazardous, bool fragile, string exp_date)
        : InventoryItem(id, name, q, loc, s, hazardous, true, fragile) {
        expiration_date = exp_date;
    }

    string getItemType() const override { return "Perishable"; }

    void displayItem() const override {
        InventoryItem::displayItem();
        cout << "Expiry Date: " << expiration_date << endl;
        cout << "--------------------------" << endl;
    }
};


// =============================================================
// CLASS 4: NonPerishableItem  (Child of InventoryItem)
// OOP: Inheritance — reuses InventoryItem, no expiry needed
// =============================================================
class NonPerishableItem : public InventoryItem {
public:
    NonPerishableItem(string id, string name, int q, string loc,
                      string s, bool haz, bool frag)
        : InventoryItem(id, name, q, loc, s, haz, false, frag) {}

    string getItemType() const override { return "Non-Perishable"; }

    void displayItem() const override {
        InventoryItem::displayItem();
        cout << "--------------------------" << endl;
    }
};


// =============================================================
// CLASS 5: Person  (Abstract Base Class)
// OOP: Abstraction — display() and getRole() are pure virtual
// =============================================================
class Person {
protected:
    int    id;
    string name;
    string contact;

public:
    Person(int i, string n, string c) : id(i), name(n), contact(c) {}

    virtual void   display() const = 0;
    virtual string getRole() const = 0;

    string getName() const { return name; }
    int    getID()   const { return id;   }

    virtual ~Person() {}
};


// =============================================================
// CLASS 6: Employee  (Child of Person)
// OOP: Inheritance + Polymorphism — overrides display()/getRole()
// =============================================================
class Employee : public Person {
private:
    string role;
    double salary;
    string department;

public:
    Employee(int i, string n, string c, string r, double s,
             string dept = "General")
        : Person(i, n, c), role(r), salary(s), department(dept) {}

    string getRole() const override { return role; }

    void display() const override {
        cout << "ID: "         << id
             << " | Staff: "   << name
             << " | Role: "    << role
             << " | Dept: "    << department
             << " | Salary: $" << salary << endl;
    }

    double getSalary() const { return salary; }
};


// =============================================================
// CLASS 7: Customer  (Child of Person)
// OOP: Inheritance + Polymorphism — overrides display()/getRole()
// =============================================================
class Customer : public Person {
private:
    string address;
    double credit_limit;

public:
    Customer(int i, string n, string c, string addr, double credit)
        : Person(i, n, c), address(addr), credit_limit(credit) {}

    string getRole() const override { return "Customer"; }

    void display() const override {
        cout << "ID: "               << id
             << " | Customer: "      << name
             << " | Contact: "       << contact
             << " | Address: "       << address
             << " | Credit Limit: $" << credit_limit << endl;
    }
};


// =============================================================
// CLASS 8: Order  (Abstract Base Class)              [DAY 3]
// OOP: Abstraction — processOrder() and displayOrder() are
//      pure virtual; forces subclasses to implement their
//      own order logic
// =============================================================
class Order {
protected:
    string orderID;
    string date;
    string productID;
    int    quantity;
    string status;   // "Pending", "Processed", "Cancelled"

public:
    Order(string oID, string d, string pID, int q)
        : orderID(oID), date(d), productID(pID),
          quantity(q), status("Pending") {}

    // Pure virtual — Abstraction
    virtual void processOrder(vector<InventoryItem*>& inventory) = 0;
    virtual void displayOrder() const = 0;

    // Shared getters
    string getOrderID()   const { return orderID;   }
    string getProductID() const { return productID; }
    string getStatus()    const { return status;    }
    void   setStatus(string s)  { status = s;       }

    virtual ~Order() {}
};


// =============================================================
// CLASS 9: CustomerOrder  (Child of Order)           [DAY 3]
// OOP: Inheritance — reuses Order base
//      Polymorphism — overrides processOrder() and displayOrder()
//      with customer-specific logic (deduct stock)
// =============================================================
class CustomerOrder : public Order {
private:
    string customerName;
    string deliveryAddress;
    double totalCost;

public:
    CustomerOrder(string oID, string d, string pID, int q,
                  string custName, string addr, double cost)
        : Order(oID, d, pID, q),
          customerName(custName), deliveryAddress(addr), totalCost(cost) {}

    void processOrder(vector<InventoryItem*>& inventory) override {
        for (InventoryItem* item : inventory) {
            if (item->getProductID() == this->productID) {
                if (this->quantity > item->getQuantity()) {
                    status = "Cancelled";
                    cout << "[ORDER] FAILED — Insufficient stock for: "
                         << productID << endl;
                } else {
                    item->setQuantity(item->getQuantity() - this->quantity);
                    status = "Processed";
                    cout << "[ORDER] SUCCESS — Dispatched "
                         << quantity << "x " << productID
                         << " to " << deliveryAddress
                         << ". Remaining stock: "
                         << item->getQuantity() << endl;
                }
                return;
            }
        }
        status = "Cancelled";
        cout << "[ORDER] ERROR — Product ID not found: " << productID << endl;
    }

    void displayOrder() const override {
        cout << "------------------------------"       << endl;
        cout << "[Customer Order]"                     << endl;
        cout << "Order ID:    " << orderID             << endl;
        cout << "Date:        " << date                << endl;
        cout << "Product ID:  " << productID           << endl;
        cout << "Quantity:    " << quantity            << endl;
        cout << "Customer:    " << customerName        << endl;
        cout << "Deliver to:  " << deliveryAddress     << endl;
        cout << "Total Cost:  $" << totalCost          << endl;
        cout << "Status:      " << status              << endl;
        cout << "------------------------------"       << endl;
    }
};


// =============================================================
// CLASS 10: ReturnOrder  (Child of Order)            [DAY 3]
// OOP: Inheritance — reuses Order base
//      Polymorphism — overrides processOrder() and displayOrder()
//      with return-specific logic (restore stock + approval)
// =============================================================
class ReturnOrder : public Order {
private:
    string returnReason;
    string approvalStatus;  // "Pending", "Approved", "Rejected"

public:
    ReturnOrder(string oID, string d, string pID, int q, string reason)
        : Order(oID, d, pID, q),
          returnReason(reason), approvalStatus("Pending") {}

    // Approve or reject the return
    void approve() {
        approvalStatus = "Approved";
        cout << "[RETURN] Order " << orderID << " APPROVED." << endl;
    }
    void reject() {
        approvalStatus = "Rejected";
        cout << "[RETURN] Order " << orderID << " REJECTED." << endl;
    }

    // processOrder — restores stock to inventory on approval
    void processOrder(vector<InventoryItem*>& inventory) override {
        if (approvalStatus != "Approved") {
            cout << "[RETURN] Cannot process — approval status is: "
                 << approvalStatus << ". Call approve() first." << endl;
            return;
        }
        for (InventoryItem* item : inventory) {
            if (item->getProductID() == this->productID) {
                item->setQuantity(item->getQuantity() + this->quantity);
                status = "Processed";
                cout << "[RETURN] Stock restored — "
                     << quantity << "x " << productID
                     << " returned to inventory. New stock: "
                     << item->getQuantity() << endl;
                return;
            }
        }
        cout << "[RETURN] ERROR — Product ID not found: " << productID << endl;
    }

    void displayOrder() const override {
        cout << "------------------------------"         << endl;
        cout << "[Return Order]"                         << endl;
        cout << "Order ID:        " << orderID          << endl;
        cout << "Date:            " << date             << endl;
        cout << "Product ID:      " << productID        << endl;
        cout << "Quantity:        " << quantity         << endl;
        cout << "Return Reason:   " << returnReason     << endl;
        cout << "Approval Status: " << approvalStatus   << endl;
        cout << "Order Status:    " << status           << endl;
        cout << "------------------------------"         << endl;
    }

    string getApprovalStatus() const { return approvalStatus; }
};


// =============================================================
//  MAIN — Checkpoint Demos + Interactive Menu
// =============================================================
int main() {

    // -----------------------------------------------------------
    // CHECKPOINT A: InventoryItem Polymorphism
    // Same displayItem() call → different output per subclass
    // -----------------------------------------------------------
    cout << "========================================" << endl;
    cout << "  CHECKPOINT A: InventoryItem Hierarchy " << endl;
    cout << "  Polymorphism via InventoryItem* ptr   " << endl;
    cout << "========================================" << endl;

    vector<InventoryItem*> demoInventory;
    demoInventory.push_back(
        new PerishableItem("FOOD-M-WHT-P", "Maize Flour",
                           50, "Fridge-A1", "M", false, false, "2026-12-01"));
    demoInventory.push_back(
        new NonPerishableItem("CHEM-S-CLR-H", "Battery Acid",
                              10, "Aisle-B3", "S", true, false));

    for (InventoryItem* item : demoInventory)
        item->displayItem();  // Polymorphism ✓

    // -----------------------------------------------------------
    // CHECKPOINT B: Person Polymorphism
    // Same display()/getRole() call → different output per subclass
    // -----------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "  CHECKPOINT B: Person Hierarchy        " << endl;
    cout << "  Polymorphism via Person* ptr          " << endl;
    cout << "========================================" << endl;

    vector<Person*> people;
    people.push_back(new Customer(101, "Wanjiku Njoroge", "0712345678",
                                  "Githurai 45", 50000.0));
    people.push_back(new Customer(102, "Otieno Mwangi",  "0723456789",
                                  "Industrial Area", 200000.0));
    people.push_back(new Employee(201, "James Kamau",    "0734567890",
                                  "Manager", 85000.0, "Management"));
    people.push_back(new Employee(202, "Aisha Omondi",   "0745678901",
                                  "QC Inspector", 35000.0, "Quality Control"));

    for (Person* p : people) {
        p->display();
        cout << "  → getRole(): \"" << p->getRole() << "\"" << endl;
    }

    // -----------------------------------------------------------
    // CHECKPOINT C: Order Hierarchy Polymorphism       [DAY 3]
    // 2x CustomerOrder + 1x ReturnOrder via Order* pointer
    // Same processOrder() & displayOrder() calls → different
    // behaviour per subclass = Polymorphism ✓
    // -----------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "  CHECKPOINT C: Order Hierarchy         " << endl;
    cout << "  Polymorphism via Order* ptr           " << endl;
    cout << "========================================" << endl;

    // Orders share the demo inventory from Checkpoint A
    vector<Order*> demoOrders;

    // 2 Customer Orders
    demoOrders.push_back(
        new CustomerOrder("ORD-001", "2026-05-01",
                          "FOOD-M-WHT-P", 5,
                          "Wanjiku Njoroge", "Githurai 45", 600.0));
    demoOrders.push_back(
        new CustomerOrder("ORD-002", "2026-05-01",
                          "CHEM-S-CLR-H", 100,      // ← will fail (only 10 in stock)
                          "Otieno Mwangi", "Industrial Area", 60000.0));

    // 1 Return Order
    ReturnOrder* ret = new ReturnOrder("RET-001", "2026-05-01",
                                       "FOOD-M-WHT-P", 2,
                                       "Damaged packaging");
    demoOrders.push_back(ret);

    // Process all via base pointer — Polymorphism ✓
    cout << "\n--- Processing all orders ---" << endl;
    for (Order* o : demoOrders) {
        // ReturnOrder needs approval before processing
        if (ReturnOrder* r = dynamic_cast<ReturnOrder*>(o)) {
            r->approve();  // approve the return first
        }
        o->processOrder(demoInventory);
    }

    // Display all via base pointer — Polymorphism ✓
    cout << "\n--- Order Summary ---" << endl;
    for (Order* o : demoOrders)
        o->displayOrder();

    // Cleanup checkpoint memory
    for (InventoryItem* i : demoInventory) delete i;
    for (Person*        p : people)        delete p;
    for (Order*         o : demoOrders)    delete o;
    demoInventory.clear();
    people.clear();
    demoOrders.clear();

    // -----------------------------------------------------------
    // INTERACTIVE MENU
    // -----------------------------------------------------------
    vector<InventoryItem*> warehouseInventory;
    vector<Order*>         warehouseOrders;
    int orderCounter  = 1000;  // auto-increment order IDs
    int returnCounter = 2000;  // auto-increment return IDs
    int choice;

    do {
        cout << "\n===== Foreigns & Locals WMS =====" << endl;
        cout << "1. Add Item to Inventory"             << endl;
        cout << "2. View Inventory"                    << endl;
        cout << "3. Place Customer Order"              << endl;
        cout << "4. Place Return Order"                << endl;
        cout << "5. View All Orders"                   << endl;
        cout << "6. Exit"                              << endl;
        cout << "Enter your choice: ";
        cin  >> choice;

        switch (choice) {

            // ── Add Item to Inventory ──────────────────────────
            case 1: {
                string name, type, size, color, loc, exp_date;
                double price;
                int    quantity, haz, per, frag;

                cout << "\n--Enter Product Details--\n";
                cout << "Name: ";
                cin  >> ws;
                getline(cin, name);
                cout << "Type (FOOD, ELECTRONICS, CHEMICAL): ";
                cin  >> type;
                cout << "Size (S, M, L): ";
                cin  >> size;
                cout << "Color: ";
                cin  >> color;
                cout << "Price: $";
                cin  >> price;

                cout << "Hazardous? (1=Yes, 0=No): ";
                while (!(cin >> haz) || haz < 0 || haz > 1) {
                    cout << "Invalid. Enter 1 or 0: ";
                    cin.clear(); cin.ignore(1000, '\n');
                }
                cout << "Perishable? (1=Yes, 0=No): ";
                while (!(cin >> per) || per < 0 || per > 1) {
                    cout << "Invalid. Enter 1 or 0: ";
                    cin.clear(); cin.ignore(1000, '\n');
                }
                cout << "Fragile? (1=Yes, 0=No): ";
                while (!(cin >> frag) || frag < 0 || frag > 1) {
                    cout << "Invalid. Enter 1 or 0: ";
                    cin.clear(); cin.ignore(1000, '\n');
                }

                Product newProduct(name, type, size, color,
                                   price, haz, per, frag);
                string generatedID = newProduct.getProductID();

                cout << "\n--Enter Inventory Details--\n";
                cout << "Quantity: ";
                cin  >> quantity;
                cout << "Location (e.g., Aisle-1, Fridge-A1): ";
                cin  >> loc;

                if (per == 1) {
                    cout << "Expiration Date (YYYY-MM-DD): ";
                    cin  >> exp_date;
                    warehouseInventory.push_back(
                        new PerishableItem(generatedID, name, quantity,
                                           loc, size, haz, frag, exp_date));
                } else {
                    warehouseInventory.push_back(
                        new NonPerishableItem(generatedID, name, quantity,
                                              loc, size, haz, frag));
                }
                cout << "\nItem added! ID: " << generatedID << endl;
                break;
            }

            // ── View Inventory ─────────────────────────────────
            case 2:
                if (warehouseInventory.empty()) {
                    cout << "Inventory is empty." << endl;
                } else {
                    for (InventoryItem* item : warehouseInventory)
                        item->displayItem();   // Polymorphism ✓
                }
                break;

            // ── Place Customer Order ───────────────────────────
            case 3: {
                if (warehouseInventory.empty()) {
                    cout << "No inventory to order from. Add items first." << endl;
                    break;
                }

                string productID, custName, addr, date;
                double cost;
                int    qty;

                cout << "\n--Place Customer Order--\n";
                cout << "Product ID to order: ";
                cin  >> productID;
                cout << "Quantity: ";
                cin  >> qty;
                cout << "Customer Name: ";
                cin  >> ws; getline(cin, custName);
                cout << "Delivery Address: ";
                getline(cin, addr);
                cout << "Date (YYYY-MM-DD): ";
                cin  >> date;
                cout << "Total Cost: $";
                cin  >> cost;

                string oID = "ORD-" + to_string(++orderCounter);
                CustomerOrder* co = new CustomerOrder(
                    oID, date, productID, qty, custName, addr, cost);
                co->processOrder(warehouseInventory);
                warehouseOrders.push_back(co);
                break;
            }

            // ── Place Return Order ─────────────────────────────
            case 4: {
                if (warehouseInventory.empty()) {
                    cout << "No inventory to return to. Add items first." << endl;
                    break;
                }

                string productID, reason, date;
                int    qty, approveChoice;

                cout << "\n--Place Return Order--\n";
                cout << "Product ID to return: ";
                cin  >> productID;
                cout << "Quantity: ";
                cin  >> qty;
                cout << "Return Reason: ";
                cin  >> ws; getline(cin, reason);
                cout << "Date (YYYY-MM-DD): ";
                cin  >> date;

                string rID = "RET-" + to_string(++returnCounter);
                ReturnOrder* ro = new ReturnOrder(
                    rID, date, productID, qty, reason);

                cout << "Approve this return? (1=Yes, 0=No): ";
                cin  >> approveChoice;
                if (approveChoice == 1) {
                    ro->approve();
                    ro->processOrder(warehouseInventory);
                } else {
                    ro->reject();
                    cout << "Return order logged but not processed." << endl;
                }
                warehouseOrders.push_back(ro);
                break;
            }

            // ── View All Orders ────────────────────────────────
            case 5:
                if (warehouseOrders.empty()) {
                    cout << "No orders placed yet." << endl;
                } else {
                    cout << "\n--- All Orders ---" << endl;
                    for (Order* o : warehouseOrders)
                        o->displayOrder();   // Polymorphism ✓
                }
                break;

            case 6:
                cout << "Exiting. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 6);

    // Cleanup
    for (InventoryItem* i : warehouseInventory) delete i;
    for (Order*         o : warehouseOrders)    delete o;
    warehouseInventory.clear();
    warehouseOrders.clear();

    return 0;
}
