//
// Created by Codes on 21/05/2022.
//

#include "LockedWindow.h"


void LockedWindow::compileScrollArea() {
    QFont font;
    font.setPointSize(20);
    if(db::lockedNotesMemory.size() > 0) {
        //db::lockedNotesMemory.scan();
        for (int i = 0; i < db::lockedNotesMemory.size(); i++) {
            QPushButton *btn = new IdPushButton((db::lockedNotesMemory[i].getTitle()).c_str(), i);
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

void LockedWindow::homeWindow() {
    QFont btnFont;
    btnFont.setPointSize(25);
    addNewNoteBtn = new QPushButton("+", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, &LockedWindow::newNoteWindow);
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(70, 70);
    addNewNoteBtn->move(680, 680);
    addNewNoteBtn->setFont(btnFont);
    addNewNoteBtn->show();

    titleLabel = new QLabel("Locked Notes", this);
    titleLabel->setFixedSize(200, 50);
    titleLabel->setStyleSheet("color: #000000");
    titleLabel->move(300, 30);
    titleLabel->setFont(btnFont);
    titleLabel->show();

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

    this->compileScrollArea();
    scrollArea->show();
} // DONE

void LockedWindow::newNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);

    this->destroyHomeWindow();

    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, &LockedWindow::saveNewNote);
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->setFixedSize(200, 50);
    saveNote->move(50, 30);
    saveNote->setFont(font2);
    saveNote->show();

    addToFavorites = new QPushButton("Add To Favorites", this);
    addToFavorites->setStyleSheet("background-color: #7F5AF0");
    addToFavorites->move(300, 30);
    addToFavorites->setFixedSize(200, 50);
    addToFavorites->setFont(font2);
    addToFavorites->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &LockedWindow::destroyNewNoteWIndow);
    cancel->setStyleSheet("background-color: #7F5AF0;");
    cancel->move(550, 30);
    cancel->setFixedSize(200, 50);
    cancel->setFont(font2);
    cancel->show();

    noteTitle = new QTextEdit(this);
    noteTitle->setPlaceholderText("Note Title");
    noteTitle->move(50, 100);
    noteTitle->setStyleSheet("background-color: #004643");
    noteTitle->setFixedSize(700, 50);
    noteTitle->setFont(font);
    noteTitle->show();

    noteContent = new QTextEdit(this);
    noteContent->setPlaceholderText("Note Content");
    noteContent->move(50, 160);
    noteContent->setFixedSize(700, 590);
    noteContent->setFont(font);
    noteContent->setStyleSheet("background-color: #004643");
    noteContent->show();
}

void LockedWindow::editNoteWindow(int index) {
    QFont btnFont;
    btnFont.setPointSize(18);

    QFont textFont;
    textFont.setPointSize(20);

    this->destroyHomeWindow();
    editNote = new QPushButton("Edit Note", this);
    connect(editNote, &QPushButton::clicked, this,[this, index]{
        changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                   (editNoteContent->toPlainText()).toStdString());
    } );
    editNote->move(50, 30);
    editNote->setFixedSize(200, 50);
    editNote->setStyleSheet("background-color: #7F5AF0");
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
    connect(exitEdit, &QPushButton::clicked, this, &LockedWindow::destroyEditNoteWindow);
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
    editAddToLocked->setStyleSheet("background-color: #7F5AF0");
    editAddToLocked->move(425, 100);
    editAddToLocked->setFixedSize(200, 50);
    editAddToLocked->setFont(btnFont);
    editAddToLocked->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText((db::lockedNotesMemory[index].getTitle()).c_str());
    editNoteTitle->move(50, 190);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFont(textFont);
    editNoteTitle->setFixedSize(700, 50);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText((db::lockedNotesMemory[index].getContent()).c_str());
    editNoteContent->move(50, 270);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFont(textFont);
    editNoteContent->setFixedSize(700, 500);
    editNoteContent->show();
}

