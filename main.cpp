#include <cstring>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <string>
#include <set>
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
	
	return 0;
}