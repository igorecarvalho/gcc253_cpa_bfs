#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include "graph.h"
#include "bag.h"

#define COARSENESS 32

//construtor do grafo
Graph::Graph(int leng){
	this->leng = leng;
	this->vect_adj = new std::vector<int>[this->leng];
}

//método que adiciona arestas ao vertices
void Graph::add_edge(int v, int w){
	//push_back adiciona um elemento no final do vector
	this->vect_adj[v].push_back(w);
	//grafo direcionado
	//this->vect_adj[w].push_back(v);
}

//Busca em largura tradicional
void Graph::BFS(int vertex){
	//cria um vetor de niveis para alocacao de memoria com uso de memset
	int levels[this->leng];
	//alocação de memoria para um vetor de inteiros
	memset(&levels, 0xFF, this->leng * sizeof(int));
	//criação de uma fila de inteiros
	std::queue<int> frontier;

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
		for (std::vector<int>::const_iterator it = this->vect_adj[current].begin(), end = this->vect_adj[current].end(); it != end; ++it){
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

	for (int i = 0; i < this->leng; ++i)	{
		if (levels[i] != -1){
			std::cout <<  "vertex: " << i << " - level: " << levels[i] << std::endl;
		}
	}
}

//método que gerencia e faz o processamento da bag
void Graph::process_level_bag(Bag *&frontier, Bag *&new_frontier, int levels[], int level){

	//std::cout << "entrou no process_level_bagz\n";
	
	if(frontier->bag_size() > COARSENESS){
		//cria uma bag e faz o processamento de level da bag criada e das bag's recebidas
		Bag* new_bag = frontier->bag_split();
		process_level_bag(new_bag, new_frontier, levels, level);
		process_level_bag(frontier, new_frontier, levels, level);
	}else{
		//std::cout << "ta menor q COARSENESS\n";
	
		std::stack<Vertex *> vertices;
	
		for (int i = 0; i <= frontier->largest_nonempty_index; ++i)	{
	
			//std::cout << "entrou no for: " << i << std::endl;
	
			if (frontier->backbone[i] != NULL) {

				//std::cout << "frontier->backbone[i] != NULL\n";

				vertices.push(frontier->backbone[i]->root);
				//std::cout << "vertices.push\n";

				while(vertices.size() > 0){

					//std::cout << "vertices.size(): " << vertices.size() << std::endl;

					//vertice atual é o vertice do topo da pilha e o remove
					Vertex *current = vertices.top();
					//std::cout << "current\n";

					vertices.pop();
					//std::cout << "pop vertices\n";

					//se o vertice atual possui "filho" a esquerda
					if(current->left != NULL){
						vertices.push(current->left);
						//std::cout << "vertices.push(current->left)\n";
					}
					//se o vertice atual possui "filho" a direita
					if(current->right != NULL){
						vertices.push(current->right);
						//std::cout << "vertices.push(current->right)\n";
					}

					//
					for(std::vector<int>::iterator it = this->vect_adj[current->vertex].begin(), end = this->vect_adj[current->vertex].end(); it != end; it++){
						//std::cout << "for doidao\n";
						if(levels[*it] < 0){
							//std::cout << "veio no if do it\n";
							new_frontier->bag_insert_vertex(*it);
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
	//int *x;
	memset(&levels, 0xFF, this->leng * sizeof(int));
	//std::cout << "alocou memoria" << std::endl;

	//criacao de uma bag
	Bag* frontier = new Bag(this->leng);
	//std::cout << "criou frontier\n";
	//Bag * buf;
	frontier->bag_insert_vertex(vertex);
	std::cout << "inseriu vertice na bags: " << vertex << std::endl;
	int level = 0;
	levels[vertex] = level;

	while (!frontier->bag_empty()){
		//std::cout << "bag nao ta vazia\n";
		Bag* new_frontier = new Bag(this->leng);
		//std::cout << "criou nova frontier\n";

		this->process_level_bag(frontier, new_frontier, levels, level);

		frontier->bag_clear();
        frontier->bag_merge(new_frontier);

		level++;
	}

	for (int i = 0; i < this->leng; ++i){
		if (levels[i] != -1){
			std::cout << "vertex: " << i << " - level: " << levels[i] << std::endl;
		}
	}
}
