//
// Created by Codes on 22/05/2022.
//

#include "db.h"

NotesMemory db::genericNotesMemory = NotesMemory("genericNotes.lsml", true);
NotesMemory db::favoriteNotesMemory = NotesMemory("favoriteNotes.lsml", false, true);
NotesMemory db::lockedNotesMemory = NotesMemory("lockedNotes.lsml", false, false, true);