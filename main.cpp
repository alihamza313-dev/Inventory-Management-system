#include <iostream>
#include <string>
#include <climits>  
#include <fstream>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    string name;
    double price;
    int quantity;
};


string toLowerCase(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void showMainMenu() {
    cout << "\033[1;36m\n===== INVENTORY MANAGEMENT SYSTEM =====\033[0m\n"; // Cyan Bold
    cout << "\033[1;33m1.\033[0m Add Category\n";
    cout << "\033[1;33m2.\033[0m Add Item\n";
    cout << "\033[1;33m3.\033[0m View All Items\n";
    cout << "\033[1;33m4.\033[0m Update Quantity\n";
    cout << "\033[1;33m5.\033[0m Search Item\n";
    cout << "\033[1;33m6.\033[0m Delete Item\n";
    cout << "\033[1;33m7.\033[0m Low Stock Report\n";
    cout << "\033[1;33m8.\033[0m Save Data\n";
    cout << "\033[1;33m9.\033[0m Save And Exit\n";
}


void addCategory(string *&Category, int &categoryCount, Item **&items, int *&itemCount) {
    string* newCategory = new string[categoryCount+1];
    Item** newItems = new Item *[categoryCount+1];
    int* newitemCount = new int[categoryCount+1];

    for (int i=0; i<categoryCount; i++) {
        newCategory[i] = Category[i];
        newItems[i] = items[i];
        newitemCount[i] = itemCount[i];
    }

    string temp;
    cout << "\nEnter New Category Name: ";
    cin.ignore();
    getline(cin,temp);

    newCategory[categoryCount] = temp;
    newItems[categoryCount] = nullptr;
    newitemCount[categoryCount] = 0;

    delete[] Category;
    delete[] items;
    delete[] itemCount;

    Category = newCategory;
    items = newItems;
    itemCount = newitemCount;

    categoryCount++;

    cout << "\033[1;32mCategory '" << temp << "' added successfully!\033[0m\n";
}


void addItem(string *Category, int categoryCount, Item **&items, int *&itemCount) {
    if (categoryCount <= 0) {
        cout << "\033[1;31m\nNo categories available. Add a category first.\033[0m\n";
        return;
    } 

    cout << "\033[1;36m\n---- Available Categories ----\033[0m\n";
    for (int i=0; i<categoryCount; i++) {
        // cout << i+1 << ". " << Category[i] << endl;
        cout << "\033[1;33m" << i+1 << ". " <<"\033[0m" << Category[i] << endl;
    }

    int choice;
    cout << "\nSelect category number to add item: ";
    cin >> choice;
    choice--;

    while (choice < 0 || choice >= categoryCount) {  
        cout << "\033[1;31mInvalid Choice!\033[0m\n";
        cout << "Select category number to add item: ";
        cin >> choice;
        choice--;
    }

    int count = itemCount[choice];
    Item *newArray = new Item[count + 1];

    for (int i=0; i<count; i++) {
        newArray[i] = items[choice][i];
    }

    // Entering Item Details
    int newID;
    bool unique = true;

    do {
        unique = true;
        cout << "\nEnter Item ID: ";
        cin >> newID;

        for (int i = 0; i < categoryCount; i++) {
            for (int j = 0; j < itemCount[i]; j++) {
                if (items[i][j].id == newID) {
                    cout << "\033[1;31mID already exists! Enter a unique ID.\033[0m\n";
                    unique = false;
                    break;
                }
            }
            if (!unique) break; 
        }

    } while (!unique);

    newArray[count].id = newID;

    cout << "Enter Item Name: ";
    cin.ignore();
    getline(cin, newArray[count].name);
    while (true) {
        if(!(newArray[count].name.empty())) {
            break;
        }

        cout << "\033[1;31mItem Name can't be Empty!\033[0m\n";
        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, newArray[count].name);
    }

    cout << "Enter Price: ";
    cin >> newArray[count].price;
    while(true) {
        if(newArray[count].price >= 0) {
            break;
        }

        cout << "\033[1;31mPrice can't be Negative!\033[0m\n";
        cout << "Enter Price: ";
        cin >> newArray[count].price;
    }
    cout << "Enter Quantity: ";
    cin >> newArray[count].quantity;

    while(true) {
        if(newArray[count].quantity >= 0) {
            break;
        }

        cout << "\033[1;31mQuantity can't be Negative!\033[0m\n";
        cout << "Enter Quantity: ";
        cin >> newArray[count].quantity;
    }

    delete[] items[choice];
    items[choice] = newArray;
    itemCount[choice]++;

    cout << "\033[1;32mItem added successfully to category '" << Category[choice] << "'!\033[0m\n";
}


void viewItem(string *Category, int categoryCount, Item **&items, int *&itemCount) {
    if (categoryCount == 0) {
        cout << "\033[1;31m\nNo categories found.\033[0m\n";
        return;
    }

    int sortChoice = 0;
    while (true) {
        cout << "\033[1;36m\n===== VIEW OPTIONS =====\033[0m\n";
        cout << "\033[1;33m1.\033[0m View items sorted by ID\n";
        cout << "\033[1;33m2.\033[0m View items sorted by Price\n";
        cout << "\033[1;33m3.\033[0m View items as is (Random/Original)\n";
        cout << "Enter your choice (1-3): ";
        cin >> sortChoice;
        if (sortChoice >= 1 && sortChoice <= 3) break;
        cout << "\033[1;31mInvalid choice! Please enter 1, 2, or 3.\033[0m\n";
    }

    cout << "\033[1;36m\n===== INVENTORY LIST =====\033[0m\n";

    for (int i = 0; i < categoryCount; i++) {
        cout << "\nCategory: " << Category[i] << endl;

        if (itemCount[i] == 0) {
            cout << "\033[33m  (No items yet)\033[0m\n";
            continue;
        }

        Item *tempItems = new Item[itemCount[i]];
        for (int j = 0; j < itemCount[i]; j++) tempItems[j] = items[i][j];


        if (sortChoice == 1) { // Sort by ID
            for (int a = 0; a < itemCount[i] - 1; a++) {
                for (int b = 0; b < itemCount[i] - a - 1; b++) {
                    if (tempItems[b].id > tempItems[b + 1].id) {
                        swap(tempItems[b], tempItems[b + 1]);
                    }
                }
            }
        }

        else if (sortChoice == 2) { // Sort by Price
            for (int a = 0; a < itemCount[i] - 1; a++) {
                for (int b = 0; b < itemCount[i] - a - 1; b++) {
                    if (tempItems[b].price > tempItems[b + 1].price) {
                        swap(tempItems[b], tempItems[b + 1]);
                    }
                }
            }
        }

        // Print items
        for (int j = 0; j < itemCount[i]; j++) {
            cout << "  ID: " << tempItems[j].id
                 << " | Name: " << tempItems[j].name
                 << " | Price: " << tempItems[j].price
                 << " | Quantity: " << tempItems[j].quantity
                 << endl;
        }

        delete[] tempItems;
    }
}


void updateItem(string *Category, int categoryCount, Item **items, int *itemCount) {
    if (categoryCount <= 0) {
        cout << "\033[1;31m\nNo categories found.\033[0m\n";
        return;
    }

    int updateChoice;
    cout << "\033[1;36m\n===== UPDATION CHOICES =====\033[0m\n";
    cout << "\033[1;33m1.\033[0m Update Name\n";
    cout << "\033[1;33m2.\033[0m Update Price\n";
    cout << "\033[1;33m3.\033[0m Update Quantity\n";
    cout << "\033[1;33m4.\033[0m Update All\n";

    cout << "\nEnter Your Choice (1-4): ";
    cin >> updateChoice;
    while (true) {
        if(updateChoice >=1 && updateChoice <= 4) break;
        cout << "\033[1;31mInvalid Choice!\033[0m\n";
        cout << "Enter Your Choice (1-4): ";
        cin >> updateChoice;
    }

    int searchID;
    cout << "Enter Item ID to Update: ";
    cin >> searchID;

    bool found = false;

    if (updateChoice == 1) {
        for (int i=0; i<categoryCount; i++) {
        for (int j=0; j<itemCount[i]; j++) {
            if(items[i][j].id == searchID) {
                cout << "Current Name: " << items[i][j].name << endl;
                cout << "Enter New Name: ";
                cin.ignore();
                getline(cin,items[i][j].name);

            while (true) {
                if(!(items[i][j].name.empty())) {
                    break;
                }
                cout << "\033[1;31mItem Name can't be Empty!\033[0m\n";
                cout << "Enter Item Name: ";
                cin.ignore();
                getline(cin, items[i][j].name);
            }

            cout << "\033[1;32mName Updated Successfully!\033[0m\n";
            found = true;
            break;
            }   
        }
            if(found) {
                break;
            }
        }
    }

    else if (updateChoice == 2) {
        for (int i=0; i<categoryCount; i++) {
            for (int j=0; j<itemCount[i]; j++) {
                if(items[i][j].id == searchID) {
                    cout << "Current Price: " << items[i][j].price << endl;
                    cout << "Enter New Price: ";
                    cin >> items[i][j].price;

                    while(true) {
                        if(items[i][j].price >= 0) {
                            break;
                        }

                        cout << "\033[1;31mPrice can't be Negative!\033[0m\n";
                        cout << "Enter New Price: ";
                        cin >> items[i][j].price;
                    }

                    cout << "\033[1;32mPrice Updated Successfully!\033[0m\n";
                    found = true;
                    break;
                }   
            }
            if(found) {
                break;
            }
        }
    }

    else if (updateChoice == 3) {
        for (int i=0; i<categoryCount; i++) {
            for (int j=0; j<itemCount[i]; j++) {
                if(items[i][j].id == searchID) {
                    cout << "Current Quantity: " << items[i][j].quantity << endl;
                    cout << "Enter New Quantity: ";
                    cin >> items[i][j].quantity;

                    while(true) {
                        if(items[i][j].quantity >= 0) {
                            break;
                        }

                        cout << "\033[1;31mQuantity can't be Negative!\033[0m\n";
                        cout << "Enter New Quantity: ";
                        cin >> items[i][j].quantity;
                    }
                    cout << "\033[1;32mQuantity Updated Successfully!\033[0m\n";
                    found = true;
                    break;
                }   
            }
            if(found) {
                break;
            }
        }
    }

    else if (updateChoice == 4) {
        for (int i=0; i<categoryCount; i++) {
            for (int j=0; j<itemCount[i]; j++) {
                if(items[i][j].id == searchID) {
                    cout << "Current Name: " << items[i][j].name << endl;
                    cout << "Enter New Name: ";
                    cin.ignore();
                    getline(cin, items[i][j].name);

                    while (true) {
                        if(!(items[i][j].name.empty())) {
                            break;
                        }
                        cout << "\033[1;31mItem Name can't be Empty!\033[0m\n";
                        cout << "Enter Item Name: ";
                        cin.ignore();
                        getline(cin, items[i][j].name);
                    }

                    cout << "Current Price: " << items[i][j].price << endl;
                    cout << "Enter New Price: ";
                    cin >> items[i][j].price;

                    while(true) {
                        if(items[i][j].price >= 0) {
                            break;
                        }

                        cout << "\033[1;31mPrice can't be Negative!\033[0m\n";
                        cout << "Enter New Price: ";
                        cin >> items[i][j].price;
                    }

                    cout << "Current Quantity: " << items[i][j].quantity << endl;
                    cout << "Enter New Quantity: ";
                    cin >> items[i][j].quantity;

                    while(true) {
                        if(items[i][j].quantity >= 0) {
                            break;
                        }

                        cout << "\033[1;31mQuantity can't be Negative!\033[0m\n";
                        cout << "Enter New Quantity: ";
                        cin >> items[i][j].quantity;
                    }

                    cout << "\033[1;32m\nItem Updated Successfully!\033[0m\n";
                    found = true;
                    break;
                }   
            }
            if(found) {
                break;
            }
        }
    }

    if(!found) {
        cout << "\033[1;31mItem with ID " << searchID << " not found!\033[0m\n";
    }

}


void searchItem(string *Category, int categoryCount, Item **items, int *itemCount) {
    if (categoryCount <= 0) {
        cout << "\033[1;31m\nNo categories found.\033[0m\n";
        return;
    }

    int searchChoice;

    cout << "\033[1;36m\n===== SEARCH ITEMS =====\033[0m\n";
    cout << "\033[1;33m1.\033[0m Search by ID\n";
    cout << "\033[1;33m2.\033[0m Search by Name\n";
    cout << "Enter your choice (1-2): ";

    cin >> searchChoice;

    while (searchChoice < 1 || searchChoice > 2) {
        cout << "\033[1;31mInvalid choice!\033[0m\n";
        cout << "Enter your choice (1-2): ";
        cin >> searchChoice;
    }

    bool found = false;

    if (searchChoice == 1) {
        int id;
        cout << "Enter Item ID: ";
        cin >> id;

        for (int i = 0; i < categoryCount; i++) {
            for (int j = 0; j < itemCount[i]; j++) {
                if (items[i][j].id == id) {
                    cout << "\033[1;32m\nItem Found in Category: " << Category[i] << "\033[0m" << endl;
                    cout << "ID: " << items[i][j].id
                         << " | Name: " << items[i][j].name
                         << " | Price: " << items[i][j].price
                         << " | Quantity: " << items[i][j].quantity
                         << endl;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    } else if (searchChoice == 2) {
        cin.ignore();
        string name;
        cout << "Enter Item Name: ";
        getline(cin, name);

        for (int i = 0; i < categoryCount; i++) {
            for (int j = 0; j < itemCount[i]; j++) {
                if (toLowerCase(items[i][j].name) == toLowerCase(name)) {
                    cout << "\033[1;32m\nItem Found in Category: " << Category[i] << "\033[0m" << endl;
                    cout << "ID: " << items[i][j].id;
                    cout << " | Name: " << items[i][j].name;
                    cout << " | Price: " << items[i][j].price;
                    cout << " | Quantity: " << items[i][j].quantity;
                    cout << endl;

                    found = true;
                }
            }
        }
    }

    if (!found) {
        cout << "\033[1;31mItem not found!\033[0m\n";
    }
}


void deleteItem(string *Category, int categoryCount, Item **items, int *itemCount) {
    if (categoryCount <= 0) {
        cout << "\033[1;31mNo categories found!\033[0m\n";
        return;
    }

    int searchID;
    cout << "Enter Item ID to Delete: ";
    cin >> searchID;

    char confirm;
    cout << "\033[1;36mAre you Sure (y/n): \033[0m";
    cin >> confirm;

    if (confirm != 'y' && confirm != 'Y') {
        cout << "\033[1;33mItem deletion canceled.\033[0m\n";
        return;
    }

    bool found = false;
    int index = 0;

    for (int i=0; i<categoryCount; i++) {
        for (int j=0; j<itemCount[i]; j++) {
            if(items[i][j].id == searchID) {
                int count = itemCount[i];
                Item *newArray = new Item[count - 1];
                int l = 0;

                for (int k=0; k<count; k++) {
                    if (k != j) {
                        newArray[l] = items[i][k];
                        l++;
                    }
                }

                delete[] items[i];
                items[i] = newArray;
                itemCount[i]--;

                cout << "\033[1;32mItem with ID " << searchID << " deleted successfully from category '" << Category[i] << "'!\033[0m\n";
                found = true;
                break;
            }   
        }
        if(found) {
            break;
        }
    }
    if(!found) {
        cout << "\033[1;31mItem with ID " << searchID << " not found!\033[0m\n";
    }
}


void deleteCategory (string *&Category, int &categoryCount, Item **&items, int *&itemCount) {
    if (categoryCount == 0) {
        cout << "\033[1;31mNo categories found!\033[0m\n";
        return;
    }

    cout << "\nCategories:\n";
    for (int i = 0; i < categoryCount; i++) {
        cout << i + 1 << ". " << Category[i] << endl;
    }

    int choice;
    cout << "Enter category number to delete: ";
    cin >> choice;
    choice--; 

    while (true) {
        if(choice >= 0 && choice < categoryCount) break;
        cout << "\033[1;31mInvalid category number.\033[0m\n";
        cout << "Enter category number to delete: ";
        cin >> choice;
        choice--;
    }

    // Warning before deletion
    char confirm;
    cout << "\033[1;33mDeleting this category will also delete all its items. Continue? (y/n): \033[0m";
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "\033[1;33mCategory deletion canceled.\033[0m\n";
        return;
    }

    delete[] items[choice];

    string *newCategory = new string[categoryCount - 1];
    Item **newItems = new Item *[categoryCount - 1];
    int* newItemCount = new int[categoryCount - 1];

    int j = 0;
    for (int i=0; i<categoryCount; i++) {
        if (i == choice) continue;
        newCategory[j] = Category[i];
        newItems[j] = items[i];
        newItemCount[j] = itemCount[i];
        j++;
    }

    delete[] Category;
    delete[] items;
    delete[] itemCount;

    Category = newCategory;
    items = newItems;
    itemCount = newItemCount;
    categoryCount--;
    
    cout << "\033[1;32mCategory deleted successfully!\033[0m\n";
}



void showLowStock(string *Category, int categoryCount, Item **items, int *itemCount) {
    if (categoryCount == 0) {
        cout << "\033[1;31mNo categories found!\033[0m\n";
        return;
    }

    bool found = false;

    cout << "\033[1;31m\n===== LOW STOCK ITEMS (Qty < 5) =====\033[0m\n";

    for (int i=0; i<categoryCount; i++) {
        for (int j=0; j<itemCount[i]; j++) {
            if(items[i][j].quantity < 5) {
                cout << "Category: " << Category[i] << endl;
                cout << "  ID: " << items[i][j].id;
                cout << " | Name: " << items[i][j].name;
                cout << " | Price: " << items[i][j].price;
                cout << " | Quantity: " << items[i][j].quantity;
                cout << endl;
                
                found = true;
            }
        }
    }

    if(!found) {
        cout << "\033[1;36m  (No items are currently below the low stock threshold)\033[0m\n";
    }
}


void loadData(string *&Category, int &categoryCount, Item **&items, int *&itemCount)
{
    ifstream reading("inventory.txt", ios::binary);
    if (!reading.is_open()) {
        cout << "\nNo previous data found. Starting fresh!\n";
        categoryCount = 0;
        Category = new string[0];
        items = new Item*[0];
        itemCount = new int[0];
        return;
    }
    if (Category != nullptr) {
        delete[] Category;
        Category = nullptr;
    }
    if (items != nullptr) {
        for(int i = 0; i < categoryCount; i++){
            delete[] items[i];
        }
        delete[] items;
    }
    if (itemCount != nullptr) {
        delete[] itemCount;
        itemCount = nullptr;
    }
    categoryCount = 0;
    reading.seekg(0, ios::end);
    if (reading.tellg() == 0) {
        cout << "\nInventory file exists but is empty. Starting fresh.\n";
        categoryCount = 0;
        Category = new string[0];
        items = new Item*[0];
        itemCount = new int[0];
        return;
    }
    reading.seekg(0, ios::beg);
    reading.read((char*)&categoryCount, sizeof(categoryCount));
    Category  = new string[categoryCount];
    items     = new Item*[categoryCount];
    itemCount = new int[categoryCount];
    for (int i = 0; i < categoryCount; i++) {
        int len;
        reading.read((char*)&len, sizeof(len));
        Category[i].resize(len);// // makes space for exactly 5 chars
        reading.read(&Category[i][0], len);    // put from the first character into the string 
        int itmcount;
        reading.read((char*)&itmcount, sizeof(itmcount));
        itemCount[i] = itmcount;
        items[i] = new Item[itmcount];
        for (int j = 0; j < itmcount; j++) {
            Item &itm = items[i][j];
            reading.read((char*)&itm.id, sizeof(int));
            reading.read((char*)&itm.price, sizeof(double));
            reading.read((char*)&itm.quantity, sizeof(int));
            int length;
            reading.read((char*)&length, sizeof(length));
            itm.name.resize(length);
            reading.read(&itm.name[0], length); // [0] means the first char of the string and read onwards
        }
    }
    reading.close();
    cout << "\033[1;32mAll data loaded successfully! (" << categoryCount << " categories)\033[0m\n";
}

void saveData(string *Category, int &categoryCount, Item **items, int *itemCount)
{
    ofstream writing("inventory.txt",ios::binary);
    if (!writing.is_open()) {
        cout << "\nUnable to open the file to save data\n";
        return ;
    }
    int count=categoryCount;

    writing.write((char*)&count,sizeof(count));
    for(int i=0;i<count;i++){
        int len=Category[i].size();
        writing.write((char*)&len,sizeof(len));
        writing.write(Category[i].c_str(),len);
        int itmcount=itemCount[i];
        writing.write((char*)&itmcount,sizeof(int));
        for(int j=0;j<itmcount;j++){
            Item &itm=items[i][j];
            writing.write((char*)&itm.id,sizeof(int));
            writing.write((char*)&itm.price,sizeof(double));
            writing.write((char*)&itm.quantity,sizeof(int));
            int length=itm.name.size();
            writing.write((char*)&length,sizeof(length));
            writing.write(itm.name.c_str(),length);
        }
    }
    writing.close();
    cout<<"\033[1;32mAll data has been stored successfully in the binary file\033[0m\n";
}


int main () {
    int choice = 0;

    // For Category
    string *Category = nullptr;
    int categoryCount = 0;

    // For Items
    Item **items = nullptr;
    int *itemCount = nullptr;

    loadData(Category, categoryCount, items, itemCount);

    if (Category == nullptr) {
        Category = new string[0];
        items = new Item*[0];
        itemCount = new int[0];
    }


    while (true) {
        showMainMenu();

        cout << "\nEnter your Choice (1-8): ";
        cin >> choice;

        while (true) {
            if(choice >= 1 && choice <=9) {
                break;
            } 
            cout << "\033[1;31mInvalid Choice!\033[0m\n";
            cout << "Enter your Choice (1-8): ";
            cin >> choice;
        }

        if(choice == 1) {
            addCategory(Category, categoryCount, items, itemCount);
        }
        else if (choice == 2) {
            addItem(Category,categoryCount, items, itemCount);
        }
        else if (choice == 3) {
            viewItem(Category, categoryCount, items, itemCount);
        }
        else if (choice == 4) {
            updateItem(Category, categoryCount, items, itemCount);
        }

        else if(choice == 5) {
            searchItem(Category, categoryCount, items, itemCount);
        }

        else if (choice == 6) {
            int deleteChoice;

            cout << "\033[1;36m\n===== DELETION CHOICES =====\033[0m\n";
            cout << "\033[1;33m1.\033[0m Delete Item\n";
            cout << "\033[1;33m2.\033[0m Delete Category\n";

            cout << "\nEnter Your Choice (1-2): ";
            cin >> deleteChoice;
            while (true) {
                if(deleteChoice ==1 || deleteChoice == 2) break;
                cout << "\033[1;31mInvalid Choice!\033[0m\n";
                cout << "Enter Your Choice (1-2): ";
                cin >> deleteChoice;
            }

            if (deleteChoice == 1) deleteItem(Category, categoryCount, items, itemCount);
            else if (deleteChoice == 2) deleteCategory(Category, categoryCount, items, itemCount);
        }

        else if (choice == 7) {
            showLowStock(Category, categoryCount, items, itemCount);
        }

        else if(choice == 8) {
            saveData(Category, categoryCount, items, itemCount);
        }
        else if (choice == 9) {
            saveData(Category, categoryCount, items, itemCount);
            break;
        }
    }

    for (int i = 0; i < categoryCount; i++) {
        delete[] items[i];
    }

    delete[] items;
    delete[] itemCount;
    delete[] Category;

    return 0;
}