#include "Collision.h"

bool collision::CircleAndRectangle(aqua::CVector2 circle_pos, float radius, aqua::CVector2 rectangle_pos, aqua::CVector2 size)
{
	aqua::CVector2 circleCenter;
	aqua::CVector2 rectangleStart;
	aqua::CVector2 rectangleEnd;

	circleCenter.x = circle_pos.x + radius;
	circleCenter.y = circle_pos.y + radius;

	rectangleStart.x = rectangle_pos.x;
	rectangleStart.y = rectangle_pos.y;

	rectangleEnd.x = rectangle_pos.x + size.x;
	rectangleEnd.y = rectangle_pos.y + size.y;
		
	bool a = false, b = false, c = false, d = false, e = false, f = false;
	bool result = false;

	a = (circleCenter.x > rectangleStart.x) &&
		(circleCenter.x < rectangleEnd.x) &&
		(circleCenter.y > rectangleStart.y - radius) &&
		(circleCenter.y < rectangleEnd.y + radius);

	b = (circleCenter.x > rectangleStart.x - radius) &&
		(circleCenter.x < rectangleEnd.x + radius) &&
		(circleCenter.y > rectangleStart.y) &&
		(circleCenter.y < rectangleEnd.y);

	c = std::powf(rectangleStart.x - circleCenter.x, 2) +
		std::powf(rectangleStart.y - circleCenter.y, 2) <
		std::powf(radius, 2);

	d = std::powf(rectangleEnd.x - circleCenter.x, 2) +
		std::powf(rectangleStart.y - circleCenter.y, 2) <
		std::powf(radius, 2);

	e = std::powf(rectangleEnd.x - circleCenter.x, 2) +
		std::powf(rectangleEnd.y - circleCenter.y, 2) <
		std::powf(radius, 2);

	f = std::powf(rectangleStart.x - circleCenter.x, 2) +
		std::powf(rectangleEnd.y - circleCenter.y, 2) <
		std::powf(radius, 2);

	result = a || b || c || d || e || f;

	return result;
}

bool collision::RectangleAndRectangle(aqua::CVector2 first_pos, aqua::CVector2 first_size, aqua::CVector2 second_pos, aqua::CVector2 second_size)
{
	aqua::CVector2 rectangleFirstStart;
	aqua::CVector2 rectangleFirstEnd;
	aqua::CVector2 rectangleSecondStart;
	aqua::CVector2 rectangleSecondEnd;

	rectangleFirstStart.x = first_pos.x;
	rectangleFirstStart.y = first_pos.y;

	rectangleFirstEnd.x = first_pos.x + first_size.x;
	rectangleFirstEnd.y = first_pos.y + first_size.y;

	rectangleSecondStart.x = second_pos.x;
	rectangleSecondStart.y = second_pos.y;

	rectangleSecondEnd.x = second_pos.x + second_size.x;
	rectangleSecondEnd.y = second_pos.y + second_size.y;

	bool result = false;

	result = (rectangleFirstEnd.x > rectangleSecondStart.x) &&
	(rectangleFirstStart.x < rectangleSecondEnd.x) &&
	(rectangleFirstEnd.y > rectangleSecondStart.y) &&
	(rectangleFirstStart.y < rectangleSecondEnd.y);

	return result;
}

bool collision::IsPlayerOnBoard(aqua::CVector2 player_pos, aqua::CVector2 player_size, aqua::CVector2 floor_pos, aqua::CVector2 floor_size)
{
	aqua::CVector2 playerLeftPos;
	aqua::CVector2 playerRightPos;
	aqua::CVector2 floorLeftPos;
	aqua::CVector2 floorRightPos;

	playerLeftPos.x = player_pos.x;
	playerLeftPos.y = player_pos.y + player_size.y;

	playerRightPos.x = player_pos.x + player_size.x;
	playerRightPos.y = player_pos.y + player_size.y;

	floorLeftPos.x = floor_pos.x;
	floorLeftPos.y = floor_pos.y;

	floorRightPos.x = floor_pos.x + floor_size.x;
	floorRightPos.y = floor_pos.y;

	bool a = false, b = false , c = false, d = false;
	bool result = false;

	a = (playerLeftPos.x > floorLeftPos.x) &&
		(playerLeftPos.x < floorRightPos.x);

	b = (playerRightPos.x > floorLeftPos.x) &&
		(playerRightPos.x < floorRightPos.x);

	c = (playerLeftPos.y > floorLeftPos.y) &&
		(playerRightPos.y > floorRightPos.y);

	d = (playerLeftPos.y < floorLeftPos.y + floor_size.y) &&
		(playerRightPos.y < floorRightPos.y + floor_size.y);

	result = (a || b) && (c || d);

	return result;
}
