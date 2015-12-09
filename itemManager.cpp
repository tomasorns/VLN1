#include "itemManager.h"

void itemManager::addItem(Item item){
    // Adds item to data structure

    item.id = getNextValId("Scientists");
    repositories repo;
    repo.addScientist(item);
}

void itemManager::addComputer(Computer cmp){
    // Add computer to db

    cmp.id = getNextValId("Computers");
    repositories repo;
    repo.addComputer(cmp);
}

void itemManager::modItem(Item item){
    // modifies item in db, simply a "middleman" for consoleIndex and repositories
    repositories repo;
    repo.modScientists(item);
}

void itemManager::modComputer(Computer cmp){
    // modifies computer in db, simply a "middleman" for consoleIndex and repositories
    repositories repo;
    repo.modComputer(cmp);
}

int itemManager::getNextValId(string table){
    // this function is to get next id with info from db
    // so next line can get a id with increment of 1
    repositories repo;
    return repo.nextVal(table);
}

void itemManager::remove(string id, string table){
    // removes for specific table, this way only one function is needed instead of two
    repositories repo;

    if(table=="Scientists"){
        repo.removeScientist(id);
    } else {
        repo.removeComputer(id);
    }

}

bool itemManager::itemExistsId(string id, string table){
    //  Checks if id matches with something in spcified table
    // This is basicly for error handling purposes, if the item does
    // not exist user is notified and the program does not try to
    // work on something that isn't there

    repositories repo;
    return repo.itemExists(id, table);
}

Item itemManager::getItemById(string id){
    // returns item with specific id, very useful when the program only needs
    // one item but not the whole list
    repositories repo;
    return repo.getItemById(id);
}

Computer itemManager::getComputerById(string id){
    // returns computer with specific id, very useful when the program only needs
    // one item but not the whole list
    repositories repo;
    return repo.getComputerById(id);
}

list<Item> itemManager::searchItem(string search){
    // Searches for all instances of 'search' string in scientists table and returns
    // a list of scientists that is easy to print out
    repositories repo;
    return repo.searchItem(search);
}

list<Computer> itemManager::searchComputer(string search){
    // Searches for all instances of 'search' string in computers table and returns
    // a list of computers that is easy to print out
    repositories repo;
    return repo.searchComputer(search);

}

list<Item> itemManager::getAllItemsListed(string command){
    // returns all items in scientists listed for easy printing
    // here it's possible to specify if list should be ordered
    // in ascending or descending when calling the getAllScientists
    // function

    repositories repo;
    list<Item> item;

    if(command == "-id"){
        item = repo.getAllScientists("id", true);
    } else if (command == "-yb"){
        item = repo.getAllScientists("yearborn", true);
    } else if (command == "-yd"){
        item = repo.getAllScientists("yeardead", true);
    } else if (command == "-mf"){
        item = repo.getAllScientists("sex", false);
    } else if (command == "-ff"){
        item = repo.getAllScientists("sex", true);
    } else if (command == "-a"){
        item = repo.getAllScientists("name", true);
    } else if (command == "-d"){
        item = repo.getAllScientists("name", false);
    } else {
        cout << "Unknown list command, type 'list -h' to see all list commands" << endl;
    }
    return item;
}

list<Computer> itemManager::getAllComputersListed(string command){
    // returns all items in computers listed for easy printing
    // here it's possible to specify if list should be ordered
    // in ascending or descending when calling the getAllComputers
    // function

    repositories repo;
    list<Computer> cmp;

    if(command == "-id"){
        cmp = repo.getAllComputers("id", true);
    } else if (command == "-m"){
        cmp  = repo.getAllComputers("make", true);
    } else if (command == "-md"){
        cmp  = repo.getAllComputers("make", false);
    } else if (command == "-ym"){
        cmp  = repo.getAllComputers("yearmade", true);
    } else if (command == "-im"){
        cmp  = repo.getAllComputers("made", false);
    } else if (command == "-a"){
        cmp  = repo.getAllComputers("name", true);
    } else if (command == "-d"){
        cmp  = repo.getAllComputers("name", false);
    } else {
        cout << "Unknown list command, type 'list -h' to see all list commands" << endl;
    }
    return cmp;
}

void itemManager::setupRepo(){
    // This function calls setup in repo, middleman for indexConsole
    repositories repo;
    repo.setup();
}

void itemManager::connect(string sId, string cId){
    // Sends what to connect to db layer
    repositories repo;
    repo.connect(sId,cId);
}

list<Computer> itemManager::getConnections(string sId){
    // Returns a list of all computers that are connected to scientists with id = sId
    repositories repo;
    return repo.getConnections(sId);
}

void itemManager::removeConnection(string sId, string cId){
    // if user needs to remove a connection between a scientist and a computer
    repositories repo;
    repo.removeConnection(sId, cId);
}

bool itemManager::is_emptyS(){
    // Checks if scientists table is empty
    repositories repo;
    return repo.is_emptyS();
}

bool itemManager::is_emptyC(){
    // Checks if computers table is empty
    repositories repo;
    return repo.is_emptyC();
}

