#ifndef CONSOLEINDEX_H
#define CONSOLEINDEX_H

#include "itemManager.h"

using namespace std;

class consoleIndex
{
public:
    // Starts the console app.
    void start();

private:
    // Make instance of item manager
    itemManager item_manager;


    // Displays welcome message and instructions
    void welcome();

    // Displays help menu with available commands to use
    void help();

    // Displays help menu for list with available commands
    // to use with list
    void sListHelp();

    void cListHelp();

    // Uses itemManager to display list of scientists according to
    // given command
    void sList();

    // Uses itemManager to display list of computers according to
    // given command
    void cList();

    // Uses itemManager to search the list
    void search();

    // Uses itemManager to add item to the list
    void addItem(istream& in);

    // Uses itemManager to add computer to the list
    void addComputer(istream& in);

    // modifies scientist on the list
    void modItem();

    // modifies computer on the list
    void modComputer();

    // Adds connection betweene scientist and computer
    void connect();

    // removes connection between scientist and computer
    void removeConnection();

    // Displays every instance in the list and asks user
    // to enter id of which item he/she wants to remove from
    // the list
    void removeItemById();

    // Executes command entered to in the program, returns
    // true if the repl should continue
    bool executeCommand(string command);

    // Starts a read-evaluate-print loop
    void repl();

    // prints a list of scientists
    void printItem(list<Item> item);

    // prints a list of computers
    void printComputer(list<Computer> cmp);

    // prints all connections
    void printConnections();

};

#endif // CONSOLEINDEX_H
