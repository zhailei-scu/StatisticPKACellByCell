CC := g++
obj := StatisticPKAShiftedToCenterZone.o main.o
exe := StatisticPKAShiftedToCenterZone.exe

all:$(exe)

$(exe):$(obj)
	$(CC) -o $@ $^ -BStatic -L../Common -lCommon
main.o:main.cpp
	$(CC) -c $< -o $@
StatisticPKAShiftedToCenterZone.o:StatisticPKAShiftedToCenterZone.cpp
	$(CC) -c $< -I../Common -std=c++11 -o $@


clean:
	rm -rf *.o *.exe
