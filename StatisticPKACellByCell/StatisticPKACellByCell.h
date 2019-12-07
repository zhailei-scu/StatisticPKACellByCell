#ifndef STATISTICPKACELLBYCELL_H
#define STATISTICPKACELLBYCELL_H
#include <string>



class StatisticPKACellByCell {
public:
	StatisticPKACellByCell();
	~StatisticPKACellByCell();

	StatisticPKACellByCell(const StatisticPKACellByCell& r);
	StatisticPKACellByCell operator =(const StatisticPKACellByCell& r);

public:

	static void StartStatistic(const std::string& InputFilePath, const std::string& OutputFilePath);
};

#endif
