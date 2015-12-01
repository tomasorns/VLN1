#include "itemManager.h"

void itemManager::addItem(Item item){
    // Adds item to data structure

    // this (getNextValId) can be done better but it'll be useless
    // when SQL is added
    getNextValId();
    item.id = getId();

    ofstream file ("monkeybusiness.txt", ios_base::app);
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    // If file is empty it doesn't add new line before writing to file
    if(!is_empty()){
        file << endl;
        file << item;
    }
    else {
        file << item;
    }

    file.close();
}

void itemManager::getNextValId(){
    // this (getNextValId) can be done better but it'll be useless
    // when SQL is added
    string id;

    // This is done mainly to create the file if it doesn't exist
    // if it exists, this does nothing else than opening it and closing.
    ofstream cFile ("monkeybusiness.txt", ios_base::app);
    if (cFile.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    cFile.close();
    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,id, '\n');
        if (id.find(";")){
            id = id.substr(0,id.find(";"));
        }
    }

    int intId = atoi(id.c_str()) + 1;
    setId(intId);
    file.close();
}

void itemManager::removeItem(Item rItem){
    // This function removes item from datastructure. This is a little "skítamix".
    // It adds everything in the datastructure to a list of items but excludes the
    // item that the user wants to remove, terminates the data file and then creates
    // a new one with everything on the list created.

    list<Item> item;
    string line; string idLine;
    int id;


    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    // Add everything exept data with corresponding id to a list of items
    while(!file.eof()){
        getline(file,line, '\n');
        idLine = line.substr(0, line.find(";"));
        id = atoi(idLine.c_str());
        if(id != rItem.id){
            item.push_back(reconstructItem(line));
        }
    }

    file.close();

    // Because ofstream doesn't specify that it wants to append to the file after opening it
    // the data file is terminated and a new one is made.
    ofstream cFile ("monkeybusiness.txt");
    bool i = false;
    list<Item>::const_iterator item_it;
    for (item_it = item.begin(); item_it != item.end(); item_it++){
        if(i){
            cFile << endl;
            cFile << (*item_it).id << ";"
                  << (*item_it).name << ";"
                  << (*item_it).sex << ";"
                  << (*item_it).yearBorn << ";"
                  << (*item_it).yearDead;
        } else {
            cFile << (*item_it).id << ";"
                  << (*item_it).name << ";"
                  << (*item_it).sex << ";"
                  << (*item_it).yearBorn << ";"
                  << (*item_it).yearDead;
            i = true;
        }
    }

    cFile.close();

}

bool itemManager::itemExists(string search){
    // Checks if item exists in data structure. returns true if it is
    // but false otherwise.

    string line;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        if(line.find(search) != std::string::npos){
            file.close();
            return 1;
        }
    }

    file.close();
    return false;
}

list<Item> itemManager::searchItem(string search){
    // Searches for all instances of 'search' string, adds it to list of items
    // and then prints said list.

    list<Item> item;
    string line;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        if(line.find(search) != std::string::npos){
            item.push_back(reconstructItem(line));
        }
    }

    file.close();
    printList(item);
    return item;
}

Item itemManager::reconstructItem(string line){
    // This function reconstructs a line in the data file to a object of type item.

    Item item;
    int pos = 0; string yb; string yd;

    string id = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());
    item.id = atoi(id.c_str());

    item.name = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());

    item.sex = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());

    yb = line.substr(pos, line.find(";"));
    item.yearBorn = atoi(yb.c_str());
    line = line.substr(line.find(";")+1, line.length());

    item.yearDead = atoi(line.c_str());

    return item;
}

list<Item> itemManager::getAllItems(){
    // Returns a list of items that are included in txt file
    list<Item> item;
    string line;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        item.push_back(reconstructItem(line));
    }

    file.close();
    return item;
}

Item itemManager::getItemById(string id){
    // Searches for item with corresponding id and returns it

    Item item;
    string line; string idLine;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        idLine = line.substr(0, line.find(";"));
        if(idLine == id){
            return reconstructItem(line);
        }
    }

    file.close();
    return item;
}

bool itemManager::itemExistsId(string id){
    // Checks if item exists in data structure with id. returns true if it is
    // but false otherwise.
    string line; string idLine;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        idLine = line.substr(0, line.find(";"));
        if(idLine == id){
            return true;
        }
    }

    file.close();
    return false;
}

void itemManager::getAllItemsListed(string command){
    // Uses printList to print a list according to given
    // command after sorting it properly. This function sorts
    // by name ascending, descending, females first, males first,
    // by year of birth ascending and year of death ascending

    list<Item> item;
    item = getAllItems();
    if(command == "-id"){
    printList(item);
    } else if (command == "-yb"){
        item.sort([](const Item & first, const Item & second) { return first.yearBorn < second.yearBorn; });
        printList(item);
    } else if (command == "-yd"){
        item.sort([](const Item & first, const Item & second) { return first.yearDead < second.yearDead; });
        printList(item);
    } else if (command == "-mf"){
        item.sort([](const Item & first, const Item & second) { return first.sex > second.sex; });
        printList(item);
    } else if (command == "-ff"){
        item.sort([](const Item & first, const Item & second) { return first.sex < second.sex; });
        printList(item);
    } else if (command == "-a"){
        item.sort([](const Item & first, const Item & second) { return first.name < second.name; });
        printList(item);
    } else if (command == "-d"){
        item.sort([](const Item & first, const Item & second) { return first.name > second.name; });
        printList(item);
    } else {
        cout << "Unknown list command, type 'list -h' to see all list commands" << endl;
    }
}

bool itemManager::is_empty(){
    // Checks if file is empty, first it creates a file if it doesn't exist.
    ofstream cFile ("monkeybusiness.txt", ios_base::app);
    cFile.close();

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        cout << "Opening file failed." << endl;
        cout << "Terminating ..." << endl;
        exit(1);
    }

    if (file.peek() == std::ifstream::traits_type::eof()){
        file.close();
        return 1;
    }

    file.close();
    return 0;
}

void itemManager::printList(list<Item> item){
    // Simple print function.

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

