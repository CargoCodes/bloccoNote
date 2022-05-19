//
// Created by viato on 12/05/2022.
//

#ifndef BLOCCONOTE_NOTE_H
#define BLOCCONOTE_NOTE_H

#include "LsmL.h"
#include <iostream>

class Note {
public:

    explicit Note(const LsmL& dataBase, const string& title, const string& content="")
    : dataBase(dataBase), title(title), content(content) {}

    const string &getTitle() const {
        return title;
    }

    void setTitle(const string &newTitle) {
        this->dataBase.editField(this->title, newTitle);
        this->title = newTitle;
    }

    const string &getContent() const {
        return content;
    }

    void setContent(const string &newContent) {
        this->dataBase.editAttr(this->title,
                                "content", "content", newContent);
        this->content = newContent;
    }

    bool remove() {
        return this->dataBase.removeField(this->title);
    }

    void save() {
        if(this->title.empty())
            throw EmptyNoteTitleError("You must at least set a title for the note");
        this->dataBase.addField(this->title);
        this->dataBase.addAttr(this->title,
                               "content",
                               this->content.empty() ? "":this->content);
    }

    void edit(const string& newtitle, const string& newContent) {
        this->dataBase.editField(this->title, newtitle);
        this->title = newtitle;
        this->dataBase.editAttr(this->title,
                                "content",
                                "content",
                                newContent);
        this->content = newContent;
    }

private:
    LsmL dataBase;

    string title;
    string content;


    class EmptyNoteTitleError : public runtime_error {
    public:
        explicit EmptyNoteTitleError(const char* message) : runtime_error(message) {
            cerr << message << endl;
        }
    };
};


#endif //BLOCCONOTE_NOTE_H
