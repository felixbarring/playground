
#ifndef SRC_WRITINGFILE_READINGFILETEST_H_
#define SRC_WRITINGFILE_READINGFILETEST_H_

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

bool fileExists(string& fileName) {
    ifstream infile(fileName);
    return infile.good();
}

void writingFileTest() {

	string fileName = "../resources/hello/derp.txt";

	if (!fileExists(fileName)) {
		cout << "Writing to file \n";
		ofstream outStream(fileName);
		outStream << "Hello Output\n";
		outStream.close();
	} else {
		cout << "File already exists";
	}

}



#endif /* SRC_READINGFILE_READINGFILETEST_H_ */
