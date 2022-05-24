//
// Created by Codes on 23/05/2022.
//

#include "FolderManager.h"

FolderManager::FolderManager(string filePath) : filePath(filePath) {
    auto dbContent = this->folderDataBase.read();

    for (auto fieldContainer: dbContent) {
        for (auto field: fieldContainer) {
            string folderName = field.first;
            NoteFolder folder(folderName);
            try {
                auto notes = this->folderDataBase.getField(folderName);
                for (auto note: notes) {
                    string noteName = note.first;
                    string noteContent = note.second;

                    folder.newNote(noteName, noteContent);
                }
            } catch (...) {}

            this->folders.push_back(folder);
        }
    }
}
