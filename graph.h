#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include "bag.h"

class Graph{
	private:
		std::vector<int> *vect_adj;
		int leng;
	public:
		Graph (int vertex);
		void add_edge(int v, int w);
		void BFS(int vertex);
		//bfs com bag
		void process_level_bag(Bag *&frontier, Bag *&new_frontier, int levels[], int level);
		void BAGBFS(int vertex);

};

#endif //GRAPH_H
