#include "gtest/gtest.h"
#include "../NotesManager.h"

NotesManager notesManager;

TEST(NotesManager, emptyManager) {
    EXPECT_EQ(notesManager.size(), 0);
}

TEST(NotesManager, newNote) {
    try {
        notesManager.newNote("firstNote", "firstNoteContent");
        SUCCEED();
    } catch(...) {
        FAIL();
    }
}

TEST(NotesManager, lockedNote) {
    try {
        notesManager.newNote("lockedNote", "lockedNoteContent", true);
    } catch (...) {
        FAIL();
    }

    EXPECT_TRUE(notesManager[1].isLocked());
}

TEST(NotesManager, favoriteNote) {
    try {
        notesManager.newNote("favoriteNote", "favoriteNoteContent", false, true);
    } catch (...) {
        FAIL();
    }

    EXPECT_TRUE(notesManager[2].isFavorite());
}

TEST(NotesManager, unlockNote) {
    try {
        notesManager.unlock(1);
    } catch (...) {
        FAIL();
    }

    EXPECT_FALSE(notesManager[1].isLocked());
}

/*
TEST(NotesManger, removeNoteFromFavorites) { // FIXME
    try {
        notesManager->removeFromFavorites(2);
    } catch (...) {
        FAIL();
    }

    EXPECT_FALSE((*notesManager)[2].isFavorite());
}*/

TEST(NotesManager, onlyGenericNotes) {
    notesManager.removeFromFavorites(2);
    EXPECT_EQ(notesManager.countLockedNotes(), 0);
    EXPECT_EQ(notesManager.countFavoriteNotes(), 0);
}


TEST(NotesManager, onlyLockedNotes) {
    notesManager.newNote("newNote1", "note1");
    notesManager.newNote("newNote2", "note2");

    for (int i = 0; i < notesManager.size(); i++) {
        notesManager.lock(i);
    }

    EXPECT_EQ(notesManager.countLockedNotes(), 5);
}


TEST(NotesManager, onlyFavoriteNotes) {
    for (int i = 0; i < notesManager.size(); i++) {
        notesManager.unlock(i);
        notesManager.favorite(i);
    }

    EXPECT_EQ(notesManager.countFavoriteNotes(), 5);
}

TEST(NotesManager, deleteAll) {
    notesManager.deleteAll();

    EXPECT_EQ(notesManager.size(), 0);
}
