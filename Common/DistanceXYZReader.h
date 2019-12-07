#ifndef DISTANCEXYZREADER_H
#define DISTANCEXYZREADER_H
#include "stdlib.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include <iomanip>
#include <map>
#include <list>

class OneMinDistInfo {
public:
	OneMinDistInfo();
	~OneMinDistInfo();
public:

	OneMinDistInfo(const OneMinDistInfo &r);
	OneMinDistInfo operator = (const OneMinDistInfo &r);
	void cleanup();
public:
	int SubjectZoneID;
	int ObjectZoneID;
	int SubjectCellID;
	double MinDist_xyz[3];
	double MinDist;
};


class OneStatisticInfo {
public:
	OneStatisticInfo();
	~OneStatisticInfo();
public:

	OneStatisticInfo(const OneStatisticInfo &r);
	OneStatisticInfo & operator = (const OneStatisticInfo &r);
	void cleanup();
public:
	double Ave_MinDist_x;
	double Ave_MinDist_y;
	double Ave_MinDist_z;
	double Ave_MinDist;
	double DevSqrt_MinDist_x;
	double DevSqrt_MinDist_y;
	double DevSqrt_MinDist_z;
	double DevSqrt_MinDist;
	int Count;
};




class DistanceXYZReader {
private:
	DistanceXYZReader();
	~DistanceXYZReader();

	DistanceXYZReader(const DistanceXYZReader& r) = delete;
	DistanceXYZReader operator =(const DistanceXYZReader& r) = delete;

	static DistanceXYZReader* instance;

	std::vector<OneMinDistInfo> DistInfo;

public:

	static DistanceXYZReader* GetInstance();
	static void ReleaseInstance();

	void ReadFromFile(const std::string& InputFilePath, int& minZoneID, int& maxZoneID, int& minCeilID, int& maxCeilID);


	std::vector<OneMinDistInfo> * GetDistInfo();
private:

	class CGarb {
	public:
		CGarb();
		~CGarb();
	};


	static CGarb CGarbInstance;
};

#endif
