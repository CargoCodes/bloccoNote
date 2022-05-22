//
// Created by viato on 12/05/2022.
//

#ifndef BLOCCONOTE_NOTE_H
#define BLOCCONOTE_NOTE_H

#include "LsmL.h"
#include <iostream>

/*
 * this->dataBaseVector[0] -> genericDataBase
 * this->dataBaseVector[1] -> favoritesBataBase
 * this->dataBaseVector[2] -> lockedDataBase
 */


class Note {
public:

    explicit Note(const string& title, const string& content)
    : title_(title), content_(content){
        dbVector_.reserve(3);
    }

    string getTitle() const {
        return title_;
    }

    void setTitle(const string &newTitle) {
        if(not locked_) {
            dbVector_[0]->editField(this->title_, newTitle);
            if(favorite_)
                dbVector_[1]->editField(this->title_, newTitle);
            this->title_ = newTitle;
        }
    }

    const string &getContent() const {
        return content_;
    }

    void setContent(const string &newContent) {
        if (not locked_) {
            dbVector_[0]->editAttr(this->title_, "content", "content", newContent);
            if (favorite_)
                dbVector_[1]->editAttr(this->title_, "content", "content", newContent);
            this->content_ = newContent;
        }
    }

    void remove() {
        dbVector_[0]->removeField(this->title_);
        if (favorite_)
            dbVector_[1]->removeField(this->title_);
        if (locked_)
            dbVector_[2]->removeField(this->title_);
    }

    void save() {
        if(this->title_.empty())
            throw EmptyNoteTitleError("You must at least set a title_ for the note");

        dbVector_[0]->addField(this->title_);
        dbVector_[0]->addAttr(this->title_, "content", this->content_);
        dbVector_[0]->addAttr(this->title_, "locked", this->locked_ ? "true" : "false");
        dbVector_[0]->addAttr(this->title_, "favorite", this->favorite_ ? "true" : "false");
        if (favorite_){
            dbVector_[1]->addField(this->title_);
            dbVector_[1]->addAttr(this->title_, "content", this->content_);
            dbVector_[1]->addAttr(this->title_, "locked", this->locked_ ? "true" : "false");
            dbVector_[1]->addAttr(this->title_, "favorite", this->favorite_ ? "true" : "false");
        }
        if(locked_) {
            dbVector_[2]->addField(this->title_);
            dbVector_[2]->addAttr(this->title_, "content", this->content_);
            dbVector_[2]->addAttr(this->title_, "locked", this->locked_ ? "true" : "false");
            dbVector_[2]->addAttr(this->title_, "favorite", this->favorite_ ? "true" : "false");
        }
    }

    void edit(const string& newtitle, const string& newContent) {
        if(not locked_) {
            dbVector_[0]->editField(this->title_, newtitle);
            dbVector_[0]->editAttr(newtitle, "content", "content", newContent);
            if(favorite_){
                dbVector_[1]->editField(this->title_, newtitle);
                dbVector_[1]->editAttr(newtitle, "content", "content", newContent);
            }
            this->title_ = newtitle;
            this->content_ = newContent;
        }
    }

    void updateGenericDataBase(LsmL* dataBase) {
        this->dbVector_[0] = (dataBase);
    }

    void updateFavoritesDatabase(LsmL* dataBase) {
        this->dbVector_[1] = (dataBase);
        this->favorite_ = true;
    }

    void updateLockedDataBase(LsmL* dataBase) {
        this->dbVector_[2] = (dataBase);
        this->locked_ = true;
    }

    void removeFromFavorites() {
        this->favorite_ = false;
        auto* db = this->dbVector_[1];
        db->removeField(this->title_);
        this->dbVector_[1] = nullptr;
    }

    void removeFromLocked() {
        this->locked_ = false;
        auto* db = this->dbVector_[2];
        db->removeField(this->title_);
        this->dbVector_[2] = nullptr;
    }

    void lock() {
        this->locked_ = true;
        dbVector_[0]->editAttr(this->title_, "locked", "locked", "true");
        if(favorite_)
            dbVector_[1]->editAttr(this->title_, "locked", "locked", "true");
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

    vector<LsmL*> dbVector_;

    class EmptyNoteTitleError : public runtime_error {
    public:
        explicit EmptyNoteTitleError(const char* message) : runtime_error(message) {
            cerr << message << endl;
        }
    };
};


#endif //BLOCCONOTE_NOTE_H
