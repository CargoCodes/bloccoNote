//
// Created by Codes on 20/05/2022.
//

#ifndef BLOCCONOTE_MAINWINDOW_H
#define BLOCCONOTE_MAINWINDOW_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QMainWindow>
#include <QVBoxLayout>
#include "NotesMemory.h"
#include "IdPushButton.h"
#include "LockedWindow.h"
#include "db.h"

using namespace std;

class MainWindow : public QMainWindow {
public:
     MainWindow() {
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
        addToFavorites->hide();
        addToLocked->hide();
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
        db::genericNotesMemory.newNote((this->noteTitle->toPlainText()).toStdString(),
                                         (this->noteContent->toPlainText()).toStdString());
        destroyNewNoteWIndow();
    }

    void removeNote(int index) {
        db::genericNotesMemory.deleteNote(index);
        this->destroyEditNoteWindow();
    }

    void changeNote(int index, const std::string& title, const std::string& content) {
        db::genericNotesMemory.editNote(index, title, content);
        this->destroyEditNoteWindow();
    }

    //void openFavorites();
    void openLocked() {
        blockedWindow.show();
    }

    static void addNoteToFavorites(int index) {
        db::genericNotesMemory.transferNote(index, db::favoriteNotesMemory);
    }

    static void addNoteToLocked(int index) {
        db::genericNotesMemory.transferNote(index, db::lockedNotesMemory);
    }

protected:
    LockedWindow blockedWindow;

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
    QPushButton* addToFavorites;
    QPushButton* addToLocked;
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


#endif //BLOCCONOTE_MAINWINDOW_H
