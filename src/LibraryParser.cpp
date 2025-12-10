#include "LibraryParser.h"
#include "FileReader.h"
#include "LibraryList.h"
#include "StrUtils.h"
#include <algorithm>
#include <iostream>

// Проверка что в строке определяется библиотека через find_package
bool isFindPackageLine(const std::string& line) {
    // Удаление комментариев и перевод букв в нижний регистр
    std::string cleanLine = removeComments(line);
    std::string lowerLine = toLowerCase(cleanLine);
    // Проверяем наличие find_package
    return lowerLine.find("find_package(") != std::string::npos;
}

// Проверка что в строке определяется библиотека через fetchcontent_declare
bool isFetchContentLine(const std::string& line) {
    // Удаление комментариев и перевод букв в нижний регистр
    std::string cleanLine = removeComments(line);
    std::string lowerLine = toLowerCase(cleanLine);
    // Проверяем FetchContent
    return lowerLine.find("fetchcontent_declare(") != std::string::npos;
}

// Получение имени библиотеки определённой в find_package
std::string extractLibraryNameFromFindPackage(const std::string& line) {
    // Удаление комментариев и перевод букв в нижний регистр
    std::string cleanLine = removeComments(line);
    std::string lowerLine = toLowerCase(cleanLine);

    // Определяем позицию начала имени библиотеки. 13 - длина "find_package("
    size_t nameStart = lowerLine.find("find_package(") + 13;
    // Определяем начало имени библиотеки
    while (nameStart < cleanLine.length() && 
            (cleanLine[nameStart] == ' ' || cleanLine[nameStart] == '\t')) {
        nameStart++;
    }
    // Определяем конец имени библиотеки
    size_t nameEnd = nameStart;
    while (nameEnd < line.length() && line[nameEnd] != ' ' && line[nameEnd] != ')' 
            && line[nameEnd] != '\n' && line[nameEnd] != '\r') {
        nameEnd++;
    }

    return trim(line.substr(nameStart, nameEnd - nameStart));
}

// Получение имени библиотеки определённой в fetchcontent_declare
std::string extractLibraryNameFromFetchContent(const std::string& line, const std::string& nextLine) {
    // Удаление комментариев и перевод букв в нижний регистр
    std::string cleanLine = removeComments(line);
    std::string lowerLine = toLowerCase(cleanLine);

    // Определяем позицию начала имени библиотеки. 21 - длина "fetchcontent_declare("
    size_t nameStart = lowerLine.find("fetchcontent_declare(") + 21; 
    // Определяем начало имени библиотеки
    while (nameStart < cleanLine.length() && 
            (cleanLine[nameStart] == ' ' || cleanLine[nameStart] == '\t')) {
        nameStart++;
    }
    // Определяем конец имени библиотеки
    size_t nameEnd = nameStart;
    while (nameEnd < cleanLine.length() && cleanLine[nameEnd] != ' ' && cleanLine[nameEnd] != ')' 
            && cleanLine[nameEnd] != '\n' && line[nameEnd] != '\r') {
        nameEnd++;
    }
    
    // Если имя библиотеки в строке с FetchContent_Declare
    if (nameEnd > nameStart) {
        return trim(cleanLine.substr(nameStart, nameEnd - nameStart));
    } else {
    // Если имя библиотеки на следующей строке т.е. nameEnd = nameStart = std::string::npos 
        // Удаление пробелов слева и стправа на следующей строке
        std::string trimedNextLine = trim(nextLine);
        // Начало имени библиотеки 0 позиция
        // Определение конца имени библиотеки
        size_t nameEnd = 0;
        while (nameEnd < trimedNextLine.length() && trimedNextLine[nameEnd] != ' ' && 
                trimedNextLine[nameEnd] != ')' && trimedNextLine[nameEnd] != '\n' && line[nameEnd] != '\r') {
        nameEnd++;
        }

        return trimedNextLine.substr(0, nameEnd);
    }
    return "";
}

// Поиск библиотек в CMakeLists.txt
void findLibraries(const std::string& filepath, LibraryList& libraryList) {
    
    // Попытка составить список строк из файла
    std::vector<std::string> lines;
    try {
        lines = readLines(filepath);
    } catch (const std::exception& e) {
        std::cerr << "Error reading file: " << e.what() << std::endl;
        return;
    }
    
    // Последовательная проверка строк
    for (size_t i = 0; i < lines.size(); ++i) {
        std::string line = lines[i];

        // Проверка что в строке есть find_package
        if (isFindPackageLine(line)) {
            // Получение имени библиотеки
            std::string libName = extractLibraryNameFromFindPackage(line);
            //добавление имени библиотеки в список библиотек
            if (!libName.empty()) {
                auto library = std::make_shared<Library>(libName);
                libraryList.addLibrary(library);
            }
        }
        // Проверка что в строке есть FetchContent
        else if (isFetchContentLine(line)) {
            // Получение имени библиотеки
            std::string nextLine = lines[i+1];  // На случай если имя библиотеки на следующей строке
            std::string libName = extractLibraryNameFromFetchContent(line,nextLine);
            //добавление имени библиотеки в список библиотек
            if (!libName.empty()) {
                auto library = std::make_shared<Library>(libName);
                libraryList.addLibrary(library);
            }
        }
    }
    // Сортировка списка библиотек
    libraryList.sortLibrary();
    // Удаление дубликатов библиотек
    libraryList.removeDuplicates();
}