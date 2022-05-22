#ifndef BLOCCONOTE_NOTE_H
#define BLOCCONOTE_NOTE_H

#include "LsmL.h"
#include <iostream>


class Note {
public:

    explicit Note(const string& title, const string& content, LsmL dataBase)
    : title_(title), content_(content), dataBase(dataBase){}

    string getTitle() const {
        return title_;
    }

    const string &getContent() const {
        return content_;
    }

    void remove() {
        dataBase.removeField(this->title_);
    }

    void save() {
        if(this->title_.empty())
            throw EmptyNoteTitleError("You must at least set a title_ for the note");

        dataBase.addField(this->title_);
        dataBase.addAttr(this->title_, "content", this->content_);
    }

    void edit(const string& newtitle, const string& newContent) {
        dataBase.editField(this->title_, newtitle);
        dataBase.editAttr(newtitle, "content", "content", newContent);
    }

    void lock() {
        this->locked_ = true;
    }

    bool isLocked() const {
        return locked_;
    }

    void favorite() {
        this->favorite_ = true;
    }

    bool isFavorite() const {
        return this->favorite_;
    }

private:
    string title_;
    string content_;

    bool locked_ = false;
    bool favorite_ = false;

    LsmL dataBase;

    class EmptyNoteTitleError : public runtime_error {
    public:
        explicit EmptyNoteTitleError(const char* message) : runtime_error(message) {
            cerr << message << endl;
        }
    };
};


#endif //BLOCCONOTE_NOTE_H
