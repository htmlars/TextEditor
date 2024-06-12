#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), textEdit(new QTextEdit(this)) {
    setCentralWidget(textEdit); // basic functionality of a text input stream has been implemented
    createMenus(); // method to create the navbar
}

void MainWindow::createMenus() {
    QMenuBar *bar = menuBar();
    QMenu *fileMenu = bar->addMenu(tr("&File"));

    QAction *saveAction = new QAction(tr("Save"), this); // method to save a text file

    QAction *exitAction = new QAction(tr("Exit"), this); // method to exit the navbar dropdown
}

