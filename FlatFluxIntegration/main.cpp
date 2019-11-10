#include "Integration.h"

#include <iostream>

int main(int argc,char** argv) {


	std::cout << argv[0] << std::endl;

	if (argc < 2) {
		std::cout << "The argument number is: " << argc << std::endl;
		std::cout << "You must special the 1) the output file path" << std::endl;
		system("pause");
		exit(1);
	}

	std::string outDataFilePath;

	outDataFilePath = std::string(argv[1]);

	Integration(outDataFilePath);

	std::cout << "End of the program" << std::endl;

	system("pause");

	return 0;
}