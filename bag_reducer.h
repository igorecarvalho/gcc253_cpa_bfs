#ifndef BAG_REDUCER_H
#define BAG_REDUCER_H

#include "bag.h"

class Bag_reducer {
	public:
		static void reducer(Bag *left, Bag *right){
			left->bag_merge(right);
		}

		Bag_reducer(){
			
		}
}