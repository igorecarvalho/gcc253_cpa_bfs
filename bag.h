#ifndef BAG_H
#define BAG_H

#include "pennant.h"

class Bag{
	private:
		//Tamanho da bag
		int len;

	public:
		Pennant** backbone;
		int largest_nonempty_index;

		Bag();
		Bag(int r);
		~Bag();
		void bag_clear();
		void bag_init(int len);
		void bag_insert_vertex(int vertex);
		void bag_insert(Pennant* vertices);
		void bag_merge(Bag* y);
		Bag* bag_split();
		void bag_print();
		int bag_size();
		bool bag_empty();
};

#endif //BAG_H
