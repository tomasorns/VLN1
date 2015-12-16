#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QTableWidget>
#include "itemManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Used some variable mainly to store data

    unsigned int indexOfCurrMod;

    unsigned int indexOfCurrModCmp;

    itemManager item_manager;

    list<Item> currListSci;

    list<Computer> currListCmp;

    list<Computer> currListCmpRem;

    bool isClickedSci = false;

    bool isClickedCmp = false;

    bool isClickedSciRem = false;

    bool isClickedCmpRem = false;

    void loadHomeScreen();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    // These slots are described in the definition of them.

    void displayAllScientists();

    void displayAllComputers();

    void displayScientists(list<Item> item);

    void displayComputers(list<Computer> cmp);

    void displayConnections(list<Computer> cmp);

    void on_searchScientist_textChanged(const QString &arg1);

    void on_addSci_clicked();

    void on_listScientistsR_clicked(const QModelIndex &index);

    void on_removeSciButton_clicked();

    void on_listScientistsMod_clicked(const QModelIndex &index);

    void on_modSciButton_clicked();

    void on_pushButton_clicked();

    void on_sciConnections_clicked(const QModelIndex &index);

    void on_sciConnectionsAdd_clicked(const QModelIndex &index);

    void on_cmpConnectionsAdd_clicked(const QModelIndex &index);

    void on_connectButton_clicked();

    void on_sciConnectionsRem_clicked(const QModelIndex &index);

    void on_cmpConnectionsRem_clicked(const QModelIndex &index);

    void on_removeConnectionButton_clicked();

    void on_listComputersMod_clicked(const QModelIndex &index);

    void on_modCmpButton_clicked();

    void on_cmpModconfButton_clicked();

    void on_listComputersR_clicked(const QModelIndex &index);

    void on_removeCmpButton_clicked();

    void on_addCmp_clicked();

    void on_sciSortButton_clicked();

    void on_cmpSortButton_clicked();

    void on_searchComp_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
