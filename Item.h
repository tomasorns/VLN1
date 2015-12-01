#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;


// Struct that keeps track of item (person)
struct Item{
    int id;
    string name;
    string sex;
    int yearBorn;
    int yearDead;
};

// Overloaded operators
ostream& operator<< (ostream& out, const Item& item);

istream& operator>> (istream& out, Item& item);

#endif // ITEM_H
