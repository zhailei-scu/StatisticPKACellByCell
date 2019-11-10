#ifndef STATISTIC_H
#define STATISTIC_H
#include <vector>

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
	double MinDist_xyz[3];
	double MinDist;
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

	void ReadFromFile(const std::string& InputFilePath, int& minZoneID, int& maxZoneID);
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