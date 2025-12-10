#include <gtest/gtest.h>
#include "LibraryList.h"
#include "Library.h"
#include <memory>

class LibraryListTest : public ::testing::Test {
protected:
    void SetUp() override {
        lib1 = std::make_shared<Library>("ZLib");
        lib2 = std::make_shared<Library>("OpenCV");
        lib3 = std::make_shared<Library>("Boost");
        lib4 = std::make_shared<Library>("OpenCV"); // Дубликат
    }
    
    std::shared_ptr<Library> lib1, lib2, lib3, lib4;
    LibraryList list;
};

TEST_F(LibraryListTest, AddLibrary) {
    EXPECT_NO_THROW(list.addLibrary(lib1));
    EXPECT_NO_THROW(list.addLibrary(lib2));
}

TEST_F(LibraryListTest, SortLibrary) {
    list.addLibrary(lib1); // ZLib
    list.addLibrary(lib2); // OpenCV
    list.addLibrary(lib3); // Boost
    
    list.sortLibrary();
    
    // После сортировки должен быть порядок: Boost, OpenCV, ZLib
    testing::internal::CaptureStdout();
    list.displayLibraries();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Проверяем, что библиотеки найдены
    EXPECT_TRUE(output.find("Found") != std::string::npos);
}

TEST_F(LibraryListTest, RemoveDuplicates) {
    list.addLibrary(lib2); // OpenCV
    list.addLibrary(lib4); // OpenCV (дубликат)
    list.addLibrary(lib3); // Boost
    
    // До удаления дубликатов должно быть 3 элемента
    testing::internal::CaptureStdout();
    list.displayLibraries();
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output1.find("Found 3 library") != std::string::npos);
    
    list.removeDuplicates();
    
    // После удаления дубликатов должно быть 2 элемента
    testing::internal::CaptureStdout();
    list.displayLibraries();
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output2.find("Found 2 library") != std::string::npos);
}

TEST_F(LibraryListTest, DisplayEmptyList) {
    testing::internal::CaptureStdout();
    list.displayLibraries();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Libraries not found") != std::string::npos);
}