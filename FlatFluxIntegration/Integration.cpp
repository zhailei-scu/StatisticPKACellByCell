#include "Integration.h"
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>

void Integration(const std::string& OutputFilePath) {
	//---Local Vars---
	int CellLimit;
	double Result;
	double param_a;
	double param_b;
	int NP;
	std::stringstream ss;
	std::string OutFile;
	std::fstream ofs;
	int outwidth;
	int iInterval;
	//---Body---

	outwidth = 20;

	param_a = 0.90232;
	param_b = -1.7623;
	NP = 100000;

	Result = 0;

	CellLimit = 50000;



	if (OutputFilePath.length() > 0) {

		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "IntegrationCellByCell_New.txt";

		ss >> OutFile;

	}
	else {
		ss.clear();

		ss.str("");

		ss << "IntegrationCellByCell_New.txt";

		ss >> OutFile;

	}

	ofs.open(OutFile,std::ios::out | std::ios::ate);


	ofs << std::setw(outwidth) << "TotalZoneNumber"
		<< std::setw(outwidth) << "NParticle"
		<< std::setw(outwidth) << "CumulativeNP"
		<< std::setw(outwidth) << "CumulativeRatio"
		<< std::endl;

	/*
	for (int CL = 0; CL <= CellLimit; CL++) {
		Result = 0;

		for (int j = -CL; j <= CL; j++) {

			for (int i = -CL; i <= CL; i++) {

				ZoneID = std::max(abs(i), abs(j));
				Result += param_a*NP*std::pow(ZoneID + 1, param_b);
			}
		}


		ofs << std::setw(outwidth) << CL
			<< std::setw(outwidth) << NP
			<< std::setw(outwidth) <<std::setiosflags(std::ios::scientific) << Result
			<< std::endl;

	}
	*/

	
	for (int ZoneID = 0; ZoneID <= CellLimit; ZoneID++) {

		for (int j = -ZoneID; j <= ZoneID; j = j++) {

			if (j == -ZoneID || j == ZoneID) {
				iInterval = 1;
			}
			else {
				iInterval = 2 * ZoneID;
			}

			for (int i = -ZoneID; i <= ZoneID; i = i + iInterval) {

				ZoneID = std::max(abs(i), abs(j));
				Result += param_a * NP*std::pow(ZoneID + 1, param_b);
			}
		}


		ofs << std::setw(outwidth) << ZoneID
			<< std::setw(outwidth) << NP
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Result
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Result/ NP
			<< std::endl;

	}
	






}