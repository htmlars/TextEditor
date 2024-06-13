#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), textEdit(new QTextEdit(this)) {
    setCentralWidget(textEdit); // Basic functionality of a text input stream has been implemented
    createMenus(); // Method to create the navbar
}

void MainWindow::createMenus() {
    QMenuBar *bar = menuBar(); // creates a navbar / menu
    QMenu *fileMenu = bar->addMenu(tr("&Datei")); // adds a file to the menu

    QAction *saveAction = new QAction(tr("Speichern"), this); // Dropdown option to exit the text editor
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile); // connects the event action to the beenden function
    fileMenu->addAction(saveAction); // appends the action to the fileMenu

    QAction *saveAsAction = new QAction(tr("Speichern unter"), this); // Dropdown option to save a text file
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveAsFile); // connects the event action to the saveFile method
    fileMenu->addAction(saveAsAction); // appends the action to the fileMenu

    QAction *exitAction = new QAction(tr("Beenden"), this); // Dropdown Option to exit File
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitFile); // connects the event action to the saveFile method
    fileMenu->addAction(exitAction); // appends the action to the fileMenu
}

void MainWindow::saveAsFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Speichern"), "", tr("Text Files (*.txt);;All Files (*)")); // opens a file dialog to save it somewhere
    if (fileName.isEmpty()) { // the method is returned from when no filename is selected
        return;
    }
    QFile file(fileName); // creates a qfile object with the filename
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // tries to open the file in write mode
        QMessageBox::warning(this, tr("Error"), tr("Kann nicht speichern: ") + file.errorString()); // throws error when file cant be opened
        return;
    }
    QTextStream out(&file); // creates a textstream to write into the file
    out << textEdit->toPlainText(); // writes the text of the textedit into the file
    file.close(); // closes the file
}

void MainWindow::saveFile() { // quits the application
    saveFile(); // calls saveFile method
    QApplication::quit(); // quits the application
}

void MainWindow::exitFile() { // quits the application without saving
    QApplication::quit(); // quits the application
}

