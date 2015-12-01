#include <iostream>
#include <fstream>
#include "consoleIndex.h"

using namespace std;

void consoleIndex::welcome(){
    // Welcomes the user to console app
    cout << "Welcome to MonkeyBusiness v1.0" << endl
         << "Type 'help' for help" << endl;
}

void consoleIndex::help(){
    // Displays help menu
    cout << "Commands available:" << endl
        << "help:               displays this help menu" << endl
        << "add:                adds new item to list" << endl
        << "remove:             removes item from list" << endl
        << "list -h             show help menu for list, commands on how to arrange the list" << endl
        << "search 'string':    searches for 'string' in list and returns all information" << endl
        << "quit:               quits the Monkey Business" << endl;
}

void consoleIndex::listHelp(){
    // Displays help menu for list commands
    cout << "Command for list command:" << endl
         << "list -a:           list in ascending order by name" << endl
         << "list -d:           list in descending order by name" << endl
         << "list -id           list arranged by id" << endl
         << "list -mf:          lists males first, then females" << endl
         << "list -ff:          lists females first, then males" << endl
         << "list -yb:          lists after year born, earlies first" << endl
         << "list -yd:          lists after year dead, earlies first" << endl;

}

void consoleIndex::list(){
    // Calls listHelp if help command is used, otherwise it prints all items that
    // correspons to input command
    string listCommand;
    cin >> listCommand;
    if (item_manager.is_empty()){
        cout << "The list is empty." << endl;
    } else {
        if (listCommand == "-h"){
            listHelp();
        } else if(listCommand == "-id"){ // this does the same as the on below ¯\_(ツ)_/¯
            item_manager.getAllItemsListed(listCommand);
        } else if((listCommand == "-a") || (listCommand == "-d") || (listCommand == "-mf") || (listCommand == "-ff") || (listCommand == "-yb") || (listCommand == "-yd")){
            item_manager.getAllItemsListed(listCommand);
        } else {
            cout << "List Command '" << listCommand << "' unknown, type 'list -h' to see available commands" << endl;
        }
    }
}

void consoleIndex::search(){
    // Checks if item exists in list, and searches it only if it existm
    // This is done so the search function doesn't return empty item
    string itemName;
    cin >> itemName;
    if(item_manager.is_empty()){
        cout << "The list is empty." << endl;
    } else {
        if(item_manager.itemExists(itemName)){
            item_manager.searchItem(itemName);
        } else {
            cout << "Person not found." << endl;
        }
    }
}

void consoleIndex::addItem(istream &in){
    // Makes new instance of item and uses overloaded operator to read in
    Item item;
    in >> item;
    item_manager.addItem(item);
}

void consoleIndex::removeItemById(){
    // Displays all items in sorted by ascending id, then asks the user to enter
    // the id of whom they want to remove, and removes only if item with entered
    // id exists.
    item_manager.getAllItemsListed("-id");
    cout << "Enter the id of person you want to remove [enter 'c' to cancel]:" << endl;
    string id;
    cin >> id;
    if (id != "c"){
        if(item_manager.itemExistsId(id)){
            item_manager.removeItem(item_manager.getItemById(id));
            if (item_manager.is_empty()){
                cout << "You've emptied the list, YOU MONSTER!" << endl;
            } else {
                item_manager.getAllItemsListed("-id");
            }
        } else {
            cout << "Item with id = " << id << "not found" << endl;
        }
    }
}


bool consoleIndex::executeCommand(string command){
    // executes entered commands, if there is a space between commands, f.ex. 'list -id'
    // it matches list here below and clears whitespaces and the sends '-id' to the
    // function as cin
    if ((command == "help") || (command == "h")){
        help();
    } else if ((command == "quit") || (command == "q")){
        return false;
    } else if (command == "add"){
        cout << "Enter the following information:" << endl;
        cout << "Name: ";
        ws(cin);
        addItem(cin);
    } else if (command == "list") {
        ws(cin);
        list();
    } else if (command == "search") {
        ws(cin);
        search();
    } else if (command == "remove") {
        removeItemById();
    } else {
        cout << "Command " << command << " not found." << endl;
    }

    return true;
}

void consoleIndex::repl(){
    // Starts a read-evaluate-print loop
    string command;
        do {
            cout << "MonkeyBusiness> ";
        } while(cin >> command && executeCommand(command));
        cout << endl << "Is anyone here? Hello?" << endl;
        cout << "Oh.. are you leaving? :(" << endl;
}

void consoleIndex::start(){
    // Start function, the only function called from main function
    // displays welcome screen and info on how to see help menu if
    // needed.
    welcome();
    repl();
}




