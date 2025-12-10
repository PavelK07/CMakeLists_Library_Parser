#pragma once

#include <string>
#include <vector>

// Функции для работы с файлом

// Получение списка строк
std::vector<std::string> readLines(const std::string& filepath);    

// Получение корректного пути к файлу
std::string getCorrectFilePath(int& argc, char* argv[]);

// Проверка существования файла
bool fileExists(const std::string& filepath);