//
// Created by Codes on 23/05/2022.
//

#include "FolderManager.h"

FolderManager::FolderManager() {
    auto dbContent = this->folderDataBase.read();

    for (auto fieldContainer: dbContent) {
        for (auto field: fieldContainer) {
            string folderName = field.first;
            NoteFolder folder(folderName);
            try {
                auto notes = this->folderDataBase.getField(folderName);
                for (auto note: notes) {
                    string noteName = note.first;

                    folder.newNote(noteName);
                }
            } catch (...) {}

            this->folders.push_back(folder);
        }
    }
}
