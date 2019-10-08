#ifndef BAG_H
#define BAG_H

#include "pennant.h"

class Bag{
	private:
		//Posicao no vetor
		int k;

	public:
		Pennant** backbone;
		int largest_nonempty_index;

		Bag();
		Bag(int r);
		~Bag();
		void bag_clear();
		void bag_init(int len);
		void bag_insert_vertex(int vertex);
		void bag_insert(pennant *&vertices);
		void bag_merge(Bag* y);
		Bag* bag_split();
		void bag_print();
		void bag_size();
		bool bag_empty();
};