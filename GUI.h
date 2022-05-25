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
        this->homeWindow(true, false, false);
    }

protected slots:

    void homeWindow(bool generic, bool locked, bool favorites);

    void compileScrollArea(bool generic, bool locked, bool favorites);

    void destroyHome(bool generic, bool locked, bool favorites) {
        addNewNoteBtn->hide();
        if (generic) {
            collections->hide();
            favoriteNotes->hide();
            lockedNotes->hide();
        }
        if (locked or favorites) {
            backToHome->hide();
        }
        scrollArea->hide();
    }

    void addNewNote(bool generic, bool locked, bool favorites);

    void destroyAddNewNote() {
        saveNote->hide();
        cancel->hide();
        noteTitle->hide();
        noteContent->hide();
    }

    void editGenericNote(int index, bool generic, bool locked, bool favorites);

    void editLockedNote(int index, bool generic, bool locked, bool favorites);

    void editFavoriteNote(int index, bool generic, bool locked, bool favorites);

    void destroyEditNote(bool generic, bool locked, bool favorites) {
        if (generic or favorites) {
            deleteNote->hide();
            editNote->hide();
        }
        if (generic) {
            editAddToLocked->hide();
            editAddToFavorites->hide();
        }
        if (favorites)
            removeFromFavorites->hide();
        if (locked)
            showUnlockNote->hide();
        exitEdit->hide();
        addToCollection->hide();
        editNoteTitle->hide();
        editNoteContent->hide();
    }

    void changeNote(int index, std::string title, std::string content,
                    bool generic, bool favorites) {
        if (generic)
            genericNotesMemory->editNote(index, title, content);
        else if (favorites) {
            favoriteNotesMemory->editNote(index, title, content);
        }
    }

    void removeNote(int index, bool generic, bool favorites) {
        if (generic)
            (*genericNotesMemory)[index].remove();
        else if (favorites)
            (*favoriteNotesMemory)[index].remove();
    }

    /*
     *
     * Collections Window
     *
     */

    void collectionHomeWindow();

    void destroyCollectionHomeWindow() {
        collectionToHome->hide();
        newCollection->hide();
        delete newCollection;
        collectionScrollArea->hide();
    }

    void newCollectionPopUp();

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

    void addNoteToCollection(int collectionIndex, int noteIndex, NotesMemory *provenienceDataBase) {
        (*folderManager)[collectionIndex].newNote((*provenienceDataBase)[noteIndex].getTitle(),
                                                  (*provenienceDataBase)[noteIndex].getContent());
    }

    /*void addNoteToCollection(int collectionIndex, std::string title, NotesMemory *provenienceDataBase) {
        (*folderManager)[collectionIndex].newNote((*provenienceDataBase)[title].getTitle(),
                                                  (*provenienceDataBase)[title].getContent());
    }*/

    void destroyAddtoCollectionPopUp() {
        addToCollectionBasePopUp->hide();
    }


protected:
    // dataBases
    NotesMemory *genericNotesMemory = new NotesMemory("genericNotes.lsml");
    NotesMemory *favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    NotesMemory *lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);
    FolderManager *folderManager = new FolderManager("foldersDb.lsml");

    // home page
    QPushButton* addNewNoteBtn;
    QPushButton* favoriteNotes;
    QPushButton *lockedNotes;
    QPushButton *collections;
    QScrollArea *scrollArea;
    QPushButton *backToHome;
    QWidget *widget;
    QVBoxLayout* boxLayout;
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
    QPushButton *showUnlockNote;
    QPushButton *removeFromFavorites;

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


    void errorPopUp(const string &errorMessage);

    QWidget *popUpBase;
    QLabel *message;
    QPushButton *okBtn;
};

#endif //BLOCCONOTE_GUI_H
