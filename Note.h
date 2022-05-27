#ifndef BLOCCONOTE_NOTE_H
#define BLOCCONOTE_NOTE_H

#include "LsmL.h"
#include <iostream>

/*
 * Container class
 * This class only exists to store note's data in an accessible way
 * it has no direct interaction with the other classes or with the GUI
 * The aim of the class is to make data accessible without having to
 * interact with the dataBase
 */

class Note {
public:

    explicit Note(const string &title, const string &content, LsmL *dataBase = nullptr)
            : title_(title), content_(content) {}

    string getTitle() const {
        return title_;
    }

    const string &getContent() const {
        return content_;
    }

    void edit(const string &newtitle, const string &newContent) {
        this->title_ = newtitle;
        this->content_ = newContent;
    }

    void lock() {
        this->locked_ = true;
    }

    void unlock() {
        this->locked_ = false;
    }

    bool isLocked() const {
        return locked_;
    }

    void favorite() {
        this->favorite_ = true;
    }

    void removeFromFavorites() {
        this->favorite_ = false;
    }

    bool isFavorite() const {
        return this->favorite_;
    }

private:
    string title_;
    string content_;

    bool locked_ = false;
    bool favorite_ = false;
};


#endif //BLOCCONOTE_NOTE_H
