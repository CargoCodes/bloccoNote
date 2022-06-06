#ifndef BLOCCONOTE_GUI_H
#define BLOCCONOTE_GUI_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <QtWidgets/QScrollArea>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "NotesManager.h"
#include "FolderManager.h"


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

    /*
     * Every method regarding the home window
     * is based on ints provenience, specified
     * by the three parameters:
     * generic(:bool), locked(:bool), favorite(:bool)
     *
     */

    void homeWindow(bool generic, bool locked, bool favorites);

    void compileScrollArea(bool generic, bool locked, bool favorites);

    void destroyHome(bool generic, bool locked, bool favorites) {
        addNewNoteBtn->hide();
        delete addNewNoteBtn;
        if (generic) {
            collections->hide();
            delete collections;
            favoriteNotes->hide();
            delete favoriteNotes;
            lockedNotes->hide();
            delete lockedNotes;
        }
        if (locked or favorites) {
            backToHome->hide();
            delete backToHome;
        }
        scrollArea->hide();
        delete scrollArea;
    }

    void addNewNote(bool generic, bool locked, bool favorites);

    void destroyAddNewNote() {
        saveNote->hide();
        delete saveNote;
        cancel->hide();
        delete cancel;
        noteTitle->hide();
        delete noteTitle;
        noteContent->hide();
        delete noteContent;
    }

    void editGenericNote(int index, bool generic, bool locked, bool favorites);

    void editLockedNote(int index, bool generic, bool locked, bool favorites);

    void editFavoriteNote(int index, bool generic, bool locked, bool favorites);

    void destroyEditNote(bool generic, bool locked, bool favorites) {
        if (generic or favorites) {
            deleteNote->hide();
            delete deleteNote;
            editNote->hide();
            delete editNote;
        }
        if (generic) {
            editAddToLocked->hide();
            delete editAddToLocked;
            editAddToFavorites->hide();
            delete editAddToFavorites;
        }
        if (favorites) {
            removeFromFavorites->hide();
            delete removeFromFavorites;
        }
        if (locked) {
            showUnlockNote->hide();
            delete showUnlockNote;
        }
        exitEdit->hide();
        delete exitEdit;
        addToCollection->hide();
        delete addToCollection;
        editNoteTitle->hide();
        delete editNoteTitle;
        editNoteContent->hide();
        delete editNoteContent;
    }

    void changeNote(int index, std::string title, std::string content) {
        if (folderManager->contains((*notesManager)[index].getTitle())) {
            auto folderName = folderManager->isIn((*notesManager)[index].getTitle());
            folderManager->editNote(folderName, (*notesManager)[index].getTitle(), title);
        }
        notesManager->editNote(index, title, content);
    }

    void removeNote(int index) {
        string notetitle = (*notesManager)[index].getTitle();
        folderManager->deleteNote(notetitle);
        notesManager->deleteNote(index);
    }

    /*
     *
     * Collections Window
     *
     */

    void collectionHomeWindow();

    void destroyCollectionHomeWindow() {
        collectionToHome->hide();
        delete collectionToHome;
        newCollection->hide();
        delete newCollection;
        collectionScrollArea->hide();
        delete collectionScrollArea;
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
        delete backToCollections;
        removeFolder->hide();
        delete removeFolder;
        cover->hide();
        delete cover;
        folderScrollArea->hide();
        delete folderScrollArea;
    }

    /*
     *
     * Add To Collection PopUp
     *
     */

    void addToCollectionPopUp(int noteIndex);

    void addNoteToCollection(int collectionIndex, int noteIndex) {
        if ((*folderManager)[collectionIndex].isIn((*notesManager)[noteIndex].getTitle()))
            errorPopUp("Note \"" + (*notesManager)[noteIndex].getTitle() +
                       "\" is altready\npart of \"" + (*folderManager)[collectionIndex].getFolderName() +
                       "\" collection");
        else
            (*folderManager)[collectionIndex].newNote((*notesManager)[noteIndex].getTitle());
    }

    void destroyAddtoCollectionPopUp() {
        addToCollectionBasePopUp->hide();
        delete addToCollectionBasePopUp;
    }


protected:
    // dataBases
    NotesManager *notesManager = new NotesManager(); // dataBase which contains all the notes (saved locally by LsmL system)
    FolderManager *folderManager = new FolderManager(); // dataBase which contains all the folders an the notes
    // which they contain (saved locally by LsmL system)

    // home page
    QPushButton *addNewNoteBtn;
    QPushButton *favoriteNotes;
    QPushButton *lockedNotes;
    QPushButton *collections;
    QScrollArea *scrollArea;
    QPushButton *backToHome;
    QWidget *widget;
    QVBoxLayout *boxLayout;
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

    QWidget *popUpBaseWidget;
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
    QLabel *cover;
    QPushButton *removeFolder;
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

    void compileAddToCollectionPopUp(int noteIndex);

    /*
     *
     * Error PopUp
     *
     */

    void errorPopUp(const string &errorMessage);

    QWidget *popUpBase;
    QLabel *message;
    QPushButton *okBtn;
};

#endif //BLOCCONOTE_GUI_H
