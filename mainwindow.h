#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <stack>
#include <QLabel>

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
        void undo();
        void cut();
        void copy();
        void paste();
        void deleteText();

    private:
        void createMenus();
        bool askForSave();
        bool modified;
        void setupConnections();
        void setModified(bool value);
        void updateCharCount();

        QTextEdit *textEdit;
        std::stack<QString> undoStack;
        QLabel *charCountLabel;
        // highlight Text
        // WordCounter
};

#endif // MAINWINDOW_H
