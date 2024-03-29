#pragma once

#ifndef FIELD_HPP
#define FIELD_HPP

#include"Cell.hpp"
#include"Global.hpp"

/*
* \brief Класс для создания объекта "Игровое поле"
*/
class Field {
public:
	/// Конструктор по умолчанию
	Field();
	/// Метод заполнения поля объектами "Корабль"
	void Fill_in();
	/// Метода для вывода игрового поля в консоль
	//void Print();	
	/// Геттер объекта "Клекта" по переданным координатам
	Cell At(int hor, int vert) { return matrix_[hor][vert]; }
private:	
	Cell matrix_[_SIZE][_SIZE]; // Матрица объектов класса "Клетка"
};

#endif // !FIELD_HPP