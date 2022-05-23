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

            for (auto note: field.second) {
                string noteName = note.first;
                string noteContent = note.second;

                folder.newNote(noteName, noteContent);
            }
            this->folders.push_back(folder);
        }
    }
}
