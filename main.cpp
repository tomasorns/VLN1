#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "consoleIndex.h"
#include <cstdlib>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    consoleIndex console_index;

    console_index.start();

    return a.exec();
}
