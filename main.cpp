#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <set>
#include <chrono> 
#include "graph.h"

using namespace std;

void read_graph(Graph &graph){
	set <string> edge_set;
	string edge_tuple;

	int v, w;
	int num_edges = 0;

	while (scanf("%i %i", &v, &w) == 2){
		if(v == w) continue;
		graph.add_edge(v, w);
		num_edges++;
	}
}

int main(int argc, char **argv){
	if (argc < 2) {
		cerr << "Correct Usage: ./main <num_vertices> <edges_filename>" << endl;
		exit(1);
	}

	Graph graph(atoi(argv[1]));
	read_graph(graph);

	do{
		cout << "1 - BFS" << endl;
		cout << "2 - BAGBFS" << endl;
		cout << "3 - SAIR" << endl;
		cout << "Digite a opção desejada!" << endl;
		cin >> opc;

		auto start = high_resolution_clock::now();
		switch (opc){
			case 1: graph.BFS(1);
				cout << "BFS time: ";
				break;
			case 2: graph.BAGBFS(1);
				cout << "BAGBFS time: ";
				break;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);
		cout << duration.count() << " microseconds" << endl;
	} while (opc != 3);
	return 0;
}