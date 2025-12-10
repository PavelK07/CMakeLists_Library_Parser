#include "LibraryList.h"
#include "FileReader.h"
#include "LibraryParser.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    std::string filepath = getCorrectFilePath(argc,argv);

    std::cout << "--------------------------------------" << std::endl;
    LibraryList libraryList;
    findLibraries(filepath, libraryList);
    libraryList.displayLibraries();
    std::cout << "--------------------------------------" << std::endl;

    return 0;
}