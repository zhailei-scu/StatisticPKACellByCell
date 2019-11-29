#ifndef STATISTIC_H
#define STATISTIC_H
#include <vector>
#include <string>

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




class Statistic {
private:
	Statistic();
	~Statistic();

	Statistic(const Statistic& r) = delete;
	Statistic operator =(const Statistic& r) = delete;

	static Statistic* instance;

	std::vector<OneMinDistInfo> DistInfo;

public:

	static Statistic* GetInstance();
	static void ReleaseInstance();

	void ReadFromFile(const std::string& InputFilePath, int& minZoneID, int& maxZoneID, int& minCeilID, int& maxCeilID);
	void StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath);

private:

	class CGarb{
	public:
		CGarb();
		~CGarb();
	};


	static CGarb CGarbInstance;
};

#endif