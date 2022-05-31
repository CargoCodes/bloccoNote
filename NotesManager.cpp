//
// Created by Codes on 26/05/2022.
//

#include "NotesManager.h"

void NotesManager::scan() {
    if (this->size() > 0)
        this->notes.clear();

    if (not this->mainDataBase.isEmpty()) { // reads if the dataBase is not empty
        auto content = this->mainDataBase.read(); // reads the database

        for (auto &fieldContainer: content) { // goes through all the fields
            for (auto &internalField: fieldContainer) { // goes through the pairs in the field
                string noteTitle = internalField.first; // gets the note title
                string noteContent;
                bool locked = false;
                bool favorite = false;

                noteContent = this->mainDataBase.getAttr(noteTitle, "content"); // sets content

                if (this->mainDataBase.getAttr(noteTitle, "locked") == "true") // sets locked attribute
                    locked = true;

                if (this->mainDataBase.getAttr(noteTitle, "favorite") == "true") // sets the favorite attribute
                    favorite = true;

                this->addNote(noteTitle, noteContent, locked, favorite); // adds note with attributes to memory
            }
        }
    }
}

void NotesManager::addNote(const string &title, const string &content, bool locked, bool favorite) {
    // adds the note to memory without adding it to the dataBase
    Note newNote = Note(title, content);

    if (locked)
        newNote.lock();
    if (favorite)
        newNote.favorite();

    this->notes.push_back(newNote);
}

void NotesManager::newNote(const string &title, const string &content, bool locked, bool favorite) {
    // adds the note to memory also adding it to the dataBase
    this->mainDataBase.addField(title);
    this->mainDataBase.addAttr(title, "content", content);

    Note newNote = Note(title, content);

    if (locked) {
        this->mainDataBase.addAttr(title, "locked", "true");
        newNote.lock();
    } else
        this->mainDataBase.addAttr(title, "locked", "false");

    if (favorite) {
        this->mainDataBase.addAttr(title, "favorite", "true");
        newNote.favorite();
    } else
        this->mainDataBase.addAttr(title, "favorite", "false");

    this->notes.push_back(newNote);

    this->updated = true;
}

void NotesManager::editNote(int index, const string &newTitle, const string &newContent) {
    // edits the note to both memory and dataBase
    if (this->checkIndex(index)) {
        if (not this->notes[index].isLocked()) {
            auto note = this->notes[index];

            this->mainDataBase.editAttr(note.getTitle(), "content", "content", newContent);
            this->mainDataBase.editField(note.getTitle(), newTitle);

            note.edit(newTitle, newContent);

            this->updated = true;
        }
    }
}

void NotesManager::deleteNote(int index) {
    // removes note from both memory and dataBase
    if (this->checkIndex(index)) {
        this->mainDataBase.removeField(this->notes[index].getTitle());
        if (this->notes.size() > 1) {
            auto end = this->notes.begin();

            for (int i = 0; i <= index; i++)
                end++;

            auto begin = end;
            begin--;

            this->notes.erase(begin, end);
        } else
            this->notes.clear();
        this->updated = true;
    }
}