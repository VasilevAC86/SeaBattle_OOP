#pragma once

#include"Player.hpp"

/*
* \brief Класс для создания объекта "Игра"
*/
class Game {
public:
	Game(std::string name1, std::string name2):p1_(name1),p2_(name2){}
	/// Геттер адреса игрока 1
	Player* P1() { return &p1_; }
	/// Геттер адреса игрока 2
	Player* P2() { return &p2_; }
	/*
	* \brief Метод расстановки кораблей на поле вручную
	* \details Параметр bool player определяет, какой игрок расставляет корабли
	* player = true для игрока 1, player = false для игрока 2
	*/
	void By_Hand(bool player);
private:
	Player p1_; // Игрок 1
	Player p2_; // Игрок 2
};