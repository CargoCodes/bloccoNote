//
// Created by viato on 12/05/2022.
//

#include "NotesMemory.h"

void NotesMemory::scan() {
    if(not dataBase.isEmpty()){ // if database is not empty
        auto content = dataBase.read(); // reads the content of the database
        for(auto& classcont:content){ // for each class coontainer in the vector
            for(auto& internalClass: classcont){ // for each pair in class container
                auto noteTitle = internalClass.first; // notetitle is the first elememt of the pair
                cout << noteTitle << endl;
                auto attributeList = internalClass.second; // map of attributes
                string noteContent; // initialiser
                for(auto& attribute : attributeList) { // gets pair from map
                    noteContent = attribute.second; // gets the attribute content, ehich is the second element of the pair
                }
                this->newNote(noteTitle, noteContent); // creates and stores new note
            }
        }
    }
}