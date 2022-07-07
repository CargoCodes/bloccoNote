#include "gtest/gtest.h"
#include "../FolderManager.h"

FolderManager* folderManager = new FolderManager();

TEST(FolderManager, emptyManager) {
    EXPECT_EQ(folderManager->size(), 0);
}

TEST(FolderManager, newFolder) {
    try {
        folderManager->addNewFolder("firstFolder");
        SUCCEED();
    } catch (...) {
        FAIL();
    }

    EXPECT_EQ(folderManager->size(), 1);
}

TEST(FolderManager, addNoteToFolder) {
    try {
        folderManager->addNote(0, "firstNote");
        folderManager->addNote(0, "secondNote");
        folderManager->addNote(0, "thirdNote");
        SUCCEED();
    } catch(...) {
        FAIL();
    }

    EXPECT_EQ(folderManager->countNotes(0), 3);
}

TEST(FolderManager, countFolders) {
    try {
        folderManager->addNewFolder("secondFolder");
        folderManager->addNewFolder("thirdFolder");
        folderManager->addNewFolder("fourthFolder");
    } catch (...) {
        FAIL();
    }

    EXPECT_EQ(folderManager->size(), 4);
}

TEST(FolderManager, removeFolder) {
    try {
        folderManager->removeFolder(2);
    } catch (...) {
        FAIL();
    }

    EXPECT_EQ(folderManager->size(), 3);
}

TEST(FolderManager, removeAllFolders) {
    folderManager->deleteAll();

    EXPECT_EQ(folderManager->size(), 0);
}
