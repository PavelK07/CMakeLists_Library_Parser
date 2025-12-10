#include "StrUtils.h"
#include <cctype>
#include <string>
#include <algorithm>

//  Удаление ненужных пробелов в начале и конце строки
std::string trim(const std::string& str) {
    // Позиция первого элемента не являющегося пробелом или переносом
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (std::string::npos == first) {
        return str;
    }
    // Позиция последнего элемента не являющегося пробелом или переносом
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

// Удаление комментакиев
std::string removeComments(const std::string& line) {
    // Проверка есть ли в строке комментарии
    size_t commentPos = line.find('#');
    // Если есть то возвращается субстрока до символа "#" 
    if (commentPos != std::string::npos) {
        return line.substr(0, commentPos);
    }
    // Если комментариев нет возвращается строка без изменений
    return line;
}

// Перевод всех букв в строке в нижний регистр
std::string toLowerCase(const std::string& str) {
    
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}