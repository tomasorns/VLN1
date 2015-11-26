#include "itemManager.h"

void itemManager::addItem(Item item){
    // add item to data structure
    ofstream file;
    file.open("monkeybusiness.txt");
    file << "test123.\n";
    file.close();
}

void itemManager::removeItem(Item item){
    // remove item from structure
}

bool itemManager::itemExists(string name){
    // check if item exists
    return true;
}

Item itemManager::getItemByName(string name){
    // return item with name
    Item item;
    return item;
}
