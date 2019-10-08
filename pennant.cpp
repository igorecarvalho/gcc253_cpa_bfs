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
	if (y == NULL) return;

	//atribui ao vertice da esquerda do vertice recebido pela funcao union o vertice
	//da esquerda da raiz
	y->root->left = this->root->left;
	this->root->left = y->root;
	y->root = NULL;
	delete y;
	y = NULL;
}

//Implementação da função de split
Pennant* Pennant::pennant_split(){
	if (this->root->left == NULL){
		return NULL;
	}

	//aloca um novo pennant que sua raiz é o nó da esquerda da raiz
	Pennant *y = new Pennant(this->root->left);
	//no a esquerda se torna o no da direita
	this-root->left = y->root->right;
	//no da direira se torna nulo
	y->root->right = NULL;
	//retorna o novo pennant
	return y;
}

//Implementação da função suporte a função de união
//esta função verifica onde e quais vertices realização a união
void Pennant::support_merge(Pennant *&x, Pennant *&y, Pennant *&carry){
	if (x == NULL && y == NULL && carry == NULL) {
		return;
	}
	if (x != NULL && y == NULL && carry == NULL) {
		return;
	}
	if (x == NULL && y != NULL && carry == NULL) {
		x = y;
		y = NULL;
		return;
	}
	if (x == NULL && y == NULL && carry != NULL) {
		x = carry;
		carry = NULL;
		return;
	}
	if (x != NULL && y != NULL && carry == NULL) {
		x->pennant_union(y);
		carry = x;
		x = NULL;
		return;
	}
	if (x != NULL && y == NULL && carry != NULL) {
		x->pennant_union(carry);
		carry = x;
		x = NULL;
		return;
	}
	if (x == NULL && y != NULL && carry != NULL) {
		y->pennant_union(carry);
		carry = y;
		y = NULL;
		return;
	}
	if (x != NULL && y != NULL && carry != NULL) {
		carry->pennant_union(y);
		return;
	}
}