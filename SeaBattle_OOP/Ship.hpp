#pragma once

#ifndef SHIP_HPP
#define SHIP_HPP

#include"Cell.hpp"

class Ship {
public:
	Ship():point_(nullptr), size_(0), vector_('0'), state_('2') {}
	/// Сеттер размера корабля
	void Size(int size) { this->size_ = size; }
	/// Сеттер направления корабля относительно точки вставки (вращения)
	void Vector(char vector) { this->vector_ = vector; }
	/// Сеттер адреса клетки с координатами точки вставки корабля на поле
	void Point(Cell* point) { this->point_ = point; }
	void State(char state) { this->state_ = state; }
	/// Геттер размера корабля
	int Size()const { return size_; }
	/// Геттер направления размещения корабля относительно точки вставки
	char Vector()const { return vector_; }
	/// Геттер адреса точки вставки корабля
	Cell* Point() { return point_; }
	char State()const { return state_; }
private:
	Cell* point_; // Указатель на объект "Клетка" с координатами точки вставки корабля
	int size_; // Размер корабля
	char vector_; // Направление корабля относительно точки вставки (точки поворота) point
	char state_; // Состояние корабля (0 - уничтожен, 1 - ранен, 2 - целый)
};

#endif // !SHIP_HPP
