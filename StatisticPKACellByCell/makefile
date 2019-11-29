CC := g++
obj := Statistic.o main.o
exe := StatisticPKACellByCell.exe

$(exe):$(obj)
	$(CC) -o $@ $^
$(main.o):main.cpp
	$(CC) -c $< -o $@
$(Statistic.o):Statistic.cpp
	$(CC) -c $< -o $@


clean:
	rm -rf *.o *.exe
