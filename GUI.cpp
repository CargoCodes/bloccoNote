#include "GUI.h"

void GUI::tryCompileScrollArea(bool generic, bool locked, bool favorites) {
    QFont font; // font definition
    font.setPointSize(20);

    if (generic) {
        delete genericNotesMemory;
        genericNotesMemory = new NotesMemory("genericNotes.lsml");
        if (genericNotesMemory->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < genericNotesMemory->size(); i++) { // for each note in the database creates a idButton
                auto note = (*genericNotesMemory)[i];

                QPushButton *btn = new QPushButton((note.getTitle()).c_str());
                int index = i;

                connect(btn, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
                    tryDestroyHome(generic, locked, favorites);
                    tryEditGenericNote(index, generic, locked, favorites);
                });

                btn->setStyleSheet("background-color: #2CB67D; color: black;");
                btn->setFixedSize(400, 40);
                btn->move(50, 0);
                btn->setFont(font);
                boxLayout->addWidget(btn);
            }
        }
    }

    if (generic or locked) {
        delete lockedNotesMemory;
        lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);
        if (lockedNotesMemory->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < lockedNotesMemory->size(); i++) { // for each note in the database creates a idButton

                auto note = (*lockedNotesMemory)[i];
                string title = note.getTitle();

                if (generic)
                    title += " [✖]";

                QPushButton *btn = new QPushButton(title.c_str());
                int index = i;

                connect(btn, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
                    tryDestroyHome(generic, locked, favorites);
                    tryEditLockedNote(index, generic, locked, favorites);
                });

                btn->setStyleSheet("background-color: #2CB67D; color: black;");
                btn->setFixedSize(400, 40);
                btn->move(50, 0);
                btn->setFont(font);
                boxLayout->addWidget(btn);
            }
        }
    }

    if (generic or favorites) {
        delete favoriteNotesMemory;
        favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
        if (favoriteNotesMemory->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < favoriteNotesMemory->size(); i++) { // for each note in the database creates a idButton

                auto note = (*favoriteNotesMemory)[i];
                string title = note.getTitle();

                if (generic)
                    title += " [★]";

                QPushButton *btn = new QPushButton((title.c_str()));
                int index = i;

                connect(btn, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
                    tryDestroyHome(generic, locked, favorites);
                    tryEditFavoriteNote(index, generic, locked, favorites);
                });

                btn->setStyleSheet("background-color: #2CB67D; color: black;");
                btn->setFixedSize(400, 40);
                btn->move(50, 0);
                btn->setFont(font);
                boxLayout->addWidget(btn);
            }
        }
    }
}

void GUI::tryHomeWindow(bool generic, bool locked, bool favorites) {
    QFont font;
    font.setPointSize(25);

    addNewNoteBtn = new QPushButton("+", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        tryDestroyHome(generic, locked, favorites);
        tryAddNewNote(generic, locked, favorites);
    });
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(70, 70);
    addNewNoteBtn->move(680, 680);
    addNewNoteBtn->setFont(font);
    addNewNoteBtn->show();

    if (generic) {
        collections = new QPushButton("Collections", this);
        connect(collections, &QPushButton::clicked, this, &GUI::openCollections);
        collections->setStyleSheet("background-color: #7F5AF0");
        collections->setFixedSize(200, 50);
        collections->move(50, 30);
        collections->setFont(font);
        collections->show();

        favoriteNotes = new QPushButton("Favorite Notes", this);
        connect(favoriteNotes, &QPushButton::clicked, this, [this] {
            this->tryDestroyHome(true, false, false);
            this->tryHomeWindow(false, false, true);
        });
        favoriteNotes->setStyleSheet("background-color: #7F5AF0");
        favoriteNotes->setFixedSize(200, 50);
        favoriteNotes->move(300, 30);
        favoriteNotes->setFont(font);
        favoriteNotes->show();

        lockedNotes = new QPushButton("Locked Notes", this);
        connect(lockedNotes, &QPushButton::clicked, this, [this] {
            this->tryDestroyHome(true, false, false);
            this->tryHomeWindow(false, true, false);
        });
        lockedNotes->setStyleSheet("background-color: #7F5AF0");
        lockedNotes->setFixedSize(200, 50);
        lockedNotes->move(550, 30);
        lockedNotes->setFont(font);
        lockedNotes->show();
    }

    if (locked or favorites) {
        backToHome = new QPushButton("Back To Home", this);
        connect(backToHome, &QPushButton::clicked, this, [this, locked, favorites] {
            if (locked) {
                tryDestroyHome(false, true, false);
            }
            if (favorites)
                tryDestroyHome(false, false, true);
            tryHomeWindow(true, false, false);
        });
        backToHome->setStyleSheet("background-color: #7F5AF0");
        backToHome->setFixedSize(200, 50);
        backToHome->move(300, 30);
        backToHome->setFont(font);
        backToHome->show();
    }

    scrollArea = new QScrollArea(this);
    scrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setGeometry(175, 110, 450, 690);

    widget = new QWidget();
    scrollArea->setWidget(widget);

    boxLayout = new QVBoxLayout();
    widget->setLayout(boxLayout);

    this->tryCompileScrollArea(generic, locked, favorites);
    scrollArea->show();
}

void GUI::tryAddNewNote(bool generic, bool locked, bool favorites) {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        if (generic)
            genericNotesMemory->newNote((noteTitle->toPlainText()).toStdString(),
                                        (noteContent->toPlainText()).toStdString());
        else if (locked)
            lockedNotesMemory->newNote((noteTitle->toPlainText()).toStdString(),
                                       (noteContent->toPlainText()).toStdString());
        else if (favorites)
            favoriteNotesMemory->newNote((noteTitle->toPlainText()).toStdString(),
                                         (noteContent->toPlainText()).toStdString());
        tryDestroyAddNewNote();
        tryHomeWindow(generic, locked, favorites);
    });
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->setFixedSize(200, 50);
    saveNote->move(125, 30);
    saveNote->setFont(font2);
    saveNote->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        tryDestroyAddNewNote();
        tryHomeWindow(generic, locked, favorites);
    });
    cancel->setStyleSheet("background-color: #7F5AF0;");
    cancel->move(500, 30);
    cancel->setFixedSize(200, 50);
    cancel->setFont(font2);
    cancel->show();

    noteTitle = new QTextEdit(this);
    noteTitle->setPlaceholderText("Note Title");
    noteTitle->move(50, 120);
    noteTitle->setStyleSheet("background-color: #004643");
    noteTitle->setFixedSize(700, 50);
    noteTitle->setFont(font);
    noteTitle->show();

    noteContent = new QTextEdit(this);
    noteContent->setPlaceholderText("Note Content");
    noteContent->move(50, 200);
    noteContent->setFixedSize(700, 570);
    noteContent->setFont(font);
    noteContent->setStyleSheet("background-color: #004643");
    noteContent->show();
}

void GUI::tryEditGenericNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        tryRemoveNote(index, generic, favorites);
        tryDestroyEditNote(true, false, false);
        tryHomeWindow(generic, locked, favorites);
    });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        tryDestroyEditNote(true, false, false);
        tryHomeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        tryChangeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                      (editNoteContent->toPlainText()).toStdString(), true, false);
        tryDestroyEditNote(true, false, false);
        tryHomeWindow(generic, locked, favorites);
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    editNote->setStyleSheet("background-color: #7F5AF0");
    editNote->setFont(btnFont);
    editNote->show();

    editAddToFavorites = new QPushButton("Add To Favorites", this);
    connect(editAddToFavorites, &QPushButton::clicked, this, [this, index, generic, locked, favorites] { // FIXME
        genericNotesMemory->transferNote(index, favoriteNotesMemory);
        tryDestroyEditNote(true, false, false);
        tryHomeWindow(generic, locked, favorites);
    });
    editAddToFavorites->setStyleSheet("background-color: #7F5AF0");
    editAddToFavorites->move(50, 100);
    editAddToFavorites->setFixedSize(200, 50);
    editAddToFavorites->setFont(btnFont);
    editAddToFavorites->show();

    editAddToLocked = new QPushButton("Add To Locked", this);
    connect(editAddToLocked, &QPushButton::clicked, this, [this, index, generic, locked, favorites] { // FIXME
        (*genericNotesMemory)[index].lock();
        genericNotesMemory->transferNote(index, lockedNotesMemory);
        tryDestroyEditNote(true, false, false);
        tryHomeWindow(generic, locked, favorites);
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(300, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        //addToCollectionPopUp(index, genericNotesMemory);
    });
    addToCollection->move(550, 100);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*genericNotesMemory)[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*genericNotesMemory)[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

void GUI::tryEditLockedNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    showUnlockNote = new QPushButton("Unlock", this);
    connect(showUnlockNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] { // FIXME
        this->lockedNotesMemory->transferNote(index, genericNotesMemory);
        tryDestroyEditNote(false, true, false);
        tryHomeWindow(generic, locked, favorites);
    });
    showUnlockNote->setStyleSheet("background-color: #7F5AF0");
    showUnlockNote->move(50, 30);
    showUnlockNote->setFixedSize(200, 50);
    showUnlockNote->setFont(btnFont);
    showUnlockNote->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        //addToCollectionPopUp(index, genericNotesMemory);
    });
    addToCollection->move(300, 30);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        tryDestroyEditNote(false, true, false);
        tryHomeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*lockedNotesMemory)[index].getTitle()).c_str());
    editNoteTitle->move(50, 120);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*lockedNotesMemory)[index].getContent()).c_str());
    editNoteContent->move(50, 200);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 570);
    editNoteContent->show();
}

void GUI::tryEditFavoriteNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        tryRemoveNote(index, generic, favorites);
        tryDestroyEditNote(false, false, true);
        tryHomeWindow(generic, locked, favorites);
    });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        tryDestroyEditNote(false, false, true);
        tryHomeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        tryChangeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                      (editNoteContent->toPlainText()).toStdString(), false, true);
        tryDestroyEditNote(false, false, true);
        tryHomeWindow(generic, locked, favorites);
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    editNote->setStyleSheet("background-color: #7F5AF0");
    editNote->setFont(btnFont);
    editNote->show();

    removeFromFavorites = new QPushButton("Remove From Favorites", this);
    connect(removeFromFavorites, &QPushButton::clicked, this, [this, index, generic, locked, favorites] { // FIXME
        favoriteNotesMemory->transferNote(index, genericNotesMemory);
        tryDestroyEditNote(false, false, true);
        tryHomeWindow(generic, locked, favorites);
    });
    removeFromFavorites->setFixedSize(200, 50);
    removeFromFavorites->move(175, 100);
    removeFromFavorites->setFont(btnFont);
    removeFromFavorites->setStyleSheet("background-color: #7F5AF0");
    removeFromFavorites->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        //addToCollectionPopUp(index, genericNotesMemory);
    });
    addToCollection->move(425, 100);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*favoriteNotesMemory)[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*favoriteNotesMemory)[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

void GUI::compileCollectionScrollBar() {
    QFont font; // font definition
    font.setPointSize(20);

    delete folderManager;
    folderManager = new FolderManager("foldersDb.lsml");

    if (folderManager->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folderManager->size(); i++) { // for each note in the database creates a idButton
            auto folder = (*folderManager)[i];
            QPushButton *btn = new QPushButton((folder.getFolderName()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                folderHomeWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            collectionBoxLayout->addWidget(btn);
        }
    }
}

void GUI::collectionHomeWindow() {
    QFont btnFont;
    btnFont.setPointSize(25);

    collectionToHome = new QPushButton("Back To Home", this);
    connect(collectionToHome, &QPushButton::clicked, this, &GUI::collectionToHomeWindow);
    collectionToHome->setFixedSize(200, 50);
    collectionToHome->setStyleSheet("background-color: #7F5AF0");
    collectionToHome->move(300, 30);
    collectionToHome->setFont(btnFont);
    collectionToHome->show();

    newCollection = new QPushButton("+", this);
    connect(newCollection, &QPushButton::clicked, this, &GUI::newCollectionPopUp);
    newCollection->setStyleSheet("background-color: #7F5AF0");
    newCollection->setFixedSize(70, 70);
    newCollection->move(680, 680);
    newCollection->setFont(btnFont);
    newCollection->show();

    collectionScrollArea = new QScrollArea(this);
    collectionScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    collectionScrollArea->setWidgetResizable(true);
    collectionScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    collectionScrollArea->setGeometry(175, 110, 450, 690);

    collectionWidget = new QWidget();
    collectionScrollArea->setWidget(collectionWidget);

    collectionBoxLayout = new QVBoxLayout();
    collectionWidget->setLayout(collectionBoxLayout);

    this->compileCollectionScrollBar();
    collectionScrollArea->show();
}

void GUI::newCollectionPopUp() {
    QFont font;
    font.setPointSize(18);
    popUpBaseLabel = new QLabel();
    popUpBaseLabel->setFixedSize(400, 200);
    popUpBaseLabel->setStyleSheet("background-color: #ABD1C6");
    popUpBaseLabel->setWindowTitle("Create New Collection");
    popUpBaseLabel->show();

    titleLabel = new QLabel("New Collection", popUpBaseLabel);
    titleLabel->setStyleSheet("color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->move(150, 10);
    titleLabel->setFont(font);
    titleLabel->show();

    newCollectionName = new QTextEdit(popUpBaseLabel);
    newCollectionName->setPlaceholderText("New Collection Name");
    newCollectionName->setStyleSheet("background-color: #004643");
    newCollectionName->setFixedSize(350, 50);
    newCollectionName->setFont(font);
    newCollectionName->move(25, 50);
    newCollectionName->show();

    saveNewCollection = new QPushButton("Save", popUpBaseLabel);
    connect(saveNewCollection, &QPushButton::clicked, this, [this] {
        saveCollection((newCollectionName->toPlainText()).toStdString());
        popUpBaseLabel->hide();
        destroyCollectionHomeWindow();
        collectionHomeWindow();
    });
    saveNewCollection->setStyleSheet("background-color: #7F5AF0");
    saveNewCollection->setFixedSize(125, 50);
    saveNewCollection->move(50, 120);
    saveNewCollection->setFont(font);
    saveNewCollection->show();

    exitNewCollectionPopUp = new QPushButton("Cancel", popUpBaseLabel);
    connect(exitNewCollectionPopUp, &QPushButton::clicked, this, [this] {
        popUpBaseLabel->hide();
    });
    exitNewCollectionPopUp->setStyleSheet("background-color: #7F5AF0");
    exitNewCollectionPopUp->setFixedSize(125, 50);
    exitNewCollectionPopUp->setFont(font);
    exitNewCollectionPopUp->move(225, 120);
    exitNewCollectionPopUp->show();
}

/*
 *
 *              FOLDERS SECTION
 *
 */

void GUI::compileFolderScrollArea(int index) {
    QFont font; // font definition
    font.setPointSize(20);
    delete folderManager;
    folderManager = new FolderManager("foldersDb.lsml");
    NoteFolder folder = (*folderManager)[index];
    if (folder.size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folder.size(); i++) { // for each note in the database creates a idButton
            auto note = folder[i];
            string title;
            if (note.isLocked())
                title = note.getTitle() + "[✖]";
            else if (note.isFavorite())
                title = note.getTitle() + "[★]";
            else
                title = note.getTitle();
            QPushButton *btn = new QPushButton((title).c_str());
            connect(btn, &QPushButton::clicked, this, [this, note] {
                destroyFolderHomeWindow();
                //if (note.isLocked())
                //showLockedNoteWindow(note.getTitle());
                //else if (note.isFavorite())
                //editFavoriteNoteWindow(note.getTitle());
                //else
                //editNoteWindow(note.getTitle());
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            folderBoxLayout->addWidget(btn);
        }
    }
}

void GUI::folderHomeWindow(int index) {
    QFont font; // font definition
    font.setPointSize(20);

    backToCollections = new QPushButton("Back To Collections", this);
    connect(backToCollections, &QPushButton::clicked, this, &GUI::folderToCollection);
    backToCollections->setStyleSheet("background-color: #7F5AF0");
    backToCollections->setFixedSize(200, 50);
    backToCollections->setFont(font);
    backToCollections->move(300, 30);
    backToCollections->show();

    folderScrollArea = new QScrollArea(this);
    folderScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    folderScrollArea->setWidgetResizable(true);
    folderScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    folderScrollArea->setGeometry(175, 110, 450, 690);
    folderScrollArea->show();

    folderWidget = new QWidget();
    folderScrollArea->setWidget(folderWidget);

    folderBoxLayout = new QVBoxLayout();
    folderWidget->setLayout(folderBoxLayout);

    this->compileFolderScrollArea(index);
    folderScrollArea->show();
}

/*
 *
 *              POPUP SECTION
 *
 */

void GUI::compileAddToCollectionPopUp(int noteIndex, NotesMemory *dataBase) {
    QFont font; // font definition
    font.setPointSize(20);

    delete folderManager;
    folderManager = new FolderManager("foldersDb.lsml");

    if (folderManager->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folderManager->size(); i++) { // for each note in the database creates a idButton
            auto folder = (*folderManager)[i];
            QPushButton *btn = new QPushButton((folder.getFolderName()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index, noteIndex, dataBase] {
                addNoteToCollection(index, noteIndex, dataBase);
                destroyAddtoCollectionPopUp();
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            addToCollectionBoxLayout->addWidget(btn);
        }
    }
}

void GUI::compileAddToCollectionPopUp(string title, NotesMemory *dataBase) {
    QFont font; // font definition
    font.setPointSize(20);

    delete folderManager;
    folderManager = new FolderManager("foldersDb.lsml");

    if (folderManager->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folderManager->size(); i++) { // for each note in the database creates a idButton
            auto folder = (*folderManager)[i];
            QPushButton *btn = new QPushButton((folder.getFolderName()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index, title, dataBase] {
                addNoteToCollection(index, title, dataBase);
                destroyAddtoCollectionPopUp();
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            addToCollectionBoxLayout->addWidget(btn);
        }
    }
}

void GUI::addToCollectionPopUp(int noteIndex, NotesMemory *dataBase) {
    addToCollectionBasePopUp = new QWidget();
    addToCollectionBasePopUp->setFixedSize(500, 250);
    addToCollectionBasePopUp->setStyleSheet("background-color: #ABD1C6");
    addToCollectionBasePopUp->show();

    addToCollectionScrollArea = new QScrollArea(addToCollectionBasePopUp);
    addToCollectionScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    addToCollectionScrollArea->setWidgetResizable(true);
    addToCollectionScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    addToCollectionScrollArea->setGeometry(25, 25, 450, 200);
    addToCollectionScrollArea->show();

    addToCollectionWidget = new QWidget();
    addToCollectionScrollArea->setWidget(addToCollectionWidget);

    addToCollectionBoxLayout = new QVBoxLayout();
    addToCollectionWidget->setLayout(addToCollectionBoxLayout);

    this->compileAddToCollectionPopUp(noteIndex, dataBase);
    addToCollectionScrollArea->show();
}

void GUI::addToCollectionPopUp(std::string title, NotesMemory *dataBase) {
    addToCollectionBasePopUp = new QWidget();
    addToCollectionBasePopUp->setFixedSize(500, 250);
    addToCollectionBasePopUp->setStyleSheet("background-color: #ABD1C6");
    addToCollectionBasePopUp->show();

    addToCollectionScrollArea = new QScrollArea(addToCollectionBasePopUp);
    addToCollectionScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    addToCollectionScrollArea->setWidgetResizable(true);
    addToCollectionScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    addToCollectionScrollArea->setGeometry(25, 25, 450, 200);
    addToCollectionScrollArea->show();

    addToCollectionWidget = new QWidget();
    addToCollectionScrollArea->setWidget(addToCollectionWidget);

    addToCollectionBoxLayout = new QVBoxLayout();
    addToCollectionWidget->setLayout(addToCollectionBoxLayout);

    this->compileAddToCollectionPopUp(title, dataBase);
    addToCollectionScrollArea->show();
}