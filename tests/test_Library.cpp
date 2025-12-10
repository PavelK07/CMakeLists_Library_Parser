#include <gtest/gtest.h>
#include "Library.h"

TEST(LibraryTest, ConstructorAndGetter) {
    Library lib("TestLibrary");
    EXPECT_EQ(lib.getName(), "TestLibrary");
    
    Library lib2("Another");
    EXPECT_EQ(lib2.getName(), "Another");
}