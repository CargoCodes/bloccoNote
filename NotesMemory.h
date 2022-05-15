//
// Created by viato on 12/05/2022.
//

#ifndef BLOCCONOTE_NOTESMEMORY_H
#define BLOCCONOTE_NOTESMEMORY_H


#include "KvK.h"
#include "Note.h"
#include <vector>
#include "utils.h"

class NotesMemory {
public:
    NotesMemory();

    void addNote(const Note& note) { // adds to the storage an existing note
        this->memory.push_back(note);
    }

    void newNote(const string& title, const string& content) { // creates a new note and stores it
        Note newNote(dataBase, title, content);
        newNote.save();
        this->memory.push_back(newNote);
    }

    const KvK& getDataBase() const { // returns reference to database
        return this->dataBase;
    }

    bool deleteNote(int id){ // deletes a note by its id (index in the storage vector)
        if(id >= 0 and id < memory.size()) { // checks id correctness
            this->memory[id].remove(); // deletes the note
            this->memory = pop(memory, id); // removes the note from the memory
            return true;
        }
        return false;
    }

    bool editNote(int id, const string& title="", const string& content="") { // edits a note in the memory
        if(id >= 0 and id < memory.size()){ // checks id correctness
            auto& note = this->memory[id]; // creates a reference to the note
            note.edit(title, content); // edits the note content, which is edited also in the databse by the note itself
            return true;
        }
        return false;
    }

private:
    KvK dataBase = KvK("notesMemory.kvk"); // notes database for local storage

    vector<Note> memory; // memory array
};


#endif //BLOCCONOTE_NOTESMEMORY_H
