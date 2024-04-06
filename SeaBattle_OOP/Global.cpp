#include "Global.hpp"
#include<iostream>

char Exc(std::string tmp) {
	try {
		if (tmp.size() != 1)
			throw std::exception("\n\033[91mInput error! The entered value is not a symbol!\033[0m\n");
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
		bool key = false;
		while (!key) {
			std::cout << "Enter \033[4myour choise\033[0m one more time (one symbol) -> ";
			std::cin >> tmp;
			if (tmp.size() != 1)
				key = false;
			else
				key = true;
		}
	}
	return tmp.at(0);
}
