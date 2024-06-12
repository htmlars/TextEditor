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
        void saveFile();
        void createMenus();
        void saveAndExit();
};

#endif // MAINWINDOW_H
