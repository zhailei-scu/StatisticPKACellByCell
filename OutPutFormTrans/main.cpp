#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {
	string filename;
	stringstream ss;
	fstream ofsRead;
	fstream ofsWrite;
	string tempBuf;
	int EventID;
	int TrackID;
	int StepID;
	double preEng;
	double postEng;
	double deltaEng;
	double deltaTime;
	double originVector_x, originVector_y, originVector_z;
	double originstep_x, originstep_y, originstep_z;
	double prestep_x, prestep_y, prestep_z;
	double poststep_x, poststep_y, poststep_z;
	std::string processname;
	std::string particleName;
	int trackStatus;
	int OutWidth;
	//---Body---

	OutWidth = 20;

	if (argc < 2) {
		std::cout << "You should special the readed file name" << std::endl;
	}

	filename = string(argv[1]);

	ofsRead.open(filename,std::ios::in);

	ss.clear();

	ss.str("");

	ss <<"OutPutResult_Trans.txt";

	ofsWrite.open(ss.str(), std::ios::out | std::ios::ate);

	ofsWrite
		<< std::setw(OutWidth) << "EventID"
		<< std::setw(OutWidth) << "TrackID"
		<< std::setw(OutWidth) << "StepID"
		<< std::setw(OutWidth) << "PreEng(MeV)"
		<< std::setw(OutWidth) << "PostEng(MeV)"
		<< std::setw(OutWidth) << "DeltaEng(MeV)"
		<< std::setw(OutWidth) << "DeltaTime(ns)"
		<< std::setw(OutWidth) << "OriginDirection_x"
		<< std::setw(OutWidth) << "OriginDirection_y"
		<< std::setw(OutWidth) << "OriginDirection_z"
		<< std::setw(OutWidth) << "OriginPos_x(mm)"
		<< std::setw(OutWidth) << "OriginPos_y(mm)"
		<< std::setw(OutWidth) << "OriginPos_z(mm)"
		<< std::setw(OutWidth) << "PrePos_x(mm)"
		<< std::setw(OutWidth) << "PrePos_y(mm)"
		<< std::setw(OutWidth) << "PrePos_z(mm)"
		<< std::setw(OutWidth) << "PostPos_x(mm)"
		<< std::setw(OutWidth) << "PostPos_y(mm)"
		<< std::setw(OutWidth) << "PostPos_z(mm)"
		<< std::setw(OutWidth) << "ProcessName"
		<< std::setw(OutWidth) << "ParticleName"
		<< std::setw(OutWidth) << "TrackStatus"
		<< std::endl;



	getline(ofsRead, tempBuf); // the first line

	while (getline(ofsRead, tempBuf)) {

		ss.clear();
		ss.str("");

		ss << tempBuf;

		if (tempBuf.size() < 1) {
			continue;
		}

		processname.clear();
		std::string().swap(processname);

		ss >> EventID
			>> TrackID
			>> StepID
			>> preEng
			>> postEng
			>> deltaEng
			>> deltaTime
			>> originVector_x >> originVector_y >> originVector_z
			>> originstep_x >> originstep_y >> originstep_z
			>> prestep_x >> prestep_y >> prestep_z
			>> poststep_x >> poststep_y >> poststep_z
			>> processname
			>> particleName
			>> trackStatus;


		std::cout << EventID << std::endl;


		if (0 == processname.compare("hadElastic")) {

			ofsWrite << tempBuf<<std::endl;
		}


	}


	ofsRead.close();



	ofsWrite.close();

	return 0;
}