//
// Created by Codes on 20/05/2022.
//

#ifndef BLOCCONOTE_GUINTERFACE_H
#define BLOCCONOTE_GUINTERFACE_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QMainWindow>
#include <QVBoxLayout>
#include "NotesMemory.h"
#include "IdPushButton.h"

using namespace std;

class GUInterface : public QMainWindow{
public:
     GUInterface() {
        this->setFixedSize(600, 600);
        this->setStyleSheet("background-color: #ABD1C6");
        this->homeWindow();
    }

private slots:
    void homeWindow();

    void newNoteWindow();

    void editNoteWindow(int index);

    void destroyHomeWindow() {
        addNewNoteBtn->hide();
        scrollArea->hide();
    };

    void destroyNewNoteWIndow() {
        saveNote->hide();
        cancel->hide();
        noteTitle->hide();
        noteContent->hide();
        this->homeWindow();
    }

    void destroyEditNoteWindow() {
        editNote->hide();
        deleteNote->hide();
        exitEdit->hide();
        this->editNoteTitle->hide();
        this->editNoteContent->hide();
        this->homeWindow();
    }

    void saveNewNote() {
        this->notesMemory.newNote((this->noteTitle->toPlainText()).toStdString(),
                                  (this->noteContent->toPlainText()).toStdString());
        destroyNewNoteWIndow();
    }

    void removeNote(int index) {
        this->notesMemory.deleteNote(index);
        this->destroyEditNoteWindow();
    }

    void changeNote(int index, const std::string& title, const std::string& content) {
        this->notesMemory.editNote(index, title, content);
        this->destroyEditNoteWindow();
    }

private:
    NotesMemory notesMemory;

    // home page
    QPushButton* addNewNoteBtn;
    QScrollArea* scrollArea;
    QWidget* widget;
    QVBoxLayout* boxLayout;
    void compileScrollBar();

    // new note window
    QPushButton* saveNote;
    QPushButton* cancel;
    QTextEdit* noteTitle;
    QTextEdit* noteContent;

    // edit note window
    QPushButton* editNote;
    QPushButton* deleteNote;
    QPushButton* exitEdit;
    QTextEdit* editNoteTitle;
    QTextEdit* editNoteContent;


};


#endif //BLOCCONOTE_GUINTERFACE_H
