#include "white_block.h"

CWhiteBlock::CWhiteBlock(aqua::IGameObject* parent)
	: IBlock(parent, "WhiteBlock")
{
	m_Sprite.Create("data/w_block.png");
}
