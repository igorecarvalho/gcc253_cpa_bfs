#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include "graph.h"
#include "bag.h"

using namespace std;

#define COARSENESS 25

//construtor do grafo
Graph::Graph(int leng){
	this->leng = leng;
	this->vect_adj = new vector<int>[this->leng];
}

//método que adiciona arestas ao vertices
void Graph::add_edge(int v, int w){
	//push_back adiciona um elemento no final do vector
	this->vect_adj[v].push_back(w);
	this->vect_adj[w].push_back(v);
}

//Busca em largura tradicional
void Graph::BFS(int vertex){
	//cria um vetor de niveis para alocacao de memoria com uso de memset
	int levels[this->leng];
	//alocação de memoria para um vetor de inteiros
	memset(&levels, 0xFF, this->leng * sizeof(int))
	//criação de uma fila de inteiros
	queue<int> frontier;

	int level = 0;
	//inserção na fila
	frontier.push(vertex);
	levels[vertex] = level;

	int last_elem_in_level = vertex;

	while (!frontier.empty()){
		//retorna uma referencia para o próximo elemento da fila
		int current = frontier.front();
		//remove o proximo elemento da fila e diminui o tamanho da fila
		frontier.pop();
		//realiza o "for" iterando com base nos elementos do vector
		for (vector<int>::const_iterator it = this->vect_adj[current].begin(), end = this->vect_adj[current].end(); it != end; ++it){
			if (levels[*it] < 0){
				frontier.push(*it);
				levels[*it] = level + 1;
			}
		}
		if (current == last_elem_in_level){
			++level;
			//ultimo elemento da fila
			last_elem_in_level = frontier.back();
		}
	}

	for (int i = 0; i < this->vertex; ++i)	{
		cout << i << ": " << levels[i] << endl;
	}
}

//método que gerencia e faz o processamento da bag
void Graph::process_level_bag(Bag *&frontier, Bag *&new_frontier, int levels[], int level){
	if(frontier->size() > COARSENESS){
		//cria uma bag e faz o processamento de level da bag criada e das bag's recebidas
		Bag* new_bag = frontier->split();
		process_level_bag(new_bag, new_frontier, levels, level);
		process_level_bag(frontier, new_frontier, levels, level);
	}else{
		stack<Vertex *> vertices;
		for (int i = 0; i <= frontier->largest_nonempty_index; ++i)	{
			if (frontier->backbone[i] != NULL) {
				vertices.push(frontier->backbone[i]->root);
				while(vertices.size() > 0){
					//vertice atual é o vertice do topo da pilha e o remove
					Vertex *current = vertices.top();
					vertices.pop();

					//se o vertice atual possui "filho" a esquerda
					if(current->left != NULL){
						vertices.push(current->left);
					}
					//se o vertice atual possui "filho" a direita
					if(current->rigth != NULL){
						vertices.push(current->right);
					}

					//
					for(vector<int>::iterator it = this->vect_adj[current->vertex].begin(), end = this->vect_adj[current->vertex].end(); it != end; ++it){
						if(levels[*it] < 0){
							new_frontier.bag_insert_vertex(*it);
							levels[*it] = level + 1;
						}
					}
				}
			}
		}
	}
}

void Graph::BAGBFS(int vertex){
	//criação de um vetor de tamanho do grafo
	int levels[this->leng];
	memset(&levels, 0xFF, this->leng * sizeof(int));

	//criacao de uma bag
	Bag* frontier = new Bag();
	Bag * buf;
	frontier->bag_insert_vertex(vertex);
	int level = 0;
	levels[vertex] = level;

	while (!frontier.empty()){
		Bag new_frontier;

		this->process_level_bag(frontier, new_frontier, levels, level);

		frontier->bag_clear();
		frontier->bag_merge(new_frontier.get_value());

		level++;
	}

	for (int i = 0; i < this->leng; ++i){
		cout << i << ": " << levels[i] << endl;
	}
}