//
// Created by Codes on 23/05/2022.
//

#ifndef BLOCCONOTE_FOLDERMANAGER_H
#define BLOCCONOTE_FOLDERMANAGER_H

#include "NoteFolder.h"
#include "LsmL.h"

/*
 * Rsponsabilities:
 * - interact with the folder's dataBase (add, remove, edit, read)
 * - hadle operations on folders
 * - interact with the GUI
 * - observer class between folders and GUI
 */

class FolderManager {
public:
    FolderManager();

    NoteFolder operator[](int index) {
        return folders[index];
    }

    void addNote(int folderIndex, string title) {
        if (checkIndex(folderIndex)) {
            folderDataBase.addAttr(folders[folderIndex].getFolderName(), title, "");
            folders[folderIndex].newNote(title);
            updated = true;
        }
    }

    void editNote(int folderIndex, string noteTitle, string newTitle) {
        if (checkIndex(folderIndex)) {
            string folderName = folders[folderIndex].getFolderName();
            folderDataBase.editAttr(folderName, noteTitle, newTitle);
            updated = true;
        }
    }

    void editNote(string folderName, string noteTitle, string newTitle) {
        for (auto folder: folders) {
            if (folder.getFolderName() == folderName) {
                folder.editNote(noteTitle, newTitle);
                folderDataBase.editAttr(folderName, noteTitle, newTitle, "");
                updated = true;
            }
        }
    }

    void deleteNote(string title) {
        auto folderName = this->isIn(title);
        if (not folderName.empty()) {
            folderDataBase.removeAttr(folderName, title);
            updated = true;
        }
    }

    void addNewFolder(string folderName) {
        folderDataBase.addField(folderName);
        auto newFolder = NoteFolder(folderName);
        folders.push_back(newFolder);
        updated = true;
    }

    void removeFolder(int index) {
        if (checkIndex(index)) {
            auto end = this->folders.begin();
            for (int i = 0; i <= index; i++)
                end++;
            auto begin = end;
            begin--;
            folderDataBase.removeField(folders[index].getFolderName());
            this->folders.erase(begin, end);
            this->updated = true;
        }
    }

    int size() {
        return folders.size();
    }

    string isIn(string noteTitle) {
        for (auto folder: folders) {
            if (folder.isIn(noteTitle))
                return folder.getFolderName();
        }
        return "";
    }

    bool contains(string title) {
        for (auto folder: folders) {
            if (folder.isIn(title))
                return true;
        }
        return false;
    }

    bool isUpdated() {
        return this->updated;
    }

private:
    vector<NoteFolder> folders;

    string filePath = "foldersDb.lsml";

    bool updated = false;

    LsmL folderDataBase = LsmL(this->filePath);

    bool checkIndex(int index) {
        if (index >= 0 and index < folders.size()) {
            return true;
        }
        return false;
    }
};


#endif //BLOCCONOTE_FOLDERMANAGER_H
