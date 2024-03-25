#include"Ship.hpp"

template <int size>
Ship::Ship(char hor, char vert, std::array<Cell, size> arr) {
	this->state_ = '0';
	for (Cell& el : arr) {		
		el.Hor(hor);
		el.Vert(vert);
		el.State('1');
	}
}

