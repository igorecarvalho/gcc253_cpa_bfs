#include <cmath>
#include <cstdlib>
#include <iostream>
#include "bag.h"
#include "vertex.h"
#include "pennant.h"

using namespace std;

//método para inicializacao das bag de acordo com o posição no vetor
//posicao que tambem servirá como tamanho da bag
void Bag::bag_init(int len){
	this->backbone = new Pennant*[len]();
	this->len = len;
	this->largest_nonempty_index = -1;
}

//construtor com parâmentros vazio, inicializa uma bag de tamanho 20
Bag::Bag(){
	this->bag_init(20);
}

//construtor com parametro de tamanho para criação da bag
Bag::Bag(int k){
	this->bag_init(k);
}

//método que percorre a bag e deleta o backbone de cada posição
void Bag::bag_clear(){
	for (int i = 0; i <= this->largest_nonempty_index; ++i)	{
		delete this->backbone[i];
		this->backbone[i] = NULL;
	}
	this->largest_nonempty_index = -1;
}

//destrutor
Bag::~Bag(){
	this->bag_clear();
	delete[] this->backbone;
}

//método que insere um novo vertice na bag
void Bag::bag_insert_vertex(int value){
	Vertex* vertex = new Vertex(value);
	Pennant *vertices = new Pennant(vertex);
	this->bag_insert(vertices);
}

//método que realiza a inserção dos pennants na bag
void Bag::bag_insert(Pennant *&vertices){
	int i = 0;
	while (this->backbone[i] != NULL){
		this->backbone[i]->pennant_union(vertices);
		vertices = this->backbone[i];
		this->backbone[i] = NULL;
		++i;
	}

	this->backbone[i] = vertices;
	if (i > largest_nonempty_index){
		this->largest_nonempty_index = i;
	}
}

//método que realiza o marge entre duas bags
void Bag::bag_merge(Bag* bag){
	int max_index = max(bag->largest_nonempty_index, this->largest_nonempty_index);
	Pennant *carry = NULL;

	for (int i = 0; i <= max_index; ++i)	{
		Pennant::support_merge(this->backbone[i], bag->backbone[i], carry);
	}

	//caso carry seja diferente de nulo então houve um split e carry possui parte dos
	//pennants
	if (carry != NULL) {
		max_index++;
		//carrry é inserido na ultima posicao do backbone
		this->backbone[max_index] = carry;
	}
	this->largest_nonempty_index = max_index;
}

//método que faz o split de uma bag e retorna uma das partes
Bag* Bag::bag_split(){
	Bag *splited_bag = new Bag(this->len);
	Pennant *first_elemment = this->backbone[0];
	this->backbone[0] = NULL;

	for (int i = 1; i <= this->largest_nonempty_index; ++i)	{
		if (this->backbone[i] != NULL){
			splited_bag->backbone[i-1] = this->backbone[i]->pennant_split();
			this->backbone[i-1] = this->backbone[i];
			this->backbone[i] = NULL;
		}
	}

	//atualiza o maior indice da bag com elementos e atribui a nova bag do split
	if (this->largest_nonempty_index != 0){
		this->largest_nonempty_index = this->largest_nonempty_index--;
		splited_bag->largest_nonempty_index = this->largest_nonempty_index;
	}

	if (first_elemment != NULL) {
		this->bag_insert(first_elemment);
	}

	return splited_bag;
}

//imprime a bag
void Bag::bag_print(){
	cout << "Bag: { ";
	for (int i = 0; i < this->len; ++i){
		cout << (this->backbone[i] != NULL) * pow(2, i) << " ";
	}
	cout << "}" << endl;
}

//retorna no tamanho da bag
int Bag::bag_size(){
	int leng = 0;
	for (int i = 0; i <= this->largest_nonempty_index ; ++i){
		if(this->backbone[i] != NULL){
			leng += pow(2, i);
		}
	}
	return leng;
}

//verifica se a bag esta vazia
bool Bag::bag_empty(){
	return (this->largest_nonempty_index < 0);
}
