#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

using namespace std;

struct Item{
    string name;
    string sex;
    string yearBorn;
    string yearDead;
};

ostream& operator<< (ostream& out, const Item& item);

istream& operator>> (istream& out, Item& item);

#endif // ITEM_H
