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
	/*\brief Метод расстановки кораблей на поле вручную
	* \details Параметр bool player определяет, какой игрок расставляет корабли
	* player = true для игрока 1, player = false для игрока 2
	*/
	void Hand(bool player);
	/*\brief Метод расстановки кораблей на поле автоматически
	* \details Параметр bool player определяет, какой игрок расставляет корабли
	* player = true для игрока 1, player = false для игрока 2
	*/
	void Auto(bool player);
	/*\brief Метод хода
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

/// Блок внешних функций
/// Внешняя функция отрисовки горизонтальной черты в таблице доступных кораблей
void Print_Horizon();
/*\brief Внешняя функция проверки наличия выбранного игроком типа корабля
* \details Если игрок вводит некорректные значения (<1 или > 4), функция просит игрока ввести размер корабля заново.
* Функция возвращает размер выбранног игроком корабля после проверки введённого игроком значения
*/
int Check_Position_Ship(std::string& position_text);
/// Внешняя функция определения координаты ряда игрового поля
int Enter_Row();
/// Внешняя функция определения координаты столбца игрового поля
int Enter_Col();
/// Внешняя функция перемещения курсора в точку консоли с координатами x, y
void gotoxy(int x, int y);
/// Внешняя функция получения текущей координаты консоли Х
int Xcoord();
/// Внешняя функция получения текущей координаты консоли Y
int Ycoord();

#endif // !GAME_HPP