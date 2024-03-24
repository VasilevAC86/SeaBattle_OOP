#pragma once

#include"Field.hpp"
#include"Statistics.hpp"

#include<iostream>
#include<string>

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
	/// Геттер поля игрока
	Field field() { return field_; }
	/// Геттер имени игрока
	std::string Name() { return name_; }
	/// Геттер статистики игрока
	Statistic Stat() { return s_; }
private:
	std::string name_; // Имя игрока
	Field field_; // Игровое поле игрока
	Statistic s_; // Персональная статистика игрока	
};