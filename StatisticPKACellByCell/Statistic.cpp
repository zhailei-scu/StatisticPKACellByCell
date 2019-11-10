#include "Statistic.h"
#include "stdlib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include <iomanip>

void OneMinDistInfo::cleanup() {
	this->SubjectZoneID = -1;
	this->ObjectZoneID = -1;

	for (int i = 0; i < 3; i++) {
		this->MinDist_xyz[i] = 0;
	}

	this->MinDist = 0;
}

OneMinDistInfo::OneMinDistInfo() {
	cleanup();
}

OneMinDistInfo::~OneMinDistInfo() {
	cleanup();
}

OneMinDistInfo OneMinDistInfo::operator = (const OneMinDistInfo &r) {
	this->SubjectZoneID = r.SubjectZoneID;
	this->ObjectZoneID = r.ObjectZoneID;

	for (int i = 0; i < 3; i++) {
		this->MinDist_xyz[i] = r.MinDist_xyz[i];
	}
	
	this->MinDist = r.MinDist;
	return *this;
}

OneMinDistInfo::OneMinDistInfo(const OneMinDistInfo &r) {

	this->SubjectZoneID = r.SubjectZoneID;
	this->ObjectZoneID = r.ObjectZoneID;

	for (int i = 0; i < 3; i++) {
		this->MinDist_xyz[i] = r.MinDist_xyz[i];
	}

	this->MinDist = r.MinDist;
}


Statistic* Statistic::instance = new Statistic();

Statistic::Statistic() {
	this->instance = NULL;
}

Statistic::~Statistic() {
	this->DistInfo.clear();
	std::vector<OneMinDistInfo>().swap(this->DistInfo);
}

Statistic* Statistic::GetInstance() {
	return instance;
}


void Statistic::ReleaseInstance() {
	if (NULL != instance) {
		delete instance;
		instance = NULL;
	}
}

void Statistic::ReadFromFile(const std::string& InputFilePath,int& minZoneID,int& maxZoneID) {
	std::stringstream ss;
	std::string tempBuf;
	std::fstream ofs;
	int subjectZoneID;
	int objectZoneID;
	int subjectCellID;
	int objectCellID;
	int subjectEventID;
	int objectEventID;
	int subjectTrackID;
	int objectTrackID;
	int subjectStepID;
	int objectStepID;
	double MinDist_xyz[3];
	double MinDist;
	OneMinDistInfo MinDistInfo;
	int index;

	minZoneID = 100000000;
	maxZoneID = 0;

	index = 0;

	ofs.open(InputFilePath.c_str(), std::ios::in);

	getline(ofs, tempBuf); // the first line

	while (getline(ofs, tempBuf)) {

		ss.clear();
		ss.str("");

		ss << tempBuf;

		if (tempBuf.size() < 1) {
			continue;
		}

		MinDistInfo.cleanup();

		ss >> subjectZoneID
			>> subjectCellID
			>> subjectEventID
			>> subjectTrackID
			>> subjectStepID
			>> objectZoneID
			>> objectCellID
			>> objectEventID
			>> objectTrackID
			>> objectStepID
			>> MinDist_xyz[0] >> MinDist_xyz[1] >> MinDist_xyz[2]
			>> MinDist;

		MinDistInfo.SubjectZoneID = subjectZoneID;
		MinDistInfo.ObjectZoneID = objectZoneID;

		for (int i = 0; i < 3; i++) {

			MinDistInfo.MinDist_xyz[i] = MinDist_xyz[i];
		}

		MinDistInfo.MinDist = MinDist;

		this->DistInfo.push_back(MinDistInfo);

		minZoneID = std::min(subjectZoneID, minZoneID);
		maxZoneID = std::max(subjectZoneID, maxZoneID);

		std::cout << index << std::endl;

		index++;
	}

	ofs.close();

}

void Statistic::StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath) {
	int minZoneID;
	int maxZoneID;
	std::stringstream ss;
	std::string StatisticPath;
	std::fstream ofs;
	int outwidth;
	int totalZone;
	double* Ave_MinDist_x;
	double* Ave_MinDist_y;
	double* Ave_MinDist_z;
	double* Ave_MinDist;
	double* DevSqrt_MinDist_x;
	double* DevSqrt_MinDist_y;
	double* DevSqrt_MinDist_z;
	double* DevSqrt_MinDist;
	int* Count;
	int tempZoneID;

	outwidth = 20;

	minZoneID = 0;
	maxZoneID = 0;

	this->ReadFromFile(InputFilePath, minZoneID, maxZoneID);

	std::cout << minZoneID << std::endl;
	std::cout << maxZoneID << std::endl;

	totalZone = maxZoneID - minZoneID + 1;

	if (totalZone < 0) {
		std::cout << "The total zone number cannot less than 0." << std::endl;
		system("pause");
		exit(1);
	}


	if (OutputFilePath.length() > 0) {

		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "StatisticCellByCell_New.txt";

		ss >> StatisticPath;

	}
	else {
		ss.clear();

		ss.str("");

		ss << "StatisticCellByCell_New.txt";

		ss >> StatisticPath;

	}

	ofs.open(StatisticPath,std::ios::out | std::ios::ate);


	ofs << std::setw(outwidth) << "ZoneID"
		<< std::setw(outwidth) << "Count"
		<< std::setw(outwidth) << "Ave_MinDist_x" 
		<< std::setw(outwidth) << "Ave_MinDist_y" 
		<< std::setw(outwidth) << "Ave_MinDist_z"
		<< std::setw(outwidth) << "Ave_MinDist"
		<< std::setw(outwidth) << "DevSqrt_MinDist_x"
		<< std::setw(outwidth) << "DevSqrt_MinDist_y"
		<< std::setw(outwidth) << "DevSqrt_MinDist_z"
		<< std::setw(outwidth) << "DevSqrt_MinDist"
		<< std::endl;


	Ave_MinDist_x = new double[totalZone];
	Ave_MinDist_y = new double[totalZone];
	Ave_MinDist_z = new double[totalZone];
	Ave_MinDist = new double[totalZone];

	DevSqrt_MinDist_x = new double[totalZone];
	DevSqrt_MinDist_y = new double[totalZone];
	DevSqrt_MinDist_z = new double[totalZone];
	DevSqrt_MinDist = new double[totalZone];

	Count = new int[totalZone];

	for (int i = 0; i < totalZone; i++) {
		Ave_MinDist_x[i] = 0;
		Ave_MinDist_y[i] = 0;
		Ave_MinDist_z[i] = 0;
		Ave_MinDist[i] = 0;

		DevSqrt_MinDist_x[i] = 0;
		DevSqrt_MinDist_y[i] = 0;
		DevSqrt_MinDist_z[i] = 0;
		DevSqrt_MinDist[i] = 0;

		Count[i] = 0;
	}


	std::vector<OneMinDistInfo>::iterator it = this->DistInfo.begin();

	for (; it != this->DistInfo.end(); it++) {

		tempZoneID = it->SubjectZoneID;
		Ave_MinDist_x[tempZoneID - minZoneID] += it->MinDist_xyz[0];
		Ave_MinDist_y[tempZoneID - minZoneID] += it->MinDist_xyz[1];
		Ave_MinDist_z[tempZoneID - minZoneID] += it->MinDist_xyz[2];

		Ave_MinDist[tempZoneID - minZoneID] += it->MinDist;

		Count[tempZoneID - minZoneID] += 1;
	}
	
	for (int i = 0; i < totalZone; i++) {
		if (Count[i] > 0) {
			Ave_MinDist_x[i] /= Count[i];
			Ave_MinDist_y[i] /= Count[i];
			Ave_MinDist_z[i] /= Count[i];
			Ave_MinDist[i] /= Count[i];
		}
	}

	it = this->DistInfo.begin();
	for (; it != this->DistInfo.end(); it++) {

		tempZoneID = it->SubjectZoneID;
		DevSqrt_MinDist_x[tempZoneID - minZoneID] += std::pow(it->MinDist_xyz[0] - Ave_MinDist_x[tempZoneID - minZoneID], 2);
		DevSqrt_MinDist_y[tempZoneID - minZoneID] += std::pow(it->MinDist_xyz[1] - Ave_MinDist_y[tempZoneID - minZoneID], 2);
		DevSqrt_MinDist_z[tempZoneID - minZoneID] += std::pow(it->MinDist_xyz[2] - Ave_MinDist_z[tempZoneID - minZoneID], 2);
		DevSqrt_MinDist[tempZoneID - minZoneID] += std::pow(it->MinDist - Ave_MinDist[tempZoneID - minZoneID], 2);
	}

	for (int i = 0; i < totalZone; i++) {
		if (Count[i] > 0) {
			DevSqrt_MinDist_x[i] /= Count[i];
			DevSqrt_MinDist_y[i] /= Count[i];
			DevSqrt_MinDist_z[i] /= Count[i];
			DevSqrt_MinDist[i] /= Count[i];

			DevSqrt_MinDist_x[i] = std::sqrt(DevSqrt_MinDist_x[i]);
			DevSqrt_MinDist_y[i] = std::sqrt(DevSqrt_MinDist_y[i]);
			DevSqrt_MinDist_z[i] = std::sqrt(DevSqrt_MinDist_z[i]);
			DevSqrt_MinDist[i] = std::sqrt(DevSqrt_MinDist[i]);
		}
	}


	for (int i = 0; i < totalZone; i++) {
		ofs << std::setw(outwidth) << i + minZoneID
			<< std::setw(outwidth) << Count[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Ave_MinDist_x[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Ave_MinDist_y[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Ave_MinDist_z[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << Ave_MinDist[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << DevSqrt_MinDist_x[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << DevSqrt_MinDist_y[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << DevSqrt_MinDist_z[i]
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << DevSqrt_MinDist[i]
			<< std::endl;
	}

	ofs.close();

	if (NULL != Ave_MinDist_x) { 
		delete[] Ave_MinDist_x; 
		Ave_MinDist_x = NULL;
	}

	if (NULL != Ave_MinDist_y) {
		delete[] Ave_MinDist_y;
		Ave_MinDist_y = NULL;
	}

	if (NULL != Ave_MinDist_z) {
		delete[] Ave_MinDist_z;
		Ave_MinDist_z = NULL;
	}

	if (NULL != Ave_MinDist) {
		delete[] Ave_MinDist;
		Ave_MinDist = NULL;
	}

	if (NULL != Count) {
		delete[] Count;
		Count = NULL;
	}

}



Statistic::CGarb::CGarb() {

}

Statistic::CGarb::~CGarb() {
	ReleaseInstance();
}