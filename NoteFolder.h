//
// Created by Codes on 23/05/2022.
//

#ifndef BLOCCONOTE_NOTEFOLDER_H
#define BLOCCONOTE_NOTEFOLDER_H

#include "Note.h"
#include <vector>
#include <iostream>

using namespace std;

/*
 * This class is only a container for informations about a folder.
 * It doesn't interact with the database, and do not perform any action on the notes.
 * Just an interface carrying variables.
 */

class NoteFolder {
public:
    NoteFolder(string folderName) : folderName(folderName) {}

    // all the methods are only getters and setters

    void newNote(string title) {
        notesArray.push_back(title);
    }

    string operator[](int index) {
        return notesArray[index];
    }

    void editNote(string noteTitle, string newTitle) {
        for (int i = 0; i < notesArray.size(); i++) {
            if (notesArray[i] == noteTitle) {
                notesArray[i] = newTitle;
            }
        }
    }

    string getFolderName() {
        return folderName;
    }

    int size() {
        return notesArray.size();
    }

    bool isIn(string noteTitle) {
        for (auto note: notesArray) {
            if (note == noteTitle) {
                return true;
            }
        }
        return false;
    }

private:
    string folderName;

    vector<string> notesArray;
};


#endif //BLOCCONOTE_NOTEFOLDER_H
