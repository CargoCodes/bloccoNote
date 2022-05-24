#include "GUI.h"

/*
 *
 *              GENERIC SECTION
 *
 */

void GUI::compileScrollBar() {
    QFont font; // font definition
    font.setPointSize(20);

    delete genericNotesMemory;
    genericNotesMemory = new NotesMemory("genericNotes.lsml");

    if (genericNotesMemory->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < genericNotesMemory->size(); i++) { // for each note in the database creates a idButton
            auto note = (*genericNotesMemory)[i];
            QPushButton *btn = new QPushButton((note.getTitle()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->destroyHomeWindow();
                this->editNoteWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            boxLayout->addWidget(btn);
        }
    }

    delete lockedNotesMemory;
    lockedNotesMemory = new NotesMemory("lockedNotes.lsml", false, true);
    if(lockedNotesMemory->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < lockedNotesMemory->size(); i++) { // for each note in the database creates a idButton
            auto note = (*lockedNotesMemory)[i];
            QPushButton *btn = new QPushButton((note.getTitle() + " [✖]").c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->destroyHomeWindow();
                this->showLockedNoteWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            boxLayout->addWidget(btn);
        }
    }

    delete favoriteNotesMemory;
    favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    if(favoriteNotesMemory->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < favoriteNotesMemory->size(); i++) { // for each note in the database creates a idButton
            auto note = (*favoriteNotesMemory)[i];
            QPushButton *btn = new QPushButton(((note.getTitle() + " [★]").c_str()));
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->destroyHomeWindow();
                this->editFavoriteNoteWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            boxLayout->addWidget(btn);
        }
    }
}

void GUI::homeWindow() {
    QFont font;
    font.setPointSize(25);
    addNewNoteBtn = new QPushButton("+", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, &GUI::newNoteWindow);
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(70, 70);
    addNewNoteBtn->move(680, 680);
    addNewNoteBtn->setFont(font);
    addNewNoteBtn->show();

    collections = new QPushButton("Collections", this);
    connect(collections, &QPushButton::clicked, this, &GUI::openCollections);
    collections->setStyleSheet("background-color: #7F5AF0");
    collections->setFixedSize(200, 50);
    collections->move(50, 30);
    collections->setFont(font);
    collections->show();

    favoriteNotes = new QPushButton("Favorite Notes", this);
    connect(favoriteNotes, &QPushButton::clicked, this, &GUI::openFavorites);
    favoriteNotes->setStyleSheet("background-color: #7F5AF0");
    favoriteNotes->setFixedSize(200, 50);
    favoriteNotes->move(300, 30);
    favoriteNotes->setFont(font);
    favoriteNotes->show();

    lockedNotes = new QPushButton("Locked Notes", this);
    connect(lockedNotes, &QPushButton::clicked, this, &GUI::openLocked);
    lockedNotes->setStyleSheet("background-color: #7F5AF0");
    lockedNotes->setFixedSize(200, 50);
    lockedNotes->move(550, 30);
    lockedNotes->setFont(font);
    lockedNotes->show();

    scrollArea = new QScrollArea(this);
    QPalette scrollAreaBg = QPalette();
    scrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    scrollArea->setPalette(scrollAreaBg);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setGeometry(175, 110, 450, 690);

    widget = new QWidget();
    scrollArea->setWidget(widget);

    boxLayout = new QVBoxLayout();
    widget->setLayout(boxLayout);

    this->compileScrollBar();
    scrollArea->show();
}

void GUI::newNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    this->destroyHomeWindow();
    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, &GUI::saveNewNote);
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->setFixedSize(200, 50);
    saveNote->move(125, 30);
    saveNote->setFont(font2);
    saveNote->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &GUI::destroyNewNoteWIndow);
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

void GUI::editNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, index] {
        changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                   (editNoteContent->toPlainText()).toStdString());
        destroyEditNoteWindow();
        homeWindow();
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    if(not (*genericNotesMemory)[index].isLocked())
        editNote->setStyleSheet("background-color: #7F5AF0");
    else
        editNote->setStyleSheet("background-color: #2B2B2B");
    editNote->setFont(btnFont);
    editNote->show();

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index] { removeNote(index); });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, &GUI::destroyEditNoteWindow);
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editAddToFavorites = new QPushButton("Add To Favorites", this);
    connect(editAddToFavorites, &QPushButton::clicked, this, [this, index] {
        genericNotesMemory->transferNote(index, favoriteNotesMemory);
        this->destroyEditNoteWindow();
    });
    editAddToFavorites->setStyleSheet("background-color: #7F5AF0");
    editAddToFavorites->move(50, 100);
    editAddToFavorites->setFixedSize(200, 50);
    editAddToFavorites->setFont(btnFont);
    editAddToFavorites->show();

    editAddToLocked = new QPushButton("Add To Locked", this);
    connect(editAddToLocked, &QPushButton::clicked, this, [this, index] {
        (*genericNotesMemory)[index].lock();
        genericNotesMemory->transferNote(index, lockedNotesMemory);
        this->destroyEditNoteWindow();
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(300, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, index] {
        addToCollectionPopUp(index, genericNotesMemory);
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

void GUI::editNoteWindow(std::string title) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editNote = new QPushButton("Edit", this);
    connect(editNote, &QPushButton::clicked, this, [this, title] {
        changeNote(title, (editNoteTitle->toPlainText()).toStdString(),
                   (editNoteContent->toPlainText()).toStdString());
        destroyEditNoteWindow();
        homeWindow();
    });
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    if (not(*genericNotesMemory)[title].isLocked())
        editNote->setStyleSheet("background-color: #7F5AF0");
    else
        editNote->setStyleSheet("background-color: #2B2B2B");
    editNote->setFont(btnFont);
    editNote->show();

    deleteNote = new QPushButton("Delete", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, title] { removeNote(title); });
    deleteNote->move(300, 30);
    deleteNote->setFixedSize(200, 50);
    deleteNote->setFont(btnFont);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, &GUI::destroyEditNoteWindow);
    exitEdit->setFixedSize(200, 50);
    exitEdit->move(550, 30);
    exitEdit->setFont(btnFont);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editAddToFavorites = new QPushButton("Add To Favorites", this);
    connect(editAddToFavorites, &QPushButton::clicked, this, [this, title] {
        genericNotesMemory->transferNote(title, favoriteNotesMemory);
        this->destroyEditNoteWindow();
    });
    editAddToFavorites->setStyleSheet("background-color: #7F5AF0");
    editAddToFavorites->move(50, 100);
    editAddToFavorites->setFixedSize(200, 50);
    editAddToFavorites->setFont(btnFont);
    editAddToFavorites->show();

    editAddToLocked = new QPushButton("Add To Locked", this);
    connect(editAddToLocked, &QPushButton::clicked, this, [this, title] {
        (*genericNotesMemory)[title].lock();
        genericNotesMemory->transferNote(title, lockedNotesMemory);
        this->destroyEditNoteWindow();
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(300, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    addToCollection = new QPushButton("Add To Collection", this);
    connect(addToCollection, &QPushButton::clicked, this, [this, title] {
        addToCollectionPopUp(title, genericNotesMemory);
    });
    addToCollection->move(550, 100);
    addToCollection->setFixedSize(200, 50);
    addToCollection->setFont(btnFont);
    addToCollection->setStyleSheet("background-color: #7F5AF0");
    addToCollection->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText(((*genericNotesMemory)[title].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText(((*genericNotesMemory)[title].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

/*
 *
 *              LOCKED SECTION
 *
 */


void GUI::compileLockedScrollArea() {
    QFont font;
    font.setPointSize(20);
    if(lockedNotesMemory->size() > 0) {
        delete lockedNotesMemory;
        lockedNotesMemory = new NotesMemory("lockedNotes.lsml");
        for (int i = 0; i < lockedNotesMemory->size(); i++) {
            QPushButton *btn = new QPushButton(((*lockedNotesMemory)[i].getTitle()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->destroyLockedHomeWindow();
                this->showLockedNoteWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            lockedBoxLayout->addWidget(btn);
        }
    }
}

void GUI::lockedHomeWindow() {
    QFont btnFont;
    btnFont.setPointSize(25);

    addNewLockedNoteBtn = new QPushButton("+", this);
    connect(addNewLockedNoteBtn, &QPushButton::clicked, this, &GUI::lockedNewNoteWindow);
    addNewLockedNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewLockedNoteBtn->setFixedSize(70, 70);
    addNewLockedNoteBtn->move(680, 680);
    addNewLockedNoteBtn->setFont(btnFont);
    addNewLockedNoteBtn->show();

    returnToMainHome = new QPushButton("Back To Home", this);
    connect(returnToMainHome, &QPushButton::clicked, this, &GUI::lockedToHome);
    returnToMainHome->setFixedSize(200, 50);
    returnToMainHome->setStyleSheet("background-color: #7F5AF0");
    returnToMainHome->move(300, 30);
    returnToMainHome->setFont(btnFont);
    returnToMainHome->show();

    lockedScrollArea = new QScrollArea(this);
    lockedScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    lockedScrollArea->setWidgetResizable(true);
    lockedScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    lockedScrollArea->setGeometry(175, 110, 450, 690);

    lockedWidget = new QWidget();
    lockedScrollArea->setWidget(lockedWidget);

    lockedBoxLayout = new QVBoxLayout();
    lockedWidget->setLayout(lockedBoxLayout);

    this->compileLockedScrollArea();
    lockedScrollArea->show();
}

void GUI::lockedNewNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    this->destroyLockedHomeWindow();

    saveLockedNote = new QPushButton("Save", this);
    connect(saveLockedNote, &QPushButton::clicked, this, &GUI::saveLockedWindow);
    saveLockedNote->setStyleSheet("background-color: #7F5AF0");
    saveLockedNote->setFixedSize(200, 50);
    saveLockedNote->move(125, 30);
    saveLockedNote->setFont(font2);
    saveLockedNote->show();

    lockCancel = new QPushButton("Cancel", this);
    connect(lockCancel, &QPushButton::clicked, this, &GUI::destroyNewLockedNoteWindow);
    lockCancel->setStyleSheet("background-color: #7F5AF0;");
    lockCancel->move(475, 30);
    lockCancel->setFixedSize(200, 50);
    lockCancel->setFont(font2);
    lockCancel->show();

    lockedNoteTitle = new QTextEdit(this);
    lockedNoteTitle->setPlaceholderText("Note Title");
    lockedNoteTitle->move(50, 120);
    lockedNoteTitle->setStyleSheet("background-color: #004643");
    lockedNoteTitle->setFixedSize(700, 50);
    lockedNoteTitle->setFont(font);
    lockedNoteTitle->show();

    lockedNoteContent = new QTextEdit(this);
    lockedNoteContent->setPlaceholderText("Note Content");
    lockedNoteContent->move(50, 200);
    lockedNoteContent->setFixedSize(700, 570);
    lockedNoteContent->setFont(font);
    lockedNoteContent->setStyleSheet("background-color: #004643");
    lockedNoteContent->show();
}

void GUI::showLockedNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    showUnlockNote = new QPushButton("Unlock", this);
    connect(showUnlockNote, &QPushButton::clicked, this, [this, index] {
        this->lockedNotesMemory->transferNote(index, genericNotesMemory);
        destroyLockedNoteShowWindow();
    });
    showUnlockNote->setStyleSheet("background-color: #7F5AF0");
    showUnlockNote->move(125, 30);
    showUnlockNote->setFixedSize(200, 50);
    showUnlockNote->setFont(btnFont);
    showUnlockNote->show();

    exitShow = new QPushButton("Exit", this);
    connect(exitShow, &QPushButton::clicked, this, &GUI::destroyLockedNoteShowWindow);
    exitShow->setFixedSize(200, 50);
    exitShow->move(500, 30);
    exitShow->setFont(btnFont);
    exitShow->setStyleSheet("background-color: #7F5AF0");
    exitShow->show();

    showNoteTitle = new QTextEdit(this);
    showNoteTitle->setPlaceholderText("Note Title");
    showNoteTitle->setText(((*lockedNotesMemory)[index].getTitle()).c_str());
    showNoteTitle->move(50, 140);
    showNoteTitle->setStyleSheet("background-color: #004643");
    showNoteTitle->setFont(textFont);
    showNoteTitle->setFixedSize(700, 50);
    showNoteTitle->show();

    showNoteContent = new QTextEdit(this);
    showNoteContent->setPlaceholderText("Note Content");
    showNoteContent->setText(((*lockedNotesMemory)[index].getContent()).c_str());
    showNoteContent->move(50, 220);
    showNoteContent->setStyleSheet("background-color: #004643");
    showNoteContent->setFont(textFont);
    showNoteContent->setFixedSize(700, 550);
    showNoteContent->show();
}

void GUI::showLockedNoteWindow(std::string title) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    showUnlockNote = new QPushButton("Unlock", this);
    connect(showUnlockNote, &QPushButton::clicked, this, [this, title] {
        this->lockedNotesMemory->transferNote(title, genericNotesMemory);
        destroyLockedNoteShowWindow();
    });
    showUnlockNote->setStyleSheet("background-color: #7F5AF0");
    showUnlockNote->move(125, 30);
    showUnlockNote->setFixedSize(200, 50);
    showUnlockNote->setFont(btnFont);
    showUnlockNote->show();

    exitShow = new QPushButton("Exit", this);
    connect(exitShow, &QPushButton::clicked, this, &GUI::destroyLockedNoteShowWindow);
    exitShow->setFixedSize(200, 50);
    exitShow->move(500, 30);
    exitShow->setFont(btnFont);
    exitShow->setStyleSheet("background-color: #7F5AF0");
    exitShow->show();

    showNoteTitle = new QTextEdit(this);
    showNoteTitle->setPlaceholderText("Note Title");
    showNoteTitle->setText(((*lockedNotesMemory)[title].getTitle()).c_str());
    showNoteTitle->move(50, 140);
    showNoteTitle->setStyleSheet("background-color: #004643");
    showNoteTitle->setFont(textFont);
    showNoteTitle->setFixedSize(700, 50);
    showNoteTitle->show();

    showNoteContent = new QTextEdit(this);
    showNoteContent->setPlaceholderText("Note Content");
    showNoteContent->setText(((*lockedNotesMemory)[title].getContent()).c_str());
    showNoteContent->move(50, 220);
    showNoteContent->setStyleSheet("background-color: #004643");
    showNoteContent->setFont(textFont);
    showNoteContent->setFixedSize(700, 550);
    showNoteContent->show();
}

/*
 *
 *              FAVORITE SECTION
 *
 */

void GUI::compileFavoriteScrollArea() {
    QFont font; // font definition
    font.setPointSize(20);
    delete favoriteNotesMemory;
    favoriteNotesMemory = new NotesMemory("favoriteNotes.lsml", true);
    if (favoriteNotesMemory->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < favoriteNotesMemory->size(); i++) { // for each note in the database creates a idButton
            auto note = (*favoriteNotesMemory)[i];
            QPushButton *btn = new QPushButton(((note.getTitle()).c_str()));
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->destroyFavoriteHomeWindow();
                this->editFavoriteNoteWindow(index);
            });
            btn->setStyleSheet("background-color: #2CB67D; color: black;");
            btn->setFixedSize(400, 40);
            btn->move(50, 0);
            btn->setFont(font);
            favoriteBoxLayout->addWidget(btn);
        }
    }
}

void GUI::favoriteHomeWindow() {
    QFont btnFont;
    btnFont.setPointSize(25);

    addNewFavoriteNoteBtn = new QPushButton("+", this);
    connect(addNewFavoriteNoteBtn, &QPushButton::clicked, this, [this] {
        destroyFavoriteHomeWindow();
        GUI::newFavoriteNoteWindow();
    });
    addNewFavoriteNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewFavoriteNoteBtn->setFixedSize(70, 70);
    addNewFavoriteNoteBtn->move(680, 680);
    addNewFavoriteNoteBtn->setFont(btnFont);
    addNewFavoriteNoteBtn->show();

    returnToHome = new QPushButton("Back To Home", this);
    connect(returnToHome, &QPushButton::clicked, this, &GUI::favoriteToHome);
    returnToHome->setFixedSize(200, 50);
    returnToHome->setStyleSheet("background-color: #7F5AF0");
    returnToHome->move(300, 30);
    returnToHome->setFont(btnFont);
    returnToHome->show();

    favoriteScrollArea = new QScrollArea(this);
    favoriteScrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    favoriteScrollArea->setWidgetResizable(true);
    favoriteScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    favoriteScrollArea->setGeometry(175, 110, 450, 690);

    favoriteWidget = new QWidget();
    favoriteScrollArea->setWidget(favoriteWidget);

    favoriteBoxLayout = new QVBoxLayout();
    favoriteWidget->setLayout(favoriteBoxLayout);

    this->compileFavoriteScrollArea();
    favoriteScrollArea->show();
}

void GUI::newFavoriteNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    this->destroyHomeWindow();
    saveFavoriteNote = new QPushButton("Save", this);
    connect(saveFavoriteNote, &QPushButton::clicked, this, &GUI::saveFavoriteNoteWindow);
    saveFavoriteNote->setStyleSheet("background-color: #7F5AF0");
    saveFavoriteNote->setFixedSize(200, 50);
    saveFavoriteNote->move(125, 30);
    saveFavoriteNote->setFont(font2);
    saveFavoriteNote->show();

    cancelFavoriteNote = new QPushButton("Cancel", this);
    connect(cancelFavoriteNote, &QPushButton::clicked, this, [this] {
        destroyNewFavoriteNoteWindow();
        favoriteHomeWindow();

    });
    cancelFavoriteNote->setStyleSheet("background-color: #7F5AF0;");
    cancelFavoriteNote->move(500, 30);
    cancelFavoriteNote->setFixedSize(200, 50);
    cancelFavoriteNote->setFont(font2);
    cancelFavoriteNote->show();

    favoriteNoteTitle = new QTextEdit(this);
    favoriteNoteTitle->setPlaceholderText("Note Title");
    favoriteNoteTitle->move(50, 120);
    favoriteNoteTitle->setStyleSheet("background-color: #004643");
    favoriteNoteTitle->setFixedSize(700, 50);
    favoriteNoteTitle->setFont(font);
    favoriteNoteTitle->show();

    favoriteNoteContent = new QTextEdit(this);
    favoriteNoteContent->setPlaceholderText("Note Content");
    favoriteNoteContent->move(50, 200);
    favoriteNoteContent->setFixedSize(700, 570);
    favoriteNoteContent->setFont(font);
    favoriteNoteContent->setStyleSheet("background-color: #004643");
    favoriteNoteContent->show();
}

void GUI::editFavoriteNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editFavoriteNote = new QPushButton("Edit", this);
    connect(editFavoriteNote, &QPushButton::clicked, this, [this, index] {
        changeFavoriteNote(index, (editFavoriteNoteTitle->toPlainText()).toStdString(),
                           (editFavoriteNoteContent->toPlainText()).toStdString());
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    editFavoriteNote->move(50, 30);
    editFavoriteNote->setFixedSize(200, 50);
    editFavoriteNote->setStyleSheet("background-color: #7F5AF0");
    editFavoriteNote->setFont(btnFont);
    editFavoriteNote->show();

    deleteFavoriteNote = new QPushButton("Delete", this);
    connect(deleteFavoriteNote, &QPushButton::clicked, this, [this, index] {
        removeFavoriteNote(index);
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    deleteFavoriteNote->move(300, 30);
    deleteFavoriteNote->setFixedSize(200, 50);
    deleteFavoriteNote->setFont(btnFont);
    deleteFavoriteNote->setStyleSheet("background-color: #7F5AF0");
    deleteFavoriteNote->show();

    exitFavoriteEdit = new QPushButton("Cancel", this);
    connect(exitFavoriteEdit, &QPushButton::clicked, this, [this] {
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    exitFavoriteEdit->setFixedSize(200, 50);
    exitFavoriteEdit->move(550, 30);
    exitFavoriteEdit->setFont(btnFont);
    exitFavoriteEdit->setStyleSheet("background-color: #7F5AF0");
    exitFavoriteEdit->show();

    removeFromFavorites = new QPushButton("Remove From Favorites", this);
    connect(removeFromFavorites, &QPushButton::clicked, this, [this, index] {
        favoriteNotesMemory->transferNote(index, genericNotesMemory);
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    removeFromFavorites->setFixedSize(200, 50);
    removeFromFavorites->move(300, 100);
    removeFromFavorites->setFont(btnFont);
    removeFromFavorites->setStyleSheet("background-color: #7F5AF0");
    removeFromFavorites->show();

    editFavoriteNoteTitle = new QTextEdit(this);
    editFavoriteNoteTitle->setPlaceholderText("Note Title");
    editFavoriteNoteTitle->setText(((*favoriteNotesMemory)[index].getTitle()).c_str());
    editFavoriteNoteTitle->move(50, 190);
    editFavoriteNoteTitle->setStyleSheet("background-color: #004643");
    editFavoriteNoteTitle->setFont(textFont);
    editFavoriteNoteTitle->setFixedSize(700, 50);
    editFavoriteNoteTitle->show();

    editFavoriteNoteContent = new QTextEdit(this);
    editFavoriteNoteContent->setPlaceholderText("Note Content");
    editFavoriteNoteContent->setText(((*favoriteNotesMemory)[index].getContent()).c_str());
    editFavoriteNoteContent->move(50, 270);
    editFavoriteNoteContent->setStyleSheet("background-color: #004643");
    editFavoriteNoteContent->setFont(textFont);
    editFavoriteNoteContent->setFixedSize(700, 500);
    editFavoriteNoteContent->show();
}

void GUI::editFavoriteNoteWindow(std::string title) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editFavoriteNote = new QPushButton("Edit", this);
    connect(editFavoriteNote, &QPushButton::clicked, this, [this, title] {
        changeFavoriteNote(title, (editFavoriteNoteTitle->toPlainText()).toStdString(),
                           (editFavoriteNoteContent->toPlainText()).toStdString());
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    editFavoriteNote->move(50, 30);
    editFavoriteNote->setFixedSize(200, 50);
    editFavoriteNote->setStyleSheet("background-color: #7F5AF0");
    editFavoriteNote->setFont(btnFont);
    editFavoriteNote->show();

    deleteFavoriteNote = new QPushButton("Delete", this);
    connect(deleteFavoriteNote, &QPushButton::clicked, this, [this, title] {
        removeFavoriteNote(title);
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    deleteFavoriteNote->move(300, 30);
    deleteFavoriteNote->setFixedSize(200, 50);
    deleteFavoriteNote->setFont(btnFont);
    deleteFavoriteNote->setStyleSheet("background-color: #7F5AF0");
    deleteFavoriteNote->show();

    exitFavoriteEdit = new QPushButton("Cancel", this);
    connect(exitFavoriteEdit, &QPushButton::clicked, this, [this] {
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    exitFavoriteEdit->setFixedSize(200, 50);
    exitFavoriteEdit->move(550, 30);
    exitFavoriteEdit->setFont(btnFont);
    exitFavoriteEdit->setStyleSheet("background-color: #7F5AF0");
    exitFavoriteEdit->show();

    removeFromFavorites = new QPushButton("Remove From Favorites", this);
    connect(removeFromFavorites, &QPushButton::clicked, this, [this, title] {
        favoriteNotesMemory->transferNote(title, genericNotesMemory);
        destroyEditFavoriteNoteWindow();
        favoriteHomeWindow();
    });
    removeFromFavorites->setFixedSize(200, 50);
    removeFromFavorites->move(300, 100);
    removeFromFavorites->setFont(btnFont);
    removeFromFavorites->setStyleSheet("background-color: #7F5AF0");
    removeFromFavorites->show();

    editFavoriteNoteTitle = new QTextEdit(this);
    editFavoriteNoteTitle->setPlaceholderText("Note Title");
    editFavoriteNoteTitle->setText(((*favoriteNotesMemory)[title].getTitle()).c_str());
    editFavoriteNoteTitle->move(50, 190);
    editFavoriteNoteTitle->setStyleSheet("background-color: #004643");
    editFavoriteNoteTitle->setFont(textFont);
    editFavoriteNoteTitle->setFixedSize(700, 50);
    editFavoriteNoteTitle->show();

    editFavoriteNoteContent = new QTextEdit(this);
    editFavoriteNoteContent->setPlaceholderText("Note Content");
    editFavoriteNoteContent->setText(((*favoriteNotesMemory)[title].getContent()).c_str());
    editFavoriteNoteContent->move(50, 270);
    editFavoriteNoteContent->setStyleSheet("background-color: #004643");
    editFavoriteNoteContent->setFont(textFont);
    editFavoriteNoteContent->setFixedSize(700, 500);
    editFavoriteNoteContent->show();
}

/*
 *
 *              COMPILATIONS SECTION
 *
 */

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
                if (note.isLocked())
                    showLockedNoteWindow(note.getTitle());
                else if (note.isFavorite())
                    editFavoriteNoteWindow(note.getTitle());
                else
                    editNoteWindow(note.getTitle());
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