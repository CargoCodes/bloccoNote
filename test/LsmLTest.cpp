#include "gtest/gtest.h"

#include "../LsmL.h"

#include <map>
#include <iostream>
#include <vector>

LsmL lsml = LsmL("/Users/Codes.py/CLionProjects/bloccoNote/test/testFile.lsml");

TEST(LsmL, EmptyTest) {
    EXPECT_TRUE(lsml.isEmpty());
}

TEST(LsmL, addField) {
    EXPECT_TRUE(lsml.addField("field1"));
    EXPECT_FALSE(lsml.addField("field1"));
}

TEST(LsmL, addAttr) {
    EXPECT_TRUE(lsml.addAttr("field1", "attribute1", "1"));
    try {
        lsml.addAttr("Field2", "attribute1", "1");
        FAIL();
    } catch (LsmL::FieldNotFoundError &e) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
    EXPECT_FALSE(lsml.addAttr("field1", "attribute1", "1"));
}

TEST(LsmL, getField) {
    std::map<std::string, std::string> expectedResult;
    expectedResult.insert(std::pair<std::string, std::string>("attribute1", "1"));

    auto map = lsml.getField("field1");

    for (auto attr: map) {
        cout << attr.first << " -> " << attr.second << endl;
    }

    EXPECT_EQ(lsml.getField("field1"), expectedResult);
    try {
        lsml.getField("field2");
        FAIL();
    } catch (LsmL::FieldNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
}

TEST(LsmL, getAttr) {
    cout << lsml.getAttr("field1", "attribute1") << endl;
    EXPECT_EQ(lsml.getAttr("field1", "attribute1"), "1");

    /*try {
        lsml.getAttr("field1", "attr2");
        FAIL();
    } catch(LsmL::AttributeNotFoundError) {
        SUCCEED();
    } catch (...){
        FAIL();
    }*/

    try {
        lsml.getAttr("field2", "attr");
        FAIL();
    } catch (LsmL::FieldNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }

}


TEST(LsmL, editField) {
    EXPECT_TRUE(lsml.editField("field1", "Field1"));

    try {
        lsml.editField("field2", "Field2");
        FAIL();
    } catch (LsmL::FieldNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
}

TEST(LsmL, editAttr) {
    EXPECT_TRUE(lsml.editAttr("Field1", "attribute1", "Attribute1", "first"));

    try {
        lsml.editAttr("Field1", "attr2", "Attr2");
        FAIL();
    } catch (LsmL::AttributeNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
}

TEST(LsmL, removeAttr) {
    EXPECT_TRUE(lsml.removeAttr("Field1", "Attribute1"));

    try {
        lsml.removeAttr("Field1", "attr2");
        FAIL();
    } catch (LsmL::AttributeNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
}

TEST(LsmL, removeField) {
    EXPECT_TRUE(lsml.removeField("Field1"));

    try {
        lsml.removeField("field2");
        FAIL();
    } catch (LsmL::FieldNotFoundError) {
        SUCCEED();
    } catch (...) {
        FAIL();
    }
}

TEST(LsmL, clearFile) {
    EXPECT_TRUE(lsml.clearFile());
}
