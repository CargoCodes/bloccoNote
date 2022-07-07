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
        scan();
    }

    Note operator[](int index) {
        if (checkIndex(index)) {
            return notes[index];
        }
        throw IndexOutOfRange("Index out of range");
    }

    void newNote(const string &title, const string &content, bool locked = false, bool favorite = false);

    int indexOf(string title) const {
        for (int i = 0; i < notes.size(); i++) {
            if (notes[i].getTitle() == title) {
                return i;
            }
        }
        return -1;
    }

    void print() const {
        for(auto note : notes) {
            cout << note.getTitle() << " " << note.isLocked() << " " << note.isFavorite() << endl;
        }
    }

    int size() const {
        return notes.size();
    }

    int countFavoriteNotes() const {
        int counter = 0;
        for (auto note : notes) {
            if (note.isFavorite())
                counter++;
        }
        return counter;
    }

    int countLockedNotes() const {
        int counter = 0;
        for (auto note : notes) {
            if (note.isLocked())
                counter++;
        }
        return counter;
    }

    void editNote(int index, const string &newTitle, const string &newContent);

    void lock(int index) {
        if (checkIndex(index)) {
            notes[index].lock();
            mainDataBase.editAttr(notes[index].getTitle(),
                                        "locked", "locked", "true");
            updated = true;
            scan();
        }
    }

    void unlock(int index) {
        if (checkIndex(index)) {
            notes[index].unlock();
            mainDataBase.editAttr(notes[index].getTitle(),
                                        "locked", "locked", "false");
            updated = true;
            scan();
        }
    }

    void favorite(int index) {
        if (checkIndex(index)) {
            notes[index].favorite();
            mainDataBase.editAttr(notes[index].getTitle(),
                                        "favorite", "favorite", "true");
            updated = true;
            scan();
        }
    }

    void removeFromFavorites(int index) {
        if (checkIndex(index)) {
            notes[index].removeFromFavorites();
            mainDataBase.editAttr(notes[index].getTitle(),
                                        "favorite", "favorite", "false");
            updated = true;
            scan();
        }
    }

    bool isUpdated() const {
        return updated;
    }

    void deleteNote(int index);

    void deleteAll() {
        for (int i = 0; i < size(); i++)
            deleteNote(i);
        notes.clear();
        mainDataBase.clearFile();
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
        if (index >= 0 and index < size())
            return true;
        return false;
    }
};


#endif //BLOCCONOTE_NOTESMANAGER_H

/*\..{[|<->_<'>]|}../*/
