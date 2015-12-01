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
    void listHelp();

    // Uses itemManager to display the list according to
    // given command
    void list();

    // Uses itemManager to search the list
    void search();

    // Uses itemManager to add item to the list
    void addItem(istream& in);

    // Displays every instance in the list and asks user
    // to enter id of which item he/she wants to remove from
    // the list
    void removeItemById();

    // Executes command entered to in the program, returns
    // true if the repl should continue
    bool executeCommand(string command);

    // Starts a read-evaluate-print loop
    void repl();

};

#endif // CONSOLEINDEX_H
