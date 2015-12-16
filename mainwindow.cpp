#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::loadHomeScreen(){
    QString filename("mb.jpg");
    ui->homeScreen->setPixmap(QPixmap(filename));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadHomeScreen();
    item_manager.setupRepo();

    displayAllScientists();
    displayAllComputers();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::displayAllScientists(){
    // If I don't need to display custom list of scientists
    list<Item> item = item_manager.getAllItemsListed("-id");

    displayScientists(item);
}

void MainWindow::displayAllComputers(){
    // If I don't need to display custom list of computers
    list<Computer> cmp = item_manager.getAllComputersListed("-id");

    displayComputers(cmp);
}

void MainWindow::displayScientists(list<Item> item){
    // Displays list of scientists everywhere where needed, this slot
    // is also used to update every list that need update after changes,
    // such as removals and adds.

    ui->listSciSort->clear();
    ui->listScientistsAdd->clear();
    ui->listScientistsR->clear();
    ui->listScientistsMod->clear();
    ui->sciConnections->clear();
    ui->sciConnectionsAdd->clear();
    ui->sciConnectionsRem->clear();

    ui->listSciSort->setRowCount(item.size());
    ui->listSciSort->setColumnCount(4);
    ui->listSciSort->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->listSciSort->setHorizontalHeaderLabels(QString("Name;Sex;Year Born;Year of Death").split(";"));
    ui->listSciSort->verticalHeader()->setVisible(false);
    int row = 0;
    list<Item>::const_iterator item_it;
    for (item_it = item.begin(); item_it != item.end(); item_it++){
       Item currItem = (*item_it);

       // Table view
       ui->listSciSort->setItem(row,0,new QTableWidgetItem(QString::fromStdString(currItem.name)));
       ui->listSciSort->setItem(row,1,new QTableWidgetItem(QString::fromStdString(currItem.sex)));
       ui->listSciSort->setItem(row,2,new QTableWidgetItem(QString::number((*item_it).yearBorn)));
       ui->listSciSort->setItem(row,3,new QTableWidgetItem(QString::number((*item_it).yearDead)));
       row++;

       // List view
       ui->listScientistsR->addItem(QString::fromStdString(currItem.name));
       ui->listScientistsMod->addItem(QString::fromStdString(currItem.name));
       ui->listScientistsAdd->addItem(QString::fromStdString(currItem.name));
       ui->sciConnections->addItem(QString::fromStdString(currItem.name));
       ui->sciConnectionsAdd->addItem(QString::fromStdString(currItem.name));
       ui->sciConnectionsRem->addItem(QString::fromStdString(currItem.name));
    }

    currListSci = item;
}


void MainWindow::displayComputers(list<Computer> cmp){
    // Displays list of computers everywhere where needed, this slot
    // is also used to update every list that need update after changes,
    // such as removals and adds.
    ui->cmpConnectionsAdd->clear();
    ui->listCmpSort->clear();
    ui->listComputersR->clear();
    ui->listComputersAdd->clear();
    ui->listComputersMod->clear();

    ui->listCmpSort->setRowCount(cmp.size());
    ui->listCmpSort->setColumnCount(4);
    ui->listCmpSort->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->listCmpSort->setHorizontalHeaderLabels(QString("Name;Make;Year Made;Was it made?").split(";"));
    ui->listCmpSort->verticalHeader()->setVisible(false);
    int row = 0;
    list<Computer>::const_iterator cmp_it;
    for (cmp_it = cmp.begin(); cmp_it != cmp.end(); cmp_it++){
       Computer currCmp = (*cmp_it);



       ui->listCmpSort->setItem(row,0,new QTableWidgetItem(QString::fromStdString(currCmp.name)));
       ui->listCmpSort->setItem(row,1,new QTableWidgetItem(QString::fromStdString(currCmp.make)));
       ui->listCmpSort->setItem(row,2,new QTableWidgetItem(QString::number((*cmp_it).yearMade)));
       ui->listCmpSort->setItem(row,3,new QTableWidgetItem(QString::fromStdString(currCmp.made)));
       row++;

       ui->listComputersR->addItem(QString::fromStdString(currCmp.name));
       ui->listComputersMod->addItem(QString::fromStdString(currCmp.name));
       ui->listComputersAdd->addItem(QString::fromStdString(currCmp.name));
       ui->cmpConnectionsAdd->addItem(QString::fromStdString(currCmp.name));
    }

    currListCmp = cmp;
}

void MainWindow::displayConnections(list<Computer> cmp){
    // Used to display computers that are connected to certain scientist

    ui->cmpConnections->clear();
    ui->cmpConnectionsRem->clear();

    list<Computer>::const_iterator cmp_it;
    for (cmp_it = cmp.begin(); cmp_it != cmp.end(); cmp_it++){
       Computer currCmp = (*cmp_it);
       ui->cmpConnections->addItem(QString::fromStdString(currCmp.name));
       ui->cmpConnectionsRem->addItem(QString::fromStdString(currCmp.name));
    }

}


void MainWindow::on_searchScientist_textChanged(const QString &arg1){
    // Detects if searchbar is being typed on and updates results on the go
    ui->sciSearchLabel->clear();
    string input = ui->searchScientist->text().toStdString();

    list<Item> item = item_manager.searchItem(input);
    displayScientists(item);
}

void MainWindow::on_addSci_clicked(){
    // Adds scientist to database, sends errors if there is some information missing
    //

    Item item;

    QString name = ui->sciName->text();
    QString sex = ui->sciSex->text();
    QString yb = ui->sciYb->text();
    QString yd = ui->sciYd->text();

    if(name.isEmpty()){
        // message
        ui->sciNameError->clear();
        ui->sciNameError->setText("<Span style='color: #ED1C58'>Name cannot be empty!</span>");
        return;
    } else if (sex.isEmpty()) {
        ui->sciSexError->clear();
        ui->sciSexError->setText("<Span style='color: #ED1C58'>Sex cannot be empty!</span>");
        return;
    } else if (yb.isEmpty()){
        ui->sciYbError->clear();
        ui->sciYbError->setText("<Span style='color: #ED1C58'>Year born cannot be empty!</span>");
        return;
    } else if (yd.isEmpty()) {
        ui->sciYdError->clear();
        ui->sciYdError->setText("<Span style='color: #ED1C58'>Year of death cannot be empty! Type 0000 if not dead.</span>");
        return;
    }

    ui->sciName->clear();
    ui->sciSex->clear();
    ui->sciYb->clear();
    ui->sciYd->clear();

    item.name = name.toStdString();
    item.sex = sex.toStdString();
    item.yearBorn = yb.toInt();
    item.yearDead = yd.toInt();

    item_manager.addItem(item);

    displayAllScientists();
}

void MainWindow::on_listScientistsR_clicked(const QModelIndex &index){
    // Only checks if scientist has been chosen for removal and sets the remove button available
    ui->removeSciButton->setEnabled(true);
}

void MainWindow::on_removeSciButton_clicked(){
    // If the remove button is clicked this slot removes the scientists but only
    // after the user confirms on messagebox

    unsigned int selectedSci = ui->listScientistsR->currentIndex().row();

    int reply = QMessageBox::question(this,"Remove Scientist", "Are you sure you want to remove selected Scientist?",
                                                              QMessageBox::Yes, QMessageBox::No);
    if(reply == QMessageBox::Yes){
        if(currListSci.size() > selectedSci){
            list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
            item_manager.remove(to_string((*item_it).id),"Scientists");
        }
    }

    ui->removeSciButton->setEnabled(false);
    displayAllScientists();

}

void MainWindow::on_listScientistsMod_clicked(const QModelIndex &index){
    // If scientist has been chosen this sets the modify button available
    ui->modSciButton->setEnabled(true);
}



void MainWindow::on_modSciButton_clicked(){
    // This displays the info that can be modified in text fields that then can be modified.

    unsigned int selectedSci = ui->listScientistsMod->currentIndex().row();

    if(currListSci.size() > selectedSci){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        indexOfCurrMod = (*item_it).id;
        ui->sciNameMod->setText(QString::fromStdString((*item_it).name));
        ui->sciSexMod->setText(QString::fromStdString((*item_it).sex));
        ui->sciYbMod->setText(QString::number((*item_it).yearBorn));
        ui->sciYdMod->setText(QString::number((*item_it).yearDead));
    }


    ui->modSciButton->setEnabled(false);
    displayAllScientists();
}

void MainWindow::on_pushButton_clicked(){
    // When desired info has been modified by the user this slot completes the modification
    // Proper error messages are displayed if there is some information missing.

    Item item;
    item.id = indexOfCurrMod;

    QString name = ui->sciNameMod->text();
    QString sex = ui->sciSexMod->text();
    QString yb = ui->sciYbMod->text();
    QString yd = ui->sciYdMod->text();

    if(name.isEmpty()){
        ui->sciNameErrorMod->clear();
        ui->sciNameErrorMod->setText("<Span style='color: #ED1C58'>Name cannot be empty!</span>");
        return;
    } else if (sex.isEmpty()) {
        ui->sciSexErrorMod->clear();
        ui->sciSexErrorMod->setText("<Span style='color: #ED1C58'>Sex cannot be empty!</span>");
        return;
    } else if (yb.isEmpty()){
        ui->sciYbErrorMod->clear();
        ui->sciYbErrorMod->setText("<Span style='color: #ED1C58'>Year born cannot be empty!</span>");
        return;
    } else if (yd.isEmpty()) {
        ui->sciYdErrorMod->clear();
        ui->sciYdErrorMod->setText("<Span style='color: #ED1C58'>Year of death cannot be empty! Type 0000 if not dead.</span>");
        return;
    }

    ui->sciNameMod->clear();
    ui->sciSexMod->clear();
    ui->sciYbMod->clear();
    ui->sciYdMod->clear();

    item.name = name.toStdString();
    item.sex = sex.toStdString();
    item.yearBorn = yb.toInt();
    item.yearDead = yd.toInt();

    item_manager.modItem(item);

    displayAllScientists();
}

void MainWindow::on_sciConnections_clicked(const QModelIndex &index){
    // When scientist is chosen this slot displays the computers connected in the list view
    // next to the scientist list

    ui->cmpConnections->clear();
    unsigned int selectedSci = ui->sciConnections->currentIndex().row();

    list<Computer> cmp;
    if(currListSci.size() > selectedSci){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        cmp = item_manager.getConnections(to_string((*item_it).id));
    }


    displayConnections(cmp);
}

void MainWindow::on_sciConnectionsAdd_clicked(const QModelIndex &index){
    // Only to make connect button available if user has selected bot computer and scientist
    isClickedSci = true;
    if(isClickedCmp){
        ui->connectButton->setEnabled(true);
    }
}

void MainWindow::on_cmpConnectionsAdd_clicked(const QModelIndex &index){
    // Only to make connect button available if user has selected bot computer and scientist
    isClickedCmp = true;
    if(isClickedSci){
        ui->connectButton->setEnabled(true);
    }
}

void MainWindow::on_connectButton_clicked(){
    // Connects scientist and computer

    unsigned int selectedSci = ui->sciConnectionsAdd->currentIndex().row();
    unsigned int selectedCmp = ui->cmpConnectionsAdd->currentIndex().row();

    if((currListSci.size() > selectedSci) && (currListCmp.size() > selectedCmp)){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        list<Computer>::iterator cmp_it = std::next(currListCmp.begin(), selectedCmp);
        item_manager.connect(to_string((*item_it).id),to_string((*cmp_it).id));
    }

    ui->connectButton->setEnabled(false);
}

void MainWindow::on_sciConnectionsRem_clicked(const QModelIndex &index){
    // Removes connection between scientist and computer.
    // only possible if both scientist and computer have been chosen.

    isClickedSciRem = true;
    if(isClickedCmpRem){
        ui->removeConnectionButton->setEnabled(true);
    }

    ui->cmpConnectionsRem->clear();
    unsigned int selectedSci = ui->sciConnectionsRem->currentIndex().row();

    list<Computer> cmp;
    if(currListSci.size() > selectedSci){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        cmp = item_manager.getConnections(to_string((*item_it).id));
    }
    ui->removeConnectionButton->setEnabled(false);
    currListCmpRem = cmp;
    displayConnections(cmp);
}

void MainWindow::on_cmpConnectionsRem_clicked(const QModelIndex &index){
    // Checks if computer has been selected for connection removal

    isClickedCmpRem = true;
    if(isClickedSciRem){
        ui->removeConnectionButton->setEnabled(true);
    }
}

void MainWindow::on_removeConnectionButton_clicked(){
    // Removes connection if all conditions are met

    unsigned int selectedSci = ui->sciConnectionsRem->currentIndex().row();
    unsigned int selectedCmp = ui->cmpConnectionsRem->currentIndex().row();

    if((currListSci.size() > selectedSci) && (currListCmpRem.size() > selectedCmp)){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        list<Computer>::iterator cmp_it = std::next(currListCmpRem.begin(), selectedCmp);
        item_manager.removeConnection(to_string((*item_it).id),to_string((*cmp_it).id));
    }

    list<Computer> cmp;
    if(currListSci.size() > selectedSci){
        list<Item>::iterator item_it = std::next(currListSci.begin(), selectedSci);
        cmp = item_manager.getConnections(to_string((*item_it).id));
    }

    ui->connectButton->setEnabled(false);
    displayConnections(cmp);
}

void MainWindow::on_listComputersMod_clicked(const QModelIndex &index){
    // Sets modification button available if computer has been selected
    ui->modCmpButton->setEnabled(true);
}

void MainWindow::on_modCmpButton_clicked(){
    // This displays the info that can be modified in text fields that then can be modified.
    unsigned int selectedCmp = ui->listComputersMod->currentIndex().row();

    if(currListCmp.size() > selectedCmp){
        list<Computer>::iterator cmp_it = std::next(currListCmp.begin(), selectedCmp);
        indexOfCurrModCmp = (*cmp_it).id;
        ui->cmpNameMod->setText(QString::fromStdString((*cmp_it).name));
        ui->cmpMakeMod->setText(QString::fromStdString((*cmp_it).make));
        ui->cmpYmMod->setText(QString::number((*cmp_it).yearMade));
        ui->cmpMadeMod->setText(QString::fromStdString((*cmp_it).made));
    }


    ui->modCmpButton->setEnabled(false);
    displayAllScientists();
}

void MainWindow::on_cmpModconfButton_clicked(){
    // Modifies computer selected and displays errors if there is any information missing.
    Computer cmp;
    cmp.id = indexOfCurrModCmp;

    QString name = ui->cmpNameMod->text();
    QString make = ui->cmpMakeMod->text();
    QString ym = ui->cmpYmMod->text();
    QString made = ui->cmpMadeMod->text();

    if(name.isEmpty()){
        ui->cmpNameErrorMod->clear();
        ui->cmpNameErrorMod->setText("<Span style='color: #ED1C58'>Name cannot be empty!</span>");
        return;
    } else if (make.isEmpty()) {
        ui->cmpMakeErrorMod->clear();
        ui->cmpMakeErrorMod->setText("<Span style='color: #ED1C58'>Make cannot be empty!</span>");
        return;
    } else if (ym.isEmpty()){
        ui->cmpYmErrorMod->clear();
        ui->cmpYmErrorMod->setText("<Span style='color: #ED1C58'>Year made cannot be empty! If it was not made enter 0000</span>");
        return;
    } else if (made.isEmpty()) {
        ui->cmdMadeErrorMod->clear();
        ui->cmdMadeErrorMod->setText("<Span style='color: #ED1C58'>Was it made? cannot be empty!</span>");
        return;
    }

    ui->cmpNameMod->clear();
    ui->cmpMakeMod->clear();
    ui->cmpYmMod->clear();
    ui->cmpMadeMod->clear();

    cmp.name = name.toStdString();
    cmp.make = make.toStdString();
    cmp.yearMade = ym.toInt();
    cmp.made = made.toStdString();

    item_manager.modComputer(cmp);

    displayAllComputers();
}

void MainWindow::on_listComputersR_clicked(const QModelIndex &index){
    // Sets remove button available if computer has been chosen to removal
    ui->removeCmpButton->setEnabled(true);
}

void MainWindow::on_removeCmpButton_clicked(){
    // Removes selected computer after confirmation via messagebox
    unsigned int selectedCmp = ui->listComputersR->currentIndex().row();

    int reply = QMessageBox::question(this,"Remove Computer", "Are you sure you want to remove selected Computer?",
                                                              QMessageBox::Yes, QMessageBox::No);
    if(reply == QMessageBox::Yes){
        if(currListSci.size() > selectedCmp){
            list<Computer>::iterator cmp_it = std::next(currListCmp.begin(), selectedCmp);
            item_manager.remove(to_string((*cmp_it).id),"Computers");
        }
    }

    ui->removeCmpButton->setEnabled(false);
    displayAllComputers();
}

void MainWindow::on_addCmp_clicked(){
    // Adds new computer to database. Displays error messages if there
    // is any information missing from form.
    Computer cmp;

    QString name = ui->cmpName->text();
    QString make = ui->cmpMake->text();
    QString ym = ui->cmpYm->text();
    QString made = ui->cmpMade->text();

    if(name.isEmpty()){
        ui->cmpNameError->clear();
        ui->cmpNameError->setText("<Span style='color: #ED1C58'>Name cannot be empty!</span>");
        return;
    } else if (make.isEmpty()) {
        ui->cmpMakeError->clear();
        ui->cmpMakeError->setText("<Span style='color: #ED1C58'>Make cannot be empty!</span>");
        return;
    } else if (ym.isEmpty()){
        ui->cmpYmError->clear();
        ui->cmpYmError->setText("<Span style='color: #ED1C58'>Year made cannot be empty! If it was not made enter 0000</span>");
        return;
    } else if (made.isEmpty()) {
        ui->cmpMadeError->clear();
        ui->cmpMadeError->setText("<Span style='color: #ED1C58'>Was it made? cannot be empty!</span>");
        return;
    }

    ui->cmpName->clear();
    ui->cmpMake->clear();
    ui->cmpYm->clear();
    ui->cmpMade->clear();

    cmp.name = name.toStdString();
    cmp.make = make.toStdString();
    cmp.yearMade = ym.toInt();
    cmp.made = made.toStdString();

    item_manager.addComputer(cmp);

    displayAllComputers();
}



void MainWindow::on_sciSortButton_clicked(){
    // Sort function for scientist, use same function as old UI layer
    list<Item> item;
    if(ui->sciSortNameAsc->isChecked()){
        item = item_manager.getAllItemsListed("-a");
    } else if (ui->sciSortNameDesc->isChecked()){
        item = item_manager.getAllItemsListed("-d");
    } else if (ui->sciSortSexAsc->isChecked()){
        item = item_manager.getAllItemsListed("-mf");
    } else if (ui->sciSortSexDesc->isChecked()){
        item = item_manager.getAllItemsListed("-ff");
    } else if (ui->sciSortYb->isChecked()){
        item = item_manager.getAllItemsListed("-yb");
    } else if (ui->sciSortYd->isChecked()){
        item = item_manager.getAllItemsListed("-yd");
    } else {
        item = item_manager.getAllItemsListed("-id");
    }

    displayScientists(item);
}

void MainWindow::on_cmpSortButton_clicked(){
    // Sort function for Computers, use same function as old UI layer
    list<Computer> cmp;
    if(ui->cmpSortNameAsc->isChecked()){
        cmp = item_manager.getAllComputersListed("-a");
    } else if (ui->cmpSortNameDesc->isChecked()){
        cmp = item_manager.getAllComputersListed("-d");
    } else if (ui->cmpSortMakeAsc->isChecked()){
        cmp = item_manager.getAllComputersListed("-m");
    } else if (ui->cmpSortMakeDesc->isChecked()){
        cmp = item_manager.getAllComputersListed("-md");
    } else if (ui->cmpSortYm->isChecked()){
        cmp = item_manager.getAllComputersListed("-ym");
    } else if (ui->cmpSortMade->isChecked()){
        cmp = item_manager.getAllComputersListed("-im");
    } else {
        cmp = item_manager.getAllComputersListed("-id");
    }

    displayComputers(cmp);
}

void MainWindow::on_searchComp_textChanged(const QString &arg1){
    // Detects if searchbar is being typed on and updates results on the go
    ui->cmpSearchLabel->clear();
    string input = ui->searchComp->text().toStdString();

    list<Computer> cmp = item_manager.searchComputer(input);
    displayComputers(cmp);
}
