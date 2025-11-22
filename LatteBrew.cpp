#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <ctime>

using namespace std;

struct Item {
    int id;
    string name;
    double price;
    int stock;
};

class Shop {
private:
    vector<Item> menu;
    double total;
public:
    Shop() : total(0.0) {
        // initial menu - you can change items/prices/stocks here
        menu = {
            {1, "Espresso", 90.00, 10},
            {2, "Cappuccino", 110.00, 8},
            {3, "Latte", 120.00, 12},
            {4, "Caramel Macchiato", 130.00, 6},
            {5, "Mocha", 125.00, 10}
        };
    }

    void showMenu() const {
        cout << "\n====== LATTE BREW CAFE ======\n";
        cout << left << setw(4) << "No" << setw(24) << "Coffee"
             << setw(10) << "Price" << "Stock\n";
        cout << "----------------------------------------\n";
        for (const auto &it : menu) {
            cout << left << setw(4) << it.id
                 << setw(24) << it.name
                 << "₱" << setw(8) << fixed << setprecision(2) << it.price
                 << it.stock << '\n';
        }
    }

    bool isValidChoice(int id) const {
        for (const auto &it : menu) if (it.id == id) return true;
        return false;
    }

    Item* findItem(int id) {
        for (auto &it : menu) if (it.id == id) return &it;
        return nullptr;
    }

    void placeOrder() {
        while (true) {
            showMenu();
            int choice = readInt("Enter item number (0 to finish): ", 0, 100);
            if (choice == 0) break;
            if (!isValidChoice(choice)) {
                cout << "Invalid choice. Try again.\n";
                continue;
            }
            Item* it = findItem(choice);
            if (!it) continue;

            cout << "Selected: " << it->name << " (₱" << fixed << setprecision(2) << it->price << ")\n";
            int maxQty = it->stock;
            if (maxQty == 0) {
                cout << "Sorry, this item is out of stock.\n";
                continue;
            }
            int qty = readInt("Enter quantity: ", 1, maxQty);
            double subtotal = qty * it->price;
            total += subtotal;
            it->stock -= qty;

            cout << qty << " x " << it->name << " added. Subtotal: ₱" << fixed << setprecision(2) << subtotal << "\n";
        }
    }

    void checkout() {
        cout << "\n======= CHECKOUT =======\n";
        cout << "Total Amount Due: ₱" << fixed << setprecision(2) << total << "\n";
        if (total > 0.0) {
            double received = readDouble("Enter cash received: ₱", 0.0, 1000000.0);
            if (received < total) {
                cout << "Not enough cash. Transaction cancelled.\n";
            } else {
                double change = received - total;
                cout << "Change: ₱" << fixed << setprecision(2) << change << "\n";
                saveReceipt(received, change);
                cout << "Thank you for ordering at LATTE BREW! ☕\n";
                total = 0.0;
            }
        } else {
            cout << "No items ordered. Goodbye.\n";
        }
    }

    static int readInt(const string &prompt, int minVal, int maxVal) {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minVal && x <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return x;
            }
            cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    static double readDouble(const string &prompt, double minVal, double maxVal) {
        double x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minVal && x <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return x;
            }
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void saveReceipt(double paid, double change) {
        // Save a simple receipt text file with timestamp
        time_t now = time(nullptr);
        tm *lt = localtime(&now);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", lt);
        string filename = string("receipt_") + buf + ".txt";
        ofstream ofs(filename);
        if (!ofs) {
            cout << "Could not write receipt file.\n";
            return;
        }
        ofs << "LATTE BREW - RECEIPT\n";
        ofs << "Date/Time: " << asctime(lt);
        ofs << "Paid: ₱" << fixed << setprecision(2) << paid << "\n";
        ofs << "Change: ₱" << fixed << setprecision(2) << change << "\n";
        ofs << "Thank you!\n";
        ofs.close();
        cout << "Receipt saved to " << filename << "\n";
    }

    void run() {
        cout << "Welcome to Latte Brew Cafe CLI!\n";
        placeOrder();
        checkout();
    }
};

int main() {
    Shop shop;
    shop.run();
    return 0;
}
