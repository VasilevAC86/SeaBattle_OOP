#pragma once

/*
* \brief Класс для создания объекта "Клетка"
*/
class Cell {
public:
	//Cell() :state_('0'), hor_('A'), vert_(1){}
	// Сеттер состояния
	void State(char state) { this->state_ = state; }
	// Сеттер координаты вертикали (строка поля)
	void Vert(char vert) { this->vert_ = vert; }
	// Сеттер координаты горизонтали (столбец поля)
	void Hor(char hor) { this->hor_ = hor; }	
	/// Геттер состояния клетки
	char State() { return state_; }
	/// Геттер координаты горизонтали
	char Hor() { return hor_; }
	/// Геттер координаты вертикали
	char Vert() { return vert_; }
private:
	char state_; // Состояние ('0' - пусто, '1' - живой корабль, '2' - подбитый корабль, '3' - промах, 'r' - точка поворота)
	char hor_; // Координата горизонтали (от A до J)
	char vert_; // Координата вертикали (от 1 до 10)
};