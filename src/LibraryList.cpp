#include "LibraryList.h"
#include <algorithm>
#include <iostream>

// Добавление библиотеки в список
void LibraryList::addLibrary(std::shared_ptr<Library>& name){
    libraries.push_back(name);
}

// Сортировка списка библиотек
void LibraryList::sortLibrary() {
    std::sort(libraries.begin(), libraries.end(), 
                [](const std::shared_ptr<Library>& a, const std::shared_ptr<Library>& b) {
                    return a->getName() < b->getName();
                });
}

// Удаление дубликатов библиотек
// Если какие-то библиотеки объявлены и в FindPackage и в FetchContent 
void LibraryList::removeDuplicates() {
    auto last = std::unique(libraries.begin(), libraries.end(),
                            [](const std::shared_ptr<Library>& a, const std::shared_ptr<Library>& b) {
                             return a->getName() == b->getName();                            
                            });                       
    libraries.erase(last, libraries.end());
}

// Вывод списка библиотек
void LibraryList::displayLibraries() const {
    // Проверка наличия найденых библиотек
    if (libraries.empty()) {
        std::cout << "Libraries not found" << std::endl;
        return;
    }
    // Вывод списка библиотек если они есть
    std::cout << "Found " << libraries.size() << " library:" << std::endl;
    int k=0;
    for (const auto& library : libraries) {
        k+=1;
        library->display(k);
    }
}