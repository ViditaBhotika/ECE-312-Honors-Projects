// Set <Project5.cpp>
// ECE 312 Project 5 submission by
// <Your Name Here>
// <Your EID>
// Slip days used: <0>
// Fall 2023

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Set.h"

/*
 * Several of the required functions have been written already
 * You may use these functions as-is or you may modify them in any way.
 * Please NOTE, you are responsible for ensuring that the functions work correctly in
 * your project solution. Just because the function works correctly in my solution does
 * NOT mean that the function will work correctly in yours.
 */

/*
 * Design NOTES:
 *
 * The design provided in this starter kit assumes
 * (1) empty sets will be represented with length == 0 and elements == nullptr (i.e., address 0)
 * (2) amortized doubling is not used, and capacity is ignored/unused. Functions should assume that
 * the amount of storage available in the elements[] array is equal to length
 */



/* done for you already */
void destroySet(Set* self) {
    free(self->elements);
}

/* done for you already */
void createEmptySet(Set* self) {
    self->len = 0;
    self->elements = nullptr;
}

/* done for you already */
void createSingletonSet(Set* self, int x) {
    self->elements = (int*) malloc(sizeof(int));
    self->elements[0] = x;
    self->len = 1;
}

/* done for you already */
void createCopySet(Set* self, const Set* other) {
    self->elements = (int*) malloc(other->len * sizeof(int));
    for (int k = 0; k < other->len; k += 1) {
        self->elements[k] = other->elements[k];
    }
    self->len = other->len;
}

/* done for you already */
void assignSet(Set* self, const Set* other) {
    if (self == other) { return; }

    destroySet(self);
    createCopySet(self, other);
}

/* return true if x is an element of self */
bool isMemberSet(const Set* self, int x) {
    int length = self -> len;
    int lowInd = 0;
    int highInd = length - 1;
    while (length != 0) {
        int midInd = (lowInd + highInd) / 2;
        if (self->elements[midInd] == x) {
            return 1;
        } else if (self->elements[midInd] > x) {
            highInd = midInd - 1;
        } else {
            lowInd = midInd + 1;
        }

        length = highInd - lowInd + 1;
    }

    return 0;
}

/*
 * add x as a new member to this set.
 * If x is already a member, then self should not be changed
 * Be sure to restore the design invariant property that elemnts[] remains sorted
 * (yes, you can assume it is sorted when the function is called, that's what an invariant is all about)
 */
void insertSet(Set* self, int x) {
    int length = self -> len;
    int lastI;
    for (int i = 0; i <= length; i++) {
        if (i == length) {
            self->elements = (int*)realloc(self->elements, sizeof(int) * (length + 1));
            length++;
            self->elements[length-1] = x;
            self->len = length;
            return;
        }
        if (self->elements[i] == x) { // item already exists in set
            return;
        }
         
        if (x < self->elements[i]) { // item is less than element being compared, so insert item at this spot
            self->elements = (int*)realloc(self->elements, sizeof(int) * (length + 1));
            length++;
            lastI = i;
            break;
        }
    }

    int numBeingReplaced;
    int numReplacing = x;
    for (int i = lastI; i < length; i++) {
        if (i == length - 1) {
            self->elements[i] = numReplacing;
        }
        numBeingReplaced = self->elements[i];
        self->elements[i] = numReplacing;
        numReplacing = numBeingReplaced;
    }
    self->len = length;
    return;
}


/*
 * don't forget: it is OK to try to remove an element
 * that is NOT in the set.
 * If 'x' is not in the set 'self', then
 * removeSet should do nothing (it's not an error)
 * Otherwise, ('x' IS in the set), remove x. Be sure to update self->length
 * It is not necessary (nor recommended) to call malloc -- if removing an element means the
 * array on the heap is "too big", that's almost certainly OK, and reallocating a smaller array
 * is almost definitely NOT worth the trouble
 */
void removeSet(Set* self, int x) {
    if (self->len == 0) {
        return;
    }

    int curr;

    for (int i = 0; i <= self->len; i++) {
        if (i == self->len) {
            return;
        }

        if (self->elements[i] == x) {
            curr = i;
            break;
        }
    }

    for (int j = curr; j < (self->len) - 1; j++) {
        self->elements[j] = self->elements[j+1];
    }

    self->elements = (int*)realloc(self->elements, ((self->len) - 1) * sizeof(int));
    (self->len)--;

}

/* done for you already */
void displaySet(const Set* self) {
    int k;

    printf("{");

    if (self->len == 0) {
        printf("}");
    }
    else {
        for (k = 0; k < self->len; k += 1) {
            if (k < self->len - 1) {
                printf("%d,", self->elements[k]);
            } else {
                printf("%d}", self->elements[k]);
            }
        }
    }
}

/* return true if self and other have exactly the same elements */
bool isEqualToSet(const Set* self, const Set* other) {
    if (self->len != other->len) { // if the sets aren't same length, they can't be equal
        return 0;
    }

    for (int i = 0; i < self->len; i++) { // compare each element in self to the element at the same index in other
        if (self->elements[i] != other->elements[i]) {
            return 0;
        }
    }
    
    return 1;
}

/* return true if every element of self is also an element of other */
bool isSubsetOf(const Set* self, const Set* other) {
    if (self->len > other->len) { //subset size can't be larger than set size
        return 0;
    } 

    int selfInd = 0;
    int otherInd = 0;

    while (selfInd < self->len) {
        if (otherInd >= other->len) {
            return 0;
        } 

        if (self->elements[selfInd] != other->elements[otherInd]) {
            otherInd++;
        } else {
            otherInd++;
            selfInd++;
        }
    }

    return 1;
}

/* done for you */
bool isEmptySet(const Set* self) {
    return self->len == 0;
}

/* remove all elements from self that are not also elements of other */
void intersectFromSet(Set* self, const Set* other) {
    if (self->len == 0) {
        return;
    } else if (other->len == 0) {
        assignSet(self, other);
        return;
    } else if (isEqualToSet(self, other)) { // sets are equal, so intersection is self
        return;
    }

    Set* newSet = (Set*) malloc(sizeof(Set));
    newSet->len = 0;
    newSet->elements = NULL;

    int selfInd = 0;
    int otherInd = 0;
    int newSetInd = 0;

    while (selfInd < self->len && otherInd < other->len) {
        if (self->elements[selfInd] > other->elements[otherInd]) { // no hope of matching current element in other
            otherInd++;
        } else if (self->elements[selfInd] < other->elements[otherInd]) { // no hope of matching current element in self
            selfInd++;
        } else { // elements are same
            newSet->len++;
            newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));
            newSet->elements[newSetInd] = self->elements[selfInd];
            selfInd++; //following 3 lines don't impact final set if we decide we are done
            otherInd++;
            newSetInd++;
        }
    }

    assignSet(self, newSet);
    destroySet(newSet);
    free(newSet);


}


/* remove all elements from self that are also elements of other */
void subtractFromSet(Set* self, const Set* other) {
    if (other->len == 0 || self->len == 0) {
        return;
    } else if (isEqualToSet(self,other)) {
        destroySet(self);
        createEmptySet(self);
        return;
    }

    Set* newSet = (Set*) malloc(sizeof(Set));
    newSet->len = 0;
    newSet->elements = NULL;

    int selfInd = 0;
    int otherInd = 0;
    int newSetInd = 0;

    while(selfInd < self->len) {
        if (otherInd >= other->len) { //other array has been completely iterated, so now we add rest of self to new array
            newSet->len++;
            newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));

            newSet->elements[newSetInd] = self->elements[selfInd];
            newSetInd++;
            selfInd++;
        } else {
            if (self->elements[selfInd] == other->elements[otherInd]) {
                selfInd++;
                otherInd++;
            } else if (self->elements[selfInd] > other->elements[otherInd]) {
                otherInd++;
            } else {
                newSet->len++;
                newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));

                newSet->elements[newSetInd] = self->elements[selfInd];
                newSetInd++;
                selfInd++;
            }
        }
    }

    assignSet(self, newSet);
    destroySet(newSet);
    free(newSet);
}

/* add all elements of other to self (obviously, without creating duplicate elements) */
void unionInSet(Set* self, const Set* other) {
    if (self->len == 0) { // self is empty, so copy other into self and return
        assignSet(self, other);
        return;
    } else if (other->len == 0) { // other is empty, so leave self unchanged (even if self is empty)
        return;
    } else if (isSubsetOf(self, other)) {
        assignSet(self, other);
        return;
    } else if (isSubsetOf(other, self)) {
        return;
    }

    Set* newSet = (Set*) malloc(sizeof(Set));
    newSet->len = 0;
    newSet->elements = NULL;

    int selfInd = 0;
    int otherInd = 0;
    int newSetInd = 0;

    while (selfInd < self->len && otherInd < other->len) {
        newSet->len++;
        newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));
        if (self->elements[selfInd] == other->elements[otherInd]) {
            newSet->elements[newSetInd] = self->elements[selfInd];
            selfInd++;
            otherInd++;
        } else if (self->elements[selfInd] < other->elements[otherInd]) {
            newSet->elements[newSetInd] = self->elements[selfInd];
            selfInd++;
        } else {
            newSet->elements[newSetInd] = other->elements[otherInd];
            otherInd++;
        }

        newSetInd++;
    }

    if (selfInd < self->len) {
        for (int i = selfInd; i < self->len; i++) {
            newSet->len++;
            newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));
            newSet->elements[newSetInd] = self->elements[i];
            newSetInd++;
        }
    } else if (otherInd < other->len) {
        for (int i = otherInd; i < other->len; i++) {
            newSet->len++;
            newSet->elements = (int*)realloc(newSet->elements, (newSet->len)*sizeof(int));
            newSet->elements[newSetInd] = other->elements[i];
            newSetInd++;
        }
    }

    assignSet(self, newSet);
    destroySet(newSet);
    free(newSet);
}
