/*
========================================================================
 TikTok Shop Assistant
 ------------------------------------------------------------------------
 LDCW6123 - Part 2: Interactive Program
 Connected to Part 1: TikTok Social Commerce (Christensen's Disruptive
 Innovation Model)

 This program simulates two disruptive mechanics from our Part 1 poster:
   1. AI Recommendation Engine -> suggests a trending product based on
      the category the user picks, the same way TikTok's "For You Page"
      surfaces products without the user actively searching for them.
   2. TikTok Shop Integration -> an in-app checkout flow that applies
      "Live flash sale" / bundle discounts and calculates shipping,
      mirroring the seamless checkout described under Performance
      Improvement on the poster.
========================================================================
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

// ---------------- Function prototypes ----------------
void printWelcome();
int getCategoryChoice();
void recommendProduct(int category, string &productName, double &price);
int getValidQuantity();
double calculateDiscount(double subtotal, int quantity, string &discountLabel);
double calculateShipping(double amountAfterDiscount);
void printReceipt(const string &productName, double price, int quantity,
                   double subtotal, double discount, const string &discountLabel,
                   double shipping, double total);
bool askContinue();

int main() {
    cout << fixed << setprecision(2);   // show all RM values as 2 decimal places

    printWelcome();

    double grandTotal = 0.0;
    int itemsBought = 0;
    bool shopping = true;

    while (shopping) {
        int category = getCategoryChoice();
        if (category == 0) break;       // user chose "Exit"

        string productName;
        double price;
        recommendProduct(category, productName, price);

        cout << "\nTikTok AI recommends: \"" << productName
             << "\" - RM" << price << "\n";
        cout << "(Suggested for you, based on your For You Page activity)\n";

        cout << "\nAdd this to your cart? (1 = Yes, 2 = No): ";
        int addChoice;
        cin >> addChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input - let's try again.\n";
            continue;
        }
        if (addChoice != 1) {
            cout << "No problem, let's browse another category.\n";
            continue;
        }

        int quantity = getValidQuantity();
        double subtotal = price * quantity;

        string discountLabel;
        double discount = calculateDiscount(subtotal, quantity, discountLabel);
        double afterDiscount = subtotal - discount;

        double shipping = calculateShipping(afterDiscount);
        double total = afterDiscount + shipping;

        printReceipt(productName, price, quantity, subtotal, discount,
                     discountLabel, shipping, total);

        grandTotal += total;
        itemsBought++;

        shopping = askContinue();
    }

    cout << "\n========================================\n";
    if (itemsBought > 0) {
        cout << "Checkout complete! Items bought: " << itemsBought << "\n";
        cout << "Grand total: RM" << grandTotal << "\n";
    } else {
        cout << "No items purchased this time.\n";
    }
    cout << "Thanks for shopping with TikTok Shop!\n";
    cout << "========================================\n";

    return 0;
}

// ---------------- Function definitions ----------------

void printWelcome() {
    cout << "========================================\n";
    cout << "      TIKTOK SHOP ASSISTANT\n";
    cout << "========================================\n";
    cout << "Discover. Watch. Shop. Without leaving the app.\n";
}

int getCategoryChoice() {
    int choice;
    while (true) {
        cout << "\nWhat are you into today?\n";
        cout << "  1. Fashion & Beauty\n";
        cout << "  2. Electronics & Gadgets\n";
        cout << "  3. Home & Living\n";
        cout << "  4. Food & Beverage\n";
        cout << "  0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number between 0 and 4.\n";
            continue;
        }
        if (choice >= 0 && choice <= 4) return choice;
        cout << "Invalid choice, please try again.\n";
    }
}

void recommendProduct(int category, string &productName, double &price) {
    // Switch statement = the "AI Recommendation Engine"
    switch (category) {
        case 1:
            productName = "Korean Glass-Skin Serum Set";
            price = 89.90;
            break;
        case 2:
            productName = "Mini Wireless Clip-on Mic";
            price = 65.00;
            break;
        case 3:
            productName = "LED Sunset Projector Lamp";
            price = 39.90;
            break;
        case 4:
            productName = "Brown Sugar Pearl Milk Tea Kit";
            price = 25.50;
            break;
        default:
            productName = "Mystery Box";
            price = 19.90;
    }
}

int getValidQuantity() {
    int qty;
    while (true) {
        cout << "Enter quantity: ";
        cin >> qty;
        if (cin.fail() || qty <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a positive whole number.\n";
            continue;
        }
        return qty;
    }
}

double calculateDiscount(double subtotal, int quantity, string &discountLabel) {
    // Tiered logic inspired by TikTok LIVE flash sales & creator bundle deals
    if (quantity >= 5) {
        discountLabel = "Bundle Deal (15%)";
        return subtotal * 0.15;
    } else if (subtotal > 150.0) {
        discountLabel = "TikTok LIVE Flash Sale (10%)";
        return subtotal * 0.10;
    } else if (subtotal > 80.0) {
        discountLabel = "Creator Promo Code (5%)";
        return subtotal * 0.05;
    }
    discountLabel = "No discount applied";
    return 0.0;
}

double calculateShipping(double amountAfterDiscount) {
    const double FREE_SHIPPING_THRESHOLD = 50.0;
    const double FLAT_SHIPPING_FEE = 5.90;
    return (amountAfterDiscount >= FREE_SHIPPING_THRESHOLD) ? 0.0 : FLAT_SHIPPING_FEE;
}

void printReceipt(const string &productName, double price, int quantity,
                   double subtotal, double discount, const string &discountLabel,
                   double shipping, double total) {
    cout << "\n------------ ORDER SUMMARY ------------\n";
    cout << "Item:       " << productName << "\n";
    cout << "Unit Price: RM" << price << "\n";
    cout << "Quantity:   " << quantity << "\n";
    cout << "Subtotal:   RM" << subtotal << "\n";
    cout << "Discount:   -RM" << discount << " (" << discountLabel << ")\n";
    cout << "Shipping:   RM" << shipping;
    if (shipping == 0.0) cout << " (Free Shipping!)";
    cout << "\n----------------------------------------\n";
    cout << "TOTAL:      RM" << total << "\n";
    cout << "----------------------------------------\n";
}

bool askContinue() {
    int choice;
    cout << "\nKeep browsing your FYP? (1 = Yes, 2 = No, checkout): ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return choice == 1;
}
