#include "background.h"

const int CBackground::m_max_backgrounds = 4;

CBackground::CBackground(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Background")
{
}

void CBackground::TitleInit(void)
{
	BACKGROUND bg = (BACKGROUND)GetRand(m_max_backgrounds);
	switch (bg)
	{
	case CBackground::BACKGROUND::HOUSE:
		m_Background.Create("data/house.png");
		break;
	case CBackground::BACKGROUND::LIBRARY:
		m_Background.Create("data/library.png");
		break;
	case CBackground::BACKGROUND::STAR:
		m_Background.Create("data/star.png");
		break;
	case CBackground::BACKGROUND::THRONE:
		m_Background.Create("data/throne.png");
		break;
	case CBackground::BACKGROUND::WOOD:
		m_Background.Create("data/wood.png");
		break;
	}
}

void CBackground::Initialize(aqua::controller::DEVICE_ID device, PLAYER_ID id)
{
	using namespace aqua::controller;
	switch (id)
	{
	case PLAYER_ID::WHITE:
		if(device == DEVICE_ID::P1)
		m_Background.Create("data/throne_1P.png");
		else if(device == DEVICE_ID::P2)
		m_Background.Create("data/throne_2P.png");
		break;
	case PLAYER_ID::BLUE:
		if (device == DEVICE_ID::P1)
			m_Background.Create("data/house_1P.png");
		else if (device == DEVICE_ID::P2)
			m_Background.Create("data/house_2P.png");
		break;
	case PLAYER_ID::GREEN:
		if (device == DEVICE_ID::P1)
			m_Background.Create("data/library_1P.png");
		else if (device == DEVICE_ID::P2)
			m_Background.Create("data/library_2P.png");
		break;
	case PLAYER_ID::PINK:
		if (device == DEVICE_ID::P1)
			m_Background.Create("data/star_1P.png");
		else if (device == DEVICE_ID::P2)
			m_Background.Create("data/star_2P.png");
		break;
	}
}

void CBackground::Draw(void)
{
	m_Background.Draw();
}

void CBackground::Finalize(void)
{
	m_Background.Delete();
}
