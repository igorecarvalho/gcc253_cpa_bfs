#ifndef VERTEX_H
#define VERTEX_H

#include <cstdlib>

//Criação de uma estrutura para comportar cada vertice do grafo
struct Vertex{
	int vertex;
	Vertex* left;
	Vertex* right;

	Vertex(int x){
		this->vertex = x;
		this->left = NULL;
		this->right = NULL;
	}	
};

#endif

