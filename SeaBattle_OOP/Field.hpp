#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include<array>
#include<iostream>

#include"Cell.hpp"
#include"Global.hpp"
#include"Ship.hpp"

/*
* \brief Класс для создания объекта "Игровое поле"
*/
class Field {
public:
	/// Конструктор по умолчанию
	Field();
	/// Геттер объекта "Клекта" по координатам для просмотра информации
	Cell At_Get(int hor, int vert)const { return matrix_[hor][vert]; }
	/// Доступ к объекту "Клетка" по координатам для изменения параметров объекта "Клетка"
	Cell* At_Set(int hor, int vert) { return &matrix_[hor][vert]; }
	/// Доступ к объекту "Корабль" по индексу массива для изменения параметров объекта "Корабль"
	Ship& At_Set_Ship(int num) { return fleet_[num]; }
	/// Геттер объекта "Корабль" по индексу массива для просмотра информации
	Ship At_Get_Ship(int num)const {return fleet_[num]; }
	/// Метод перевода занятых клеток поля (статус '1') в статус '0' (пусто) и очистки данных о кораблях
	void Clear();	
private:	
	Cell matrix_[_SIZE][_SIZE]; // Матрица объектов класса "Клетка"
	std::array<Ship, _QAUNTITY> fleet_; // Флот игрока (массив объектов "Корабль")	
};

#endif // !FIELD_HPP