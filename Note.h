//
// Created by viato on 12/05/2022.
//

#ifndef BLOCCONOTE_NOTE_H
#define BLOCCONOTE_NOTE_H

#include "KvK.h"
#include <iostream>

class Note {
public:

    explicit Note(const KvK& dataBase, const string& title, const string& content="")
    : dataBase(dataBase), title(title), content(content) {}

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &newTitle) {
        this->dataBase.editClass(this->title, newTitle); // changes the title in the database
        this->title = newTitle; // changes title in its own object
    }

    const string &getContent() const {
        return content;
    }

    void setContent(const string &newContent) {
        this->dataBase.editAttr(this->title, // changes content in the database
                                "content", "content", newContent);
        this->content = newContent; // changes content in its own object
    }

    bool remove() { // removes the object from the database
        return this->dataBase.removeClass(this->title);
    }

    void save() {
        if(this->title.empty()) // checks title existence
            throw EmptyNoteTitleError("You must at least set a title for the note");
        this->dataBase.addClass(this->title); // creates a field in the database
        this->dataBase.addAttr(this->title, // enters the data in the database
                               "content",
                               this->content.empty() ? "":this->content);
    }

    void edit(const string& newTitle, const string& newContent) {
        this->dataBase.editClass(this->title, newTitle); // edits the field name in the database
        this->title = newTitle; // changes the title in the object
        this->dataBase.editAttr(this->title, // changes the content in the database
                                "content",
                                "content",
                                newContent);
        this->content = newContent; // changes the content in the object
    }



private:
    KvK dataBase; // database, received from NotesMemory object

    string title;
    string content;


    class EmptyNoteTitleError : public runtime_error { // error nested class
    public:
        explicit EmptyNoteTitleError(const char* message) : runtime_error(message) {}
    };
};


#endif //BLOCCONOTE_NOTE_H
