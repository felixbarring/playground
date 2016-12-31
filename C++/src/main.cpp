
#include <iostream>

#include "readingFile/readingFileTest.h"
#include "writingFile/writingFile.h"
#include "interfaces/interfaceTest.h"

int main()
{
	std::cout << "Learning C++\n";

	std::cout << "\n" << "Reading File Test \n\n";
	readingFileTest();

	std::cout << "\n" << "Writing File Test \n\n";
	writingFileTest();

	std::cout << "\n" << "Interface Test \n\n";
	interfaceTest();


}
