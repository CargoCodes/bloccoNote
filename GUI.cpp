#include "GUI.h"

void GUI::compileScrollBar() {
    QFont font; // font definition
    font.setPointSize(20);

    delete genericNotesMemory;
    genericNotesMemory = new NotesMemory("genericNotes.lsml");

    if(genericNotesMemory->size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < genericNotesMemory->size(); i++) { // for each note in the database creates a idButton
            auto note = (*genericNotesMemory)[i];
            QPushButton *btn = new QPushButton((note.getTitle()).c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
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
            QPushButton *btn = new QPushButton((note.getTitle() + " ~ [x]").c_str());
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->editNoteWindow(index);
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
            QPushButton *btn = new QPushButton(((note.getTitle() + " ~ [*]").c_str()));
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                this->editNoteWindow(index);
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

    favoriteNotes = new QPushButton("Favorite Notes", this);
    //connect(favoriteNotes, &QPushButton::clicked, this, &GUI::openFavorites);
    favoriteNotes->setStyleSheet("background-color: #7F5AF0");
    favoriteNotes->setFixedSize(200, 50);
    favoriteNotes->move(125, 30);
    favoriteNotes->setFont(font);
    favoriteNotes->show();

    lockedNotes = new QPushButton("Locked Notes", this);
    connect(lockedNotes, &QPushButton::clicked, this, &GUI::openLocked);
    lockedNotes->setStyleSheet("background-color: #7F5AF0");
    lockedNotes->setFixedSize(200, 50);
    lockedNotes->move(500, 30);
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
    saveNote->move(125, 50);
    saveNote->setFont(font2);
    saveNote->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &GUI::destroyNewNoteWIndow);
    cancel->setStyleSheet("background-color: #7F5AF0;");
    cancel->move(500, 50);
    cancel->setFixedSize(200, 50);
    cancel->setFont(font2);
    cancel->show();

    noteTitle = new QTextEdit(this);
    noteTitle->setPlaceholderText("Note Title");
    noteTitle->move(50, 140);
    noteTitle->setStyleSheet("background-color: #004643");
    noteTitle->setFixedSize(700, 50);
    noteTitle->setFont(font);
    noteTitle->show();

    noteContent = new QTextEdit(this);
    noteContent->setPlaceholderText("Note Content");
    noteContent->move(50, 220);
    noteContent->setFixedSize(700, 550);
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
    editNote = new QPushButton("Edit Note", this);
    connect(editNote, &QPushButton::clicked, this,[this, index]{
        if(not (*genericNotesMemory)[index].isLocked())
            changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                       (editNoteContent->toPlainText()).toStdString());
    } );
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    if(not (*genericNotesMemory)[index].isLocked())
        editNote->setStyleSheet("background-color: #7F5AF0");
    else
        editNote->setStyleSheet("background-color: #2B2B2B");
    editNote->setFont(btnFont);
    editNote->show();

    deleteNote = new QPushButton("Delete Note", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index]{ removeNote(index); });
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
    editAddToFavorites->setStyleSheet("background-color: #7F5AF0");
    editAddToFavorites->move(175, 100);
    editAddToFavorites->setFixedSize(200, 50);
    editAddToFavorites->setFont(btnFont);
    editAddToFavorites->show();

    editAddToLocked = new QPushButton("Add To Locked", this);
    connect(editAddToLocked, &QPushButton::clicked, this, [this, index]{
        (*genericNotesMemory)[index].lock();
        //genericNotesMemory.transferNote(index, lockedNotesMemory);
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(425, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

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

/*
 *
 *
 *              LOCKED SECTION
 *
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
    connect(lockCancel, &QPushButton::clicked, this, &GUI::destroyLockedNewNoteWindow);
    lockCancel->setStyleSheet("background-color: #7F5AF0;");
    lockCancel->move(475, 30);
    lockCancel->setFixedSize(200, 50);
    lockCancel->setFont(font2);
    lockCancel->show();

    lockedNoteTitle = new QTextEdit(this);
    lockedNoteTitle->setPlaceholderText("Note Title");
    lockedNoteTitle->move(50, 100);
    lockedNoteTitle->setStyleSheet("background-color: #004643");
    lockedNoteTitle->setFixedSize(700, 50);
    lockedNoteTitle->setFont(font);
    lockedNoteTitle->show();

    lockedNoteContent = new QTextEdit(this);
    lockedNoteContent->setPlaceholderText("Note Content");
    lockedNoteContent->move(50, 160);
    lockedNoteContent->setFixedSize(700, 590);
    lockedNoteContent->setFont(font);
    lockedNoteContent->setStyleSheet("background-color: #004643");
    lockedNoteContent->show();
}

void GUI::showLockedNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyLockedHomeWindow();

    deleteLockedNote = new QPushButton("Delete", this);
    connect(deleteLockedNote, &QPushButton::clicked, this, [this, index]{ removeLockedNote(index); });
    deleteLockedNote->move(300, 30);
    deleteLockedNote->setFixedSize(200, 50);
    deleteLockedNote->setFont(btnFont);
    deleteLockedNote->setStyleSheet("background-color: #7F5AF0");
    deleteLockedNote->show();

    exitShow = new QPushButton("Exit", this);
    connect(exitShow, &QPushButton::clicked, this, &GUI::destroyLockedNoteShowWindow);
    exitShow->setFixedSize(200, 50);
    exitShow->move(550, 30);
    exitShow->setFont(btnFont);
    exitShow->setStyleSheet("background-color: #7F5AF0");
    exitShow->show();

    showUnlockNote = new QPushButton("Unlock", this);
    connect(showUnlockNote, &QPushButton::clicked, this, [this, index]{
        this->lockedNotesMemory->transferNote(index, genericNotesMemory);
        destroyLockedNoteShowWindow();
    });
    showUnlockNote->setStyleSheet("background-color: #7F5AF0");
    showUnlockNote->move(50, 30);
    showUnlockNote->setFixedSize(200, 50);
    showUnlockNote->setFont(btnFont);
    showUnlockNote->show();

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


/*
 *
 *
 *              FAVORITE SECTION
 *
 *
 */