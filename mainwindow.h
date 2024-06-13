#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() = default;

    private:
        QTextEdit *textEdit;
        void createMenus();
        void saveAsFile();
        void saveFile();
        void exitFile();
        // void openFile();
        // highlight Text
        // WordCounter
};

#endif // MAINWINDOW_H
