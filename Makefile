all: bag.o graph.o main.o pennant.o
	gcc -o ./main bag.o main.o graph.o pennant.o

pennant.o: pennant.cpp pennant.h vertex.h
	gcc -o ./pennant.o -c ./pennant.cpp

bag.o: bag.cpp bag.h vertex.h pennant.o
	gcc -o ./bag.o -c ./bag.cpp

main.o: main.cpp
	gcc -o ./main.o -c ./main.cpp

graph.o: graph.cpp graph.h bag.o
	gcc -o ./graph.o -c ./graph.cpp

clear:
	rm ./main *.o
