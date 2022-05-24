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
#include "FolderManager.h"
#include <QLabel>

using namespace std;

class GUI : public QMainWindow {
public:
    GUI() {
        this->setFixedSize(800, 800);
        this->setWindowTitle("Awesome Notes");
        this->setStyleSheet("background-color: #ABD1C6");
        this->homeWindow();
    }

protected slots:

    /*
     *
     *
     * Window Movements
     *
     *
     */

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

    void openCollections() {
        destroyHomeWindow();
        collectionHomeWindow();
    }

    void favoriteToHome() {
        destroyFavoriteHomeWindow();
        homeWindow();
    }

    void collectionToHomeWindow() {
        destroyCollectionHomeWindow();
        homeWindow();
    }

    void folderToCollection() {
        destroyFolderHomeWindow();
        collectionHomeWindow();
    }

    /*
     *
     *
     * Generic Windowr
     *
     *
     */

    void homeWindow();

    void newNoteWindow();

    void editNoteWindow(int index);

    void editNoteWindow(std::string title);

    void destroyHomeWindow() {
        addNewNoteBtn->hide();
        scrollArea->hide();
        favoriteNotes->hide();
        lockedNotes->hide();
        collections->hide();
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
        editAddToFavorites->hide();
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

    void removeNote(std::string title) {
        genericNotesMemory->deleteNote(title);
        this->destroyEditNoteWindow();
    }

    void changeNote(int index, const std::string &title, const std::string &content) {
        genericNotesMemory->editNote(index, title, content);
    }

    void changeNote(std::string notetitle, const std::string &title, const std::string &content) {
        genericNotesMemory->editNote(notetitle, title, content);
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

    void showLockedNoteWindow(std::string title);

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
        lockedHomeWindow();
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

    void editFavoriteNoteWindow(std::string title);

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

    void removeFavoriteNote(std::string title) {
        favoriteNotesMemory->deleteNote(title);
    }

    void changeFavoriteNote(int index, const std::string &title, const std::string &content) {
        favoriteNotesMemory->editNote(index, title, content);
    }

    void changeFavoriteNote(std::string notetitle, const std::string &title, const std::string &content) {
        favoriteNotesMemory->editNote(notetitle, title, content);
    }

    /*
     *
     * Copilations
     *
     */

    void collectionHomeWindow();

    void destroyCollectionHomeWindow() {
        collectionToHome->hide();
        newCollection->hide();
        collectionScrollArea->hide();
    }

    void newCollectionPopUp();

    void saveCollection(std::string folderName) {
        folderManager->addNewFolder(folderName);
    }

    /*
     *
     * Folders
     *
     */

    void folderHomeWindow(int index);

    void destroyFolderHomeWindow() {
        backToCollections->hide();
        folderScrollArea->hide();
    }

    /*
     *
     * Add To Collection PopUp
     *
     */

    void addToCollectionPopUp(int noteIndex, NotesMemory *dataBase);

    void addToCollectionPopUp(std::string title, NotesMemory *dataBase);

    void addNoteToCollection(int collectionIndex, int noteIndex, NotesMemory *provenienceDataBase) {
        (*folderManager)[collectionIndex].newNote((*provenienceDataBase)[noteIndex].getTitle(),
                                                  (*provenienceDataBase)[noteIndex].getContent());
    }

    void addNoteToCollection(int collectionIndex, std::string title, NotesMemory *provenienceDataBase) {
        (*folderManager)[collectionIndex].newNote((*provenienceDataBase)[title].getTitle(),
                                                  (*provenienceDataBase)[title].getContent());
    }

    void destroyAddtoCollectionPopUp() {
        addToCollectionBasePopUp->hide();
    }


protected:
    // dataBases
    NotesMemory *genericNotesMemory = new NotesMemory("genericNotes.lsml");
    NotesMemory *favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    NotesMemory *lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);
    FolderManager *folderManager = new FolderManager("foldersDb.lsml");

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
    QPushButton *lockedNotes;
    QPushButton *collections;
    QScrollArea *scrollArea;
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
    QPushButton *editAddToLocked;
    QPushButton *addToCollection;
    QPushButton *exitEdit;
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
    QPushButton *showUnlockNote;
    QPushButton *addLockedToCollection;
    QPushButton *exitShow;
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
    QPushButton *addFavoriteToCollection;
    QPushButton *exitFavoriteEdit;
    QTextEdit *editFavoriteNoteTitle;
    QTextEdit *editFavoriteNoteContent;

    /*
     *
     *
     * Collections Window
     *
     *
     */

    QPushButton *collectionToHome;
    QScrollArea *collectionScrollArea;
    QWidget *collectionWidget;
    QVBoxLayout *collectionBoxLayout;
    QPushButton *newCollection;

    void compileCollectionScrollBar();

    /*
     *
     * Collection PopUp
     *
     */

    QLabel *popUpBaseLabel;
    QLabel *titleLabel;
    QTextEdit *newCollectionName;
    QPushButton *saveNewCollection;
    QPushButton *exitNewCollectionPopUp;

    /*
     *
     * Folder Window
     *
     */

    QPushButton *backToCollections;
    QWidget *folderWidget;
    QVBoxLayout *folderBoxLayout;
    QScrollArea *folderScrollArea;

    void compileFolderScrollArea(int index);

    /*
     *
     * Add To Collection PopUp
     *
     */

    QWidget *addToCollectionBasePopUp;
    QWidget *addToCollectionWidget;
    QVBoxLayout *addToCollectionBoxLayout;
    QScrollArea *addToCollectionScrollArea;

    void compileAddToCollectionPopUp(int noteIndex, NotesMemory *dataBase);

    void compileAddToCollectionPopUp(string title, NotesMemory *dataBase);
};

#endif //BLOCCONOTE_GUI_H
