#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QTextEdit>
#include <stack>
#include <QLabel>

class TextEditor : public QMainWindow {
    Q_OBJECT

    public:
        TextEditor(QWidget *parent = nullptr);
        ~TextEditor() = default;

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
        void toggleDarkMode(bool dark);

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
};

#endif // TEXTEDITOR_H
