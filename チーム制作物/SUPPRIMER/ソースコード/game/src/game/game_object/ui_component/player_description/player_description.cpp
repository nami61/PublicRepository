#include "player_description.h"

const aqua::CVector2 CPlayerDescription::m_p1_pos = aqua::CVector2(300.0f, 600.0f);
const aqua::CVector2 CPlayerDescription::m_p2_pos = aqua::CVector2(1000.0f, 600.0f);

CPlayerDescription::CPlayerDescription(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "PlayerDescription")
{
}

void CPlayerDescription::Initialize(aqua::controller::DEVICE_ID device)
{
	switch (device)
	{
	case aqua::controller::DEVICE_ID::P1:
		m_White.Create("data/title_p1_white.png");
		m_Blue.Create("data/title_p1_blue.png");
		m_Green.Create("data/title_p1_green.png");
		m_Pink.Create("data/title_p1_pink.png");
		m_White.position = m_p1_pos;
		m_Blue.position = m_p1_pos;
		m_Green.position = m_p1_pos;
		m_Pink.position = m_p1_pos;
		break;
	case aqua::controller::DEVICE_ID::P2:
		m_White.Create("data/title_p2_white.png");
		m_Blue.Create("data/title_p2_blue.png");
		m_Green.Create("data/title_p2_green.png");
		m_Pink.Create("data/title_p2_pink.png");
		m_White.position = m_p2_pos;
		m_Blue.position = m_p2_pos;
		m_Green.position = m_p2_pos;
		m_Pink.position = m_p2_pos;
		break;
	}
}

void CPlayerDescription::Draw(PLAYER_ID id)
{
	switch (id)
	{
	case PLAYER_ID::WHITE:
		m_White.Draw();
		break;
	case PLAYER_ID::BLUE:
		m_Blue.Draw();
		break;
	case PLAYER_ID::GREEN:
		m_Green.Draw();
		break;
	case PLAYER_ID::PINK:
		m_Pink.Draw();
		break;
	}
}

void CPlayerDescription::Finalize(void)
{
	m_White.Delete();
	m_Blue.Delete();
	m_Green.Delete();
	m_Pink.Delete();
}
