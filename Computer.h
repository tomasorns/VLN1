#ifndef COMPUTER_H
#define COMPUTER_H


#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;


// Struct that keeps track of computer
struct Computer{
    int id;
    string name;
    string make;
    int yearMade;
    string made;
};

// Overloaded operators
ostream& operator<< (ostream& out, const Computer& cmp);

istream& operator>> (istream& out, Computer& cmp);


#endif // COMPUTER_H
