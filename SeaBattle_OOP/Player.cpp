﻿#include "Player.hpp"

void Player::Clear() {
	s_.Clear(); // Сбрасываем статистику кораблей в ноль
	field_.Clear(); // Меняем статус клеток на '0' (пусто) и чистим данные о кораблях
}