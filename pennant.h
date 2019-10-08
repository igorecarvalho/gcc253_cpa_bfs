#ifndef PENNANT_H
#define PENNANT_H

#include "vertex.h"

class Pennant{
	public:
		Vertex *root;

		//Construtor do pennant a partir de um vértice raiz
		Pennant(Vertex* root);

		//Destrutor
		~Pennant();

		//Método que faz a união entre dois Pennants
		void pennant_union(Pennant *&y);

		//Método que faz a divisão do Pennant e retorna
		Pennant* pennant_split();

		//Método que define onde o merge será realizado
		static void support_merge(Pennant *&x, Pennant *&y, Pennant *&carry);
};

#endif