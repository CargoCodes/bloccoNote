//
// Created by Codes on 26/05/2022.
//

#include "NotesManager.h"

void NotesManager::scan() {
    if (this->size() > 0)
        this->notes.clear();

    if (not this->mainDataBase.isEmpty()) {
        auto content = this->mainDataBase.read();

        for (auto &fieldContainer: content) {
            for (auto &internalField: fieldContainer) {
                string noteTitle = internalField.first;
                string noteContent;
                bool locked = false;
                bool favorite = false;

                noteContent = this->mainDataBase.getAttr(noteTitle, "content");

                if (this->mainDataBase.getAttr(noteTitle, "locked") == "true")
                    locked = true;

                if (this->mainDataBase.getAttr(noteTitle, "favorite") == "true")
                    favorite = true;

                this->addNote(noteTitle, noteContent, locked, favorite);
            }
        }
    }
}

void NotesManager::addNote(const string &title, const string &content, bool locked, bool favorite) {
    Note newNote = Note(title, content);

    if (locked)
        newNote.lock();
    if (favorite)
        newNote.favorite();

    this->notes.push_back(newNote);
}

void NotesManager::newNote(const string &title, const string &content, bool locked, bool favorite) {
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