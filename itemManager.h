#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "Item.h"

class itemManager
{
public:
    void addItem(Item item);

    void removeItem(Item item);

    bool itemExists(string name);

    Item getItemByName(string name);

private:


};

#endif // ITEMMANAGER_H
