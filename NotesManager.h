//
// Created by Codes on 26/05/2022.
//

#ifndef BLOCCONOTE_NOTESMANAGER_H
#define BLOCCONOTE_NOTESMANAGER_H


#include "LsmL.h"
#include "Note.h"
#include <vector>
#include <iostream>

using namespace std;

/*
 * Responsabilities:
 * - contain all the notes and hadle them (add, edit, remove, read)
 * - interact with the note's dataBase
 * - interact with the GUI
 * - observer function for both GUI and notes
 */

class NotesManager {
public:
    NotesManager() {
        this->scan();
    }

    Note operator[](int index) {
        if (this->checkIndex(index)) {
            return this->notes[index];
        }
        throw IndexOutOfRange("Index out of range");
    }

    void newNote(const string &title, const string &content, bool locked = false, bool favorite = false);

    int indexOf(string title) {
        for (int i = 0; i < this->notes.size(); i++) {
            if (this->notes[i].getTitle() == title) {
                return i;
            }
        }
        return -1;
    }

    int size() {
        return this->notes.size();
    }

    void editNote(int index, const string &newTitle, const string &newContent);

    void lock(int index) {
        if (checkIndex(index)) {
            this->notes[index].lock();
            this->mainDataBase.editAttr(notes[index].getTitle(),
                                        "locked", "locked", "true");
            this->updated = true;
        }
    }

    void unlock(int index) {
        if (checkIndex(index)) {
            this->notes[index].unlock();
            this->mainDataBase.editAttr(notes[index].getTitle(),
                                        "locked", "locked", "false");
            updated = true;
        }
    }

    void favorite(int index) {
        if (this->checkIndex(index)) {
            this->notes[index].favorite();
            this->mainDataBase.editAttr(notes[index].getTitle(),
                                        "favorite", "favorite", "true");
            this->updated = true;
        }
    }

    void removeFromFavorites(int index) {
        if (checkIndex(index)) {
            this->notes[index].removeFromFavorites();
            this->mainDataBase.editAttr(notes[index].getTitle(),
                                        "favorite", "favorite", "false");
            this->updated = true;
        }
    }

    bool isUpdated() {
        return this->updated;
    }

    void deleteNote(int index);

    void deleteAll() {
        for (int i = 0; i < this->size(); i++) {
            deleteNote(0);
        }
        this->mainDataBase.clearFile();
    }

    class IndexOutOfRange : public out_of_range {
    public:
        IndexOutOfRange(const char *messsage) : out_of_range(messsage) {
            cerr << messsage << endl;
        }
    };

private:
    LsmL mainDataBase = LsmL("dataBase.lsml");
    vector<Note> notes;
    bool updated = false;

    void scan();

    void addNote(const string &title, const string &content,
                 bool locked = false, bool favorite = false);

    bool checkIndex(int index) {
        if (index >= 0 and index < this->size())
            return true;
        return false;
    }

};


#endif //BLOCCONOTE_NOTESMANAGER_H

/*\..{[|<->_<'>]|}../*/