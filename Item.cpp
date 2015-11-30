#include "Item.h"

using namespace std;

//override operators for item

istream& operator>> (istream& in, Item& item)
{
    getline(in, item.name);
    cout << "Sex (M/F): ";
    getline(in, item.sex);
    cout << "Year born: ";
    getline(in, item.yearBorn);
    cout << "Year dead: ";
    getline(in, item.yearDead);
    return in;
}

ostream& operator<< (ostream& out, const Item& item)
{
    out << item.id;
    out << ";" << item.name;
    out << ";" << item.sex;
    out << ";" << item.yearBorn;
    out << ";" << item.yearDead;
    return out;
}
