codenames: main.o func.o
	g++ main.o func.o -o codenames

main.o: main.cpp
	g++ -c main.cpp

func.cpp: func.cpp func.h
	g++ -c func.pp

clean:
	rm *.o
	rm codenames
