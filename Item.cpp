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
    out << "Name:  " << item.name << endl;
    out << "Sex (M/F): " << item.sex << endl;
    out << "Year born: " << item.yearBorn << endl;
    out << "Year dead: " << item.yearDead << endl;
    return out;
}
