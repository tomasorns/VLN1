#ifndef REPOSITORIES_H
#define REPOSITORIES_H

#include <QtSql>

#include "itemManager.h"

class dbException {};

class repositories{
public:
    // Setups function, start db connection and creates tables
    void setup();

    // Adds scientist to db
    void addScientist(Item item);

    // Add computer to db
    void addComputer(Computer cmp);

    // modifies scientist in db
    void modScientists(Item item);

    // modifies computer in db
    void modComputer(Computer cmp);

    // removes scientist from db
    void removeScientist(string id);

    // removes computer from db
    void removeComputer(string id);

    // Returns all scientists from db
    list<Item> getAllScientists(string command, bool asc);

    // Returns all computers from db
    list<Computer> getAllComputers(string command, bool asc);

    // adds connection to db
    void connect(string sId, string cId);

    // removes connection from db
    void removeConnection(string sId, string cId);

    // returns a list of connections in db
    list<Computer> getConnections(string sId);

    // checks if item exists in db
    bool itemExists(string id, string table);

    // returns scientist with specific id from db
    Item getItemById(string id);

    // returns computer with specific id from db
    Computer getComputerById(string id);

    // checks if scientist table is empty
    bool is_emptyS();

    // checks if computer table is empty
    bool is_emptyC();

    // searches in table scientists
    list<Item> searchItem(string search);

    // searches in table computers
    list<Computer> searchComputer(string search);

    // return next id val in specific table
    int nextVal(string table);

    QSqlDatabase db;
};

#endif // REPOSITORIES_H
