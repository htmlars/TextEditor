#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QAbstractButton>>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), textEdit(new QTextEdit(this)), modified(false) {
    setCentralWidget(textEdit);
    createMenus();
    setupConnections();
}

void MainWindow::setupConnections() {
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::textModified);
}

void MainWindow::textModified() {
    setModified(true); // set modified to true when text is modified
}

void MainWindow::setModified(bool value) {
    modified = value;
}

void MainWindow::createMenus() {
    QMenuBar *bar = menuBar(); // creates a navbar / menu
    QMenu *fileMenu = bar->addMenu(tr("&Datei")); // adds a file to the menu

    QAction *newAction = new QAction(tr("Neues Fenster"), this); // Dropdown option to create a new text file
    connect(newAction, &QAction::triggered, this, &MainWindow::newFile); // connects the event action to the newFile method
    fileMenu->addAction(newAction); // appends the action to the fileMenu

    QAction *openAction = new QAction(tr("Öffnen"), this); // Dropdown option to open a text file
    connect(openAction, &QAction::triggered, this, &MainWindow::openFile); // connects the event action to the openFile method
    fileMenu->addAction(openAction); // appends the action to the fileMenu

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

void MainWindow::newFile() {
    if (askForSave()) {
        textEdit->clear();
        modified = false;
    }
}

bool MainWindow::askForSave() {
    if (modified) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(tr("Editor"));
        msgBox.setText(tr("Möchten Sie die Änderungen speichern?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        QAbstractButton *saveButton = msgBox.button(QMessageBox::Save);
        if (saveButton)
            saveButton->setText(tr("Speichern"));

        QAbstractButton *discardButton = msgBox.button(QMessageBox::Discard);
        if (discardButton)
            discardButton->setText(tr("Nicht speichern"));

        QAbstractButton *cancelButton = msgBox.button(QMessageBox::Cancel);
        if (cancelButton)
            cancelButton->setText(tr("Abbrechen"));

        msgBox.setDefaultButton(QMessageBox::Save); // default button when the enter button is clicked
        int ans = msgBox.exec();

        if (ans == QMessageBox::Save) {
            saveAsFile();
            modified = false;
        } else if (ans == QMessageBox::Cancel) {
            return false;
        }
    }
    return true; // return the value
}



void MainWindow::openFile() {
    if (askForSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Öffnen"), "", tr("Text Files (*.txt);;All Files (*)")); // opens a file dialog to open a file
        if (fileName.isEmpty()) { // the method is returned from when no filename is selected
            return;
        }
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // tries to open the file in read mode
            QMessageBox::warning(this, tr("Error"), tr("Kann nicht öffnen: ") + file.errorString()); // throws error when file cant be opened
            return;
        }
        QTextStream in(&file); // creation of a qtextstream object that points to the file
        textEdit->setPlainText(in.readAll()); // text stream reads the entire content
        file.close(); // closes the file
        modified = false;
    }
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
    modified = false;
}

void MainWindow::saveFile() { // quits the application
    if (askForSave()) {
        return;
    }
    saveAsFile();
}

void MainWindow::exitFile() {    // quits the application without saving
    if (askForSave())
    {
        QApplication::quit(); // quits the application
    }
}

