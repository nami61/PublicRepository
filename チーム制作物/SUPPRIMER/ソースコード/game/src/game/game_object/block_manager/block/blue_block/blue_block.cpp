#include "blue_block.h"

CBlueBlock::CBlueBlock(aqua::IGameObject* parent)
	: IBlock(parent, "BlueBlock")
{
	m_Sprite.Create("data/b_block.png");
}
