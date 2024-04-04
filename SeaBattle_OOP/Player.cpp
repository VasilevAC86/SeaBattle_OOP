#include "Player.hpp"

void Player::Clear() {
	s_.Clear(); // Сбрасываем статистику кораблей в ноль
	field_.Clear(); // Меняем статус клеток на '0' (пусто) и чистим данные о кораблях
}

bool Player::Loser() {
	for (int i = 0; i < _QAUNTITY; ++i) {
		if (Get_Field().At_Get_Ship(i).State())
			return true;
	}

	return false;
}
