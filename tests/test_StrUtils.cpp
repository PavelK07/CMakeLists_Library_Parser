#include <gtest/gtest.h>
#include "StrUtils.h"

TEST(StrUtilsTest, Trim) {
    EXPECT_EQ(trim("  hello  "), "hello");
    EXPECT_EQ(trim("\t\nhello\r\n"), "hello");
    EXPECT_EQ(trim("no_spaces"), "no_spaces");
    EXPECT_EQ(trim(""), "");
    EXPECT_EQ(trim("   "), "");
}

TEST(StrUtilsTest, RemoveComments) {
    EXPECT_EQ(removeComments("find_package(OpenCV) # comment"), "find_package(OpenCV) ");
    EXPECT_EQ(removeComments("no comment"), "no comment");
    EXPECT_EQ(removeComments("# only comment"), "");
    EXPECT_EQ(removeComments("text # comment # another"), "text ");
}

TEST(StrUtilsTest, ToLowerCase) {
    EXPECT_EQ(toLowerCase("Find_Package"), "find_package");
    EXPECT_EQ(toLowerCase("FETCHCONTENT"), "fetchcontent");
    EXPECT_EQ(toLowerCase("AlreadyLower"), "alreadylower");
    EXPECT_EQ(toLowerCase("MIXED123"), "mixed123");
}