/*
 * Name: Vidita Bhotika
 * EID: vb9359
 * PA7
 * Speight, Spring 2025
 */

 #include "Customer.h"
 #include "CustomerDB.h"
 #include "UTString.h"
 #include <iostream>
 #include <stdio.h>

 using namespace std;
 
 void readString(UTString &);
 void readNum(int &);
 
 CustomerDB database;
 
 int num_books = 0;
 int num_dice = 0;
 int num_figures = 0;
 int num_towers = 0;
 
 /* clear the inventory and reset the customer database to empty */
 void reset(void) {
   database.clear();
   num_books = 0;
   num_dice = 0;
   num_figures = 0;
   num_towers = 0;
 }
 
 /*
  * selectInventItem is a convenience function that allows you
  * to obtain a pointer to the inventory record using the item type name
  * word must be "Books", "Dice", "Figures" or "Towers"
  * for example the expression *selectInventItem("Books") returns the
  * current global variable for the number of books in the inventory
  */
 int *selectInventItem(UTString word) {
   if (word == "Books") {
     return &num_books;
   } else if (word == "Dice") {
     return &num_dice;
   } else if (word == "Figures") {
     return &num_figures;
   } else if (word == "Towers") {
     return &num_towers;
   }
 
   /* NOT REACHED */
   return 0;
 }
 
 /*
  * this overload of selectInventItem is similar to selectInventItem above,
  * however this overload takes a Customer as a second argument and selects the
  * data member of that Customer that matches "word". The function returns a
  * pointer to one of the three data members from the specified customer.
  */
 int *selectInventItem(UTString word, Customer &cust) {
   if (word == "Books") {
     return &cust.books;
   } else if (word == "Dice") {
     return &cust.dice;
   } else if (word == "Figures") {
     return &cust.figures;
   } else if (word == "Towers") {
     return &cust.towers;
   }
 
   /* NOT REACHED */
   return 0;
 }
 
 /*
  * findMax searches through the CustomerDB "database" and returns the Customer
  * who has purchased the most items of the specified type.
  * type must be one of "Books", "Dice", "Figures" or "Towers".
  *
  * Note: if two or more Customers are tied for having purchased the most of that
  * item type then findMax returns the first Customer in the CustomerDB who has
  * purchased that maximal quantity.
  *
  * Note: in the special case (invalid case) where there are zero Customers in
  * the CustomerDB, fundMax returns a null pointer (0)
  */
 Customer *findMax(UTString type) {
   Customer *result = 0;
   int max = 0;
   for (int k = 0; k < database.size(); k += 1) {
     Customer &cust = database[k];
     int *p = selectInventItem(type, cust);
     if (*p > max) {
       max = *p;
       result = &cust;
     }
   }
 
   return result;
 }
 
 void processPurchase() {
   // TODO
   UTString type = UTString();
   int amount;
   UTString custName = UTString();
   
   readString(custName);
   readString(type);
   readNum(amount);
 
   int currentAmount = *(selectInventItem(type));
   if ((currentAmount) < amount) {
     cout << "Sorry " << custName.c_str() << ", we only have " << currentAmount << " "<< type.c_str() << endl;
    //  custName.~UTString();
    //  type.~UTString();
     return;
   } else if (amount == 0) {
     //custName.~UTString();
     //type.~UTString();
     return;
   }
 
   *(selectInventItem(type, database[custName])) += amount;
   *(selectInventItem(type)) -= amount;
 
   //custName.~UTString();
   //type.~UTString();
   return;
 }
 
 void processReturn() {
   // TODO
   UTString type = UTString();
   int amount;
   UTString custName = UTString();
 
   readString(custName);
   readString(type);
   readNum(amount);
   
 
   if (!database.isMember(custName)) {
     cout << "Sorry " << custName.c_str() << ", we do not have you in our database" << endl;
     //type.~UTString();
     //custName.~UTString();
     return;
   } else if (*(selectInventItem(type, database[custName])) < amount) {
     cout << custName.c_str() << ", you do not have " << amount << " " << type.c_str() << endl;
     //type.~UTString();
     //custName.~UTString();
     return;
   }
 

   *(selectInventItem(type)) += amount;
   *(selectInventItem(type, database[custName])) -= amount;
   return;
   
 }
 
 void processSummarize() {
   // TODO
   UTString books = UTString("Books");
   UTString dice = UTString("Dice");
   UTString figures = UTString("Figures");
   UTString towers = UTString("Towers");
   
   int numBooks = *(selectInventItem(books));
   int numDice = *(selectInventItem(dice));
   int numFigures = *(selectInventItem(figures));
   int numTowers = *(selectInventItem(towers));
 
   Customer* maxBooks = findMax(books);
   Customer* maxDice = findMax(dice);
   Customer* maxFigures = findMax(figures);
   Customer* maxTowers = findMax(towers);
 
   
   cout << "There are " << numBooks << " " << books.c_str() << " " << numDice << " " << dice.c_str() << " " << numFigures << " " << figures.c_str() << " and " << numTowers << " " << towers.c_str() << " in inventory" << endl;
 
   cout << "we have had a total of " << database.size() << " different customers" << endl;
 
   if (maxBooks == 0) {
     cout << "no one has purchased any Books" << endl;
   } else {
     cout << maxBooks->name.c_str() << " has purchased the most Books (" << maxBooks->books << ")" << endl;
   }
 
   if (maxDice == 0) {
     cout << "no one has purchased any Dice" << endl;
   } else {
     cout << maxDice->name.c_str() << " has purchased the most Dice (" << maxDice->dice << ")" << endl;
   }
 
   if (maxFigures == 0) {
     cout << "no one has purchased any Figures" << endl;
   } else {
     cout << maxFigures->name.c_str() << " has purchased the most Figures (" << maxFigures->figures << ")" << endl;
   }
 
   if (maxTowers == 0) {
     cout << "no one has purchased any Towers" << endl;
   } else {
     cout << maxTowers->name.c_str() << " has purchased the most Towers (" << maxTowers->towers << ")" << endl;
   }
 
   /*books.~UTString();
   dice.~UTString();
   figures.~UTString();
   towers.~UTString();*/
   
 }
 
 void processInventory() {
   // TODO
   UTString type = UTString();
   int amount;
   
   readString(type);
   readNum(amount);
   *(selectInventItem(type)) += amount;
   //type.~UTString();
   
 }
