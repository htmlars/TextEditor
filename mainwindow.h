#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    public slots:
        void newFile();
        void saveAsFile();
        void saveFile();
        void exitFile();
        void openFile();
        void textModified();

    private:
        QTextEdit *textEdit;
        void createMenus();
        bool askForSave();
        bool modified;
        void setupConnections();
        void setModified(bool value);
        // highlight Text
        // WordCounter
};

#endif // MAINWINDOW_H
