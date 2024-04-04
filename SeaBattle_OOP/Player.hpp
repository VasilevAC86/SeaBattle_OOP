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
	/*
	* \brief Метод тотальной очистки данных игрока
	* \details Используется, когда игрок решил изменить расположение кораблей 
	на поле после не понравившейся автоматической расстановки.
	Метод в поле статистика переводит все счётчики кораблей в ноль, чистит клетки
	поля от статуса "занято", изменяет данные кораблей в массиве fleet_(флот)
	*/
	void Clear();
	/*
	* \brief Метод проверки игрока на проигрыш
	* \details Проверяет статус объектов "Корабль". Если все корабли уничтожены, то возвращает true.
	* Если у игрока ещё есть "живые" корабли, то возвращает false
	*/
	bool Loser();
private:
	std::string name_; // Имя игрока
	Field field_; // Игровое поле игрока
	Statistic s_; // Персональная статистика игрока		
};

#endif // !PLAYER_HPP