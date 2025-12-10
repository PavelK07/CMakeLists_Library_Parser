#include <gtest/gtest.h>
#include "FileReader.h"
#include <fstream>
#include <cstdio>
#include <sstream>


TEST(FileReaderTest, FileExists) {
    // Создаем временный файл
    std::string tempFile = "test_file.txt";
    std::ofstream test_file(tempFile);
    test_file << "test content";
    test_file.close();
    
    EXPECT_TRUE(fileExists(tempFile));
    EXPECT_FALSE(fileExists("non_existent_file.txt"));
    
    // Удаляем временный файл
    std::remove(tempFile.c_str());
}

TEST(FileReaderTest, ReadLines) {
    // Создаем временный файл с несколькими строками
    std::string tempFile = "test_lines.txt";
    std::ofstream test_file(tempFile);
    test_file << "Line 1\nLine 2\nLine 3\n";
    test_file.close();
    
    std::vector<std::string> lines = readLines(tempFile);
    
    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "Line 1");
    EXPECT_EQ(lines[1], "Line 2");
    EXPECT_EQ(lines[2], "Line 3");
    
    // Удаляем временный файл
    std::remove(tempFile.c_str());
}

TEST(FileReaderTest, ReadLinesNonexistentFile) {
    EXPECT_THROW(readLines("non_existent_file.txt"), std::runtime_error);
}

// Временная замена std::cin
class CinRedirect {
public:
    CinRedirect(std::istream& new_input) : old(std::cin.rdbuf(new_input.rdbuf())) {}
    ~CinRedirect() { std::cin.rdbuf(old); }
    
private:
    std::streambuf* old;
};

TEST(GetCorrectFilePathTest, GetCorrectFilePathUsesCommandLineArg) {
    // Подготовка аргументов командной строки
    int argc = 2;
    char arg1[] = "test_program";
    char arg2[] = "existing_file.txt";
    char* argv[] = {arg1, arg2};

    // Создаем временный файл для теста
    std::string tempFile = "existing_file.txt";
    std::ofstream test_file(tempFile);
    test_file << "test content";
    test_file.close();
    
    std::string result = getCorrectFilePath(argc, argv);
    EXPECT_EQ(result, "existing_file.txt");
    
    // Удаляем временный файл
      std::remove(tempFile.c_str());
}

TEST(GetCorrectFilePathTest, GetCorrectFilePathAsksForInputWhenFileNotFound) {
    int argc = 1;
    char arg1[] = "test_program";
    char* argv[] = {arg1};
    
    // Создаем строковый поток для имитации ввода пользователя
    std::stringstream input_stream;
    input_stream << "existing_file.txt\n";
    
    // Перенаправляем cin
    CinRedirect redirect(input_stream);

    // Создаем временный файл
    std::string tempFile = "existing_file.txt";
    std::ofstream test_file(tempFile);
    test_file << "test content";
    test_file.close();
    
    std::string result = getCorrectFilePath(argc, argv);
    EXPECT_EQ(result, "existing_file.txt");
    
    std::remove(tempFile.c_str());
}

TEST(GetCorrectFilePathTest, GetCorrectFilePathMultipleAttemptsUntilSuccess) {
    int argc = 1;
    char arg1[] = "test_reader";
    char* argv[] = {arg1};
    
    // Имитируем несколько неудачных попыток
    std::stringstream input_stream;
    input_stream << "file1.txt\nfile2.txt\nexisting_file.txt\n";
    
    CinRedirect redirect(input_stream);
    
    // Создаем только последний файл
    std::string tempFile = "existing_file.txt";
    std::ofstream test_file(tempFile);
    test_file << "test content";
    test_file.close();
    
    std::string result = getCorrectFilePath(argc, argv);
    EXPECT_EQ(result, "existing_file.txt");
    
    std::remove(tempFile.c_str());
}