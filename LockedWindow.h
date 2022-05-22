//
// Created by Codes on 21/05/2022.
//

#ifndef BLOCCONOTE_LOCKEDWINDOW_H
#define BLOCCONOTE_LOCKEDWINDOW_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "NotesMemory.h"
#include "IdPushButton.h"
#include "db.h"

class LockedWindow : public QMainWindow {
public:
    LockedWindow() {
        this->setFixedSize(800, 800);
        this->setStyleSheet("background-color: #ABD1C6");
        this->homeWindow();
    }

protected slots:
    void homeWindow();

    void newNoteWindow();

    void editNoteWindow(int index);

    void destroyHomeWindow() {
        addNewNoteBtn->hide();
        scrollArea->hide();
        titleLabel->hide();
    };

    void destroyNewNoteWIndow() {
        saveNote->hide();
        cancel->hide();
        addToFavorites->hide();
        noteTitle->hide();
        noteContent->hide();
        this->homeWindow();
    }

    void destroyEditNoteWindow() {
        editNote->hide();
        deleteNote->hide();
        exitEdit->hide();
        editAddToFavorites->hide();
        editAddToLocked->hide();
        this->editNoteTitle->hide();
        this->editNoteContent->hide();
        this->homeWindow();
    }

    void saveNewNote() {
        db::lockedNotesMemory.newNote((this->noteTitle->toPlainText()).toStdString(),
                                         (this->noteContent->toPlainText()).toStdString());
        destroyNewNoteWIndow();
    }

    void removeNote(int index) {
        db::lockedNotesMemory.deleteNote(index);
        this->destroyEditNoteWindow();
    }

    void changeNote(int index, const std::string& title, const std::string& content) {
        db::lockedNotesMemory.editNote(index, title, content);
        this->destroyEditNoteWindow();
    }

    //void openFavorites();
    //void openLocked();

    void addNoteToFavorites(int index) {
        db::lockedNotesMemory.transferNote(index, db::favoriteNotesMemory);
    }

protected:

    // home page
    QPushButton* addNewNoteBtn;
    QLabel* titleLabel;
    QScrollArea* scrollArea;
    QWidget* widget;
    QVBoxLayout* boxLayout;
    void compileScrollArea();

    // new note window
    QPushButton* saveNote;
    QPushButton* addToFavorites;
    QPushButton* cancel;
    QTextEdit* noteTitle;
    QTextEdit* noteContent;

    // edit note window
    QPushButton* editNote;
    QPushButton* deleteNote;
    QPushButton* editAddToFavorites;
    QPushButton* editAddToLocked;
    QPushButton* exitEdit;
    QTextEdit* editNoteTitle;
    QTextEdit* editNoteContent;
};


#endif //BLOCCONOTE_LOCKEDWINDOW_H
