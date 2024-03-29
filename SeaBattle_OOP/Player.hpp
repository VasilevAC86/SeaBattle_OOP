#pragma once

#ifndef PLAYER_HPP
#define PLAYER_HPP

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
	// Конструктор по умолчанию
	Player():name_("empty") {}
	/// Сеттер имение игрока
	Player(std::string name) { this->name_ = name; }
	/// Сеттер поля игрока
	void field(const Field& field) { this->field_ = field; }
	/// Геттер поля игрока
	Field field()const { return field_; }
	/// Геттер имени игрока
	std::string Name()const { return name_; }
	/// Геттер статистики игрока
	Statistic Stat()const { return s_; }
	/// Геттер флота игрока
	//std::array<Ship, 10> Fleet() { return fleet_; }	
private:
	std::string name_; // Имя игрока
	Field field_; // Игровое поле игрока
	Statistic s_; // Персональная статистика игрока	
	//std::array<Ship, 10> fleet_; // Флот игрока (массив объектов "Корабль")
};

#endif // !PLAYER_HPP