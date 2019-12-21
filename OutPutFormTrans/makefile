CC := g++
obj := main.o
exe := OutPutFormTrans.exe

all:$(exe)

$(exe):$(obj)
	$(CC) -o $@ $^
main.o:main.cpp
	$(CC) -c $< -std=c++11 -o $@

clean:
	rm -rf *.o *.exe
