#include "player_number.h"

const aqua::CVector2 CPlayerNumber::m_default_p1_sprite_pos = aqua::CVector2(50.0f, 300.0f);
const aqua::CVector2 CPlayerNumber::m_default_p2_sprite_pos = aqua::CVector2(1570.0f, 300.0f);

CPlayerNumber::CPlayerNumber(aqua::IGameObject* parent)
{
}

void CPlayerNumber::Initialize(void)
{
	m_P1Sprite.Create("data/p1.png");
	m_P1Sprite.color = 0xffff0000;
	m_P1Sprite.position = m_default_p1_sprite_pos;
	m_P2Sprite.Create("data/p2.png");
	m_P2Sprite.color = 0xff0000ff;
	m_P2Sprite.position = m_default_p2_sprite_pos;
}

void CPlayerNumber::Draw(void)
{
	m_P1Sprite.Draw();
	m_P2Sprite.Draw();
}

void CPlayerNumber::Finalize(void)
{
	m_P1Sprite.Delete();
	m_P2Sprite.Delete();
}