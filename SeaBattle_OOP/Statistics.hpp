#pragma once

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

/*
* \brief Класс для создания объекта, хранящего статистику
*/
class Statistic {
public:
	/// Конструктор по умолчанию
	Statistic() :num_all_(0), num_1_(0), num_2_(0), num_3_(0), num_4_(0), move_(0) {}
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
	/// Методы изменения кол-ва кораблей	
	void Change_1() {
		++num_1_;
		++num_all_;
	}
	void Change_2() {
		++num_2_;
		++num_all_;
	}
	void Change_3() {
		++num_3_;
		++num_all_;
	}
	void Change_4() {
		++num_4_;
		++num_all_;
	}
private:
	int num_all_; // Всего "живых" кораблей
	int num_1_; // Кол-во "живых" одно-клеточных кораблей
	int num_2_; // Кол-во "живых" двух-клеточных кораблей
	int num_3_; // Кол-во "живых" трёх-клеточных кораблей
	int num_4_; // Кол-во "живых" четырёх-клеточных кораблей
	int move_; // Номер игрового хода
};

#endif // !STATISTICS_HPP