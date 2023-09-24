#include "player_prev.h"

CPlayerPrev::CPlayerPrev(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "PlayerPrev")
{
}

void CPlayerPrev::Initialize(aqua::CVector2 pos)
{
	m_White.Create("data/animation/white.ass");
	m_Blue.Create("data/animation/blue.ass");
	m_Green.Create("data/animation/green.ass");
	m_Pink.Create("data/animation/pink.ass");
	m_White.position = pos;
	m_Blue.position = pos;
	m_Green.position = pos;
	m_Pink.position = pos;
	m_White.Play();
	m_Blue.Play();
	m_Green.Play();
	m_Pink.Play();
}

void CPlayerPrev::Draw(PLAYER_ID id, aqua::controller::DEVICE_ID device)
{
	m_White.Update();
	m_Blue.Update();
	m_Green.Update();
	m_Pink.Update();
	if (device == aqua::controller::DEVICE_ID::P2)
	{
		m_White.scale.x = -1.0f;
		m_Blue.scale.x = -1.0f;
		m_Green.scale.x = -1.0f;
		m_Pink.scale.x = -1.0f;
	}
	switch (id)
	{
	case PLAYER_ID::WHITE: m_White.Draw(); break;
	case PLAYER_ID::BLUE: m_Blue.Draw(); break;
	case PLAYER_ID::GREEN: m_Green.Draw(); break;
	case PLAYER_ID::PINK: m_Pink.Draw(); break;
	}
}

void CPlayerPrev::Finalize(void)
{
	m_White.Delete();
	m_Blue.Delete();
	m_Green.Delete();
	m_Pink.Delete();
}
