#ifndef BLOCCONOTE_NOTESMEMORY_H
#define BLOCCONOTE_NOTESMEMORY_H


#include "LsmL.h"
#include "Note.h"
#include <vector>
#include "utils.h"

class NotesMemory {
public:
    explicit NotesMemory(const string& filePath, bool generic = true, bool favorite = false, bool locked = false) :
            filePath_(filePath), generic_(generic), favorites_(favorite), locked_(locked) {
        this->scan();
    }

    void addNote(Note* note) {
        if (generic_)
            note->updateGenericDataBase(dataBase_);
        else if(favorites_)
            note->updateFavoritesDatabase(dataBase_);
        else if(locked_)
            note->updateLockedDataBase(dataBase_);
        note->save();
        this->memory_.push_back(note);
    }

    void newNote(const string& title, const string& content, const string& locked="false", const string& favorite="false") {
        Note* newNote = new Note(title, content);
        if (this->generic_)
            newNote->updateGenericDataBase(dataBase_);
        else if(this->favorites_)
            newNote->updateFavoritesDatabase(dataBase_);
        else if(this->locked_)
            newNote->updateLockedDataBase(dataBase_);
        if(locked == "true")
            newNote->lock();
        if(favorite == "true")
            newNote->favorite();
        newNote->save();
        this->memory_.push_back(newNote);
    }

    Note operator[](int index) {
        return *memory_[index];
    }

    int size() {
        return memory_.size();
    }

    LsmL* getDataBase() const {
        return this->dataBase_;
    }

    bool deleteNote(int index){
        if(index >= 0 and index < memory_.size()) {
            auto end = this->memory_.begin();
            for(int i = 0; i <= index; i++)
                end++;
            auto begin = end;
            begin--;

            this->memory_[index]->remove();
            this->memory_.erase(begin, end);
            return true;
        }
        return false;
    }

    bool locallyDeletenote(int index) {
        if(index >= 0 and index < memory_.size()) {
            auto end = this->memory_.begin();
            for(int i = 0; i <= index; i++)
                end++;
            auto begin = end;
            begin--;
            if (generic_)
                this->deleteNote(index);
            else if (favorites_){

            } else if (locked_) {
                this->memory_[index]->removeFromLocked();
                this->memory_.erase(begin, end);
            }
            return true;
        }
        return false;
    }

    bool editNote(int id, const string& title="", const string& content="") {
        if(id >= 0 and id < memory_.size()){
            auto& note = this->memory_[id];
            note->edit(title, content);
            return true;
        }
        return false;
    }

    void transferNote(int index, NotesMemory& newMemory) {
        auto requestedNote = this->memory_[index];
        newMemory.addNote(requestedNote);
    }

    void scan();

private:
    string filePath_;
    bool generic_;
    bool favorites_;
    bool locked_;

    LsmL* dataBase_ = new LsmL(this->filePath_);

    vector<Note*> memory_;
};


#endif //BLOCCONOTE_NOTESMEMORY_H
