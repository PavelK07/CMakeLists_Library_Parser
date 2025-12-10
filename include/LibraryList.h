#pragma once

#include "Library.h"
#include <string>
#include <vector>
#include <memory>

class LibraryList {

    private:
        std::vector<std::shared_ptr<Library>> libraries; // Список библиотек

    public:
        // Добавление библиотеки
        void addLibrary(std::shared_ptr<Library>& name);
        // Сортировка библиотек
        void sortLibrary();
        // Удаление дубликатов библиотек
        //на случай если какие-то библиотеки объявлены и в FindPackage и в FetchContent
        void removeDuplicates();
        // Вывод списка библиотек
        void displayLibraries() const;
};