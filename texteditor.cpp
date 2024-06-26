#include "texteditor.h"
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
#include <QStyleFactory>
#include <QActionGroup>

TextEditor::TextEditor(QWidget *parent): QMainWindow(parent), textEdit(new QTextEdit(this)), modified(false), charCountLabel(new QLabel(this)) { // constructor
    setCentralWidget(textEdit);

    auto *status = new QStatusBar(this); // initialization of footer, where character counter will be displayed
    setStatusBar(status);
    status->addWidget(charCountLabel);

    // constructor calls the following methods
    createMenus();
    setupConnections();
    updateCharCount();


    resize(800, 600); // resizes window to 800 by 600 px

    toggleDarkMode(false);
}

void TextEditor::setupConnections() {
    connect(textEdit, &QTextEdit::textChanged, this, &TextEditor::textModified); // connects textEdit changes to textModified method
}

void TextEditor::textModified() { // method is called when text in the file is changed
    undoStack.push(textEdit->toPlainText()); // the latest update is pushed to the undoStack
    setModified(true); // set modified to true when text is modified
    updateCharCount(); // char count at the footer / statusbar is updated on text change
}

void TextEditor::setModified(bool value) { // method that accepts boolean value and sets modified variable to just that
    modified = value;
}

void TextEditor::updateCharCount() {
    int count = textEdit->toPlainText().length(); // count variable holds current character count
    charCountLabel->setText(tr("Zeichen: %1").arg(count)); // sets the label displayed in the footer to the character count
}

void TextEditor::createMenus() { // method that handles the creation of the navbar
    QMenuBar *bar = menuBar(); // creates the general navbar
    QMenu *fileMenu = bar->addMenu(tr("&Datei")); // adds a "datei" option to the nav
    QMenu *editMenu = bar->addMenu(tr("&Bearbeiten")); // adds "bearbeiten" option to the nav
    QMenu *viewMenu = bar->addMenu(tr("&Ansicht")); // adds "ansicht" option to the nav

    QAction *newAction = new QAction(tr("Neues Fenster"), this); // Dropdown option to create a new text file
    connect(newAction, &QAction::triggered, this, &TextEditor::newFile); // connects the event action to the newFile method
    fileMenu->addAction(newAction); // appends the action to the fileMenu

    QAction *openAction = new QAction(tr("Öffnen"), this); // Dropdown option to open a text file
    connect(openAction, &QAction::triggered, this, &TextEditor::openFile); // connects the event action to the openFile method
    fileMenu->addAction(openAction); // appends the action to the fileMenu

    QAction *saveAction = new QAction(tr("Speichern"), this); // Dropdown option to exit the text editor
    connect(saveAction, &QAction::triggered, this, &TextEditor::saveFile); // connects the event action to the beenden function
    fileMenu->addAction(saveAction); // appends the action to the fileMenu

    QAction *saveAsAction = new QAction(tr("Speichern unter"), this); // Dropdown option to save a text file
    connect(saveAsAction, &QAction::triggered, this, &TextEditor::saveAsFile); // connects the event action to the saveFile method
    fileMenu->addAction(saveAsAction); // appends the action to the fileMenu

    QAction *exitAction = new QAction(tr("Beenden"), this); // Dropdown Option to exit File
    connect(exitAction, &QAction::triggered, this, &TextEditor::exitFile); // connects the event action to the saveFile method
    fileMenu->addAction(exitAction); // appends the action to the fileMenu

    QAction *undoAction = new QAction(tr("Rückgängig"), this); // undo option to undo the latest change
    undoAction->setShortcut(QKeySequence::Undo); // sets shortcut for undo to basic qt undo shortcut, also displays label on the button
    connect(undoAction, &QAction::triggered, this, &TextEditor::undo); // connects the event action to the undo method
    editMenu->addAction(undoAction); // appends the action to the editMenu

    QAction *cutAction = new QAction(tr("Ausschneiden"), this); // cut option to cut the selected text
    cutAction->setShortcut(QKeySequence::Cut); // sets shortcut for cut to basic qt cut shortcut, also displays label on the button
    connect(cutAction, &QAction::triggered, this, &TextEditor::cut); // connects the event action to the cut method
    editMenu->addAction(cutAction); // appends the action to the editMenu

    QAction *copyAction = new QAction(tr("Kopieren"), this); // copy option to copy the selected text
    copyAction->setShortcut(QKeySequence::Copy); // sets shortcut for copy to basic qt copy shortcut, also displays label on the button
    connect(copyAction, &QAction::triggered, this, &TextEditor::copy); // connects the event action to the copy method
    editMenu->addAction(copyAction); // appends the action to the editMenu

    QAction *pasteAction = new QAction(tr("Einfügen"), this); // paste option to paste into the file
    pasteAction->setShortcut(QKeySequence::Paste); // sets shortcut for paste to basic qt paste shortcut, also displays label on the button
    connect(pasteAction, &QAction::triggered, this, &TextEditor::paste); // connects the event action to the paste method
    editMenu->addAction(pasteAction); // appends the action to the editMenu

    QAction *deleteAction = new QAction(tr("Löschen"), this); // delete option to delete the selected text
    deleteAction->setShortcut(QKeySequence::Delete); // sets shortcut for delete to basic qt delete shortcut, also displays label on the button
    connect(deleteAction, &QAction::triggered, this, &TextEditor::deleteText); // connects the event action to the delete method
    editMenu->addAction(deleteAction); // appends the action to the editMenu

    QActionGroup *backgroundGroup = new QActionGroup(this); // groups qactions so only one can be active at a time

    QAction *lightAction = new QAction(tr("Hell"), this); // lightMode option
    QAction *darkAction = new QAction(tr("Dunkel"), this); // darkMode option

    lightAction->setCheckable(true); // set theme modes to checkable, check label is displayed
    lightAction->setChecked(true); // start with light mode checked
    darkAction->setCheckable(true); // set theme modes to checkable, check label is displayed

    connect(lightAction, &QAction::triggered, this, [this]() { // new syntax (catch clause) to avoid new member functions
        toggleDarkMode(false); // toggles mode
    });
    connect(darkAction, &QAction::triggered, this, [this]() { // new syntax (catch clause) to avoid new member functions
        toggleDarkMode(true); // toggles mode
    });

    backgroundGroup->addAction(lightAction); // adds action to background group
    backgroundGroup->addAction(darkAction); // adds action to background group

    QMenu *backgroundMenu = viewMenu->addMenu(tr("Hintergrund")); // adds the background option to viewmenu navbar option
    backgroundMenu->addAction(lightAction);
    backgroundMenu->addAction(darkAction);
}

void TextEditor::newFile() {
    if (askForSave()) { // calls askForSave method which returns true only when no changes were made, or previous has been saved
        textEdit->clear(); // clears current file, acts as new file
        modified = false;
    }
}

bool TextEditor::askForSave() {
    if (modified && !textEdit->toPlainText().isEmpty()) { // asks for modified value and for the file to have at least some characters
        QMessageBox msgBox(this); // message box is created that acts as a dialog
        msgBox.setWindowTitle(tr("Editor")); // title of messagebox is editor
        msgBox.setText(tr("Möchten Sie die Änderungen speichern?")); // label of the messagebox
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel); // default messagebox values

        QAbstractButton *saveButton = msgBox.button(QMessageBox::Save);
        if (saveButton)
            saveButton->setText(tr("Speichern")); // this changes the label from "save" to "speichern"

        QAbstractButton *discardButton = msgBox.button(QMessageBox::Discard);
        if (discardButton)
            discardButton->setText(tr("Nicht speichern")); // this changes the label from "save" to "speichern"

        QAbstractButton *cancelButton = msgBox.button(QMessageBox::Cancel);
        if (cancelButton)
            cancelButton->setText(tr("Abbrechen")); // this changes the label from "save" to "speichern"

        msgBox.setDefaultButton(QMessageBox::Save); // default button when the enter button is clicked
        int ans = msgBox.exec(); // blocks the event loop until option is chosen and put into the variable

        if (ans == QMessageBox::Save) {
            saveAsFile(); // calls saveAs method
            modified = false; // sets modified to false again
        } else if (ans == QMessageBox::Cancel) {
            return false; // returns false
        }
    }
    return true; // returns true
}



void TextEditor::openFile() {
    if (askForSave()) { // new file can only be directly opened if previous file has been saved or discarded
        QString fileName = QFileDialog::getOpenFileName(this, tr("Öffnen"), "", tr("Text Files (*.txt);;All Files (*)")); // opens a file dialog to open a file
        if (fileName.isEmpty()) { // the method is returned from when filename is empty
            return;
        }
        QFile file(fileName); // new qfile object with the filename is created
        try {
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) { // tries to open the file in read mode; provides functions to read from and write to the device
                throw std::runtime_error("Kann nicht öffnen: " + file.errorString().toStdString());
            }
            QTextStream in(&file); // creation of a qtextstream object that points to the file
            textEdit->setPlainText(in.readAll()); // text stream reads the entire content
            file.close(); // closes the file
            modified = false;
            updateCharCount();
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Fehler"), tr(e.what())); // handles the exception
        }
    }
}

void TextEditor::saveAsFile() {
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

void TextEditor::saveFile() { // saves the file instantly if nothing was changed, else calls askforsave
    if (askForSave()) {
        return;
    }
    saveAsFile();
}

void TextEditor::exitFile() {    // quits the application without saving
    if (askForSave())
    {
        QApplication::quit(); // quits the application
    }
}

void TextEditor::undo() {
    if (!undoStack.empty()) {
        undoStack.pop(); // Remove current state as we are reverting to the previous
        if (!undoStack.empty()) { // this double check is for the case where there is only 1 character left, otherwise resulting in termination as more is undone than done
            QString lastText = undoStack.top(); // get the previous state of the text content
            textEdit->blockSignals(true); // block signals to avoid unintended infinite loops
            textEdit->setPlainText(lastText); // set the text content to the previous state
            textEdit->blockSignals(false); // release signal blocking
            setModified(true); // mark as modified
        } else {
            textEdit->clear(); // clear the text if there's only one character left (undo to an empty state)
            setModified(false); // no longer modified if content is cleared
        }
        updateCharCount(); // update character count label
    }
}

void TextEditor::cut() { // works with textedit method
    textEdit->cut();
    updateCharCount();
}

void TextEditor::copy() { // works with textedit method
    textEdit->copy();
}

void TextEditor::paste() { // works with textedit method
    textEdit->paste();
    updateCharCount();
}

void TextEditor::deleteText() { // works with textedit methods and deletes selected text
    textEdit->textCursor().removeSelectedText();
    updateCharCount();
}

void TextEditor::toggleDarkMode(bool dark) // https://stackoverflow.com/questions/15035767/is-the-qt-5-dark-fusion-theme-available-for-windows
{
    if (dark)
    {
        qApp->setStyle(QStyleFactory::create("Fusion")); // app style is set to fusion (default style)
        QPalette darkPalette; // creates palette for darkmode
        darkPalette.setColor(QPalette::Window, QColor(53, 53, 53)); // window background color
        darkPalette.setColor(QPalette::WindowText, Qt::white); // text color
        darkPalette.setColor(QPalette::Base, QColor(25, 25, 25)); // base background color
        darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53)); // alternate base background color
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white); // tooltip base color
        darkPalette.setColor(QPalette::ToolTipText, Qt::white); // tooltip text color
        darkPalette.setColor(QPalette::Text, Qt::white); // text color
        darkPalette.setColor(QPalette::Button, QColor(53, 53, 53)); // button background color
        darkPalette.setColor(QPalette::ButtonText, Qt::white); // button text color
        darkPalette.setColor(QPalette::BrightText, Qt::red); // highlighted text color (bright)
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218)); // link text color
        darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // highlighted text background color
        darkPalette.setColor(QPalette::HighlightedText, Qt::black); // highlighted text color
        qApp->setPalette(darkPalette); // apply palette
    }
    else
    {
        qApp->setStyle(QStyleFactory::create("Fusion")); // app style is set to fusion
        QPalette lightPalette; // creates palette for lightmode
        lightPalette.setColor(QPalette::Window, Qt::white); // window background color
        lightPalette.setColor(QPalette::WindowText, Qt::black); // text color
        lightPalette.setColor(QPalette::Base, Qt::white); // base background color
        lightPalette.setColor(QPalette::AlternateBase, Qt::white); // alternate base background color
        lightPalette.setColor(QPalette::ToolTipBase, Qt::white); // tooltip base color
        lightPalette.setColor(QPalette::ToolTipText, Qt::black); // tooltip text color
        lightPalette.setColor(QPalette::Text, Qt::black); // text color
        lightPalette.setColor(QPalette::Button, Qt::white); // button background color
        lightPalette.setColor(QPalette::ButtonText, Qt::black); // button text color
        lightPalette.setColor(QPalette::BrightText, Qt::red); // bright (highlighted) text color
        lightPalette.setColor(QPalette::Link, QColor(42, 130, 218)); // link text color
        lightPalette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // highlighted text background color
        lightPalette.setColor(QPalette::HighlightedText, Qt::white); // highlighted text color
        qApp->setPalette(lightPalette); // apply palette
    }
}

