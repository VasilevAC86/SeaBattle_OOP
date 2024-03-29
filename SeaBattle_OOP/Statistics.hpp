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
	/// Геттеры кол-ва кораблей
	int Num_1() { return num_1_; }
	int Num_2() { return num_2_; }
	int Num_3() { return num_3_; }
	int Num_4() { return num_4_; }
	int Num_All() { return num_all_; }	
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