#pragma once

/*
* \brief Класс для создания объекта "Клетка"
*/
class Cell {
public:
	//Cell() :state_('0'), hor_('A'), vert_(1){}
	// Блок сеттеров
	void State(char state) { this->state_ = state; }
	void Coordinate(char hor, char vert) {
		this->hor_ = hor;
		this->vert_ = vert;		
	}
	/// Геттер состояния клетки
	char State() { return state_; }
	/// Геттер координаты горизонтали
	char Coordinate_hor() { return hor_; }
	/// Геттер координаты вертикали
	char Coordinate_vert() { return vert_; }
private:
	char state_; // Состояние ('0' - пусто, '1' - живой корабль, '2' - подбитый корабльб '3' - промах)
	char hor_; // Координата горизонтали (от A до J)
	char vert_; // Координата вертикали (от 1 до 10)
};