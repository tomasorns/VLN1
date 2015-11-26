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
    // Displays commands available
    cout << "Commands available:" << endl
        << "help:           displays this help menu" << endl
        << "add:            adds new item to list" << endl
        << "remove:         removes item from list" << endl
        << "list            [-a][-ia][-mf][-ff][-yb][-yd]" << endl
        << "                lists all items in order added" << endl
        << "list -h         show help menu for list, commands on how to arrange the list" << endl
        << "search 'name':  searches for 'name' in list and returns all information" << endl
        << "quit:           quits the Monkey Business" << endl;
}

void consoleIndex::listHelp(){
    cout << "Command for list command:" << endl
         << "list -a:       list in alphabetical order by name" << endl
         << "list -ia:      list in inverted alphabetical order by name" << endl
         << "list -mf:      lists males first, then females" << endl
         << "list -ff:      lists females first, then males" << endl
         << "list -yb:      lists after year born, earlies first" << endl
         << "list -yd:      lists after year dead, earlies first" << endl;

}

void consoleIndex::list(){
    string listCommand;
    cin >> listCommand;
    if (listCommand == "-h"){
        listHelp();
    } else if((listCommand == "-a") || (listCommand == "-ia") || (listCommand == "-mf") || (listCommand == "-ff") || (listCommand == "-yb") || (listCommand == "-yd")){
        // send to orderList with listCommand as input, this logic should be in itemManager
        cout << "TODO: IMPLEMENT orderList" << endl;
    } else if(listCommand == ""){
        cout << "TODO: senda lista eins og hann kom inn" << endl;
    } else {
        cout << "List Command " << listCommand << " unknown, type 'list -h' to see available commands" << endl;
    }

}

void consoleIndex::search(){

    string itemName;
    cin >> itemName;
    if(item_manager.itemExists(itemName)){
        Item item;
        item = item_manager.getItemByName(itemName);
        cout << item << endl;
    } else {
        cout << "Person not found." << endl;
    }
}

void consoleIndex::addItem(istream &in){
    Item item;
    in >> item;
    item_manager.addItem(item);
    //cout << item << endl;

}

void consoleIndex::removeItemByName(){

    cout << "Enter the name of person you want to remove [enter 'q' to cancel]:" << endl;
    string name;
    cin >> name;
    if (name != "q"){
        if(item_manager.itemExists(name)){
            item_manager.removeItem(item_manager.getItemByName(name));
        } else {
            cout << "Person not found." << endl;
        }
    }
}



bool consoleIndex::executeCommand(string command){

    if ((command == "help") || (command == "h")){
        help();
    } else if ((command == "quit") || (command == "q")){
        return false;
    } else if (command == "add"){
        cout << "Enter the following information:" << endl; //TODO: Put this in << operator in Item
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
        removeItemByName();
    } else {
        cout << "Command " << command << " not found." << endl;
    }

    return true;
}

void consoleIndex::repl(){
    string command;
        do {
            cout << "MonkeyBusiness> ";
        } while(cin >> command && executeCommand(command));
        cout << endl << "Goodbye" << endl;
}

void consoleIndex::start(){
    welcome();
    repl();
}




