
#ifndef SRC_READINGFILE_READINGFILETEST_H_
#define SRC_READINGFILE_READINGFILETEST_H_

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readingFileTest() {

	vector<string> list;
	ifstream in_stream;
	string line;
	in_stream.open("../resources/hello/hello.txt");

	// Add all lines to the vector
	while (getline(in_stream, line))
		list.push_back(line);

	in_stream.close();

	// Print all the lines in the vector
	for (auto row : list)
		std::cout<<row<<"\n";

}

#endif /* SRC_READINGFILE_READINGFILETEST_H_ */
