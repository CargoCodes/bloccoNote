//
// Created by Codes on 23/05/2022.
//

#include "NoteFolder.h"

void NoteFolder::newNote(string title, string content) {
    Note newNote(title, content);

    try {
        this->lockedDb.getField(title);
        newNote.lock();
    } catch (...) {}

    try {
        this->favoritesDb.getField(title);
        newNote.favorite();
    } catch (...) {}

    this->notesArray.push_back(newNote);
    newNote.save();
}

void NoteFolder::editNote(int index, string title, string content) {
    auto requestedNote = this->notesArray[index];
    if (not requestedNote.isLocked()) {
        if (requestedNote.isFavorite()) {
            favoritesDb.editAttr(requestedNote.getTitle(),
                                 "content", "content", content);
            favoritesDb.editField(requestedNote.getTitle(), title);
        } else {
            genericDb.editAttr(requestedNote.getTitle(),
                               "content", "content", content);
            genericDb.editField(requestedNote.getTitle(), title);
        }
        this->notesArray[index].setTitle(title);
        this->notesArray[index].setContent(content);
    }
}