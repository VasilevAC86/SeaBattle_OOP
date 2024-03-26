#pragma once

#include"Player.hpp"

/*
* \brief Класс для создания объекта, выводящего информацию в консоль
*/
class Output {
public:
	/// Конструктор по умолчанию	
	Output():p_(nullptr){}
	/// Параметрический конструктор
	//Output(Player *p) { this->p_ = p; }	
	/// Метод для вывода игрового поля и таблицы с информацией о флоте пользователя в консоль
	void Print();
	/// Сеттер игрока
	void Set_Player(Player* p) { this->p_ = p; }	
private:
	Player *p_; // Адрес объекта "Игрок"
	
};