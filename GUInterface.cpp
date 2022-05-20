//
// Created by Codes on 20/05/2022.
//

#include "GUInterface.h"

void GUInterface::compileScrollBar() {
    QFont font;
    font.setPointSize(20);
    if(notesMemory.size() > 0) {
        for (int i = 0; i < notesMemory.size(); i++) {
            QPushButton *btn = new IdPushButton((notesMemory[i].getTitle()).c_str(), i);
            int index = i;
            connect(btn, &QPushButton::clicked, this, [this, index] {
                //auto* idBtn = dynamic_cast<IdPushButton*>(btn);
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

void GUInterface::homeWindow() {
    QFont font;
    font.setPointSize(25);
    addNewNoteBtn = new QPushButton("New Note", this);
    connect(addNewNoteBtn, &QPushButton::clicked, this, &GUInterface::newNoteWindow);
    addNewNoteBtn->setStyleSheet("background-color: #7F5AF0");
    addNewNoteBtn->setFixedSize(350, 50);
    addNewNoteBtn->move(125, 30);
    addNewNoteBtn->setFont(font);
    addNewNoteBtn->show();

    scrollArea = new QScrollArea(this);
    QPalette scrollAreaBg = QPalette();
    scrollArea->setStyleSheet("background-color: #ABD1C6; border: 0;");
    scrollArea->setPalette(scrollAreaBg);
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setGeometry(90, 110, 450, 490);

    widget = new QWidget();
    scrollArea->setWidget(widget);

    boxLayout = new QVBoxLayout();
    widget->setLayout(boxLayout);

    this->compileScrollBar();
    scrollArea->show();
}

void GUInterface::newNoteWindow() {
    QFont font;
    font.setPointSize(20);
    QFont font2;
    font2.setPointSize(18);
    this->destroyHomeWindow();
    saveNote = new QPushButton("Save", this);
    connect(saveNote, &QPushButton::clicked, this, &GUInterface::saveNewNote);
    saveNote->setStyleSheet("background-color: #7F5AF0");
    saveNote->move(100, 15);
    saveNote->setFont(font2);
    saveNote->show();

    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &GUInterface::destroyNewNoteWIndow);
    cancel->setStyleSheet("background-color: #7F5AF0; border: 0;");
    cancel->move(400, 15);
    cancel->setFont(font2);
    cancel->show();

    noteTitle = new QTextEdit(this);
    noteTitle->setPlaceholderText("Note Title");
    noteTitle->move(50, 60);
    noteTitle->setStyleSheet("background-color: #004643");
    noteTitle->setFixedSize(500, 40);
    noteTitle->setFont(font);
    noteTitle->show();

    noteContent = new QTextEdit(this);
    noteContent->setPlaceholderText("Note Content");
    noteContent->move(50, 120);
    noteContent->setFixedSize(500, 450);
    noteContent->setFont(font);
    noteContent->setStyleSheet("background-color: #004643");
    noteContent->show();
}

void GUInterface::editNoteWindow(int index) {
    this->destroyHomeWindow();
    editNote = new QPushButton("Edit Note", this);
    connect(editNote, &QPushButton::clicked, this,[this, index]{
        changeNote(index, (editNoteTitle->toPlainText()).toStdString(),
                   (editNoteContent->toPlainText()).toStdString());
    } );
    editNote->move(100, 20);
    editNote->setStyleSheet("background-color: #7F5AF0");
    editNote->show();

    deleteNote = new QPushButton("Delete Note", this);
    connect(deleteNote, &QPushButton::clicked, this, [this, index]{ removeNote(index); });
    deleteNote->move(250, 20);
    deleteNote->setStyleSheet("background-color: #7F5AF0");
    deleteNote->show();

    exitEdit = new QPushButton("Cancel", this);
    connect(exitEdit, &QPushButton::clicked, this, &GUInterface::destroyEditNoteWindow);
    exitEdit->move(400, 20);
    exitEdit->setStyleSheet("background-color: #7F5AF0");
    exitEdit->show();

    editNoteTitle = new QTextEdit(this);
    editNoteTitle->setPlaceholderText("Note Title");
    editNoteTitle->setText((this->notesMemory[index].getTitle()).c_str());
    editNoteTitle->move(50, 60);
    editNoteTitle->setStyleSheet("background-color: #004643");
    editNoteTitle->setFixedSize(500, 30);
    editNoteTitle->show();

    editNoteContent = new QTextEdit(this);
    editNoteContent->setPlaceholderText("Note Content");
    editNoteContent->setText((this->notesMemory[index].getContent()).c_str());
    editNoteContent->move(50, 120);
    editNoteContent->setStyleSheet("background-color: #004643");
    editNoteContent->setFixedSize(500, 450);
    editNoteContent->show();
}

