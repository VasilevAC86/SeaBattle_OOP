#pragma once

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

/*
* \brief Класс для создания объекта, хранящего статистику
*/
class Statistic {
public:
	/// Конструктор по умолчанию
	Statistic() :num_all_(0), num_1_(0), num_2_(0), num_3_(0), num_4_(0), useless_moves_(0) {}
	/// Геттер кол-ва однопалубных "живых" кораблей
	int Num_1()const { return num_1_; }
	/// Геттер кол-ва двухпалубных "живых" кораблей
	int Num_2()const { return num_2_; }
	/// Геттер кол-ва трёхпалубных "живых" кораблей
	int Num_3()const { return num_3_; }
	/// Геттер кол-ва четырёхпалубных "живых" кораблей
	int Num_4()const { return num_4_; }
	/// Геттер общего кол-ва "живых" кораблей
	int Num_All()const { return num_all_; }		
	/// Метод добавления кораблей
	void Add_Ship(int size);
	/// Метод удаления кораблей
	void Pop_Ship(int size);	
	/// Метод сброса кол-ва кораблей в ноль
	void Clear() {
		this->num_1_ = 0;
		this->num_2_ = 0;
		this->num_3_ = 0;
		this->num_4_ = 0;
		this->num_all_ = 0;
	}	
	/// Метод увеличения кол-ва бесполезных ходов
	void Add_Useless_Moves() { ++useless_moves_; }
	/// Геттер бесполезных ходов
	int Useless_Moves()const { return useless_moves_; }
	/// Метод сброса в ноль кол-ва бесполезных ходов
	void Clear_Useless_Moves() { this->useless_moves_ = 0; }
private:
	int num_all_; // Всего "живых" кораблей
	int num_1_; // Кол-во "живых" одно-клеточных кораблей
	int num_2_; // Кол-во "живых" двух-клеточных кораблей
	int num_3_; // Кол-во "живых" трёх-клеточных кораблей
	int num_4_; // Кол-во "живых" четырёх-клеточных кораблей
	int useless_moves_; // Счётчик бесполезных ходов-промахов (для работы уровня сложности ИИ)
};

#endif // !STATISTICS_HPP