#include "pink_block.h"

CPinkBlock::CPinkBlock(aqua::IGameObject* parent)
	: IBlock(parent, "PinkBlock")
{
	m_Sprite.Create("data/p_block.png");
}
