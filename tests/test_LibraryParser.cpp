#include <gtest/gtest.h>
#include "LibraryParser.h"
#include "StrUtils.h"
#include <fstream>

TEST(LibraryParserTest, IsFindPackageLine) {
    EXPECT_TRUE(isFindPackageLine("find_package(OpenCV REQUIRED)"));
    EXPECT_TRUE(isFindPackageLine("FIND_PACKAGE(Boost)"));
    EXPECT_TRUE(isFindPackageLine("find_package(Qt5) # комментарий"));
    EXPECT_FALSE(isFindPackageLine("fetchcontent_declare(gtest)"));
    EXPECT_FALSE(isFindPackageLine(""));
}

TEST(LibraryParserTest, IsFetchContentLine) {
    EXPECT_TRUE(isFetchContentLine("fetchcontent_declare(gtest)"));
    EXPECT_TRUE(isFetchContentLine("FetchContent_Declare(GLFW)"));
    EXPECT_TRUE(isFetchContentLine("fetchcontent_declare(sdl2) # комментарий"));
    EXPECT_FALSE(isFetchContentLine("find_package(OpenCV)"));
    EXPECT_FALSE(isFetchContentLine(""));
}

TEST(LibraryParserTest, ExtractLibraryNameFromFindPackage) {
    EXPECT_EQ(extractLibraryNameFromFindPackage("find_package(OpenCV)"), "OpenCV");
    EXPECT_EQ(extractLibraryNameFromFindPackage("find_package(Boost REQUIRED)"), "Boost");
    EXPECT_EQ(extractLibraryNameFromFindPackage("FIND_PACKAGE(Qt5)"), "Qt5");
    EXPECT_EQ(extractLibraryNameFromFindPackage("find_package(   OpenCV   )"), "OpenCV");
    EXPECT_EQ(extractLibraryNameFromFindPackage("find_package(OpenCV) # комментарий"), "OpenCV");
}

TEST(LibraryParserTest, ExtractLibraryNameFromFetchContent) {
    // Имя на той же строке
    EXPECT_EQ(extractLibraryNameFromFetchContent("fetchcontent_declare(gtest)", ""), "gtest");
    EXPECT_EQ(extractLibraryNameFromFetchContent("FetchContent_Declare(GLFW)", ""), "GLFW");
    
    // Имя на следующей строке
    std::string line1 = "fetchcontent_declare(";
    std::string line2 = "    gtest";
    EXPECT_EQ(extractLibraryNameFromFetchContent(line1, line2), "gtest");
    
    // С отступами и комментариями
    std::string line3 = "fetchcontent_declare(  OpenCV  ) # комментарий";
    EXPECT_EQ(extractLibraryNameFromFetchContent(line3, ""), "OpenCV");
}

TEST(LibraryParserTest, FindLibrariesIntegration) {
    // Создадим временный файл для тестирования
    std::string testCMakeLists = 
        "cmake_minimum_required(VERSION 3.10)\n"
        "project(TestProject)\n"
        "find_package(OpenCV REQUIRED)\n"
        "find_package(Boost 1.65 COMPONENTS system)\n"
        "fetchcontent_declare(\n"
        "    gtest\n"
        ")\n"
        "fetchcontent_declare(glfw) # комментарий\n"
        "add_executable(test main.cpp)\n";
    
    // Сохраняем во временный файл
    std::string tempFile = "test_cmakelists.txt";
    std::ofstream test_file(tempFile);
    test_file << testCMakeLists;
    test_file.close();
    
    // Тестируем
    LibraryList libraryList;
    findLibraries(tempFile, libraryList);
    
    // Проверяем вывод
    testing::internal::CaptureStdout();
    libraryList.displayLibraries();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Должны найти 4 библиотеки
    EXPECT_TRUE(output.find("Found 4 library") != std::string::npos);
    EXPECT_TRUE(output.find("Boost") != std::string::npos);
    EXPECT_TRUE(output.find("OpenCV") != std::string::npos);
    EXPECT_TRUE(output.find("gtest") != std::string::npos);
    EXPECT_TRUE(output.find("glfw") != std::string::npos);
    
    // Удаляем временный файл
    std::remove(tempFile.c_str());
}