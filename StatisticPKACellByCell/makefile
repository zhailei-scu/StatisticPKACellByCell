CC := g++
obj := StatisticPKACellByCell.o main.o
exe := StatisticPKACellByCell.exe

all:$(exe)

$(exe):$(obj)
	$(CC) -o $@ $^ -BStatic -L../Common -lCommon
main.o:main.cpp
	$(CC) -c $< -o $@
StatisticPKACellByCell.o:StatisticPKACellByCell.cpp
	$(CC) -c $< -I../Common -std=c++11 -o $@


clean:
	rm -rf *.o *.exe
