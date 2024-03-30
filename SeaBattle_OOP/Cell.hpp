#pragma once

#ifndef CELL_HPP
#define CELL_HPP

/*
* \brief Класс для создания объекта "Клетка"
*/
class Cell {
public:
	Cell()  :hor_(1), vert_('A'), state_('0') {}	
	// Сеттер состояния
	void State(char state) { this->state_ = state; }
	// Сеттер координаты вертикали (строка поля)
	void Vert(char vert) { this->vert_ = vert; }
	// Сеттер координаты горизонтали (столбец поля)
	void Hor(int hor) { this->hor_ = hor; }	
	/// Геттер состояния клетки
	char State()const { return state_; }
	/// Геттер координаты горизонтали
	int Hor()const { return hor_; }
	/// Геттер координаты вертикали
	char Vert()const { return vert_; }	
private:	
	int hor_; // Координата горизонтали (от 1 до 10)
	char vert_; // Координата вертикали (от A до J)
	char state_; // Состояние ('0' - пусто, '1' - живой корабль, '2' - подбитый корабль, '3' - промах, 'r' - точка поворота/точка вставки корабля)
};

#endif // !CELL_HPP