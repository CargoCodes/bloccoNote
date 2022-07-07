//
// Created by Codes on 26/05/2022.
//

#include "NotesManager.h"

void NotesManager::scan() {
    if (size() > 0)
        notes.clear();

    if (not mainDataBase.isEmpty()) { // reads if the dataBase is not empty
        auto content = mainDataBase.read(); // reads the database

        for (auto &fieldContainer: content) { // goes through all the fields
            for (auto &internalField: fieldContainer) { // goes through the pairs in the field
                string noteTitle = internalField.first; // gets the note title
                string noteContent;
                bool locked = false;
                bool favorite = false;

                noteContent = mainDataBase.getAttr(noteTitle, "content"); // sets content

                if (mainDataBase.getAttr(noteTitle, "locked") == "true") // sets locked attribute
                    locked = true;

                if (mainDataBase.getAttr(noteTitle, "favorite") == "true") // sets the favorite attribute
                    favorite = true;

                addNote(noteTitle, noteContent, locked, favorite); // adds note with attributes to memory
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

    notes.push_back(newNote);
}

void NotesManager::newNote(const string &title, const string &content, bool locked, bool favorite) {
    // adds the note to memory also adding it to the dataBase
    mainDataBase.addField(title);
    mainDataBase.addAttr(title, "content", content);

    Note newNote = Note(title, content);

    if (locked) {
        mainDataBase.addAttr(title, "locked", "true");
        newNote.lock();
    } else
        mainDataBase.addAttr(title, "locked", "false");

    if (favorite) {
        mainDataBase.addAttr(title, "favorite", "true");
        newNote.favorite();
    } else
        mainDataBase.addAttr(title, "favorite", "false");

    notes.push_back(newNote);

    updated = true;
    scan();
}

void NotesManager::editNote(int index, const string &newTitle, const string &newContent) {
    // edits the note to both memory and dataBase
    if (checkIndex(index)) {
        if (not notes[index].isLocked()) {
            auto note = notes[index];

            mainDataBase.editAttr(note.getTitle(), "content", "content", newContent);
            mainDataBase.editField(note.getTitle(), newTitle);

            note.edit(newTitle, newContent);

            updated = true;
            scan();
        }
    }
}

void NotesManager::deleteNote(int index) {
    // removes note from both memory and dataBase
    if (checkIndex(index)) {
        mainDataBase.removeField(notes[index].getTitle());
        if (notes.size() > 1) {
            auto end = notes.begin();

            for (int i = 0; i <= index; i++)
                end++;

            auto begin = end;
            begin--;

            notes.erase(begin, end);
        } else
            notes.clear();
        updated = true;
        scan();
    }
}

/*\..{[|<->_<'>]|}../*/
