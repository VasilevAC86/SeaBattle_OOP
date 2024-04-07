#pragma once

#ifndef CELL_HPP
#define CELL_HPP

/*
* \brief Класс для создания объекта "Клетка"
*/
class Cell {
public:
	Cell():hor_(0), vert_('A'), state_('0'), num_ship_(0) {}	
	// Сеттер состояния
	void State(char state) { this->state_ = state; }
	/// Сеттер координаты вертикали (строка поля)
	void Vert(char vert) { this->vert_ = vert; }
	/// Сеттер координаты горизонтали (столбец поля)
	void Hor(int hor) { this->hor_ = hor; }	
	/// Геттер состояния клетки
	char State()const { return state_; }
	/// Геттер координаты горизонтали
	int Hor()const { return hor_; }
	/// Геттер координаты вертикали
	char Vert()const { return vert_; }	
	/// Геттер номера корабля, которому принадлежит клетка
	int Num_Ship()const { return num_ship_; }
	/// Сеттер номера корабля
	void Set_Num_Ship(int num) { this->num_ship_ = num; }
private:	
	int num_ship_; // Номер корабля, которому принадлежит клетка
	int hor_; // Координата горизонтали (от 1 до 10)
	char vert_; // Координата вертикали (от A до J)
	char state_; // Состояние ('0' - пусто, '1' - живой корабль, '2' - подбитый корабль, '3' - промах, 'r' - точка поворота/точка вставки корабля)	
};

#endif // !CELL_HPP