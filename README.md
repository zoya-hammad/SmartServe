# Smart Serve: Integrated Cafeteria Management & Transactions

This repository contains the files for my third-semester project – Smart Serve: Integrated Cafeteria Management & Transactions.

## Project Overview
This desktop app aims to provide user and admin functionality for a cafeteria application designed to digitalize meal ordering and payment. Users can purchase meals based on existing meal plans or via student cards, view menus, apply advanced filtering, and receive transactional history. A unique QR code is generated for each transaction, which users can easily capture and present at the counter as an e-receipt for order fulfillment. Admin functionalities include user management, creation, and modification of meal plans, adding cash to student cards, menu item management, and access to user transaction history. The login system uses a SHA-256 hashing system for enhanced security. All relevant data is efficiently managed using a MySQL database for ease of access. The application contains a user-friendly, multiple-document graphical user interface allowing for ease of navigation. The GUI is  developed using QT Creator and framework in C++ programming language.

## Key Resources
- GitHub Repository: [Smart Serve Repository](https://github.com/zoya-hammad/SmartServe)

### Licenses Used
- GUI: QT Creator (LGPL License)
- QR Code Generation: Qt-QrCodeGenerator (MIT License)
- Database Connectivity: SQL Lite Studio (GPL License)
- Icons: Flaticon Free License (With Attribution)

## Problem Identification
Smart Serve addresses several critical issues in the current cafeteria system:

1. **Absence of a Digital Ticketing System:**
    Manual order placement and paper tokens for verification lead to potential errors and delays.
   
2. **Limited User Access to Records:**
   Users lack access to data regarding previously purchased meals, hindering transparency.

3. **Dependence on Cash Transactions:**
   Inconvenience for students who need cash, leading to limited accessibility.

4. **Lack of Timestamps on Receipts:**
    Handwritten receipts without timestamps can lead to disputes over wait times.

5. **Lack of Price Transparency:**
   The price of menu items is not displayed, causing stress for customers and increased workload for staff.

6. **Manual Data Calculation:**
   Data is stored on paper, hindering digital analysis for informed decisions.

7. **Lack of Data Security:**
   Customer purchases and active meal plans are not backed up, posing a risk of data loss.

## Deliverables

### 1. Digital Ticketing System
- Enables secure login, meal selection, and order placement using virtual cash cards or meal plan points.
- Generates a QR code for order verification.

### 2. User Access Portal
- Allows users to manage meal plans, view and filter the menu, purchase orders, and navigate transaction history.

### 3. Admin Access Portal
- Provides administrators with tools to manage user accounts, create/modify meal plans, add funds to student cards, edit menu items, and access analytics.

### 4. Alternative Payment Integration
- Integrates a virtual wallet for seamless and secure digital transactions.

### 5. Meal Plan ID Generation
- Implements an algorithm for generating unique Meal Plan IDs using hash tables, ensuring data integrity.

### 6. Timestamped QR Code E-Receipts
- Generates QR-coded e-receipts for each transaction, embedding crucial details like the meal name, customer ID, and timestamp.

### 7. Price Transparency and Advanced Filtering
- Enables users to filter menu items based on price and meal type, providing transparent pricing information.

### 8. Admin Dashboard Analytics
- Provides real-time analytics such as total meals purchased, total meal plans, active virtual cards, and insights into the popularity of menu items.

### 9. Graphical User Interface (GUI)
- Developed using Qt Creator, enhanced with HTML and CSS for improved user experience.
- Features a multi-document interface (MDI) model for seamless navigation across different pages.

### 10. Secure Login and Database Storage
- Implements a robust login system using the SHA-256 algorithm.
- Stores relevant cafeteria data effectively within 8 data tables, linked schematically for efficient storage, retrieval, and maintenance.

## Usage

