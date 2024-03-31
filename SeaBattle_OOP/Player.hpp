#pragma once

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include"Field.hpp"
#include"Statistics.hpp"

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
	/// Доступ к статистике игрока для считывания информации
	Statistic Get_Stat()const { return s_; }
	/// Доступ к полю игрока для считывания информации
	Field Get_Field()const { return field_; }
	/// Геттер имени игрока
	std::string Name()const { return name_; }
	/// Доступ к статистике игрока для изменения информации
	Statistic &Set_Stat() { return s_; }
	/// Доступ к полю игрока для изменения
	Field &Set_Field() { return field_; }
	
private:
	std::string name_; // Имя игрока
	Field field_; // Игровое поле игрока
	Statistic s_; // Персональная статистика игрока	
	//std::array<Ship, 10> fleet_; // Флот игрока (массив объектов "Корабль")
};

#endif // !PLAYER_HPP