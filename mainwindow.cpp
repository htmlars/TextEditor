#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QAbstractButton>
#include <exception>
#include <stack>
#include <QClipboard>
#include <QKeySequence>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), textEdit(new QTextEdit(this)), modified(false), charCountLabel(new QLabel(this)) {
    setCentralWidget(textEdit);

    auto *status = new QStatusBar(this);
    setStatusBar(status);
    status->addWidget(charCountLabel);

    createMenus();
    setupConnections();
    updateCharCount();
}

void MainWindow::setupConnections() {
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::textModified);
}

void MainWindow::textModified() {
    undoStack.push(textEdit->toPlainText());
    setModified(true); // set modified to true when text is modified
    updateCharCount();
}

void MainWindow::setModified(bool value) {
    modified = value;
}

void MainWindow::updateCharCount() {
    int count = textEdit->toPlainText().length();
    charCountLabel->setText(tr("Zeichen: %1").arg(count));
}

void MainWindow::createMenus() {
    QMenuBar *bar = menuBar(); // creates a navbar / menu
    QMenu *fileMenu = bar->addMenu(tr("&Datei")); // adds a file to the menu
    QMenu *editMenu = bar->addMenu(tr("&Bearbeiten"));

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

    QAction *undoAction = new QAction(tr("Rückgängig"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);
    editMenu->addAction(undoAction);

    QAction *cutAction = new QAction(tr("Ausschneiden"), this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, &QAction::triggered, this, &MainWindow::cut);
    editMenu->addAction(cutAction);

    QAction *copyAction = new QAction(tr("Kopieren"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
    editMenu->addAction(copyAction);

    QAction *pasteAction = new QAction(tr("Einfügen"), this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
    editMenu->addAction(pasteAction);

    QAction *deleteAction = new QAction(tr("Löschen"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteText);
    editMenu->addAction(deleteAction);
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
        try {
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // tries to open the file in read mode
                throw std::runtime_error("Kann nicht öffnen: " + file.errorString().toStdString());
            }
            QTextStream in(&file); // creation of a qtextstream object that points to the file
            textEdit->setPlainText(in.readAll()); // text stream reads the entire content
            file.close(); // closes the file
            modified = false;
            updateCharCount();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Fehler"), tr(e.what()));
        }
    }
}

void MainWindow::saveAsFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Speichern"), "", tr("Text Files (*.txt);;All Files (*)")); // opens a file dialog to save it somewhere
    if (fileName.isEmpty()) { // the method is returned from when no filename is selected
        return;
    }
    QFile file(fileName); // creates a qfile object with the filename
    try {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // tries to open the file in write mode
            throw std::runtime_error("Kann nicht speichern: " + file.errorString().toStdString());
        }
        QTextStream out(&file); // creates a textstream to write into the file
        out << textEdit->toPlainText(); // writes the text of the textedit into the file
        file.close(); // closes the file
        modified = false;
    } catch (const std::exception& e) {
        QMessageBox::warning(this, tr("Fehler"), tr(e.what()));
    }
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

void MainWindow::undo() {
    if (!undoStack.empty()) {
        undoStack.pop();
        if (!undoStack.empty()) {
            QString lastText = undoStack.top();
            undoStack.pop();
            textEdit->blockSignals(true);
            textEdit->setPlainText(lastText);
            textEdit->blockSignals(false);
        } else {
            textEdit->clear();
        }
        setModified(true);
        updateCharCount();
    }
}

void MainWindow::cut() {
    textEdit->cut();
    updateCharCount();
}

void MainWindow::copy() {
    textEdit->copy();
}

void MainWindow::paste() {
    textEdit->paste();
    updateCharCount();
}

void MainWindow::deleteText() {
    textEdit->textCursor().removeSelectedText();
    updateCharCount();
}

