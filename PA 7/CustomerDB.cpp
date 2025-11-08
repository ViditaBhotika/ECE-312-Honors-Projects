/*
 * Name: Vidita Bhotika
 * EID: vb9359
 * PA7
 * Speight, Spring 2025
 */
 #include <iostream>
 #include <cassert>
 #include "UTString.h"
 #include "CustomerDB.h"
 
 using namespace std;
 
 const int default_capacity = 1;
 
 Customer::Customer(UTString name) { // done, please do not edit
     this->books = 0;
     this->dice = 0;
     this->figures = 0;
     this->towers = 0;
     this->name = name;
 }
 
 CustomerDB::CustomerDB(void) { // done, please do not edit
     this->capacity = default_capacity;
     this->data = new Customer[this->capacity];
     this->length = 0;
 }
 
 int CustomerDB::size(void) { // done, please do not edit
     return this->length;
 }
 
 CustomerDB::~CustomerDB(void) { // done, please do not edit
     delete[] this->data;
 }
 
 
 
 void CustomerDB::clear(void) { // done, please do not edit
     delete[] this->data;
     this->capacity = default_capacity;
     this->data = new Customer[this->capacity];
     this->length = 0;
 }
 
 Customer& CustomerDB::operator[](int k) { // done, please do not edit
     assert(k >= 0 && k < this->length);
     return this->data[k];
 }
 
 Customer& CustomerDB::operator[](UTString name) { // not done, your effort goes here
   //TODO
    for (int i = 0; i < this->length; i++) {
        if (this->data[i].name == name) {
            return this->data[i];
        }
    }
 
    this->length++;
     //this->length++;
     if (this->length > this->capacity) {
        this->capacity = this->length;
         //this->capacity++;
        
        Customer* newData = new Customer[this->capacity];

        for (int i = 0; i < this->length -1; i++) {
            newData[i] = this->data[i];
        }

        delete[] this->data;
        this->data = newData;
     
         //this->data = (struct Customer*)realloc(this->data, this->capacity*sizeof(struct Customer));
     }
     
     this->data[length-1] = Customer(name);
     return this->data[length-1];
     
 }
 
 bool CustomerDB::isMember(UTString name) { 
   //TODO
     for (int i = 0; i < this->length; i++) {
         if (this->data[i].name == name) {
             return true;
         }
     }
 
     return false;
 }
 
