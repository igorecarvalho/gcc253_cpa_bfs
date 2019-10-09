#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <set>
#include <chrono> 
#include "graph.h"

using namespace std;

void read_graph(Graph &graph, FILE *file){
	set <string> edge_set;
	string edge_tuple;

	int v, w, result;
	int num_edges = 0;

	if (!file){
		printf("Problemas na abertura do arquivo\n");
	}

	while (!feof(file)){
		//if(v == w) continue;
		result = fscanf(file, "%d %d", &v, &w);
		if(result){
			//printf("%d  %d\n", v, w);
			graph.add_edge(v, w);
			num_edges++;
		}
	}
	cout << "leitura completa" << endl;
}

int main(int argc, char **argv){
	if (argc < 2) {
		cerr << "Correct Usage: ./main <num_vertices> <edges_filename>" << endl;
		exit(1);
	}

	std::cout << argv[1] << endl;
	std::cout << argv[2] << endl;

	Graph graph(atoi(argv[1]));

	FILE *file;
	file = fopen(argv[2], "rt");

	read_graph(graph, file);
    int opc;

	do{
		cout << "1 - BFS" << endl;
		cout << "2 - BAGBFS" << endl;
		cout << "3 - SAIR" << endl;
		cout << "Digite a opção desejada!" << endl;
		cin >> opc;

		auto start = std::chrono::high_resolution_clock::now();
		switch (opc){
			case 1: graph.BFS(1);
				cout << "BFS time: ";
				break;
			case 2: graph.BAGBFS(1);
				cout << "BAGBFS time: ";
				break;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		cout << duration.count() << " microseconds" << endl;
	} while (opc != 3);
	return 0;
}
