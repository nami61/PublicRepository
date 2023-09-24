#pragma once

/*!
 *  @file       device_common_data.h
 *  @brief      デバイスコモンデータ
 *  @author     Roi Namisato
 *  @date       2023/07/24
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "../player_manager/player/player_id.h"
#include "../player_manager/player/player.h"

class IPlayer;

/*!
 *  @class      CDeviceCommonData
 *
 *  @brief      デバイスコモンデータクラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/07/24
 *
 *  @version    1.0
 */

class CDeviceCommonData
	: public aqua::IGameObject
{
public:
	CDeviceCommonData(aqua::IGameObject* parent);
	~CDeviceCommonData(void) = default;

	void ResetScore(void);

	void SetPlayerID(aqua::controller::DEVICE_ID device, PLAYER_ID id);

	void SetWinner(aqua::controller::DEVICE_ID device, PLAYER_ID id) { m_WinnerDevice = device; m_Winner = id; }

	void SetLoser(aqua::controller::DEVICE_ID device) { m_LoserDevice = device; }

	PLAYER_ID GetPlayerID(aqua::controller::DEVICE_ID device);

	PLAYER_ID GetWinner(void) { return m_Winner; }

	aqua::controller::DEVICE_ID GetWinnerDevice(void) { return m_WinnerDevice; }

	aqua::controller::DEVICE_ID GetLoserDevice(void) { return m_LoserDevice; }

	int GetTotalVanishedBlocks(aqua::controller::DEVICE_ID device);
	int GetMaxVanishedBlocks(aqua::controller::DEVICE_ID device);
	int GetColorBonus(aqua::controller::DEVICE_ID device);
	int GetVanishedBonus(aqua::controller::DEVICE_ID device);
	int GetLife(aqua::controller::DEVICE_ID device);
	int GetMaxLife(aqua::controller::DEVICE_ID device);
	void SetTotalVanishedBlocks(aqua::controller::DEVICE_ID device, int blocks);
	void SetMaxVanishedBlocks(aqua::controller::DEVICE_ID device, int blocks);
	void SetColorBonus(aqua::controller::DEVICE_ID device, int blocks);
	void SetVanishedBonus(aqua::controller::DEVICE_ID device, int blocks);
	void SetLife(aqua::controller::DEVICE_ID device, int life);
	void SetMaxLife(aqua::controller::DEVICE_ID device, int max_life);

private:
	PLAYER_ID m_P1;
	PLAYER_ID m_P2;
	PLAYER_ID m_Winner;
	aqua::controller::DEVICE_ID m_WinnerDevice;
	aqua::controller::DEVICE_ID m_LoserDevice;
	int m_P1TotalVanishedBlocks;
	int m_P2TotalVanishedBlocks;
	int m_P1MaxVanishedBlocks;
	int m_P2MaxVanishedBlocks;
	int m_P1ColorBonus;
	int m_P2ColorBonus;
	int m_P1VanishedBonus;
	int m_P2VanishedBonus;
	int m_P1Life;
	int m_P1MaxLife;
	int m_P2Life;
	int m_P2MaxLife;
};