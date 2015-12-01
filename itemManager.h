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

class itemManager{
public:
    // Adds item to file
    void addItem(Item item);

    // Removes item from file
    void removeItem(Item rItem);

    // Checks if item exists on file, if any instance of
    // the string 'search' is in the file it returns true
    // whether it's a part of name or year or anything else
    bool itemExists(string search);

    // Returns list of items that matches any instance of
    // the string 'search' is in the file it returns true
    // whether it's a part of name or year or anything else
    list<Item> searchItem(string search);

    // Reconstructs instance of item after reading it from
    // .txt file and returns reconstructed item.
    Item reconstructItem(string line);

    // Uses printList to print a list according to given
    // command after sorting it properly. This function sorts
    // by name ascending, descending, females first, males first,
    // by year of birth ascending and year of death ascending
    void getAllItemsListed(string command);

    // Returns list of items that are included in txt file
    list<Item> getAllItems();

    // Function to get next value for id according to what the
    // highest id is in the .txt file
    void getNextValId();

    // Sets the private int id to new value
    void setId(int newId){id = newId;}

    // Returns private int id
    int getId(){return id;}

    // Prints list of items
    void printList(list<Item> item);

    // Returns item with id equal to string id.
    Item getItemById(string id);

    // Returns true if items exists with given id, false otherwise
    bool itemExistsId(string id);

    // Checks if file is empty, returns true if empty, false otherwise
    bool is_empty();
private:
    // Keeps track of next id
    int id;
};

#endif // ITEMMANAGER_H
