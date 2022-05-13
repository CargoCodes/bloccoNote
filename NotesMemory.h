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
    NotesMemory() = default;

    void addNote(const Note& note) {
        this->memory.push_back(note);
    }

    void newNote(const string& title, const string& content) {
        Note newNote(dataBase, title, content);
        this->memory.push_back(newNote);
    }

    const KvK& getDataBase() const {
        return this->dataBase;
    }

    bool deleteNote(int id){
        if(id > 0 and id < memory.size()) {
            this->memory[id].remove();
            this->memory = pop(memory, id);
            return true;
        }
        return false;
    }

    bool editNote(int id, const string& title="", const string& content="") {
        if(id > 0 and id < memory.size()){
            auto& note = this->memory[id];
            note.edit(title, content);
            return true;
        }
        return false;
    }

private:
    KvK dataBase = KvK("notesMemory.kvk");

    vector<Note> memory;
};


#endif //BLOCCONOTE_NOTESMEMORY_H
