// ECE 312(H) PA4
// Vidita Bhotika
// VB9359
// Spring 2025
// Speight 

#include "Invent.h"
#include "MyString.h"
#include <assert.h>
#include <stdio.h>

#define MAX_CUSTOMERS 1000
Customer customers[MAX_CUSTOMERS];
int num_customers = 0;

Customer inventoryy = {NULL, 0, 0, 0, 0};


/* you'll probably need several more global variables */
/* and of course, you have a few functions to write */

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    StringDestroy(&(inventoryy.name));
    inventoryy.books = 0;
    inventoryy.dice = 0;
    inventoryy.figures = 0;
    inventoryy.towers = 0;

    for (int i = 0; i < num_customers; i++) {
        StringDestroy(&(customers[i].name));
        customers[i].books = 0;
        customers[i].dice = 0;
        customers[i].figures = 0;
        customers[i].towers = 0;
    }

    num_customers = 0;

}

void processSummarize() {
    String books = StringCreate("Books");
    String dice = StringCreate("Dice");
    String figures = StringCreate("Figures");
    String towers = StringCreate("Towers");

    //Inventory summary
    printf("There are %d books %d Dice %d Figures and %d Towers in inventory\n", inventoryy.books, inventoryy.dice, inventoryy.figures, inventoryy.towers);

    //Number customers
    printf("we have had a total of %d different customers\n", num_customers);

    //Winners
    int booksMostInd = -1;
    int diceMostInd = -1;
    int figuresMostInd = -1;
    int towersMostInd = -1;

    int mostBooks = 0;
    int mostDice = 0;
    int mostFigures = 0;
    int mostTowers = 0;

    for (int i = 0; i < num_customers; i++) {
        if (customers[i].books > mostBooks) {
            mostBooks = customers[i].books;
            booksMostInd = i;
        }

        if (customers[i].dice > mostDice) {
            mostDice = customers[i].dice;
            diceMostInd = i;
        }

        if (customers[i].figures > mostFigures) {
            mostFigures = customers[i].figures;
            figuresMostInd = i;
        }

        if (customers[i].towers > mostTowers) {
            mostTowers = customers[i].towers;
            towersMostInd = i;
        }
    }

    if (mostBooks) {
        StringPrint(&(customers[booksMostInd].name));
        printf(" has purchased the most Books (%d)\n", mostBooks);
    } else {
        printf("no one has purchased any Books\n");
    }

    if (mostDice) {
        StringPrint(&(customers[diceMostInd].name));
        printf(" has purchased the most Dice (%d)\n", mostDice);
    } else {
        printf("no one has purchased any Dice\n");
    }

    if (mostFigures) {
        StringPrint(&(customers[figuresMostInd].name));
        printf(" has purchased the most Figures (%d)\n", mostFigures);
    } else {
        printf("no one has purchased any Figures\n");
    }

    if (mostTowers) {
        StringPrint(&(customers[towersMostInd].name));
        printf(" has purchased the most Towers (%d)\n", mostTowers);
    } else {
        printf("no one has purchased any Towers\n");
    }

    StringDestroy(&books);
    StringDestroy(&dice);
    StringDestroy(&figures);
    StringDestroy(&towers);
    

}

void processPurchase() {
    String books = StringCreate("Books");
    String dice = StringCreate("Dice");
    String figures = StringCreate("Figures");
    String towers = StringCreate("Towers");

    String customerName;
    readString(&customerName);

    String itemPurchased;
    readString(&itemPurchased);

    int numPurchased;
    readNum(&numPurchased);

    int currentAmount;
    if (StringIsEqualTo(&itemPurchased, &books)) {
        currentAmount = inventoryy.books;
    } else if (StringIsEqualTo(&itemPurchased, &dice)) {
        currentAmount = inventoryy.dice;
    } else if (StringIsEqualTo(&itemPurchased, &figures)) {
        currentAmount = inventoryy.figures;
    } else {
        currentAmount = inventoryy.towers;
    }

    if (currentAmount < numPurchased) {
        printf("Sorry ");
        StringPrint(&customerName);
        printf(", we only have %d ", currentAmount);
        StringPrint(&itemPurchased);
        printf("\n");
    
        StringDestroy(&customerName);
        StringDestroy(&itemPurchased);
        StringDestroy(&books);
        StringDestroy(&dice);
        StringDestroy(&figures);
        StringDestroy(&towers);
        return;

    } else if (numPurchased < 1) {
        StringDestroy(&customerName);
        StringDestroy(&itemPurchased);
        StringDestroy(&books);
        StringDestroy(&dice);
        StringDestroy(&figures);
        StringDestroy(&towers);
        return;
    }

    int index = -1;

    
    for (int i = 0; i < num_customers; i++) {

        if (StringIsEqualTo(&customerName, &(customers[i].name))) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        num_customers++;
        index = num_customers - 1;
        Customer newCustomer = {customerName, 0, 0, 0, 0};
        customers[index] = newCustomer;
    } else {
        StringDestroy(&customerName);
    }

    if (StringIsEqualTo(&itemPurchased, &books)) {
        customers[index].books += numPurchased;
        inventoryy.books -= numPurchased;
    } else if (StringIsEqualTo(&itemPurchased, &dice)) {
        customers[index].dice += numPurchased;
        inventoryy.dice -= numPurchased;
    } else if (StringIsEqualTo(&itemPurchased, &figures)) {
        customers[index].figures += numPurchased;
        inventoryy.figures -= numPurchased;
    } else {
        customers[index].towers += numPurchased;
        inventoryy.towers -= numPurchased;
    }
    
    StringDestroy(&itemPurchased);
    StringDestroy(&books);
    StringDestroy(&dice);
    StringDestroy(&figures);
    StringDestroy(&towers);
    
}

void processReturn() {
    String books = StringCreate("Books");
    String dice = StringCreate("Dice");
    String figures = StringCreate("Figures");
    String towers = StringCreate("Towers");

    String customerName;
    readString(&customerName);

    String itemReturned;
    readString(&itemReturned);

    int numReturned;
    readNum(&numReturned);

    int index = -1;

    for (int i = 0; i < num_customers; i++) {
        if(StringIsEqualTo(&(customers[i].name), &customerName)) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Sorry ");
        StringPrint(&customerName);
        printf(", we do not have you in our database\n");

        StringDestroy(&customerName);
        StringDestroy(&itemReturned);
        StringDestroy(&books);
        StringDestroy(&dice);
        StringDestroy(&figures);
        StringDestroy(&towers);
        return;
    }

    int currentAmount;
    if (StringIsEqualTo(&itemReturned, &books)) {
        currentAmount = customers[index].books;
    } else if (StringIsEqualTo(&itemReturned, &dice)) {
        currentAmount = customers[index].dice;
    } else if (StringIsEqualTo(&itemReturned, &figures)) {
        currentAmount = customers[index].figures;
    } else {
        currentAmount = customers[index].towers;
    }

    if (currentAmount < numReturned) {
        StringPrint(&customerName);
        printf(", you do not have %d ", numReturned);
        StringPrint(&itemReturned);
        printf("\n");

        StringDestroy(&customerName);
        StringDestroy(&itemReturned);
        StringDestroy(&books);
        StringDestroy(&dice);
        StringDestroy(&figures);
        StringDestroy(&towers);
        return;
    }

    int index2 = -1;
    
    for (int i = 0; i < num_customers; i++) {

        if (StringIsEqualTo(&customerName, &(customers[i].name))) {
            index2 = i;
            //num_customers++;
            break;
        }
    }

   
    StringDestroy(&customerName);


    if (StringIsEqualTo(&itemReturned, &books)) {
        customers[index2].books -= numReturned;
        inventoryy.books += numReturned;
    } else if (StringIsEqualTo(&itemReturned, &dice)) {
        customers[index2].dice -= numReturned;
        inventoryy.dice += numReturned;
    } else if (StringIsEqualTo(&itemReturned, &figures)) {
        customers[index2].figures -= numReturned;
        inventoryy.figures += numReturned;
    } else {
        customers[index2].towers -= numReturned;
        inventoryy.towers += numReturned;
    }
    
    StringDestroy(&itemReturned);
    StringDestroy(&books);
    StringDestroy(&dice);
    StringDestroy(&figures);
    StringDestroy(&towers);
    
}

void processInventory() {
    String books = StringCreate("Books");
    String dice = StringCreate("Dice");
    String figures = StringCreate("Figures");
    String towers = StringCreate("Towers");

    String purchaseType;
    readString(&purchaseType);
    
    int purchaseAmount;
    readNum(&purchaseAmount);

    if (StringIsEqualTo(&books, &purchaseType)) {
        inventoryy.books += purchaseAmount;
    } else if (StringIsEqualTo(&dice, &purchaseType)) {
        inventoryy.dice += purchaseAmount;
    } else if (StringIsEqualTo(&figures, &purchaseType)) {
        inventoryy.figures += purchaseAmount;
    } else {
        inventoryy.towers += purchaseAmount;
    }

    StringDestroy(&books);
    StringDestroy(&dice);
    StringDestroy(&figures);
    StringDestroy(&towers);
    StringDestroy(&purchaseType);
    
}
