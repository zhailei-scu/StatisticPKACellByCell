#include "Statistic.h"
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

void Statistic::ReadFromFile(const std::string& InputFilePath,int& minZoneID,int& maxZoneID, int& minCeilID, int& maxCeilID) {
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

void Statistic::StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath) {
	int minZoneID;
	int maxZoneID;
	int minCeilID;
	int maxCeilID;
	std::stringstream ss;
	std::string StatisticPath_Zone;
	std::string StatisticPath_Ceil;
	std::fstream ofs_Zone;
	std::fstream ofs_Ceil;
	int outwidth;
	int totalZone;
	int totalCeil;
	OneStatisticInfo* ZoneStatistic;
	std::map<int, OneStatisticInfo>* CeilStatistic;
	std::map<int, OneStatisticInfo>::iterator itmap;
	int tempZoneID;
	int tempCeilID;
	//---Body---
	outwidth = 20;

	minZoneID = 0;
	maxZoneID = 0;
	minCeilID = 0;
	maxCeilID = 0;

	this->ReadFromFile(InputFilePath, minZoneID, maxZoneID, minCeilID, maxCeilID);

	std::cout << minZoneID << std::endl;
	std::cout << maxZoneID << std::endl;
	std::cout << minCeilID << std::endl;
	std::cout << maxCeilID << std::endl;

	totalZone = maxZoneID - minZoneID + 1;
	if (totalZone < 0) {
		std::cout << "The total zone number cannot less than 0." << std::endl;
		system("pause");
		exit(1);
	}

	totalCeil = maxCeilID - minCeilID + 1;
	if (totalCeil < 0) {
		std::cout << "The total ceil number cannot less than 0." << std::endl;
		system("pause");
		exit(1);
	}


	if (OutputFilePath.length() > 0) {

		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "StatisticZoneByZone_New.txt";

		ss >> StatisticPath_Zone;


		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "StatisticCeilByCeil_New.txt";

		ss >> StatisticPath_Ceil;


	}
	else {
		ss.clear();

		ss.str("");

		ss << "StatisticZoneByZone_New.txt";

		ss >> StatisticPath_Zone;


		ss.clear();

		ss.str("");

		ss << "StatisticCeilByCeil_New.txt";

		ss >> StatisticPath_Ceil;

	}

	ofs_Zone.open(StatisticPath_Zone.c_str(),std::ios::out | std::ios::ate);

	ofs_Zone << std::setw(outwidth) << "ZoneID"
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


	ofs_Ceil.open(StatisticPath_Ceil.c_str(), std::ios::out | std::ios::ate);

	ofs_Ceil << std::setw(outwidth) << "ZoneID"
		<< std::setw(outwidth) << "CeilID"
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

	ZoneStatistic = new OneStatisticInfo[totalZone];
	CeilStatistic = new std::map<int, OneStatisticInfo>[totalZone];

	for (int i = 0; i < totalZone; i++) {
		ZoneStatistic[i].cleanup();

		CeilStatistic[i].clear();
		std::map<int, OneStatisticInfo>().swap(CeilStatistic[i]);
	}

	std::vector<OneMinDistInfo>::iterator it = this->DistInfo.begin();

	for (; it != this->DistInfo.end(); it++) {

		tempZoneID = it->SubjectZoneID;
		ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_x += it->MinDist_xyz[0];
		ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_y += it->MinDist_xyz[1];
		ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_z += it->MinDist_xyz[2];
		ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist += it->MinDist;
		ZoneStatistic[tempZoneID - minZoneID].Count += 1;

		tempCeilID = it->SubjectCellID;

		if (0 == CeilStatistic[tempZoneID - minZoneID].count(tempCeilID)) {
			CeilStatistic[tempZoneID - minZoneID].insert(std::map<int, OneStatisticInfo>::value_type(tempCeilID, OneStatisticInfo()));
		}
		
		itmap = CeilStatistic[tempZoneID - minZoneID].find(tempCeilID);

		itmap->second.Ave_MinDist_x += it->MinDist_xyz[0];
		itmap->second.Ave_MinDist_y += it->MinDist_xyz[1];
		itmap->second.Ave_MinDist_z += it->MinDist_xyz[2];
		itmap->second.Ave_MinDist += it->MinDist;
		itmap->second.Count += 1;
	}
	
	for (int i = 0; i < totalZone; i++) {
		if (ZoneStatistic[i].Count > 0) {
			ZoneStatistic[i].Ave_MinDist_x /= ZoneStatistic[i].Count;
			ZoneStatistic[i].Ave_MinDist_y /= ZoneStatistic[i].Count;
			ZoneStatistic[i].Ave_MinDist_z /= ZoneStatistic[i].Count;
			ZoneStatistic[i].Ave_MinDist /= ZoneStatistic[i].Count;
		}

		itmap = CeilStatistic[i].begin();
		for (; itmap != CeilStatistic[i].end(); itmap++) {
			if (itmap->second.Count > 0) {
				itmap->second.Ave_MinDist_x /= itmap->second.Count;
				itmap->second.Ave_MinDist_y /= itmap->second.Count;
				itmap->second.Ave_MinDist_z /= itmap->second.Count;
				itmap->second.Ave_MinDist /= itmap->second.Count;
			}
		}

	}

	it = this->DistInfo.begin();
	for (; it != this->DistInfo.end(); it++) {

		tempZoneID = it->SubjectZoneID;
		ZoneStatistic[tempZoneID - minZoneID].DevSqrt_MinDist_x += std::pow(it->MinDist_xyz[0] - ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_x, 2);
		ZoneStatistic[tempZoneID - minZoneID].DevSqrt_MinDist_y += std::pow(it->MinDist_xyz[1] - ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_y, 2);
		ZoneStatistic[tempZoneID - minZoneID].DevSqrt_MinDist_z += std::pow(it->MinDist_xyz[2] - ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist_z, 2);
		ZoneStatistic[tempZoneID - minZoneID].DevSqrt_MinDist += std::pow(it->MinDist - ZoneStatistic[tempZoneID - minZoneID].Ave_MinDist, 2);


		tempCeilID = it->SubjectCellID;
		itmap = CeilStatistic[tempZoneID - minZoneID].find(tempCeilID);
		itmap->second.DevSqrt_MinDist_x += std::pow(it->MinDist_xyz[0] - itmap->second.Ave_MinDist_x,2);
		itmap->second.DevSqrt_MinDist_y += std::pow(it->MinDist_xyz[1] - itmap->second.Ave_MinDist_y,2);
		itmap->second.DevSqrt_MinDist_z += std::pow(it->MinDist_xyz[2] - itmap->second.Ave_MinDist_z,2);
		itmap->second.DevSqrt_MinDist += std::pow(it->MinDist - itmap->second.Ave_MinDist,2);
	}

	for (int i = 0; i < totalZone; i++) {
		if (ZoneStatistic[i].Count > 0) {
			ZoneStatistic[i].DevSqrt_MinDist_x /= ZoneStatistic[i].Count;
			ZoneStatistic[i].DevSqrt_MinDist_y /= ZoneStatistic[i].Count;
			ZoneStatistic[i].DevSqrt_MinDist_z /= ZoneStatistic[i].Count;
			ZoneStatistic[i].DevSqrt_MinDist /= ZoneStatistic[i].Count;

			ZoneStatistic[i].DevSqrt_MinDist_x = std::sqrt(ZoneStatistic[i].DevSqrt_MinDist_x);
			ZoneStatistic[i].DevSqrt_MinDist_y = std::sqrt(ZoneStatistic[i].DevSqrt_MinDist_y);
			ZoneStatistic[i].DevSqrt_MinDist_z = std::sqrt(ZoneStatistic[i].DevSqrt_MinDist_z);
			ZoneStatistic[i].DevSqrt_MinDist = std::sqrt(ZoneStatistic[i].DevSqrt_MinDist);
		}

		itmap = CeilStatistic[i].begin();
		for (; itmap != CeilStatistic[i].end(); itmap++) {
			if (itmap->second.Count > 0) {
				itmap->second.DevSqrt_MinDist_x /= itmap->second.Count;
				itmap->second.DevSqrt_MinDist_y /= itmap->second.Count;
				itmap->second.DevSqrt_MinDist_z /= itmap->second.Count;
				itmap->second.DevSqrt_MinDist /= itmap->second.Count;

				itmap->second.DevSqrt_MinDist_x = std::sqrt(itmap->second.DevSqrt_MinDist_x);
				itmap->second.DevSqrt_MinDist_y = std::sqrt(itmap->second.DevSqrt_MinDist_y);
				itmap->second.DevSqrt_MinDist_z = std::sqrt(itmap->second.DevSqrt_MinDist_z);
				itmap->second.DevSqrt_MinDist = std::sqrt(itmap->second.DevSqrt_MinDist);
			}
		}


	}


	for (int i = 0; i < totalZone; i++) {
		ofs_Zone << std::setw(outwidth) << i + minZoneID
			<< std::setw(outwidth) << ZoneStatistic[i].Count
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].Ave_MinDist_x
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].Ave_MinDist_y
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].Ave_MinDist_z
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].Ave_MinDist
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].DevSqrt_MinDist_x
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].DevSqrt_MinDist_y
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].DevSqrt_MinDist_z
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << ZoneStatistic[i].DevSqrt_MinDist
			<< std::endl;


		itmap = CeilStatistic[i].begin();
		for (; itmap != CeilStatistic[i].end(); itmap++) {
			ofs_Ceil << std::setw(outwidth) << i + minZoneID
				<< std::setw(outwidth) << itmap->first
				<< std::setw(outwidth) << itmap->second.Count
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.Ave_MinDist_x
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.Ave_MinDist_y
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.Ave_MinDist_z
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.Ave_MinDist
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.DevSqrt_MinDist_x
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.DevSqrt_MinDist_y
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.DevSqrt_MinDist_z
				<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << itmap->second.DevSqrt_MinDist
				<< std::endl;
		}



	}

	ofs_Zone.close();

	ofs_Ceil.close();

	if (NULL != ZoneStatistic) {
		delete[] ZoneStatistic;
		ZoneStatistic = NULL;
	}

	if (NULL != CeilStatistic) {
		delete[] CeilStatistic;
		CeilStatistic = NULL;
	}

}



Statistic::CGarb::CGarb() {

}

Statistic::CGarb::~CGarb() {
	ReleaseInstance();
}
