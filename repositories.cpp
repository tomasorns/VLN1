#include "repositories.h"

void repositories::setup(){
    // Opens a db connection if and creates db if it doesn't exist
    // Creates db tables if they don't exists
    // This is executed in program start
    // Table Scientists is for scientists (duh)
    // Table Computers is for computers
    // Table connections stores connections between scientists and computers via foreign key

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "monkeybusiness.sqlite";
    db.setDatabaseName(dbName);
    db.setConnectOptions("foreign_keys = ON");

    if(db.open()){
        QSqlQuery query(db);

        query.exec("PRAGMA foreign_keys = ON;");

        query.exec("CREATE TABLE IF NOT EXISTS Scientists"
                   "("
                        "id INTEGER PRIMARY KEY,"
                        "name VARCHAR,"
                        "sex VARCHAR,"
                        "yearborn INTEGER,"
                        "yeardead INTEGER"
                   ")");

        query.exec("CREATE TABLE IF NOT EXISTS Computers"
                   "("
                        "id INTEGER PRIMARY KEY,"
                        "name VARCHAR,"
                        "make VARCHAR,"
                        "yearmade INTEGER,"
                        "made VARCHAR"
                   ")");

        query.exec("CREATE TABLE IF NOT EXISTS Connections"
                   "("
                        "id INTEGER PRIMARY KEY,"
                        "sId INTEGER,"
                        "cId INTEGER,"
                        "FOREIGN KEY(sId) REFERENCES Scientists(id),"
                        "FOREIGN KEY(cId) REFERENCES Computers(id)"
                   ")");
    } else {
        throw dbException();
    }
}

void repositories::addScientist(Item item){
    // Adds scientists to db
    db.open();

    QSqlQuery query(db);

    QString name = QString::fromStdString(item.name);
    QString sex = QString::fromStdString(item.sex);

    query.prepare("INSERT INTO Scientists(id, name, sex, yearborn, yeardead) "
                         "VALUES(:id, :name, :sex, :yearborn, :yeardead)");
    query.bindValue(":id", item.id);
    query.bindValue(":name", name);
    query.bindValue(":sex", sex);
    query.bindValue(":yearborn", item.yearBorn);
    query.bindValue(":yeardead", item.yearDead);

    if(!query.exec()){
        throw dbException();
    }
}


void repositories::addComputer(Computer cmp){
    // Add computer to db

    db.open();

    QSqlQuery query(db);

    QString name = QString::fromStdString(cmp.name);
    QString make = QString::fromStdString(cmp.make);
    QString made = QString::fromStdString(cmp.made);
    
    query.prepare("INSERT INTO Computers(id, name, make, yearmade, made) "
                         "VALUES(:id, :name, :make, :yearmade, :made)");
    query.bindValue(":id", cmp.id);
    query.bindValue(":name", name);
    query.bindValue(":make", make);
    query.bindValue(":yearmade", cmp.yearMade);
    query.bindValue(":made", made);

    if(!query.exec()){
        throw dbException();
    }

}

void repositories::modScientists(Item item){
    // Updated values for scientist with that have been changed by user

    db.open();

    QSqlQuery query(db);

    QString scId = QString::fromStdString(to_string(item.id));

    QString name = QString::fromStdString(item.name);
    QString sex = QString::fromStdString(item.sex);

    query.prepare("UPDATE Scientists "
                  "SET name=:name, sex=:sex, yearborn=:yearborn, yeardead=:yeardead "
                  "WHERE id = " + scId);
    query.bindValue(":id", item.id);
    query.bindValue(":name", name);
    query.bindValue(":sex", sex);
    query.bindValue(":yearborn", item.yearBorn);
    query.bindValue(":yeardead", item.yearDead);

    if(!query.exec()){
        throw dbException();
    }

}

void repositories::modComputer(Computer cmp){
    // Updates values for specific computer that has been changed by user

    db.open();

    QSqlQuery query(db);

    QString cmpId = QString::fromStdString(to_string(cmp.id));

    QString name = QString::fromStdString(cmp.name);
    QString make = QString::fromStdString(cmp.make);
    QString made = QString::fromStdString(cmp.made);

    query.prepare("UPDATE Computers "
                  "SET name=:name, make=:make, yearmade=:yearmade, made=:made "
                  "WHERE id = " + cmpId);
    query.bindValue(":id", cmp.id);
    query.bindValue(":name", name);
    query.bindValue(":make", make);
    query.bindValue(":yearmade", cmp.yearMade);
    query.bindValue(":made", made);

    if(!query.exec()){
        throw dbException();
    }

}

void repositories::removeScientist(string id){
    // Deletes scientist with specific id from db
    // Starts with deleting any connections

    db.open();

    QSqlQuery query(db);
    
    QString rId = QString::fromStdString(id);

    query.prepare("DELETE FROM Connections "
               "WHERE sId=" + rId);

    if(!query.exec()){
        throw dbException();
    }

    query.prepare("DELETE FROM Scientists "
               "WHERE id=" + rId);

    if(!query.exec()){
        throw dbException();
    }



}

void repositories::removeComputer(string id){
    // Deletes computer with specific id from db
    // Starts with deleting any connections

    db.open();

    QSqlQuery query(db);
    
    QString rId = QString::fromStdString(id);

    query.prepare("DELETE FROM Connections "
               "WHERE cId=" + rId);

    if(!query.exec()){
        throw dbException();
    }

    query.prepare("DELETE FROM Computers "
               "WHERE id=" + rId);

    if(!query.exec()){
        throw dbException();
    }

}

list<Item> repositories::getAllScientists(string command, bool asc){
    // Retrieves all scientists from db

    list<Item> items;

    db.open();
    QSqlQuery query(db);
    QString cmd = QString::fromStdString(command);

    if(asc){
        query.prepare("SELECT * FROM Scientists "
                   "ORDER BY " + cmd +" COLLATE NOCASE");
    } else {
        query.prepare("SELECT * FROM Scientists "
                   "ORDER BY " + cmd +" COLLATE NOCASE DESC");
    }

    if(!query.exec()){
        throw dbException();
    }

    while(query.next()){
        Item item;
        item.id = query.value("id").toUInt();
        item.name = query.value("name").toString().toStdString();
        item.sex = query.value("sex").toString().toStdString();
        item.yearBorn = query.value("yearborn").toUInt();
        item.yearDead = query.value("yeardead").toUInt();
        items.push_back(item);
    }

    return items;
}

list<Computer> repositories::getAllComputers(string command, bool asc){
    // Retrieves all computers from db and returns in a from of list of computers

    list<Computer> cmp;

    db.open();

    QSqlQuery query(db);
    QString cmd = QString::fromStdString(command);

    if(asc){
        query.prepare("SELECT * FROM Computers "
                   "ORDER BY " + cmd +" COLLATE NOCASE");
    } else {
        query.prepare("SELECT * FROM Computers "
                   "ORDER BY " + cmd +" COLLATE NOCASE DESC");
    }

    if(!query.exec()){
        throw dbException();
    }

    while(query.next()){
        Computer comp;
        comp.id = query.value("id").toUInt();
        comp.name = query.value("name").toString().toStdString();
        comp.make = query.value("make").toString().toStdString();
        comp.yearMade = query.value("yearmade").toUInt();
        comp.made = query.value("made").toString().toStdString();
        cmp.push_back(comp);
    }

    return cmp;
}

void repositories::connect(string sId, string cId){
    // Adds connection to connections table in tb

    db.open();

    QSqlQuery query(db);
    int scId = atoi(sId.c_str());
    int cmpId = atoi(cId.c_str());

    query.prepare("INSERT INTO Connections(id, sId, cId) "
                         "VALUES(:id, :sId, :cId)");
    query.bindValue(":id", nextVal("Connections"));
    query.bindValue(":sId", scId);
    query.bindValue(":cId", cmpId);

    if(!query.exec()){
        throw dbException();
    }
}

void repositories::removeConnection(string sId, string cId){
    // Removes connection from connections table

    db.open();

    QSqlQuery query(db);
    QString scId = QString::fromStdString(sId);
    QString cmpId = QString::fromStdString(cId);

    query.prepare("DELETE FROM Connections "
               "WHERE sId=" + scId + " AND cId=" + cmpId);

    if(!query.exec()){
        throw dbException();
    }

}

list<Computer> repositories::getConnections(string sId){
    // Returns a list of computers connected to specific scientist

    list<Computer> cmp;

    db.open();

    QSqlQuery query(db);
    QString scId = QString::fromStdString(sId);

    query.prepare("SELECT Computers.id, Computers.name, Computers.make, Computers.yearmade, Computers.made "
               "FROM Computers "
               "JOIN Connections "
               "ON Computers.id = Connections.cId "
               "AND Connections.sId = " + scId + " "
               "ORDER BY Computers.id");

    if(!query.exec()){
        throw dbException();
    }

    while(query.next()){
        Computer comp;
        comp.id = query.value("id").toUInt();
        comp.name = query.value("name").toString().toStdString();
        comp.make = query.value("make").toString().toStdString();
        comp.yearMade = query.value("yearmade").toUInt();
        comp.made = query.value("made").toString().toStdString();
        cmp.push_back(comp);
    }

    return cmp;
}

bool repositories::itemExists(string id, string table){
    // Checks if item exists in specific table

    db.open();

    QSqlQuery query(db);
    QString sId = QString::fromStdString(id);
    QString sTable = QString::fromStdString(table);

    query.prepare("SELECT * FROM " + sTable + " WHERE id=" + sId);

    if(!query.exec()){
        throw dbException();
    }

    if(query.next()){
        return true;
    } else {
        return false;
    }
}

Item repositories::getItemById(string id){
    // Retrieves specific scientist with id

    db.open();
    QSqlQuery query(db);
    QString sId = QString::fromStdString(id);

    query.prepare("SELECT * FROM Scientists WHERE id=" + sId);

    if(!query.exec()){
        throw dbException();
    }

    Item item;

    while(query.next()){
        item.id = query.value("id").toUInt();
        item.name = query.value("name").toString().toStdString();
        item.sex = query.value("sex").toString().toStdString();
        item.yearBorn = query.value("yearborn").toUInt();
        item.yearDead = query.value("yeardead").toUInt();
    }

    return item;
}

Computer repositories::getComputerById(string id){
    // Retrieves specific computer with id

    db.open();

    QSqlQuery query(db);
    QString cId = QString::fromStdString(id);

    query.prepare("SELECT * FROM Computers WHERE id=" + cId);

    if(!query.exec()){
        throw dbException();
    }

    Computer cmp;
    while(query.next()){
        cmp.id = query.value("id").toUInt();
        cmp.name = query.value("name").toString().toStdString();
        cmp.make = query.value("make").toString().toStdString();
        cmp.yearMade = query.value("yearmade").toUInt();
        cmp.made = query.value("made").toString().toStdString();
    }

    return cmp;

}

bool repositories::is_emptyS(){
    // Checks if table scientists is empty
    db.open();

    QSqlQuery query(db);

    query.prepare("SELECT * FROM Scientists");

    if(!query.exec()){
        throw dbException();
    }

    if(query.next()){
        return false;
    } else {
        return true;
    }
}

bool repositories::is_emptyC(){
    // Checks if table computers is empty
    db.open();

    QSqlQuery query(db);

    query.prepare("SELECT * FROM Computers");

    if(!query.exec()){
        throw dbException();
    }

    if(query.next()){
        return false;
    } else {
        return true;
    }
}

list<Item> repositories::searchItem(string search){
    // searches in scientists table and returns matches
    list<Item> items;

    db.open();

    QSqlQuery query(db);
    QString searchS = QString::fromStdString(search);

    query.prepare("SELECT * FROM Scientists "
               "WHERE name LIKE '%" + searchS + "%' OR "
                     "id LIKE '%" + searchS + "%' OR "
                     "sex LIKE '%" + searchS + "%' OR "
                     "yearborn LIKE '%" + searchS + "%' OR "
                     "yeardead LIKE '%" + searchS + "%'");

    if(!query.exec()){
        throw dbException();
    }

    while(query.next()){
        Item item;
        item.id = query.value("id").toUInt();
        item.name = query.value("name").toString().toStdString();
        item.sex = query.value("sex").toString().toStdString();
        item.yearBorn = query.value("yearborn").toUInt();
        item.yearDead = query.value("yeardead").toUInt();
        items.push_back(item);
    }

    return items;
}

list<Computer> repositories::searchComputer(string search){
    // searches in computers table and returns matches
    list<Computer> cmp;

    db.open();

    QSqlQuery query(db);
    QString searchS = QString::fromStdString(search);

    query.prepare("SELECT * FROM Computers "
               "WHERE name LIKE '%" + searchS + "%' OR "
                     "id LIKE '%" + searchS + "%' OR "
                     "make LIKE '%" + searchS + "%' OR "
                     "yearmade LIKE '%" + searchS + "%' OR "
                     "made LIKE '%" + searchS + "%'");

    if(!query.exec()){
        throw dbException();
    }

    while(query.next()){
        Computer comp;
        comp.id = query.value("id").toUInt();
        comp.name = query.value("name").toString().toStdString();
        comp.make = query.value("make").toString().toStdString();
        comp.yearMade = query.value("yearmade").toUInt();
        comp.made = query.value("made").toString().toStdString();
        cmp.push_back(comp);
    }

    return cmp;
}

int repositories::nextVal(string table){
    // Checks next value for id in specific table
    // could have used rowid in sqlite but more control
    // this way
    db.open();

    QSqlQuery query(db);

    QString sTable = QString::fromStdString(table);

    query.prepare("SELECT MAX(id) FROM " + sTable);

    if(!query.exec()){
        throw dbException();
    }

    int id = 0;

    while(query.next()){
        id = query.value(0).toUInt();
    }
    return id + 1;
}
