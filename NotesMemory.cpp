//
// Created by viato on 12/05/2022.
//

#include "NotesMemory.h"

void NotesMemory::scan() {
    if (this->size() > 0)
        this->memory_.clear();
    if(not dataBase_->isEmpty()){ // if database is not empty
        auto content = dataBase_->read(); // reads the content_ of the database
        for(auto& classcont:content){ // for each class coontainer in the vector

            for(auto& internalClass: classcont){ // for each pair in class container
                string noteTitle, noteContent, locked, favorite;
                noteTitle = internalClass.first; // notetitle is the first elememt of the pair
                auto attributeList = internalClass.second; // map of attributes
                for(auto& attribute : attributeList) { // gets pair from map
                    if(attribute.first == "content")
                        noteContent = attribute.second; // gets the attribute content_, ehich is the second element of the pair
                    if(attribute.first == "favorite")
                        favorite = attribute.second;
                    if(attribute.first == "locked")
                        locked = attribute.second;
                }
                this->newNote(noteTitle, noteContent, locked, favorite); // creates and stores new note
            }
        }
    }
}