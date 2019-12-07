#include "StatisticPKACellByCell.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "DistanceXYZReader.h"

StatisticPKACellByCell::StatisticPKACellByCell() {

}


StatisticPKACellByCell::~StatisticPKACellByCell() {

}


StatisticPKACellByCell::StatisticPKACellByCell(const StatisticPKACellByCell&) {

}


StatisticPKACellByCell StatisticPKACellByCell::operator=(const StatisticPKACellByCell&) {
	return *this;
}



void StatisticPKACellByCell::StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath) {
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

	DistanceXYZReader::GetInstance()->ReadFromFile(InputFilePath, minZoneID, maxZoneID, minCeilID, maxCeilID);

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

	std::vector<OneMinDistInfo>::iterator it = DistanceXYZReader::GetInstance()->GetDistInfo()->begin();

	for (; it != DistanceXYZReader::GetInstance()->GetDistInfo()->end(); it++) {

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

	it = DistanceXYZReader::GetInstance()->GetDistInfo()->begin();
	for (; it != DistanceXYZReader::GetInstance()->GetDistInfo()->end(); it++) {

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
