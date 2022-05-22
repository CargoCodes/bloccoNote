//
// Created by Codes on 20/05/2022.
//

#include "MainWindow.h"

void MainWindow::compileScrollBar() {
    QFont font; // font definition
    font.setPointSize(20);

    if(db::genericNotesMemory.size() > 0) { // verifies if the memory is not empty
        for (int i = 0; i < db::genericNotesMemory.size(); i++) { // for each note in the database creates a idButton
            QPushButton *btn = new IdPushButton((db::genericNotesMemory[i].getTitle()).c_str(), i);
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

void MainWindow::homeWindow() {
    QFont font;
    font.setPointSize(25);
    addNewNoteBtn = new QPushButton("+", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, &MainWindow::newNoteWindow);
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(70, 70);
    addNewNoteBtn->move(680, 680);
    addNewNoteBtn->setFont(font);
    addNewNoteBtn->show();

    favoriteNotes = new QPushButton("Favorite Notes", this);
    //connect(favoriteNotes, &QPushButton::clicked, this, &MainWindow::openFavorites);
    favoriteNotes->setStyleSheet("background-color: #7F5AF0");
    favoriteNotes->setFixedSize(200, 50);
    favoriteNotes->move(125, 30);
    favoriteNotes->setFont(font);
    favoriteNotes->show();

    lockedNotes = new QPushButton("Locked Notes", this);
    connect(lockedNotes, &QPushButton::clicked, this, &MainWindow::openLocked);
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
} // DONE

void MainWindow::newNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    this->destroyHomeWindow();
    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, &MainWindow::saveNewNote);
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->setFixedSize(200, 50);
    saveNote->move(125, 100);
    saveNote->setFont(font2);
    saveNote->show();

    addToFavorites = new QPushButton("Add To Favorites", this);
    addToFavorites->setStyleSheet("background-color: #7F5AF0");
    addToFavorites->move(125, 30);
    addToFavorites->setFixedSize(200, 50);
    addToFavorites->setFont(font2);
    addToFavorites->show();

    addToLocked = new QPushButton("Add To Locked", this);
    addToLocked->setStyleSheet("background-color: #7F5AF0");
    addToLocked->move(500, 30);
    addToLocked->setFixedSize(200, 50);
    addToLocked->setFont(font2);
    addToLocked->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &MainWindow::destroyNewNoteWIndow);
    cancel->setStyleSheet("background-color: #7F5AF0;");
    cancel->move(500, 100);
    cancel->setFixedSize(200, 50);
    cancel->setFont(font2);
    cancel->show();

    noteTitle = new QTextEdit(this);
    noteTitle->setPlaceholderText("Note Title");
    noteTitle->move(50, 190);
    noteTitle->setStyleSheet("background-color: #004643");
    noteTitle->setFixedSize(700, 50);
    noteTitle->setFont(font);
    noteTitle->show();

    noteContent = new QTextEdit(this);
    noteContent->setPlaceholderText("Note Content");
    noteContent->move(50, 270);
    noteContent->setFixedSize(700, 500);
    noteContent->setFont(font);
    noteContent->setStyleSheet("background-color: #004643");
    noteContent->show();
}

void MainWindow::editNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editNote = new QPushButton("Edit Note", this);
    connect(editNote, &QPushButton::clicked, this,[this, index]{
        if(not db::genericNotesMemory[index].isLocked())
            changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                       (editNoteContent->toPlainText()).toStdString());
    } );
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    if(not db::genericNotesMemory[index].isLocked())
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
    connect(exitEdit, &QPushButton::clicked, this, &MainWindow::destroyEditNoteWindow);
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
    connect(editAddToLocked, &QPushButton::clicked, this, [index]{
        db::genericNotesMemory[index].lock();
        db::genericNotesMemory.transferNote(index, db::lockedNotesMemory);
    });
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(425, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText((db::genericNotesMemory[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText((db::genericNotesMemory[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

