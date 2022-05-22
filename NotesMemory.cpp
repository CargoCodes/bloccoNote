#include "NotesMemory.h"

void NotesMemory::scan() {
    if (this->size() > 0)
        this->memory_.clear();
    if(not dataBase_.isEmpty()){ // if database is not empty
        auto content = dataBase_.read(); // reads the content_ of the database
        for(auto& classcont:content){ // for each class coontainer in the vector
            for(auto& internalClass: classcont){ // for each pair in class container
                string noteTitle, noteContent;
                noteTitle = internalClass.first; // notetitle is the first elememt of the pair
                auto attributeList = internalClass.second; // map of attributes
                for (auto &attribute: attributeList)  // gets pair from map
                    noteContent = attribute.second;
                this->newNote(noteTitle, noteContent); // creates and stores new note
            }
        }
    }
}

bool NotesMemory::deleteNote(int index) {
    if (index >= 0 and index < memory_.size()) {
        auto end = this->memory_.begin();
        for (int i = 0; i <= index; i++)
            end++;
        auto begin = end;
        begin--;
        this->memory_[index]->remove();
        this->memory_.erase(begin, end);
        return true;
    }
    return false;
}