#pragma once

#ifndef SHIP_HPP
#define SHIP_HPP

#include"Cell.hpp"

class Ship {
public:
	Ship():point_(nullptr), size_(0), vector_('0'), state_('2'), capacity_(0) {}
	/// Сеттер размера корабля
	void Size(int size) { this->size_ = size; }
	/// Сеттер направления корабля относительно точки вставки (вращения)
	void Vector(char vector) { this->vector_ = vector; }
	/// Сеттер адреса клетки с координатами точки вставки корабля на поле
	void Point(Cell* point) { this->point_ = point; }
	/// Сеттер состояния корабля
	void State(char state) { this->state_ = state; }
	/// Геттер размера корабля
	int Size()const { return size_; }
	/// Геттер направления размещения корабля относительно точки вставки
	char Vector()const { return vector_; }
	/// Геттер адреса точки вставки корабля
	Cell* Point() { return point_; }
	/// Геттер состояния корабля
	char State()const { return state_; }
	/// Геттер кол-ва "живых" клеток корабля
	int Capacity()const { return capacity_; }
	/// Сеттер кол-ва "живых" клеток корабля
	void Capacity(int capacity) { this->capacity_ = capacity; }
	/// Метод уменьшения кол-ва "живых клеток корабля"
	void Change_Capacity() { --capacity_; }
private:
	Cell* point_; // Указатель на объект "Клетка" с координатами точки вставки корабля
	int size_; // Размер корабля
	int capacity_; // Кол-во "живых" клеток корабля
	char vector_; // Направление корабля относительно точки вставки (точки поворота) point
	char state_; // Состояние корабля (0 - уничтожен, 1 - ранен, 2 - целый)
};

#endif // !SHIP_HPP
