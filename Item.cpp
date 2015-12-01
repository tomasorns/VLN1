#include "Item.h"

using namespace std;

//overload operators for item
istream& operator>> (istream& in, Item& item)
{
    string yb; string yd;
    getline(in, item.name);
    cout << "Sex (M/F): ";
    getline(in, item.sex);
    cout << "Year born: ";
    getline(in, yb);
    cout << "Year dead: ";
    getline(in, yd);
    item.yearBorn = atoi(yb.c_str());
    item.yearDead = atoi(yd.c_str());
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
