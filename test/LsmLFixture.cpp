//
// Created by Codes on 02/06/2022.
//
#include "../LsmL.h"
#include "gtest/gtest.h"

class LsmLSuite : public ::testing::Test {
protected:
    void setUp() {

    }

    LsmL lsml = LsmL("testFile.lsml");
};