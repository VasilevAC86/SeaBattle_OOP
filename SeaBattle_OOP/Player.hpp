#pragma once

#include"Field.hpp"
#include"Statistics.hpp"
#include"Ship.hpp"

#include<iostream>
#include<string>
//#include<array>

/*
* \brief Класс для создания объекта "Игрок"
*/
class Player {
public:
	Player(){} // Конструктор по умолчанию
	/// Сеттер имение игрока
	Player(std::string name) { this->name_ = name; }
	/// Сеттер поля игрока
	void field(const Field& field) { this->field_ = field; }
	/// Геттер адреса поля игрока
	Field* field() { return &field_; }
	/// Геттер имени игрока
	std::string Name()const { return name_; }
	/// Геттер адреса статистики игрока
	Statistic* Stat() { return &s_; }
	/// Геттер флота игрока
	//std::array<Ship, 10> Fleet() { return fleet_; }	
private:
	std::string name_; // Имя игрока
	Field field_; // Игровое поле игрока
	Statistic s_; // Персональная статистика игрока	
	//std::array<Ship, 10> fleet_; // Флот игрока (массив объектов "Корабль")
};