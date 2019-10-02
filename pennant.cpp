#include <stack>
#include "vertex.h"
#include "pennant.h"

using namespace std;

//Implementação do construtor
Pennant::Pennant(Vertex* root){
	this-> = root;
}

//Implementação do destrutor
Pennant::~Pennant(){
	//Verifica se a raiz não é nule e precisa realmente ser desalacoda memória
	if (this->root != NULL){
		//Criação uma pilha de vertices
		stack<Vertex *> vertices;

		//insere o a raiz no pilha
		vertices.push(this->root)
		//verifica o tamanho da pilha de vertices, caso seja maior que zero tem a
		//necessidade de desalocar memória
		while (vertices.size() > 0){

			Vertex *current = vertices.top();
			vertices.pop();

			//desaloca os vertices adjacentes na arvore binaria, caso existam.
			if (current->left != NULL){
				vertices.push(current->left);
			}
			if (current->right != NULL){
				vertices.push(current->right);
			}
			//deleta vertice atual
			delete current
		}
	}
}

//Implementação da função de união
void Pennant::pennant_union(Pennant *&y){

}