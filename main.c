/*
 * Course: PROG20799 - Data Structures & Algorithm Development - C
 * Student: Shamsheer Khan
 * Student ID: 991661386
 * Date: 18/06/2023
 * Program Description: Assignment 2 - Question 1 - C program that simulates total 
 * sales for an online fruits/vegetables store.
 * Group - 17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITEMS 10

// Represents an item with its ID, name, price, and quantity.
typedef struct {
    int itemID;
    char itemName[15];
    double itemPrice;
    int quantity;
} Item;

// Represents a node in a linked list, containing an item and a pointer to the next node.
typedef struct Node {
    Item item;
    struct Node* next;
} Node;

// Represents a cart list, which consists of a pointer to the head of the linked list.
typedef struct {
    Node* head;
} CartList;

// all the prototypes required for the project
int generateRandomNumber(int min, int max);
void initializeCartList(CartList* cartList);
void addItem(CartList* cartList, int itemID, int quantity);
void updateQuantity(CartList* cartList, int itemID, int newQuantity);
void deleteItem(CartList* cartList, int itemID);
void displayItems(CartList* cartList);
void computePayment(CartList* cartList);
void saveReceipt(CartList* cartList);

/* Main function to test the functionality of the shopping cart program.
 * Initializes the cartList.
 * Adds items to the cartList with random quantities.
 * Performs various operations such as updating quantity and deleting items.
 * Displays the items, computes the payment, and saves the receipt. 
 */
int main() {
    srand(time(0));

    CartList cartList;
    initializeCartList(&cartList);

    for (int i = 1; i <= MAX_ITEMS; i++) {
        int itemID = i;
        int quantity = generateRandomNumber(1, 10);
        addItem(&cartList, itemID, quantity);
    }

    //Step 1: Adds an item with item ID 3 and quantity 5 to the cartList.
    addItem(&cartList, 3, 5);  
    //Step 2: Updates the quantity of the item with item ID 2 to 8 in the cartList.
    updateQuantity(&cartList, 2, 8);  
    //Step 3: Deletes the item with item ID 5 from the cartList.
    deleteItem(&cartList, 5);  
    //Step 4: Displays the items in the cartList along with their details.
    displayItems(&cartList);  
    //Step 5: Calculates the total number of items and the total payment in the cartList.
    computePayment(&cartList); 
    //Step 6: Saves the receipt of the items in the cartList to a file named "receipt.txt".
    saveReceipt(&cartList);  


    return 0;
}

// An array of item names, where the index represents the item ID.
char itemsName[MAX_ITEMS + 1][15] = {"", "Carrot", "Apple", "Orange", "Parsnip", 
"Avocado", "Blueberry", "Cherry", "Asparagus", "Cabbage", "Celery"};

// An array of item prices, where the index represents the item ID.
double itemsPrice[MAX_ITEMS + 1] = {0, 1.5, 2.25, 2.75, 1.25, 0.99, 1.25, 2.25, 
2.00, 3.5, 1.25};

// Generates a random number between min and max (inclusive).
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Initializes the cartList by setting the head pointer to NULL.
void initializeCartList(CartList* cartList) {
    cartList->head = NULL;
}

// Adds an item with the given itemID and quantity to the cartList.
// If the itemID is invalid, prints an error message.
void addItem(CartList* cartList, int itemID, int quantity) {
    if (itemID < 1 || itemID > MAX_ITEMS) {
        printf("Invalid item ID!\n");
        return;
    }

    Item newItem;
    newItem.itemID = itemID;
    strcpy(newItem.itemName, itemsName[itemID]);
    newItem.itemPrice = itemsPrice[itemID];
    newItem.quantity = quantity;

    Node* newNode = (Node*) malloc(sizeof (Node));
    newNode->item = newItem;
    newNode->next = NULL;

    if (cartList->head == NULL) {
        cartList->head = newNode;
    } else {
        Node* curr = cartList->head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = newNode;
    }

    printf("Item added to the cartList.\n");
}

// Updates the quantity of the item with the given itemID in the cartList.
// If the itemID is not found, prints an error message.
void updateQuantity(CartList* cartList, int itemID, int newQuantity) {
    Node* curr = cartList->head;
    while (curr != NULL) {
        if (curr->item.itemID == itemID) {
            curr->item.quantity = newQuantity;
            printf("Quantity updated for item ID %d.\n", itemID);
            return;
        }
        curr = curr->next;
    }

    printf("Item ID %d not found in the cartList.\n", itemID);
}

// Deletes the item with the given itemID from the cartList.
// If the itemID is not found, prints an error message.
void deleteItem(CartList* cartList, int itemID) {
    Node* curr = cartList->head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (curr->item.itemID == itemID) {
            if (prev == NULL) {
                cartList->head = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr);
            printf("Item ID %d deleted from the cartList.\n", itemID);
            return;
        }

        prev = curr;
        curr = curr->next;
    }

    printf("Item ID %d not found in the cartList.\n", itemID);
}


// Displays the items in the cartList along with their details.
// Calculates the total number of items and the total payment.
void displayItems(CartList* cartList) {
    int itemCount = 0;
    double totalPayment = 0.0;

    Node* curr = cartList->head;
    while (curr != NULL) {
        printf("Item ID: %d\n", curr->item.itemID);
        printf("Item Name: %s\n", curr->item.itemName);
        printf("Item Price: $%.2f\n", curr->item.itemPrice);
        printf("Quantity: %d\n", curr->item.quantity);
        printf("------------------------\n");

        itemCount += curr->item.quantity;
        totalPayment += (curr->item.itemPrice * curr->item.quantity);

        curr = curr->next;
    }

    printf("Number of items in the cart: %d\n", itemCount);
    printf("Total payment: $%.2f\n", totalPayment);
}

// Calculates the total number of items and the total payment in the cartList.
// Prints the calculated values.
void computePayment(CartList* cartList) {
    int itemCount = 0;
    double totalPayment = 0.0;

    Node* curr = cartList->head;
    while (curr != NULL) {
        itemCount += curr->item.quantity;
        totalPayment += (curr->item.itemPrice * curr->item.quantity);

        curr = curr->next;
    }

    printf("Number of items in the cart: %d\n", itemCount);
    printf("Total payment: $%.2f\n", totalPayment);
}

// Saves the receipt of the items in the cartList to a file named "receipt.txt".
// Prints a success message if the file is created/opened successfully.
void saveReceipt(CartList* cartList) {
    FILE* file = fopen("receipt.txt", "w");
    if (file == NULL) {
        printf("Unable to create/open the file.\n");
        return;
    }

    fprintf(file, "Receipt\n");
    fprintf(file, "------------------------\n");

    Node* curr = cartList->head;
    while (curr != NULL) {
        fprintf(file, "Item ID: %d\n", curr->item.itemID);
        fprintf(file, "Item Name: %s\n", curr->item.itemName);
        fprintf(file, "Item Price: $%.2f\n", curr->item.itemPrice);
        fprintf(file, "Quantity: %d\n", curr->item.quantity);
        fprintf(file, "------------------------\n");

        curr = curr->next;
    }

    fclose(file);
    printf("Receipt saved in the file 'receipt.txt'.\n");
}



