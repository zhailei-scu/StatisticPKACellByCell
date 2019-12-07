#include "StatisticPKAShiftedToCenterZone.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "DistanceXYZReader.h"

StatisticPKAShiftedToCenterZone::StatisticPKAShiftedToCenterZone() {

}


StatisticPKAShiftedToCenterZone::~StatisticPKAShiftedToCenterZone() {

}


StatisticPKAShiftedToCenterZone::StatisticPKAShiftedToCenterZone(const StatisticPKAShiftedToCenterZone&) {

}


StatisticPKAShiftedToCenterZone StatisticPKAShiftedToCenterZone::operator=(const StatisticPKAShiftedToCenterZone&) {
	return *this;
}



void StatisticPKAShiftedToCenterZone::StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath) {
	int minZoneID;
	int maxZoneID;
	int minCeilZID;
	int maxCeilZID;
	std::stringstream ss;
	std::string StatisticPath_ShiftedToCenterZone_Total;
	std::fstream ofs_ShiftedToCenterZone_Total;
	std::string StatisticPath_ShiftedToCenterZone_DepthCeil;
	std::fstream ofs_ShiftedToCenterZone_DepthCeil;
	int outwidth;
	int totalCeilZ;
	OneStatisticInfo TotalCeilZStatistic;
	OneStatisticInfo* CeilZStatistic;
	int tempCeilZID;
	//---Body---
	outwidth = 20;

	minZoneID = 0;
	maxZoneID = 0;
	minCeilZID = 0;
	maxCeilZID = 0;

	DistanceXYZReader::GetInstance()->ReadFromFile(InputFilePath, minZoneID, maxZoneID, minCeilZID, maxCeilZID);

	totalCeilZ = maxCeilZID - minCeilZID + 1;
	if (totalCeilZ < 0) {
		std::cout << "The total ceil number cannot less than 0." << std::endl;
		system("pause");
		exit(1);
	}


	if (OutputFilePath.length() > 0) {

		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "StatisticShiftedToCenterZone_Total.txt";

		ss >> StatisticPath_ShiftedToCenterZone_Total;


		ss.clear();

		ss.str("");

		ss << OutputFilePath.c_str() << "\\" << "StatisticShiftedToCenterZone_DepthCeil.txt";

		ss >> StatisticPath_ShiftedToCenterZone_DepthCeil;


	}
	else {
		ss.clear();

		ss.str("");

		ss << "StatisticShiftedToCenterZone_Total.txt";

		ss >> StatisticPath_ShiftedToCenterZone_Total;


		ss.clear();

		ss.str("");

		ss << "StatisticShiftedToCenterZone_DepthCeil.txt";

		ss >> StatisticPath_ShiftedToCenterZone_DepthCeil;

	}

	ofs_ShiftedToCenterZone_Total.open(StatisticPath_ShiftedToCenterZone_Total.c_str(), std::ios::out | std::ios::ate);

	ofs_ShiftedToCenterZone_Total << std::setw(outwidth) << "TotalCount"
		<< std::setw(outwidth) << "Ave_MinDist_x"
		<< std::setw(outwidth) << "Ave_MinDist_y"
		<< std::setw(outwidth) << "Ave_MinDist_z"
		<< std::setw(outwidth) << "Ave_MinDist"
		<< std::setw(outwidth) << "DevSqrt_MinDist_x"
		<< std::setw(outwidth) << "DevSqrt_MinDist_y"
		<< std::setw(outwidth) << "DevSqrt_MinDist_z"
		<< std::setw(outwidth) << "DevSqrt_MinDist"
		<< std::endl;


	ofs_ShiftedToCenterZone_DepthCeil.open(StatisticPath_ShiftedToCenterZone_DepthCeil.c_str(), std::ios::out | std::ios::ate);

	ofs_ShiftedToCenterZone_DepthCeil << std::setw(outwidth) << "CeilZID"
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

	CeilZStatistic = new OneStatisticInfo[totalCeilZ];

	for (int i = 0; i < totalCeilZ; i++) {
		CeilZStatistic[i].cleanup();
	}

	TotalCeilZStatistic.cleanup();

	std::vector<OneMinDistInfo>::iterator it = DistanceXYZReader::GetInstance()->GetDistInfo()->begin();

	for (; it != DistanceXYZReader::GetInstance()->GetDistInfo()->end(); it++) {

		tempCeilZID = it->SubjectCellID;
		CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_x += it->MinDist_xyz[0];
		CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_y += it->MinDist_xyz[1];
		CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_z += it->MinDist_xyz[2];
		CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist += it->MinDist;
		CeilZStatistic[tempCeilZID - minCeilZID].Count += 1;

		TotalCeilZStatistic.Ave_MinDist_x += it->MinDist_xyz[0];
		TotalCeilZStatistic.Ave_MinDist_y += it->MinDist_xyz[1];
		TotalCeilZStatistic.Ave_MinDist_z += it->MinDist_xyz[2];
		TotalCeilZStatistic.Ave_MinDist += it->MinDist;
		TotalCeilZStatistic.Count += 1;
	}

	for (int i = 0; i < totalCeilZ; i++) {
		if (CeilZStatistic[i].Count > 0) {
			CeilZStatistic[i].Ave_MinDist_x /= CeilZStatistic[i].Count;
			CeilZStatistic[i].Ave_MinDist_y /= CeilZStatistic[i].Count;
			CeilZStatistic[i].Ave_MinDist_z /= CeilZStatistic[i].Count;
			CeilZStatistic[i].Ave_MinDist /= CeilZStatistic[i].Count;
		}

	}

	if (TotalCeilZStatistic.Count > 0) {
		TotalCeilZStatistic.Ave_MinDist_x /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.Ave_MinDist_y /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.Ave_MinDist_z /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.Ave_MinDist /= TotalCeilZStatistic.Count;
	}


	it = DistanceXYZReader::GetInstance()->GetDistInfo()->begin();
	for (; it != DistanceXYZReader::GetInstance()->GetDistInfo()->end(); it++) {

		tempCeilZID = it->SubjectCellID;
		CeilZStatistic[tempCeilZID - minCeilZID].DevSqrt_MinDist_x += std::pow(it->MinDist_xyz[0] - CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_x, 2);
		CeilZStatistic[tempCeilZID - minCeilZID].DevSqrt_MinDist_y += std::pow(it->MinDist_xyz[1] - CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_y, 2);
		CeilZStatistic[tempCeilZID - minCeilZID].DevSqrt_MinDist_z += std::pow(it->MinDist_xyz[2] - CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist_z, 2);
		CeilZStatistic[tempCeilZID - minCeilZID].DevSqrt_MinDist += std::pow(it->MinDist - CeilZStatistic[tempCeilZID - minCeilZID].Ave_MinDist, 2);


		TotalCeilZStatistic.DevSqrt_MinDist_x += std::pow(it->MinDist_xyz[0] - TotalCeilZStatistic.Ave_MinDist_x, 2);
		TotalCeilZStatistic.DevSqrt_MinDist_y += std::pow(it->MinDist_xyz[1] - TotalCeilZStatistic.Ave_MinDist_y, 2);
		TotalCeilZStatistic.DevSqrt_MinDist_z += std::pow(it->MinDist_xyz[2] - TotalCeilZStatistic.Ave_MinDist_z, 2);
		TotalCeilZStatistic.DevSqrt_MinDist += std::pow(it->MinDist - TotalCeilZStatistic.Ave_MinDist, 2);

	}

	for (int i = 0; i < totalCeilZ; i++) {
		if (CeilZStatistic[i].Count > 0) {
			CeilZStatistic[i].DevSqrt_MinDist_x /= CeilZStatistic[i].Count;
			CeilZStatistic[i].DevSqrt_MinDist_y /= CeilZStatistic[i].Count;
			CeilZStatistic[i].DevSqrt_MinDist_z /= CeilZStatistic[i].Count;
			CeilZStatistic[i].DevSqrt_MinDist /= CeilZStatistic[i].Count;

			CeilZStatistic[i].DevSqrt_MinDist_x = std::sqrt(CeilZStatistic[i].DevSqrt_MinDist_x);
			CeilZStatistic[i].DevSqrt_MinDist_y = std::sqrt(CeilZStatistic[i].DevSqrt_MinDist_y);
			CeilZStatistic[i].DevSqrt_MinDist_z = std::sqrt(CeilZStatistic[i].DevSqrt_MinDist_z);
			CeilZStatistic[i].DevSqrt_MinDist = std::sqrt(CeilZStatistic[i].DevSqrt_MinDist);
		}

	}


	if (TotalCeilZStatistic.Count > 0) {
		TotalCeilZStatistic.DevSqrt_MinDist_x /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.DevSqrt_MinDist_y /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.DevSqrt_MinDist_z /= TotalCeilZStatistic.Count;
		TotalCeilZStatistic.DevSqrt_MinDist /= TotalCeilZStatistic.Count;

		TotalCeilZStatistic.DevSqrt_MinDist_x = std::sqrt(TotalCeilZStatistic.DevSqrt_MinDist_x);
		TotalCeilZStatistic.DevSqrt_MinDist_y = std::sqrt(TotalCeilZStatistic.DevSqrt_MinDist_y);
		TotalCeilZStatistic.DevSqrt_MinDist_z = std::sqrt(TotalCeilZStatistic.DevSqrt_MinDist_z);
		TotalCeilZStatistic.DevSqrt_MinDist = std::sqrt(TotalCeilZStatistic.DevSqrt_MinDist);
	}


	ofs_ShiftedToCenterZone_Total << std::setw(outwidth) << TotalCeilZStatistic.Count
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.Ave_MinDist_x
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.Ave_MinDist_y
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.Ave_MinDist_z
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.Ave_MinDist
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.DevSqrt_MinDist_x
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.DevSqrt_MinDist_y
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.DevSqrt_MinDist_z
		<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << TotalCeilZStatistic.DevSqrt_MinDist
		<< std::endl;



	for (int i = 0; i < totalCeilZ; i++) {
		ofs_ShiftedToCenterZone_DepthCeil << std::setw(outwidth) << i + minCeilZID
			<< std::setw(outwidth) << CeilZStatistic[i].Count
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].Ave_MinDist_x
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].Ave_MinDist_y
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].Ave_MinDist_z
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].Ave_MinDist
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].DevSqrt_MinDist_x
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].DevSqrt_MinDist_y
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].DevSqrt_MinDist_z
			<< std::setw(outwidth) << std::setiosflags(std::ios::scientific) << CeilZStatistic[i].DevSqrt_MinDist
			<< std::endl;
	}

	ofs_ShiftedToCenterZone_Total.close();

	ofs_ShiftedToCenterZone_DepthCeil.close();

	if (NULL != CeilZStatistic) {
		delete[] CeilZStatistic;
		CeilZStatistic = NULL;
	}

}
