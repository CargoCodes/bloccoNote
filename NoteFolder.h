//
// Created by Codes on 23/05/2022.
//

#ifndef BLOCCONOTE_NOTEFOLDER_H
#define BLOCCONOTE_NOTEFOLDER_H

#include "Note.h"
#include <vector>
#include <iostream>

using namespace std;

class NoteFolder {
public:
    NoteFolder(string folderName) : folderName(folderName) {}

    void newNote(string title, string content);

    Note operator[](int index) {
        return notesArray[index];
    }

    void editNote(int index, string title, string content);

private:
    string folderName;

    LsmL genericDb = LsmL("genericNotes.lsml");
    LsmL lockedDb = LsmL("lockedNotes.lsml");
    LsmL favoritesDb = LsmL("favoriteNotes.lsml");

    vector<Note> notesArray;

};


#endif //BLOCCONOTE_NOTEFOLDER_H
