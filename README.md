Inventory Management System (Structured Programming)

This project is a Structured (Non-Object-Oriented) implementation of an Inventory Management System developed in C++. The design allows easy future conversion into an Object-Oriented version.


Feature	Description
Add Item:	Insert new products with ID, name, price, and quantity
View All Items:	Display all items grouped by category
Update Quantity:	Modify stock quantity of existing items
Delete Item:	Remove items using their ID
Low Stock Report:	Display items with quantity less than or equal to 5
Save and Load Data:	Store and retrieve data using a binary file (inventory.dat)
Category Management:	Manage multiple categories such as Electronics and Books
Dynamic Memory:	Implemented using new and delete[]
Pointer Usage:	Used for searching and item management

Main Menu (Program Display)
===== INVENTORY MANAGEMENT SYSTEM =====
1. Add Category
2. Add Item
3. View All Items
4. Update Quantity
5. Delete Item
6. Low Stock Report
7. Save Data
0. Exit

Explanation of Each Option
1. Add Category
Adds a new category such as Electronics or Books. Categories are stored dynamically in memory.

2. Add Item
Adds a new item under a specific category. Required inputs include category name, item ID, item name, price, and quantity.

3. View All Items
Displays all stored items grouped by their respective categories.

4. Update Quantity
Updates the stock quantity of an existing item using its ID.

5. Delete Item
Deletes an item from the inventory using its ID. The program searches all categories to locate the item.

6. Low Stock Report
Displays all items whose quantity is less than or equal to 5.

7. Save Data
Saves all inventory data, including categories and items, into a binary file named inventory.dat.

0. Exit
Automatically saves all data and frees allocated memory before terminating the program.

File Handling
Data is stored in binary format (inventory.dat)
Data is automatically loaded when the program starts
Data is automatically saved when the program exits
