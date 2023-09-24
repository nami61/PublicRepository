#include "device_common_data.h"

CDeviceCommonData::CDeviceCommonData(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "DeviceCommonData")
	, m_Winner(PLAYER_ID::WHITE)
	, m_WinnerDevice(aqua::controller::DEVICE_ID::P1)
	, m_LoserDevice(aqua::controller::DEVICE_ID::P1)
	, m_P1TotalVanishedBlocks(0)
	, m_P2TotalVanishedBlocks(0)
	, m_P1MaxVanishedBlocks(0)
	, m_P2MaxVanishedBlocks(0)
	, m_P1ColorBonus(0)
	, m_P2ColorBonus(0)
	, m_P1VanishedBonus(0)
	, m_P2VanishedBonus(0)
{
	m_P1 = m_P2 = PLAYER_ID::WHITE;
}

void CDeviceCommonData::ResetScore(void)
{
	m_P1TotalVanishedBlocks = 0;
	m_P2TotalVanishedBlocks = 0;
	m_P1MaxVanishedBlocks = 0;
	m_P2MaxVanishedBlocks = 0;
	m_P1ColorBonus = 0;
	m_P2ColorBonus = 0;
}

void CDeviceCommonData::SetPlayerID(aqua::controller::DEVICE_ID device, PLAYER_ID id)
{
	switch (device)
	{
		using namespace aqua::controller;
	case DEVICE_ID::P1: m_P1 = id; break;
	case DEVICE_ID::P2: m_P2 = id; break;
	}
}

PLAYER_ID CDeviceCommonData::GetPlayerID(aqua::controller::DEVICE_ID device)
{
	switch (device)
	{
		using namespace aqua::controller;
	case DEVICE_ID::P1: return m_P1; break;
	case DEVICE_ID::P2: return m_P2; break;
	}
	return PLAYER_ID::MAX;
}

int CDeviceCommonData::GetTotalVanishedBlocks(aqua::controller::DEVICE_ID device)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		return m_P1TotalVanishedBlocks;
	else if (device == aqua::controller::DEVICE_ID::P2)
		return m_P2TotalVanishedBlocks;
	else
		return 0;
}

int CDeviceCommonData::GetMaxVanishedBlocks(aqua::controller::DEVICE_ID device)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		return m_P1MaxVanishedBlocks;
	else if (device == aqua::controller::DEVICE_ID::P2)
		return m_P2MaxVanishedBlocks;
	else
		return 0;
}

int CDeviceCommonData::GetColorBonus(aqua::controller::DEVICE_ID device)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		return m_P1ColorBonus;
	else if (device == aqua::controller::DEVICE_ID::P2)
		return m_P2ColorBonus;
	else
		return 0;
}

int CDeviceCommonData::GetVanishedBonus(aqua::controller::DEVICE_ID device)
{
	int bonus = 0;
	if (device == aqua::controller::DEVICE_ID::P1)
	{
		bonus = m_P1VanishedBonus;
		m_P1VanishedBonus = 0;
		return bonus;
	}
	else if (device == aqua::controller::DEVICE_ID::P2)
	{
		bonus = m_P2VanishedBonus;
		m_P2VanishedBonus = 0;
		return bonus;
	}
	else
		return 0;
}

int CDeviceCommonData::GetLife(aqua::controller::DEVICE_ID device)
{
	int life = 0;
	using namespace aqua::controller;
	switch (device)
	{
	case DEVICE_ID::P1: life = m_P1Life; break;
	case DEVICE_ID::P2: life = m_P2Life; break;
	}
	return life;
}

int CDeviceCommonData::GetMaxLife(aqua::controller::DEVICE_ID device)
{
	int max_life = 0;
	using namespace aqua::controller;
	switch (device)
	{
	case DEVICE_ID::P1: max_life = m_P1MaxLife; break;
	case DEVICE_ID::P2: max_life = m_P2MaxLife; break;
	}
	return max_life;
}

void CDeviceCommonData::SetTotalVanishedBlocks(aqua::controller::DEVICE_ID device, int blocks)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		m_P1TotalVanishedBlocks += blocks;
	else if (device == aqua::controller::DEVICE_ID::P2)
		m_P2TotalVanishedBlocks += blocks;
}

void CDeviceCommonData::SetMaxVanishedBlocks(aqua::controller::DEVICE_ID device, int blocks)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		m_P1MaxVanishedBlocks = blocks;
	else if (device == aqua::controller::DEVICE_ID::P2)
		m_P2MaxVanishedBlocks = blocks;
}

void CDeviceCommonData::SetColorBonus(aqua::controller::DEVICE_ID device, int blocks)
{
	if (device == aqua::controller::DEVICE_ID::P1)
		m_P1ColorBonus += blocks;
	else if (device == aqua::controller::DEVICE_ID::P2)
		m_P2ColorBonus += blocks;
}

void CDeviceCommonData::SetVanishedBonus(aqua::controller::DEVICE_ID device, int blocks)
{
	if (device == aqua::controller::DEVICE_ID::P1)
	{
		if (blocks >= 5 && blocks < 7)
			m_P1VanishedBonus = 1;
		else if (blocks >= 7 && blocks < 9)
			m_P1VanishedBonus = 2;
		else if (blocks == 9)
			m_P1VanishedBonus = 3;
		else if (blocks >= 10 && blocks < 15)
			m_P1VanishedBonus = 5;
		else if (blocks >= 15 && blocks < 20)
			m_P1VanishedBonus = 10;
		else if (blocks >= 20 && blocks < 30)
			m_P1VanishedBonus = 16;
		else if (blocks >= 30 && blocks < 40)
			m_P1VanishedBonus = 27;
		else if (blocks >= 40)
			m_P1VanishedBonus = 50;
		else
			m_P1VanishedBonus = 0;
	}
	else if (device == aqua::controller::DEVICE_ID::P2)
	{
		if (blocks >= 5 && blocks < 7)
			m_P2VanishedBonus = 1;
		else if (blocks >= 7 && blocks < 9)
			m_P2VanishedBonus = 2;
		else if (blocks == 9)
			m_P2VanishedBonus = 3;
		else if (blocks >= 10 && blocks < 15)
			m_P2VanishedBonus = 5;
		else if (blocks >= 15 && blocks < 20)
			m_P2VanishedBonus = 10;
		else if (blocks >= 20 && blocks < 30)
			m_P2VanishedBonus = 16;
		else if (blocks >= 30 && blocks < 40)
			m_P2VanishedBonus = 27;
		else if (blocks >= 40)
			m_P2VanishedBonus = 50;
		else
			m_P2VanishedBonus = 0;
	}
}

void CDeviceCommonData::SetLife(aqua::controller::DEVICE_ID device, int life)
{
	using namespace aqua::controller;
	switch (device)
	{
	case DEVICE_ID::P1: m_P1Life = life; break;
	case DEVICE_ID::P2: m_P2Life = life; break;
	}
}

void CDeviceCommonData::SetMaxLife(aqua::controller::DEVICE_ID device, int max_life)
{
	using namespace aqua::controller;
	switch (device)
	{
	case DEVICE_ID::P1: m_P1MaxLife = max_life; break;
	case DEVICE_ID::P2: m_P2MaxLife = max_life; break;
	}
}
