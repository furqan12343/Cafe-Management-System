# Café Management System

## Overview

The **Café Management System** is a C++ application designed to streamline and automate the operations of a café. It offers three distinct portals tailored for different user roles:

- **Admin Portal:** Manage inventory, view sales reports, and oversee overall café operations.
- **Customer Portal:** Place orders, view menu items, and provide feedback.
- **Employee Portal:** Process customer orders, update order statuses, and manage daily tasks.

The system utilizes file handling to persist data, ensuring that information such as orders, pricing, inventory levels, and user credentials are securely stored and easily retrievable.

## Features

- **User Authentication:** Secure login mechanisms for Admins, Customers, and Employees.
- **Menu Management:** Admins can add, update, or remove menu items, including setting prices and descriptions.
- **Order Processing:** Customers can place orders, which are then processed and updated by Employees.
- **Inventory Management:** Real-time tracking of stock levels, with alerts for low inventory.
- **Sales Reporting:** Generation of detailed sales reports to aid in business analysis.
- **Data Persistence:** Efficient file handling ensures all data is saved and remains consistent across sessions.

## File Structure

```bash
├── src
│   ├── main.cpp           # Entry point of the application
│   ├── admin.cpp          # Implementation of admin functionalities
│   ├── customer.cpp       # Implementation of customer functionalities
│   ├── employee.cpp       # Implementation of employee functionalitie
├── include
│   ├── admin.h            # Admin class and function declarations
│   ├── customer.h         # Customer class and function declarations
│   ├── employee.h         # Employee class and function declarations
├── data
│   ├── notification.txt   # Updates on orders
│   ├── order.txt          # Records of all customer orders
│   ├── stocks.txt         # Current inventory stock levels
│   ├── employ.txt         # Employee credentials
│   └── complaints.txt     # Customer complaints
└── README.md              # Project overview and information
