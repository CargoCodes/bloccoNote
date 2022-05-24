#ifndef BLOCCONOTE_NOTESMEMORY_H
#define BLOCCONOTE_NOTESMEMORY_H

#include "LsmL.h"
#include "Note.h"
#include <vector>

class NotesMemory {
public:

    explicit NotesMemory(const string& filePath, bool favorite = false, bool locked = false) :
            filePath_(filePath), favorites_(favorite), locked_(locked) {
        this->scan();
    }

    void newNote(const string& title, const string& content) {
        Note *newNote = new Note(title, content, &dataBase_);
        if(locked_)
            newNote->lock();
        if (favorites_)
            newNote->favorite();
        newNote->save();
        this->memory_.push_back(newNote);
    }

    Note operator[](int index) {
        return *memory_[index];
    }


    Note operator[](string title) {
        for (auto note: memory_) {
            if (note->getTitle() == title)
                return *note;
        }
        throw runtime_error("Note not found");
    }

    int size() {
        return memory_.size();
    }

    bool deleteNote(int index);

    bool deleteNote(string title);

    bool editNote(int id, const string &title = "", const string &content = "") {
        if (not locked_) {
            if (id >= 0 and id < memory_.size()) {
                auto &note = this->memory_[id];
                note->edit(title, content);
                return true;
            }
            return false;
        }
        return false;
    }

    bool editNote(const std::string &noteTitle, const string &title = "", const string &content = "") {
        int index;
        bool found = false;
        for (int i = 0; i < this->size(); i++) {
            if (this->memory_[i]->getTitle() == noteTitle) {
                found = true;
                index = i;
                break;
            }
        }
        if (found)
            editNote(index, title, content);
        else
            return false;
        return true;
    }

    void transferNote(int index, NotesMemory *destination) {
        destination->newNote(this->memory_[index]->getTitle(), this->memory_[index]->getContent());
        this->deleteNote(index);
    }

    void transferNote(string title, NotesMemory *destination) {
        destination->newNote(this->operator[](title).getTitle(), this->operator[](title).getContent());
        this->deleteNote(title);
    }

    void scan();

private:

    string filePath_;
    bool favorites_;
    bool locked_;

    LsmL dataBase_ = LsmL(this->filePath_);

    vector<Note*> memory_;
};

#endif //BLOCCONOTE_NOTESMEMORY_H