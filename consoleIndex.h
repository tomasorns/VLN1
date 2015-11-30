#ifndef CONSOLEINDEX_H
#define CONSOLEINDEX_H

#include "itemManager.h"

using namespace std;

class consoleIndex
{
public:
    void start();

private:
    itemManager item_manager;

    void welcome();

    void help();

    void listHelp();

    void list();

    void search();

    void addItem(istream& in);

    void removeItemByName();

    bool executeCommand(string command);

    void repl();

};

#endif // CONSOLEINDEX_H
