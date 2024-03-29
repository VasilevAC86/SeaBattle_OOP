#pragma once

#ifndef SHIP_HPP
#define SHIP_HPP

#include<iostream>
#include<array>

#include"Cell.hpp"

/*
* \brief Базовый абстрактный класс для создания кораблей
*/
class Ship {
public:
	Ship() :state_('0') {} // Конструктор по умолчанию	
	///Шаблонный параметрический конструктор для создания объекта "корабль"	
	//template <int size>
	Ship(char hor, char vert);	
protected:		
	char state_; // Состояние корабля ('0' - целый, '1' - ранен, '2' - убит)
};

/*
* \brief Класс-наследник для создания 4-ёх палубного корабля 
*/
class Ship_4 :public Ship {
public:
	Ship_4(char hor, char vert) : Ship(hor, vert) {};
private:
	const int size_ = 4; // Размер корабля	
};

/*
* \brief Класс-наследник для создания 3-ёх палубного корабля
*/
class Ship_3 :public Ship {
public:
	Ship_3(char hor, char vert) : Ship(hor, vert) {};
private:
	const int size_ = 3; // Размер корабля	
};

/*
* \brief Класс-наследник для создания 4-ёх палубного корабля
*/
class Ship_2 :public Ship {
public:
	Ship_2(char hor, char vert) : Ship(hor, vert) {};
private:
	const int size_ = 2; // Размер корабля	
};

/*
* \brief Класс-наследник для создания однопалубного корабля
*/
class Ship_1 :public Ship {
public:
	//Ship_1(char hor, char vert):Ship(hor, vert, ship_) {};
	Ship_1(char hor, char vert) {		
		this->ship_.State('1');
		this->ship_.Hor(hor);
		this->ship_.Vert(vert);
	}
private:
	const int size_ = 1; // Размер корабля
	Cell ship_; // Клетка корабля	
};

#endif // !SHIP_HPP