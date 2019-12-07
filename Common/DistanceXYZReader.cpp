#include "DistanceXYZReader.h"
#include <cmath>

void OneMinDistInfo::cleanup() {
	this->SubjectZoneID = -1;
	this->ObjectZoneID = -1;
	this->SubjectCellID = -1;

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
	this->SubjectCellID = r.SubjectCellID;

	for (int i = 0; i < 3; i++) {
		this->MinDist_xyz[i] = r.MinDist_xyz[i];
	}

	this->MinDist = r.MinDist;
	return *this;
}

OneMinDistInfo::OneMinDistInfo(const OneMinDistInfo &r) {

	this->SubjectZoneID = r.SubjectZoneID;
	this->ObjectZoneID = r.ObjectZoneID;
	this->SubjectCellID = r.SubjectCellID;

	for (int i = 0; i < 3; i++) {
		this->MinDist_xyz[i] = r.MinDist_xyz[i];
	}

	this->MinDist = r.MinDist;
}

void OneStatisticInfo::cleanup() {
	this->Ave_MinDist_x = 0;
	this->Ave_MinDist_y = 0;
	this->Ave_MinDist_z = 0;
	this->Ave_MinDist = 0;
	this->DevSqrt_MinDist_x = 0;
	this->DevSqrt_MinDist_y = 0;
	this->DevSqrt_MinDist_z = 0;
	this->DevSqrt_MinDist = 0;
	this->Count = 0;
}

OneStatisticInfo::OneStatisticInfo() {
	cleanup();
}

OneStatisticInfo::~OneStatisticInfo() {
	cleanup();
}

OneStatisticInfo::OneStatisticInfo(const OneStatisticInfo & r) {
	this->Ave_MinDist_x = r.Ave_MinDist_x;
	this->Ave_MinDist_y = r.Ave_MinDist_y;
	this->Ave_MinDist_z = r.Ave_MinDist_z;
	this->Ave_MinDist = r.Ave_MinDist;
	this->DevSqrt_MinDist_x = r.DevSqrt_MinDist_x;
	this->DevSqrt_MinDist_y = r.DevSqrt_MinDist_y;
	this->DevSqrt_MinDist_z = r.DevSqrt_MinDist_z;
	this->DevSqrt_MinDist = r.DevSqrt_MinDist;
	this->Count = r.Count;
}

OneStatisticInfo & OneStatisticInfo::operator = (const OneStatisticInfo & r) {
	this->Ave_MinDist_x = r.Ave_MinDist_x;
	this->Ave_MinDist_y = r.Ave_MinDist_y;
	this->Ave_MinDist_z = r.Ave_MinDist_z;
	this->Ave_MinDist = r.Ave_MinDist;
	this->DevSqrt_MinDist_x = r.DevSqrt_MinDist_x;
	this->DevSqrt_MinDist_y = r.DevSqrt_MinDist_y;
	this->DevSqrt_MinDist_z = r.DevSqrt_MinDist_z;
	this->DevSqrt_MinDist = r.DevSqrt_MinDist;
	this->Count = r.Count;

	return *this;
}


DistanceXYZReader* DistanceXYZReader::instance = new DistanceXYZReader();

DistanceXYZReader::DistanceXYZReader() {
	this->instance = NULL;
}

DistanceXYZReader::~DistanceXYZReader() {
	this->DistInfo.clear();
	std::vector<OneMinDistInfo>().swap(this->DistInfo);
}

DistanceXYZReader* DistanceXYZReader::GetInstance() {
	return instance;
}


void DistanceXYZReader::ReleaseInstance() {
	if (NULL != instance) {
		delete instance;
		instance = NULL;
	}
}

std::vector<OneMinDistInfo> * DistanceXYZReader::GetDistInfo(){
	return &this->DistInfo;
}

void DistanceXYZReader::ReadFromFile(const std::string& InputFilePath, int& minZoneID, int& maxZoneID, int& minCeilID, int& maxCeilID) {
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
	minCeilID = 100000000;
	maxCeilID = 0;

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
		MinDistInfo.SubjectCellID = subjectCellID;

		for (int i = 0; i < 3; i++) {

			MinDistInfo.MinDist_xyz[i] = MinDist_xyz[i];
		}

		MinDistInfo.MinDist = MinDist;

		this->DistInfo.push_back(MinDistInfo);

		minZoneID = std::min(subjectZoneID, minZoneID);
		maxZoneID = std::max(subjectZoneID, maxZoneID);

		minCeilID = std::min(subjectCellID, minCeilID);
		maxCeilID = std::max(subjectCellID, maxCeilID);

		std::cout << index << std::endl;

		index++;
	}

	ofs.close();

}


DistanceXYZReader::CGarb::CGarb() {

}

DistanceXYZReader::CGarb::~CGarb() {
	ReleaseInstance();
}
