//
// Created by Codes on 20/05/2022.
//

#ifndef BLOCCONOTE_GUI_H
#define BLOCCONOTE_GUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QMainWindow>
#include <QVBoxLayout>
#include "NotesMemory.h"
#include <QLabel>

using namespace std;

class GUI : public QMainWindow {
public:
     GUI() {
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
        favoriteNotes->hide();
        lockedNotes->hide();
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
        editAddToFavorites->hide();
        editAddToLocked->hide();
        this->editNoteTitle->hide();
        this->editNoteContent->hide();
        this->homeWindow();
    }

    void saveNewNote() {
        genericNotesMemory->newNote((this->noteTitle->toPlainText()).toStdString(),
                                         (this->noteContent->toPlainText()).toStdString());
        destroyNewNoteWIndow();
    }

    void removeNote(int index) {
        genericNotesMemory->deleteNote(index);
        this->destroyEditNoteWindow();
    }

    void changeNote(int index, const std::string& title, const std::string& content) {
        genericNotesMemory->editNote(index, title, content);
        this->destroyEditNoteWindow();
    }

    // TODO void openFavorites();
    void openLocked() {
        destroyHomeWindow();
        lockedHomeWindow();
    }

    void lockedToHome() {
        destroyLockedHomeWindow();
        homeWindow();
    }

    // TODO void transferNote(int index);

    /*
     *
     *
     * Locked Notes Window
     *
     *
     */

    void lockedHomeWindow();

    void lockedNewNoteWindow();

    void showLockedNoteWindow(int index);

    void destroyLockedHomeWindow() {
        addNewLockedNoteBtn->hide();
        lockedScrollArea->hide();
        returnToMainHome->hide();
    }

    void destroyLockedNewNoteWindow() {
        saveLockedNote->hide();
        lockCancel->hide();
        lockedNoteTitle->hide();
        lockedNoteContent->hide();
        this->lockedHomeWindow();
    }

    void destroyLockedNoteShowWindow() {
        deleteLockedNote->hide();
        exitShow->hide();
        showUnlockNote->hide();
        this->showNoteTitle->hide();
        this->showNoteContent->hide();
        this->lockedHomeWindow();
    }

    void saveLockedWindow() {
        lockedNotesMemory->newNote((this->lockedNoteTitle->toPlainText()).toStdString(),
                                         (this->lockedNoteContent->toPlainText()).toStdString());
        destroyNewNoteWIndow();
    }

    void removeLockedNote(int index) {
        lockedNotesMemory->deleteNote(index);
        this->destroyEditNoteWindow();
    }


protected:
    // dataBases
    NotesMemory* genericNotesMemory = new NotesMemory("genericNotes.lsml");
    NotesMemory* favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    NotesMemory* lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);

    /*
     *
     *
     * Genrric Notes Window
     *
     *
     */

    // home page
    QPushButton* addNewNoteBtn;
    QPushButton* favoriteNotes;
    QPushButton* lockedNotes;
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
    QPushButton* editAddToFavorites;
    QPushButton* editAddToLocked;
    QPushButton* exitEdit;
    QTextEdit* editNoteTitle;
    QTextEdit* editNoteContent;

    /*
     *
     *
     * Locked Notes Window
     *
     *
     */

    // home page
    QPushButton* returnToMainHome;
    QPushButton* addNewLockedNoteBtn;
    QScrollArea* lockedScrollArea;
    QWidget* lockedWidget;
    QVBoxLayout* lockedBoxLayout;
    void compileLockedScrollArea();

    // new note window
    QPushButton* saveLockedNote;
    QPushButton* lockCancel;
    QTextEdit* lockedNoteTitle;
    QTextEdit* lockedNoteContent;

    // show note window
    QPushButton* deleteLockedNote;
    QPushButton* showUnlockNote;
    QPushButton* exitShow;
    QTextEdit* showNoteTitle;
    QTextEdit* showNoteContent;


    /*
     *
     *
     * Favorite Notes Window
     *
     *
     */

};


#endif //BLOCCONOTE_GUI_H
