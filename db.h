#ifndef BLOCCONOTE_DB_H
#define BLOCCONOTE_DB_H

#include "NotesMemory.h"

class db {
public:
    static NotesMemory genericNotesMemory;
    static NotesMemory favoriteNotesMemory;
    static NotesMemory lockedNotesMemory;
};

#endif //BLOCCONOTE_DB_H
