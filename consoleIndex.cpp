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
        << "adds:               adds new scientist to list" << endl
        << "addc:               adds new computer to list" << endl
        << "remove:             removes item from list" << endl
        << "mods:               modifies scientists" << endl
        << "modc:               modifies computers" << endl
        << "slist -h:           show help menu for scientist list" << endl
        << "clist -h:           show help menu for computer list" << endl
        << "connect:            connects a scientist with a computer" << endl
        << "showc:              prints connections between scientists and computers" << endl
        << "removec:            removes connections between scientists and computers" << endl
        << "search 'string':    searches for 'string' in list and returns all information" << endl
        << "                    from both scientists and computers" << endl
        << "quit:               quits the Monkey Business" << endl;
}

void consoleIndex::sListHelp(){
    // Displays help menu for list commands
    cout << "Options for slist command:" << endl
         << "list -a:           list in ascending order by name" << endl
         << "list -d:           list in descending order by name" << endl
         << "list -id           list arranged by id" << endl
         << "list -mf:          lists males first, then females" << endl
         << "list -ff:          lists females first, then males" << endl
         << "list -yb:          lists after year born, earlies first" << endl
         << "list -yd:          lists after year dead, earlies first" << endl;

}

void consoleIndex::cListHelp(){
    // Displays help menu for list commands
    cout << "Options for clist command:" << endl
         << "list -a:           list in ascending order by name" << endl
         << "list -d:           list in descending order by name" << endl
         << "list -id           list arranged by id" << endl
         << "list -m:           list arranged by make in ascneding order" << endl
         << "list -md:          list arranged by make in decending order" << endl
         << "list -ym:          list arranged in year made, earliest first" << endl
         << "list -im:          list arranged in if they where made, with made first" << endl;

}

void consoleIndex::sList(){
    // Calls listHelp if help command is used, otherwise it prints all items that
    // correspons to input command
    string listCommand;
    cin >> listCommand;
    if (item_manager.is_emptyS()){
        cout << "The list is empty." << endl;
    } else {
        if (listCommand == "-h"){
            sListHelp();
        } else if(listCommand == "-id"){ // this does the same as the on below ¯\_(ツ)_/¯
            list<Item> item;
            item = item_manager.getAllItemsListed(listCommand);
            printItem(item);
        } else if((listCommand == "-a") || (listCommand == "-d") || (listCommand == "-mf") || (listCommand == "-ff") || (listCommand == "-yb") || (listCommand == "-yd")){
            list<Item> item;
            item = item_manager.getAllItemsListed(listCommand);
            printItem(item);
        } else {
            cout << "List Command '" << listCommand << "' unknown, type 'list -h' to see available commands" << endl;
        }
    }
}

void consoleIndex::cList(){
    // Calls listHelp if help command is used, otherwise it prints all items that
    // correspons to input command
    string listCommand;
    cin >> listCommand;
    if (item_manager.is_emptyS()){
        cout << "The list is empty." << endl;
    } else {
        if (listCommand == "-h"){
            cListHelp();
        } else if(listCommand == "-id"){ // this does the same as the on below ¯\_(ツ)_/¯
            list<Computer> cmp;
            cmp = item_manager.getAllComputersListed(listCommand);
            printComputer(cmp);
        } else if((listCommand == "-a") || (listCommand == "-d") || (listCommand == "-mf") || (listCommand == "-ff") || (listCommand == "-yb") || (listCommand == "-yd")){
            list<Computer> cmp;
            cmp = item_manager.getAllComputersListed(listCommand);
            printComputer(cmp);
        } else {
            cout << "List Command '" << listCommand << "' unknown, type 'list -h' to see available commands" << endl;
        }
    }
}

void consoleIndex::search(){
    // Searches the db, this function searches both scientists and computers tables and
    // returns everything that matches, doesn't matter in which column

    string searchString;
    cin >> searchString;

    list<Item> item;
    item = item_manager.searchItem(searchString);
    printf("------------------------------------------------------------------------\n");
    if(item.empty()){
        cout << "Nothing found in Scientists for search string '" << searchString << "'" << endl << endl;
    } else {
        cout << "Scientists matching search string: "<< endl;
        printItem(item);
    }
    list<Computer> cmp;
    cmp = item_manager.searchComputer(searchString);

    if(cmp.empty()){
        cout << "Nothing found in Computers for search string '" << searchString << "'" << endl << endl;
    } else {
        cout << "Computers matching search string: "<< endl;
        printComputer(cmp);
    }
    printf("------------------------------------------------------------------------\n");

}

void consoleIndex::addItem(istream &in){
    // Makes new instance of item and uses overloaded operator to read in
    Item item;
    in >> item;
    item_manager.addItem(item);
}

void consoleIndex::addComputer(istream &in){
    // Makes new instance of computer and uses overloaded operator to read in
    Computer cmp;
    in >> cmp;
    item_manager.addComputer(cmp);
}

void consoleIndex::modItem(){
    // This is function modifies scientist, user can chose which aspect he wants to change
    // for chosen scientist

    list<Item> items;
    items = item_manager.getAllItemsListed(("-id"));

    if(!items.empty()){
       printItem(items);

       string id;
       cout << "Enter the id of the scientist you want to modify: ";
       cin >> id;

       if(item_manager.itemExistsId(id, "Scientists")){

           Item item;
           item = item_manager.getItemById(id);

           string cmd;
           cout << "What do you want to modify?" << endl << "Enter 'name' for name, 'sex' for sex, 'yb' for year born " << endl
                << "or 'yd' for year of death" << endl
                << "Enter q to cancel." << endl;
           cin >> cmd;

           if(cmd != "q"){
               if(cmd == "name") {
                   cout << "Current name: " << item.name << endl;
                   cout << "New name: ";
                   cin.ignore();
                   getline(cin, item.name);
               } else if( cmd == "sex"){
                   cout << "Current sex: " << item.sex << endl;
                   cout << "New sex (M/F): ";
                   cin.ignore();
                   getline(cin, item.sex);
               } else if( cmd == "yb"){
                   string yb;
                   cout << "Current year born: " << item.yearBorn << endl;
                   cout << "New year born: ";
                   cin >> yb;
                   item.yearBorn = atoi(yb.c_str());
               } else if( cmd == "yd"){
                   string yd;
                   cout << "Current year  of death: " << item.yearDead << endl;
                   cout << "New year of death: ";
                   cin >> yd;
                   item.yearDead = atoi(yd.c_str());
               } else {
                   cout << "Command '" << cmd << "' not recognized.." << endl;
               }
           }
           item_manager.modItem(item);
       } else {
           cout << "No scientist has id = " << id << endl;
       }
    } else {
        cout << "The list of scientists is empty, there is nothing to modify.. " << endl;
    }
}

void consoleIndex::modComputer(){
    // This is function modifies computer, user can chose which aspect he wants to change
    // for chosen computer

    list<Computer> cmps;
    cmps = item_manager.getAllComputersListed(("-id"));

    if(!cmps.empty()){

       printComputer(cmps);

       string id;
       cout << "Enter the id of the computer you want to modify: ";
       cin >> id;

       if(item_manager.itemExistsId(id, "Computers")){

           Computer cmp;
           cmp = item_manager.getComputerById(id);
           string cmd;

           cout << "What do you want to modify?" << endl << "Enter 'name' for name, 'make' for make, 'ym' for year made " << endl
                << "or 'made' for if it was made" << endl
                << "Enter q to cancel." << endl;
           cin >> cmd;

           if(cmd != "q"){
               if(cmd == "name") {
                   cout << "Current name: " << cmp.name << endl;
                   cout << "New name: ";
                   cin.ignore();
                   getline(cin, cmp.name);
               } else if( cmd == "make"){
                   cout << "Current make: " << cmp.make << endl;
                   cout << "New make: ";
                   cin.ignore();
                   getline(cin, cmp.make);
               } else if( cmd == "ym"){
                   string ym;
                   cout << "Current year made: " << cmp.yearMade << endl;
                   cout << "New year made: ";
                   cin >> ym;
                   cmp.yearMade = atoi(ym.c_str());
               } else if( cmd == "made"){
                   cout << "Was it made?: " << cmp.made << endl;
                   cout << "How 'bout now?: ";
                   cin.ignore();
                   getline(cin, cmp.name);
               } else {
                   cout << "Command '" << cmd << "' not recognized.." << endl;
               }
           }
           item_manager.modComputer(cmp);
       } else {
           cout << "No computer has id = " << id << endl;
       }
    } else {
        cout << "The list of computers is empty, there is nothing to modify.. " << endl;
    }
}

void consoleIndex::connect(){
    // Lets user connect a scientist and computer


    string sId; string cId;
    printItem(item_manager.getAllItemsListed("-id"));
    cout << endl << "Enter the id of the scientist you want to connect to a computer: ";
    cin >> sId;
    cout << endl;
    printComputer(item_manager.getAllComputersListed("-id"));
    cout << endl << "Enter the id of the computer you want to connect chosen scientist to: ";
    cin >> cId;
    item_manager.connect(sId,cId);
}

void consoleIndex::removeConnection(){
    // Lets user remove connection from scientist and a computer

    string sId; string cId;

    printConnections();

    cout << endl << "Enter q any time to cancel" << endl
         << "Enter the id of the scientists you want to remove a computer from: ";
    cin >> sId;
    if(sId != "q"){
        cout << "Enter the id of the computer you want to remove from chosen scientist: ";
        cin >> cId;
        if(cId != "q"){
            item_manager.removeConnection(sId, cId);

            printConnections();
        }
    }
}

void consoleIndex::removeItemById(){
    // Displays all items in sorted by ascending id, then asks the user to enter
    // the id of whom they want to remove, and removes only if item with entered
    // id exists.

    cout << "Enter 's' to remove Scientist or 'c' to remove Computer [enter q to quit]" << endl;
    string cmd;
    cin >> cmd;

    if(cmd != "q"){
        if(cmd == "s"){
            list<Item> item;
            item = item_manager.getAllItemsListed("-id");
            printItem(item);
            cout << "Enter the id of person you want to remove [enter 'q' to quit]:" << endl;
            string id;
            cin >> id;
            if(id != "q") {
                if(item_manager.itemExistsId(id, item_manager.getTs())){
                    item_manager.remove(id, item_manager.getTs());
                    if (item_manager.is_emptyS()){
                        cout << "You've emptied the table, YOU MONSTER!" << endl;
                    } else {
                        list<Item> items;
                        items = item_manager.getAllItemsListed("-id");
                        printItem(items);
                    }
                } else {
                    cout << "Scientist with id = " << id << " not found" << endl;
                }
            }
        } else if (cmd == "c") {
            list<Computer> cmp;
            cmp = item_manager.getAllComputersListed("-id");
            printComputer(cmp);
            cout << "Enter the id of computer you want to remove [enter 'q' to quit]:" << endl;
            string id;
            cin >> id;
            if(id != "q"){
                if(item_manager.itemExistsId(id, item_manager.getTc())){
                    item_manager.remove(id, item_manager.getTc());
                    if (item_manager.is_emptyS()){
                        cout << "You've emptied the table, YOU MONSTER!" << endl;
                    } else {
                        list<Computer> cmps;
                        cmps = item_manager.getAllComputersListed("-id");
                        printComputer(cmps);
                    }
                } else {
                    cout << "Computer with id = " << id << " not found" << endl;
                }
            }
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
    } else if (command == "adds"){
        cout << "Enter the following information:" << endl;
        cout << "Name: ";
        ws(cin);
        addItem(cin);
    } else if (command == "addc"){
        cout << "Enter the following information:" << endl;
        cout << "Name: ";
        ws(cin);
        addComputer(cin);
    } else if (command == "slist") {
        ws(cin);
        sList();
    } else if (command == "clist") {
        ws(cin);
        cList();
    } else if (command == "search") {
        ws(cin);
        search();
    } else if (command == "remove") {
        removeItemById();
    } else if (command == "connect") {
        connect();
    } else if (command == "showc") {
        printConnections();
    } else if (command == "removec") {
        removeConnection();
    } else if (command == "mods") {
        modItem();
    } else if (command == "modc") {
        modComputer();
    } else {
        cout << "Command '" << command << "' not found." << endl;
    }

    return true;
}

void consoleIndex::printItem(list<Item> item){
    // Prints list of scientists
    if(!item.empty()){
        printf(" Id | Name \t \t \t| Sex (M/F) | Year Born | Year of death\n");
        printf("------------------------------------------------------------------------\n");
        list<Item>::const_iterator item_it;
        for (item_it = item.begin(); item_it != item.end(); item_it++){
            printf("%3d   ",(*item_it).id);
            printf("%5s",((*item_it).name).c_str());
            printf("%*s",29-strlen((((*item_it).name).c_str())),((*item_it).sex).c_str());
            printf("%15d",(*item_it).yearBorn);
            printf("%12d\n",(*item_it).yearDead);
        }
        printf("------------------------------------------------------------------------\n");
    }
}

void consoleIndex::printComputer(list<Computer> cmp){
    // Prints list of computers
    if(!cmp.empty()){
        printf(" Id | Name \t \t \t| Make \t \t | Year Made | Was it made?\n");
        printf("---------------------------------------------------------------------------\n");
        list<Computer>::const_iterator cmp_it;
        for (cmp_it = cmp.begin(); cmp_it != cmp.end(); cmp_it++){
            printf("%3d   ",(*cmp_it).id);
            printf("%5s",((*cmp_it).name).c_str());
            printf("%*s",28-strlen((((*cmp_it).name).c_str()))+strlen((((*cmp_it).make).c_str())),((*cmp_it).make).c_str());
            printf("%*d",21-strlen((((*cmp_it).make).c_str())),(*cmp_it).yearMade);
            printf("%11s\n",((*cmp_it).made).c_str());
        }
        printf("---------------------------------------------------------------------------\n");
    }
}

void consoleIndex::printConnections(){
    // Prints connections between computers and scientists
    list<Item> item;
    list<Computer> cmp;
    int wid = 30;
    item = item_manager.getAllItemsListed("-id");
    printf(" Scientists \t \t \t    Computers\n");
    printf(" Id | Name \t \t \t    Id | Name \n");
    printf("------------------------------------------------------------------------\n");

    list<Item>::const_iterator item_it;
    list<Computer>::const_iterator cmp_it;

    for (item_it = item.begin(); item_it != item.end(); item_it++){
        printf("%3d   ",(*item_it).id);
        printf("%s",((*item_it).name).c_str());
        cmp = item_manager.getConnections(to_string((*item_it).id));
        if(!cmp.empty()){
            printf(":");
            for (cmp_it = cmp.begin(); cmp_it != cmp.end(); cmp_it++){
                printf(" %*d  ",wid-strlen((((*item_it).name).c_str())),(*cmp_it).id);
                printf(" %s\n", ((*cmp_it).name).c_str());
                wid = 53;
            }
            printf("------------------------------------------------------------------------\n");
            wid = 30;
        } else {
            printf("\n------------------------------------------------------------------------\n");
        }
    }
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
    item_manager.setupRepo();
    repl();
}
