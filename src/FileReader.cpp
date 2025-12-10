#include "FileReader.h"
#include <iostream>
#include <fstream>


// Проверка существования файла
bool fileExists(const std::string& filepath) {
    std::ifstream file(filepath);
    return file.good();
}

std::string getCorrectFilePath(int& argc, char* argv[]){
    // Если в аргументах командной строки не указан путь к CMakeLists.txt, предпологаем что он в той же директории 
    std::string filepath = "CMakeLists.txt";
    if (argc > 1) {
        filepath = argv[1];
    } 
    // Если файл не найден просим указать к нему путь
    while (!fileExists(filepath)) {
        std::cerr << "Error: File " << filepath << " does not exist! Write the path to CMakeLists.txt: " << std::endl;
        std::cin >> filepath;
    }
    return filepath;
}

// Получение списка строк
std::vector<std::string> readLines(const std::string& filepath) {
    std::vector<std::string> lines;
    std::ifstream file(filepath);
    
    // Проверка что файл открылся
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }

    // Читение строк из файла в вектор
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    return lines;
}