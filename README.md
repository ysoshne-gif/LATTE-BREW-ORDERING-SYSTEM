# LATTE-BREW-ORDERING-SYSTEM
Simple CLI coffee shop ordering system in C++ (Latte Brew Cafe)

# Features
# Interactive Ordering Menu
- Displays available drinks and pastries
- Accepts user item selections
- Validates inputs (no invalid menu numbers, no negative quantities)
- Allows multiple items per order

# Inventory System
- Tracks stock quantity for each item
- Prevents ordering items that are out of stock
- Dynamically updates inventory after every purchase
- Displays remaining inventory on request

# Order Summary & Billing
- Shows selected items, quantity, and price
- Computes:
    - Subtotal
    - Sales tax
    - Total amount
- Clear, formatted receipt-like output

# Payment Processing
- Accepts customer payment
- Validates insufficient payment
- Computes and displays change

# Clean, Modular C++ Code
- Uses functions for:
- Menu display
- Ordering
- Price calculation
- Payment logic
- Inventory management
- Improves readability and structure
- New developers can easily understand and extend the system

# Error Handling & Input Validation
- Rejects non-numeric entries
- Prevents accidental crashes
- Forces user to re-enter when inputs are invalid

# Modern C++ Practices
- Uses arrays/vectors to store menu data
- Uses loops for cleaner repetition
- Uses constants for fixed prices

# Extra Quality-of-Life Features
- Clear screen option (Windows-friendly)
- Program loop — allows multiple customers
- Exit option
- Works on Windows, Linux, and macOS
