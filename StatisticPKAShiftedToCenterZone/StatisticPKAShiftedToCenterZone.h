#ifndef STATISTICPKASHIFTTOCENTERZONE_H
#define STATISTICPKASHIFTTOCENTERZONE_H
#include <string>



class StatisticPKAShiftedToCenterZone {
public:
	StatisticPKAShiftedToCenterZone();
	~StatisticPKAShiftedToCenterZone();

	StatisticPKAShiftedToCenterZone(const StatisticPKAShiftedToCenterZone& r);
	StatisticPKAShiftedToCenterZone operator =(const StatisticPKAShiftedToCenterZone& r);

public:

	static void StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath);
};

#endif
