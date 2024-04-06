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
	/// Метод для обведения уничтоженного корабля "прострелянными" клетками
	void Snake(int num);	
	/* \brief Метод установки нового корабля на поле после проверки возможности его установки
		* \details Если точка вставки соприкасается с уже существующим кораблём, или
		* игрок пытается установить корабль в уже занятую клетку, метод возвращает false
		* Если корабль по правилам игры расположить получилось, то метод возвращает true
	*/
	bool Exam_Position(int row, int col, int num);
	/*\brief Метод проверки возможности установки корябля размером size по координате (row, col) при вращении его вокруг (row, col)
		* \details Метод возвращает направление размещения корабля по правилам относительно точки вставки (row, col).
		* Если корабль по правилам разместить не удаётся, то метод возвращает "x".
	*/
	char Orientation(int row, int col, int size);
	/*\brief Метод поворота корабля на игровом поле
		* \details Метод поворачивает установленный на поле корабль один раз по часовой стрелке.
		* Если корабль повернуть не удаётся, метод сообщает об этом.
	*/
	void Rotation(int row, int col, int num);
	/// Метод проверки возможности поворота корабля вниз относительно точки (row, col)	
	bool Exam_Turn_Down(int row, int col, int size);
	/// Метод проверки возможности поворота корабля налево относительно точки (row, col)	
	bool Exam_Turn_Left(int row, int col, int size);
	/// Метод проверки возможности поворота корабля вверх относительно точки (row, col)	
	bool Exam_Turn_Up(int row, int col, int size);
	/// Метод проверки возможности поворота корабля направо относительно точки (row, col)	
	bool Exam_Turn_Right(int row, int col, int size);	
private:
	Cell matrix_[_SIZE][_SIZE]; // Матрица объектов класса "Клетка"
	std::array<Ship, _QAUNTITY> fleet_; // Флот игрока (массив объектов "Корабль")	
};

#endif // !FIELD_HPP