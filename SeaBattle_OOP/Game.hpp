#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include"Player.hpp"

/// Интерфейс для вывода информации об игроках в консоль
class Viewer {
public:
	/// Виртуальная функция для вывода в консоль инф-ии о текущем игроке
	void Print_Player_Active(Player & p); 
	/// Виртуальная функция для вывода в консоль инф-ии о ждущем своего хода игроке
	void Print_Player_Passive(Player& p);
};

/*
* \brief Класс для создания объекта "Игра"
*/
class Game:public Viewer {
public:	
	Game(std::string name1, std::string name2):p1_(name1),p2_(name2){}	
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
	/*
	* \brief Метод хода
	* \details Параметр bool player определяет, какой игрок делает ход
	* player = true для игрока 1, player = false для игрока 2	
	*/
	void Move(bool player);
	/// Геттер игрока 1 для просмотра информации
	Player P1()const { return p1_; }
	/// Геттер игрока 2 для просмотра информации
	Player P2()const { return p2_; }
private:
	Player p1_; // Игрок 1
	Player p2_; // Игрок 2
};

#endif // !GAME_HPP