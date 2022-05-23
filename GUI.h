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

    void changeNote(int index, const std::string &title, const std::string &content) {
        genericNotesMemory->editNote(index, title, content);
    }

    void openFavorites() {
        destroyHomeWindow();
        favoriteHomeWindow();
    }

    void openLocked() {
        destroyHomeWindow();
        lockedHomeWindow();
    }

    void lockedToHome() {
        destroyLockedHomeWindow();
        homeWindow();
    }

    void favoriteToHome() {
        destroyFavoriteHomeWindow();
        homeWindow();
    }

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

    void destroyNewLockedNoteWindow() {
        saveLockedNote->hide();
        lockCancel->hide();
        lockedNoteTitle->hide();
        lockedNoteContent->hide();
        this->lockedHomeWindow();
    }

    void destroyLockedNoteShowWindow() {
        exitShow->hide();
        showUnlockNote->hide();
        this->showNoteTitle->hide();
        this->showNoteContent->hide();
        this->lockedHomeWindow();
    }

    void saveLockedWindow() {
        lockedNotesMemory->newNote((this->lockedNoteTitle->toPlainText()).toStdString(),
                                   (this->lockedNoteContent->toPlainText()).toStdString());
        destroyNewLockedNoteWindow();
    }

    /*
     *
     *
     * Favorite Notes Window
     *
     *
     */

    void favoriteHomeWindow();

    void newFavoriteNoteWindow();

    void editFavoriteNoteWindow(int index);

    void destroyFavoriteHomeWindow() {
        addNewFavoriteNoteBtn->hide();
        returnToHome->hide();
        favoriteScrollArea->hide();
    }

    void destroyNewFavoriteNoteWindow() {
        saveFavoriteNote->hide();
        cancelFavoriteNote->hide();
        favoriteNoteTitle->hide();
        favoriteNoteContent->hide();
    }

    void destroyEditFavoriteNoteWindow() {
        editFavoriteNote->hide();
        deleteFavoriteNote->hide();
        exitFavoriteEdit->hide();
        editFavoriteNoteTitle->hide();
        editFavoriteNoteContent->hide();
        removeFromFavorites->hide();
    }

    void saveFavoriteNoteWindow() {
        favoriteNotesMemory->newNote((this->favoriteNoteTitle->toPlainText()).toStdString(),
                                     (this->favoriteNoteContent->toPlainText()).toStdString());
        destroyNewFavoriteNoteWindow();
        favoriteHomeWindow();
    }

    void removeFavoriteNote(int index) {
        favoriteNotesMemory->deleteNote(index);
    }

    void changeFavoriteNote(int index, const std::string &title, const std::string &content) {
        favoriteNotesMemory->editNote(index, title, content);
    }

protected:
    // dataBases
    NotesMemory *genericNotesMemory = new NotesMemory("genericNotes.lsml");
    NotesMemory *favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    NotesMemory *lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);

    /*
     *
     *
     * Generic Notes Window
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

    // home page
    QPushButton *addNewFavoriteNoteBtn;
    QPushButton *returnToHome;
    QScrollArea *favoriteScrollArea;
    QWidget *favoriteWidget;
    QVBoxLayout *favoriteBoxLayout;

    void compileFavoriteScrollArea();

    // new note window
    QPushButton *saveFavoriteNote;
    QPushButton *cancelFavoriteNote;
    QTextEdit *favoriteNoteTitle;
    QTextEdit *favoriteNoteContent;

    // edit note window
    QPushButton *editFavoriteNote;
    QPushButton *deleteFavoriteNote;
    QPushButton *removeFromFavorites;
    QPushButton *exitFavoriteEdit;
    QTextEdit *editFavoriteNoteTitle;
    QTextEdit *editFavoriteNoteContent;
};


#endif //BLOCCONOTE_GUI_H
