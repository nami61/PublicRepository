#pragma once

#include "aqua.h"

namespace collision
{
	bool CircleAndRectangle(aqua::CVector2 circle_pos,float radius, aqua::CVector2 rectangle_pos, aqua::CVector2 size);

	bool RectangleAndRectangle(aqua::CVector2 first_pos, aqua::CVector2 first_size, aqua::CVector2 second_pos, aqua::CVector2 second_size);

	bool IsPlayerOnBoard(aqua::CVector2 player_pos, aqua::CVector2 player_size, aqua::CVector2 floor_pos, aqua::CVector2 floor_size);
};