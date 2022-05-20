#ifndef BLOCCONOTE_NOTESMEMORY_H
#define BLOCCONOTE_NOTESMEMORY_H


#include "LsmL.h"
#include "Note.h"
#include <vector>
#include "utils.h"

class NotesMemory {
public:
    NotesMemory() {
        this->scan();
    }

    void addNote(Note* note) {
        this->memory.push_back(note);
    }

    void newNote(const string& title, const string& content) {
        Note* newNote = new Note(dataBase, title, content);
        newNote->save();
        this->memory.push_back(newNote);
        //delete newNote;
    }

    Note operator[](int index) {
        return *memory[index];
    }

    int size() {
        return memory.size();
    }

    const LsmL& getDataBase() const {
        return this->dataBase;
    }

    bool deleteNote(int index){
        if(index >= 0 and index < memory.size()) {
            auto end = this->memory.begin();
            for(int i = 0; i <= index; i++)
                end++;
            auto begin = end;
            begin--;

            this->memory[index]->remove();
            this->memory.erase(begin, end);
            return true;
        }
        return false;
    }

    bool editNote(int id, const string& title="", const string& content="") {
        if(id >= 0 and id < memory.size()){
            auto& note = this->memory[id];
            note->edit(title, content);
            return true;
        }
        return false;
    }

private:
    LsmL dataBase = LsmL("notesMemory.lsml");

    vector<Note*> memory;

    void scan();
};


#endif //BLOCCONOTE_NOTESMEMORY_H
