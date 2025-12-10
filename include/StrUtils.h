#pragma once

#include <string>
#include <cctype>
#include <algorithm>

// Функции для работы со строками

// Удаление не нужных пробелов в начале и конце строки
std::string trim(const std::string& str);

// Удаление комментакиев
std::string removeComments(const std::string& line);

// Перевод всех букв в строке в нижний регистр
std::string toLowerCase(const std::string& str);