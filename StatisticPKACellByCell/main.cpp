#include "Statistic.h"
#include <iostream>

int main(int argc, char** argv) {

	std::cout << argv[0] << std::endl;

	if (argc < 3) {
		std::cout << "The argument number is: " << argc << std::endl;
		std::cout << "You must special the 1) the original file path" << std::endl;
		std::cout << "You must special the 2) the output file path" << std::endl;
		system("pause");
		exit(1);
	}

	std::string originalDataFilePath;
	std::string outDataFilePath;

	originalDataFilePath = std::string(argv[1]);
	outDataFilePath = std::string(argv[2]);

	Statistic::GetInstance()->StartStatistic(originalDataFilePath,outDataFilePath);

	std::cout << "End of the program" << std::endl;

	return 0;
}