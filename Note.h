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

    explicit Note(const string &title, const string &content)
            : title_(title), content_(content) {}

    // methods are only getters and setters

    string getTitle() const {
        return title_;
    }

    const string &getContent() const {
        return content_;
    }

    void edit(const string &newtitle, const string &newContent) {
        title_ = newtitle;
        content_ = newContent;
    }

    void lock() {
        locked_ = true;
    }

    void unlock() {
        locked_ = false;
    }

    bool isLocked() const {
        return locked_;
    }

    void favorite() {
        favorite_ = true;
    }

    void removeFromFavorites() {
        favorite_ = false;
    }

    bool isFavorite() const {
        return favorite_;
    }

private:
    string title_;
    string content_;

    bool locked_ = false;
    bool favorite_ = false;
};


#endif //BLOCCONOTE_NOTE_H

/*\..{[|<->_<'>]|}../*/