#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <list>
#include <algorithm>

#include "Item.h"
#include "Computer.h"
#include "repositories.h"

class itemManager{
public:
    // Adds item to db
    void addItem(Item item);

    // Add computer to db
    void addComputer(Computer cmp);

    // modifies item in db
    void modItem(Item item);

    // modifies computer in db
    void modComputer(Computer cmp);

    // Removes item from db
    void remove(string id, string table);

    // Checks if item exists in this table with this id
    bool itemExistsId(string id, string table);

    // Returns list of items that matches any instance of
    // the string 'search' is in the db it returns
    // whether it's a part of name or year or anything else
    list<Item> searchItem(string search);

    // Same as above but for computers
    list<Computer> searchComputer(string search);


    // Returns a list of all items from db
    list<Item> getAllItemsListed(string command);

    // Returns a list of all computers for db
    list<Computer> getAllComputersListed(string command);

    // Function to get next value for id according to what the
    // highest id is in specified db table
    int getNextValId(string table);

    // DB table name for Scientists
    string getTs(){return sTable;}

    // DB table name for Computers
    string getTc(){return cTable;}

    // Returns item with id equal to string id.
    Item getItemById(string id);

    // returns Computer with id equal to string id
    Computer getComputerById(string id);

    // middle step to open db and create tables
    void setupRepo();

    // connects scientists with computer
    void connect(string sId, string cId);

    // removes connection between scientist and computer
    void removeConnection(string sId, string cId);

    // Returns a list of all computers that are connected with scientist with id sId
    list<Computer> getConnections(string sId);

    // Checks if scientists table is empty
    bool is_emptyS();

    // Checks if computer table is empty
    bool is_emptyC();
private:
    string sTable = "Scientists";

    string cTable = "Computers";
};

#endif // ITEMMANAGER_H
