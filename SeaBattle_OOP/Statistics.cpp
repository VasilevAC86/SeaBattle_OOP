#include "Statistics.hpp"

void Statistic::Add_Ship(int size) {
	switch (size) {
	case 1: 
		++num_1_;
		++num_all_;
		break;
	case 2:
		++num_2_;
		++num_all_;
		break;
	case 3:
		++num_3_;
		++num_all_;
		break;
	default:
		++num_4_;
		++num_all_;
	}
}

void Statistic::Pop_Ship(int size) {
	switch (size) {
	case 1:
		--num_1_;
		--num_all_;
		break;
	case 2:
		--num_2_;
		--num_all_;
		break;
	case 3:
		--num_3_;
		--num_all_;
		break;
	default:
		--num_4_;
		--num_all_;
	}
}
