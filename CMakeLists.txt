cmake_minimum_required(VERSION 3.10)
project(CMakeListsParser 
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# Загружаем googletest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Загружаем все зависимости
FetchContent_MakeAvailable(googletest)

enable_testing()

# Подключаем заголовочные файлы
include_directories(${CMAKE_SOURCE_DIR}/include)

# Создаем основной исполняемый файл
add_executable(CMakeListsParser
    src/main.cpp
    src/FileReader.cpp
    src/LibraryList.cpp
    src/LibraryParser.cpp
    src/Library.cpp
    src/StrUtils.cpp
)

# Устанавливаем выходное имя
set_target_properties(CMakeListsParser PROPERTIES OUTPUT_NAME "CMakeListsParser")

# Создаем исполняемый файл для тестов
add_executable(CMakeListsParserTests
    tests/test_main.cpp
    tests/test_StrUtils.cpp
    tests/test_Library.cpp
    tests/test_LibraryList.cpp
    tests/test_LibraryParser.cpp
    tests/test_FileReader.cpp
)

# Линкуем тесты с основными исходными файлами
target_link_libraries(CMakeListsParserTests
    PRIVATE 
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
)

# Тестовой программе также нужны исходные файлы основного проекта
target_sources(CMakeListsParserTests PRIVATE
    src/FileReader.cpp
    src/LibraryList.cpp
    src/LibraryParser.cpp
    src/Library.cpp
    src/StrUtils.cpp
)

# Настраиваем директории include для тестов
target_include_directories(CMakeListsParserTests
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}/include
        ${gtest_BINARY_DIR}/include
)

# Настраиваем директории include для основного проекта
target_include_directories(CMakeListsParser
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Добавляем тесты в CTest
include(GoogleTest)
gtest_discover_tests(CMakeListsParserTests)

# Устанавливаем устанавливаемую версию
install(TARGETS CMakeListsParser
    RUNTIME DESTINATION bin
)

# Добавляем тесты
add_test(NAME TestParser COMMAND CMakeListsParser ${CMAKE_SOURCE_DIR}/CMakeLists.txt)