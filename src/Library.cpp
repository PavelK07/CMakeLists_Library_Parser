#include "Library.h"
#include <iostream>

// Вывод библиотеки с номером по списку
void Library::display(int k) const {
    std::cout << k << ". " << name << std::endl;
    std::cout << std::endl;
}

// Простой геттер
std::string Library::getName() const {
    return name;
}