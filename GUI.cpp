#include "GUI.h"

void GUI::compileScrollArea(bool generic, bool locked, bool favorites) {
    QFont font; // font definition
    font.setPointSize(20);

    if (generic) {
        if (notesManager->isUpdated()) {
            delete notesManager;
            notesManager = new NotesManager();
        }
        if (notesManager->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < notesManager->size(); i++) { // for each note in the database creates a idButton
                auto note = (*notesManager)[i];

                // adds a character to the displayed title if note is locked or favorite
                string title = note.getTitle();

                if (note.isFavorite())
                    title += " [★]";
                else if (note.isLocked())
                    title += " [✖]";

                QPushButton *btn = new QPushButton(title.c_str());
                int index = i;

                connect(btn, &QPushButton::clicked, this, [this, index, note, generic, locked, favorites] {
                    destroyHome(generic, locked, favorites);
                    if (note.isLocked())
                        editLockedNote(index, generic, locked, favorites);
                    else if (note.isFavorite())
                        editFavoriteNote(index, generic, locked, favorites);
                    else
                        editGenericNote(index, generic, locked, favorites);
                });

                btn->setStyleSheet("background-color: #2CB67D; color: black;");
                btn->setFixedSize(400, 40);
                btn->move(50, 0);
                btn->setFont(font);
                boxLayout->addWidget(btn);
            }
        }
    }

    if (locked) {
        if (notesManager->isUpdated()) {
            delete notesManager;
            notesManager = new NotesManager();
        }
        if (notesManager->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < notesManager->size(); i++) { // for each note in the database creates a idButton

                auto note = (*notesManager)[i];
                if (note.isLocked()) {
                    QPushButton *btn = new QPushButton((note.getTitle()).c_str());
                    int index = i;

                    connect(btn, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
                        destroyHome(generic, locked, favorites);
                        editLockedNote(index, generic, locked, favorites);
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

    if (favorites) {
        if (notesManager->isUpdated()) {
            delete notesManager;
            notesManager = new NotesManager();
        }
        if (notesManager->size() > 0) { // verifies if the memory is not empty
            for (int i = 0; i < notesManager->size(); i++) { // for each note in the database creates a idButton

                auto note = (*notesManager)[i];
                if (note.isFavorite()) {
                    QPushButton *btn = new QPushButton((note.getTitle()).c_str());
                    int index = i;

                    connect(btn, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
                        destroyHome(generic, locked, favorites);
                        editFavoriteNote(index, generic, locked, favorites);
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
}

void GUI::homeWindow(bool generic, bool locked, bool favorites) {
    QFont font;
    font.setPointSize(25);

    addNewNoteBtn = new QPushButton("+", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        destroyHome(generic, locked, favorites);
        addNewNote(generic, locked, favorites);
    });
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(70, 70);
    addNewNoteBtn->move(680, 680);
    addNewNoteBtn->setFont(font);
    addNewNoteBtn->show();

    if (generic) {
        collections = new QPushButton("Collections", this);
        connect(collections, &QPushButton::clicked, this, [this] {
            destroyHome(true, false, false);
            collectionHomeWindow();
        });
        collections->setStyleSheet("background-color: #7F5AF0");
        collections->setFixedSize(200, 50);
        collections->move(50, 30);
        collections->setFont(font);
        collections->show();

        favoriteNotes = new QPushButton("Favorite Notes", this);
        connect(favoriteNotes, &QPushButton::clicked, this, [this] {
            destroyHome(true, false, false);
            homeWindow(false, false, true);
        });
        favoriteNotes->setStyleSheet("background-color: #7F5AF0");
        favoriteNotes->setFixedSize(200, 50);
        favoriteNotes->move(300, 30);
        favoriteNotes->setFont(font);
        favoriteNotes->show();

        lockedNotes = new QPushButton("Locked Notes", this);
        connect(lockedNotes, &QPushButton::clicked, this, [this] {
            destroyHome(true, false, false);
            homeWindow(false, true, false);
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
                destroyHome(false, true, false);
            }
            if (favorites)
                destroyHome(false, false, true);
            homeWindow(true, false, false);
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

    compileScrollArea(generic, locked, favorites);
    scrollArea->show();
}

void GUI::addNewNote(bool generic, bool locked, bool favorites) {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        if ((notesManager->indexOf((noteTitle->toPlainText()).toStdString())) >= 0)
            errorPopUp("You can't add a note with \nthe same title as another one");
        else {
            if (((noteTitle->toPlainText()).toStdString()).empty())
                errorPopUp("Can't add a note without title");
            else {
                if (generic) {
                    notesManager->newNote((noteTitle->toPlainText()).toStdString(),
                                          (noteContent->toPlainText()).toStdString());
                } else if (locked)
                    notesManager->newNote((noteTitle->toPlainText()).toStdString(),
                                          (noteContent->toPlainText()).toStdString(), true);
                else if (favorites)
                    notesManager->newNote((noteTitle->toPlainText()).toStdString(),
                                          (noteContent->toPlainText()).toStdString(), false, true);
                destroyAddNewNote();
                homeWindow(generic, locked, favorites);
            }
        }
    });
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->setFixedSize(200, 50);
    saveNote->move(125, 30);
    saveNote->setFont(font2);
    saveNote->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        destroyAddNewNote();
        homeWindow(generic, locked, favorites);
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

void GUI::editGenericNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        removeNote(index);
        destroyEditNote(true, false, false);
        homeWindow(generic, locked, favorites);
    });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        destroyEditNote(true, false, false);
        homeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        if (((editNoteTitle->toPlainText()).toStdString()).empty())
            errorPopUp("Can't edit a note without title");
        else {
            changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                       (editNoteContent->toPlainText()).toStdString());
            destroyEditNote(true, false, false);
            homeWindow(generic, locked, favorites);
        }
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    editNote->setStyleSheet("background-color: #7F5AF0");
    editNote->setFont(btnFont);
    editNote->show();

    editAddToFavorites = new QPushButton("Add To Favorites", this);
    connect(editAddToFavorites, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        notesManager->favorite(index);
        destroyEditNote(true, false, false);
        homeWindow(generic, locked, favorites);
    });
    editAddToFavorites->setStyleSheet("background-color: #7F5AF0");
    editAddToFavorites->move(50, 100);
    editAddToFavorites->setFixedSize(200, 50);
    editAddToFavorites->setFont(btnFont);
    editAddToFavorites->show();

    editAddToLocked = new QPushButton("Add To Locked", this);
    connect(editAddToLocked, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        notesManager->lock(index);
        destroyEditNote(true, false, false);
        homeWindow(generic, locked, favorites);
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(300, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        addToCollectionPopUp(index);
    });
    addToCollection->move(550, 100);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*notesManager)[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*notesManager)[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

void GUI::editLockedNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    showUnlockNote = new QPushButton("Unlock", this);
    connect(showUnlockNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        notesManager->unlock(index);
        destroyEditNote(false, true, false);
        homeWindow(generic, locked, favorites);
    });
    showUnlockNote->setStyleSheet("background-color: #7F5AF0");
    showUnlockNote->move(50, 30);
    showUnlockNote->setFixedSize(200, 50);
    showUnlockNote->setFont(btnFont);
    showUnlockNote->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        addToCollectionPopUp(index);
    });
    addToCollection->move(300, 30);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        destroyEditNote(false, true, false);
        homeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*notesManager)[index].getTitle()).c_str());
    editNoteTitle->move(50, 120);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setReadOnly(true);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*notesManager)[index].getContent()).c_str());
    editNoteContent->move(50, 200);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setReadOnly(true);
    editNoteContent->setFixedSize(700, 570);
    editNoteContent->show();
}

void GUI::editFavoriteNote(int index, bool generic, bool locked, bool favorites) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        removeNote(index);
        destroyEditNote(false, false, true);
        homeWindow(generic, locked, favorites);
    });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, [this, generic, locked, favorites] {
        destroyEditNote(false, false, true);
        homeWindow(generic, locked, favorites);
    });
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        if (((editNoteTitle->toPlainText()).toStdString()).empty())
            errorPopUp("Can't add a note without title");
        else {
            changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                       (editNoteContent->toPlainText()).toStdString());
            destroyEditNote(false, false, true);
            homeWindow(generic, locked, favorites);
        }
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    editNote->setStyleSheet("background-color: #7F5AF0");
    editNote->setFont(btnFont);
    editNote->show();

    removeFromFavorites = new QPushButton("Remove From Favorites", this);
    connect(removeFromFavorites, &QPushButton::clicked, this, [this, index, generic, locked, favorites] {
        notesManager->removeFromFavorites(index);
        destroyEditNote(false, false, true);
        homeWindow(generic, locked, favorites);
    });
    removeFromFavorites->setFixedSize(200, 50);
    removeFromFavorites->move(175, 100);
    removeFromFavorites->setFont(btnFont);
    removeFromFavorites->setStyleSheet("background-color: #7F5AF0");
    removeFromFavorites->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] { // FIXME
        addToCollectionPopUp(index);
    });
    addToCollection->move(425, 100);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*notesManager)[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*notesManager)[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

/*
 *
 *              COLLECTIONS SECTION
 *
 */

void GUI::compileCollectionScrollBar() {
    QFont font; // font definition
    font.setPointSize(20);

    if (folderManager->isUpdated()) {
        delete folderManager;
        folderManager = new FolderManager();
    }

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
    connect(collectionToHome, &QPushButton::clicked, this, [this] {
        destroyCollectionHomeWindow();
        homeWindow(true, false, false);
    });
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

    compileCollectionScrollBar();
    collectionScrollArea->show();
}

void GUI::newCollectionPopUp() {
    QFont font;
    font.setPointSize(18);
    popUpBaseWidget = new QWidget();
    popUpBaseWidget->setFixedSize(400, 200);
    popUpBaseWidget->setStyleSheet("background-color: #ABD1C6");
    popUpBaseWidget->setWindowTitle("Create New Collection");
    popUpBaseWidget->show();

    titleLabel = new QLabel("New Collection", popUpBaseWidget);
    titleLabel->setStyleSheet("color: black;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->move(150, 10);
    titleLabel->setFont(font);
    titleLabel->show();

    newCollectionName = new QTextEdit(popUpBaseWidget);
    newCollectionName->setPlaceholderText("New Collection Name");
    newCollectionName->setStyleSheet("background-color: #004643");
    newCollectionName->setFixedSize(350, 50);
    newCollectionName->setFont(font);
    newCollectionName->move(25, 50);
    newCollectionName->show();

    saveNewCollection = new QPushButton("Save", popUpBaseWidget);
    connect(saveNewCollection, &QPushButton::clicked, this, [this] {
        folderManager->addNewFolder((newCollectionName->toPlainText()).toStdString());
        popUpBaseWidget->hide();
        destroyCollectionHomeWindow();
        collectionHomeWindow();
    });
    saveNewCollection->setStyleSheet("background-color: #7F5AF0");
    saveNewCollection->setFixedSize(125, 50);
    saveNewCollection->move(50, 120);
    saveNewCollection->setFont(font);
    saveNewCollection->show();

    exitNewCollectionPopUp = new QPushButton("Cancel", popUpBaseWidget);
    connect(exitNewCollectionPopUp, &QPushButton::clicked, this, [this] {
        popUpBaseWidget->hide();
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
    folderManager = new FolderManager();
    NoteFolder folder = (*folderManager)[index];
    if (folder.size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folder.size(); i++) { // for each note in the database creates a idButton
            auto noteName = folder[i];

            int noteIndex = notesManager->indexOf(noteName);

            auto note = (*notesManager)[noteIndex];

            string title;
            if (note.isLocked())
                title = note.getTitle() + "[✖]";
            else if (note.isFavorite())
                title = note.getTitle() + "[★]";
            else
                title = note.getTitle();
            QPushButton *btn = new QPushButton((title).c_str());
            connect(btn, &QPushButton::clicked, this, [this, note, noteIndex] {
                destroyFolderHomeWindow();
                if (note.isLocked()) {
                    editLockedNote(noteIndex, false, true, false);
                } else if (note.isFavorite()) {
                    editFavoriteNote(noteIndex, false, false, true);
                } else {
                    editGenericNote(noteIndex, true, false, false);
                }
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

    QWidget *topCover = new QWidget(this);
    topCover->setStyleSheet("background-color: #ABD1C6");
    topCover->move(300, 30);
    topCover->setFixedSize(200, 50);
    topCover->show();

    backToCollections = new QPushButton("Back To Collections", this);
    connect(backToCollections, &QPushButton::clicked, this, [this] {
        destroyFolderHomeWindow();
        collectionHomeWindow();
    });
    backToCollections->setStyleSheet("background-color: #7F5AF0");
    backToCollections->setFixedSize(200, 50);
    backToCollections->setFont(font);
    backToCollections->move(125, 30);
    backToCollections->show();

    removeFolder = new QPushButton("Remove Collection", this);
    connect(removeFolder, &QPushButton::clicked, this, [this, index] {
        folderManager->removeFolder(index);
        destroyFolderHomeWindow();
        collectionHomeWindow();
    });
    removeFolder->setStyleSheet("background-color: #7F5AF0");
    removeFolder->setFixedSize(200, 50);
    removeFolder->setFont(font);
    removeFolder->move(500, 30);
    removeFolder->show();

    cover = new QLabel(this);
    cover->setFixedSize(80, 80);
    cover->move(670, 670);
    cover->setStyleSheet("background-color: #ABD1C6");
    cover->show();

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

    compileFolderScrollArea(index);
    folderScrollArea->show();
}

/*
 *
 *               ADD TO COLLECTION POPUP SECTION
 *
 */

void GUI::compileAddToCollectionPopUp(int noteIndex) {
    QFont font; // font definition
    font.setPointSize(20);

    delete folderManager;
    folderManager = new FolderManager();

    if (folderManager->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < folderManager->size(); i++) { // for each note in the database creates a idButton
            auto folder = (*folderManager)[i];
            QPushButton *btn = new QPushButton((folder.getFolderName()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index, noteIndex] {
                addNoteToCollection(index, noteIndex);
                folderManager->addNote(index, (*notesManager)[noteIndex].getTitle());
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

void GUI::addToCollectionPopUp(int noteIndex) {
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

    compileAddToCollectionPopUp(noteIndex);
    addToCollectionScrollArea->show();
}

/*
 *
 *              ERROR POPUP
 *
 */

void GUI::errorPopUp(const string &errorMessage) {
    QFont font;
    font.setPointSize(20);

    popUpBase = new QWidget();
    popUpBase->setFixedSize(400, 200);
    popUpBase->setStyleSheet("background-color: #ABD1C6");
    popUpBase->show();

    message = new QLabel(errorMessage.c_str(), popUpBase);
    message->setStyleSheet("color: black");
    message->move(0, 0);
    message->setAlignment(Qt::AlignCenter);
    message->setFont(font);
    message->setFixedSize(400, 100);
    message->show();

    okBtn = new QPushButton("OK", popUpBase);
    connect(okBtn, &QPushButton::clicked, popUpBase, [this] {
        popUpBase->hide();
    });
    okBtn->setStyleSheet("background-color: #7F5AF0");
    okBtn->move(100, 125);
    okBtn->setFont(font);
    okBtn->setFixedSize(200, 50);
    okBtn->show();
}

/*\..{[|<->_<'>]|}../*/