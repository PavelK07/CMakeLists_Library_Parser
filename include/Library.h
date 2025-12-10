#pragma once

#include <string>

class Library {
private:
    const std::string name;

public:
    // Конструктор
    Library(const std::string& n): name(n) {}

    // Конструктор копирования
    Library(const Library& other) : name(other.name) {
    }
    
    // Деструктор
    ~Library() {  
    }

    // Вывод библиотеки с номером по списку
    void display(int k) const;

    // Получение имени библиотеки
    std::string getName() const;
};