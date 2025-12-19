#pragma once

#include "Library.h"
#include "LibraryList.h"
#include <string>
#include <vector>

// Функции для парсинга

// Проверка что в строке определяется библиотека через find_package
bool isFindPackageLine(const std::string& line);

// Проверка что в строке определяется библиотека через fetchcontent_declare
bool isFetchContentLine(const std::string& line);

// Получение имени библиотеки определённой в find_package
std::string extractLibraryNameFromFindPackage(const std::string& line);

// Получение имени библиотеки определённой в fetchcontent_declare
std::string extractLibraryNameFromFetchContent(const std::string& line, const std::string& nextLine);

// Поиск библиотек в CMakeLists.txt
void findLibraries(const std::string& filepath, LibraryList& libraryList);