#include "Computer.h"

using namespace std;

//overload operators for item
istream& operator>> (istream& in, Computer& cmp)
{
    string ym;
    getline(in, cmp.name);
    cout << "Make: ";
    getline(in, cmp.make);
    cout << "Year made: ";
    getline(in, ym);
    cout << "Was it built? (Yes/No): ";
    getline(in, cmp.made);
    cmp.yearMade = atoi(ym.c_str());
    return in;
}

ostream& operator<< (ostream& out, const Computer& cmp)
{
    out << cmp.id;
    out << ";" << cmp.name;
    out << ";" << cmp.make;
    out << ";" << cmp.yearMade;
    out << ";" << cmp.made;
    return out;
}
