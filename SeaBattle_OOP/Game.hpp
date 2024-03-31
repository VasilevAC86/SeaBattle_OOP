#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include"Player.hpp"

/*
* Интерфейс для вывода информации об игроках в консоль
*/
class Viewer {
public:
	/// Виртуальная функция для вывода в консоль инф-ии о текущем игроке
	void Print_Player_Active(Player & p); 
	/// Виртуальная функция для вывода в консоль инф-ии о ждущем своего хода игроке
	void Print_Player_Passive(Player& const p);
};

/*
* \brief Класс для создания объекта "Игра"
*/
class Game:public Viewer {
public:	
	Game(std::string name1, std::string name2):p1_(name1),p2_(name2){}
	/// Геттер игрока 1
	Player P1() { return p1_; }
	/// Геттер игрока 2
	Player P2() { return p2_; }
	/*
	* \brief Метод расстановки кораблей на поле вручную
	* \details Параметр bool player определяет, какой игрок расставляет корабли
	* player = true для игрока 1, player = false для игрока 2
	*/
	void Hand(bool player);
	/*
	* \brief Метод расстановки кораблей на поле автоматически
	* \details Параметр bool player определяет, какой игрок расставляет корабли
	* player = true для игрока 1, player = false для игрока 2
	*/
	void Auto(bool player);
private:
	Player p1_; // Игрок 1
	Player p2_; // Игрок 2
};

#endif // !GAME_HPP