//
// Created by Codes on 23/05/2022.
//

#ifndef BLOCCONOTE_FOLDERMANAGER_H
#define BLOCCONOTE_FOLDERMANAGER_H

#include "NoteFolder.h"
#include "LsmL.h"

class FolderManager {
public:
    FolderManager(string filePath);

    NoteFolder operator[](int index) {
        return folders[index];
    }

    void addNote(int folderIndex, string title, string content) {
        folders[folderIndex].newNote(title, content);
        folderDataBase.addAttr(folders[folderIndex].getFolderName(), title, content);
    }

    void editNote(int folderIndex, int noteIndex, string title, string content) {
        (folders[folderIndex]).editNote(noteIndex, title, content);
    }

    void addNewFolder(string folderName) {
        folderDataBase.addField(folderName);
        auto newFolder = NoteFolder(folderName);
        folders.push_back(newFolder);
    }

    void removeFolder(int index) {

    }

    int size() {
        return folders.size();
    }

private:
    vector<NoteFolder> folders;

    string filePath;

    LsmL folderDataBase = LsmL(this->filePath);
};


#endif //BLOCCONOTE_FOLDERMANAGER_H
