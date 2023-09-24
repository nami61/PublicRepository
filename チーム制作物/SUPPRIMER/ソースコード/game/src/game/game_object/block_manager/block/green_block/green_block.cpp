#include "green_block.h"

CGreenBlock::CGreenBlock(aqua::IGameObject* parent)
	: IBlock(parent, "GreenBlock")
{
	m_Sprite.Create("data/g_block.png");
}
