CC := g++
obj := DistanceXYZReader.o
lib := libCommon.a

all:$(lib)

$(lib):$(obj)
	ar -rcs $@ $^
DistanceXYZReader.o:DistanceXYZReader.cpp
	$(CC) -c $< -std=c++11 -o $@


clean:
	rm -rf *.o *.exe *.a
