#include "itemManager.h"

void itemManager::addItem(Item item){
    // add item to data structure

    getNextValId();
    item.id = getId();

    ofstream file ("monkeybusiness.txt", ios_base::app);

    // TODO: Check if file successfully opened.
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
    string id;
    ofstream cFile ("monkeybusiness.txt", ios_base::app);
    cFile.close();
    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        exit(1);
    }

    // TODO: Check if file successfully opened.

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

void itemManager::removeItem(list<Item> item){
    // remove item from structure
}

bool itemManager::itemExists(string name){
    // check if item exists

    string line;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        if(line.find(name) != std::string::npos){
            file.close();
            return 1;
        }
    }

    file.close();
    return false;
}

list<Item> itemManager::searchItem(string name){
    // return item with name

    list<Item> item;
    string line;

    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
        exit(1);
    }

    while(!file.eof()){
        getline(file,line, '\n');
        if(line.find(name) != std::string::npos){
            item.push_back(reconstructItem(line));
        }
    }

    file.close();
    printList(item);
    return item;
}

Item itemManager::reconstructItem(string line){

    Item item;
    int pos = 0;

    string id = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());
    item.id = atoi(id.c_str());

    item.name = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());

    item.sex = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());

    item.yearBorn = line.substr(pos, line.find(";"));
    line = line.substr(line.find(";")+1, line.length());

    item.yearDead = line;

    return item;
}

void itemManager::getAllItemsListed(string command){

}

bool itemManager::is_empty(){
    ifstream file ("monkeybusiness.txt");
    if (file.fail()){
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
    printf(" Id | Name \t \t \t| Sex (M/F) | Year Born | Year of death\n");
    printf("------------------------------------------------------------------------\n");
    list<Item>::const_iterator item_it;
    for (item_it = item.begin(); item_it != item.end(); item_it++){
        printf("%3d   ",(*item_it).id);
        printf("%5s",((*item_it).name).c_str());
        printf("%*s",29-strlen((((*item_it).name).c_str())),((*item_it).sex).c_str());
        printf("%15s",((*item_it).yearBorn).c_str());
        printf("%12s\n",((*item_it).yearDead).c_str());
    }
    printf("------------------------------------------------------------------------\n");
}
