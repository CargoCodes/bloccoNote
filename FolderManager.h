//
// Created by Codes on 23/05/2022.
//

#ifndef BLOCCONOTE_FOLDERMANAGER_H
#define BLOCCONOTE_FOLDERMANAGER_H

#include "NoteFolder.h"
#include "LsmL.h"

class FolderManager {
public:
    FolderManager(string filePath) : filePath(filePath) {}

    NoteFolder operator[](int index) {
        return folders[0];
    }

    void addNote(int folderIndex, string title, string content) {
        folders[folderIndex].newNote(title, content);
    }

    void editNote(int folderIndex, int noteIndex, string title, string content) {
        (folders[folderIndex]).editNote(noteIndex, title, content);
    }

private:
    vector<NoteFolder> folders;

    string filePath;

    LsmL folderDataBase = LsmL(this->filePath);
};


#endif //BLOCCONOTE_FOLDERMANAGER_H
