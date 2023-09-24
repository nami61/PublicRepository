#pragma once

/*!
 *  @file       round_finish_scene.h
 *  @brief      ラウンドフィニッシュシーン
 *  @author     Roi Namisato
 *  @date       2023/08/21
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../../scene.h"

class CDeviceCommonData;
class CPlayerManager;
class IPlayer;
class CRoundManager;
class CBlockManager;
class CHealthBar;

/*!
 *  @class      CRoundFinishScene
 *
 *  @brief      ラウンドフィニッシュシーンクラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/08/21
 *
 *  @version    1.0
 */

class CRoundFinishScene
	: public IScene
{
public:
	CRoundFinishScene(aqua::IGameObject* parent);
	~CRoundFinishScene(void) override = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	void Appear(void);
	void Attack(void);
	void Exit(void);

	enum class STATE
	{
		APPEAR,
		ATTACK,
		EXIT,
	};
	static const aqua::CVector2 m_default_p1_pos;
	static const aqua::CVector2 m_default_p2_pos;
	static const aqua::CVector2 m_round_label_pos;
	static const aqua::CVector2 m_p1_health_pos;
	static const aqua::CVector2 m_p2_health_pos;

	static const aqua::CVector2 m_p1_max_sprite_pos;
	static const aqua::CVector2 m_p2_max_sprite_pos;
	static const aqua::CVector2 m_p1_color_bonus_sprite_pos;
	static const aqua::CVector2 m_p2_color_bonus_sprite_pos;
	static const aqua::CVector2 m_p1_max_value_pos;
	static const aqua::CVector2 m_p2_max_value_pos;
	static const aqua::CVector2 m_p1_color_value_pos;
	static const aqua::CVector2 m_p2_color_value_pos;

	static const float m_deray_interval;
	int m_DerayCount;
	STATE m_State;
	aqua::CBoxPrimitive m_Plane;
	std::vector<aqua::CSprite> m_RoundSprites;
	aqua::CSprite m_P1MaxSprite;
	aqua::CSprite m_P1ColorBonusSprite;
	aqua::CSprite m_P2MaxSprite;
	aqua::CSprite m_P2ColorBonusSprite;
	aqua::CLabel m_P1MaxLabel;
	aqua::CLabel m_P1ColorBonusLabel;
	aqua::CLabel m_P2MaxLabel;
	aqua::CLabel m_P2ColorBonusLabel;
	aqua::CTimer m_FadeInTimer;
	aqua::CTimer m_FadeInTimerSecond;
	aqua::CTimer m_FadeOutTimer;
	aqua::CTimer m_Deray;

	aqua::CLabel StateLabel;
	aqua::CLabel Message;

	CDeviceCommonData* m_CommonData;
	CPlayerManager* m_PlayerManager;
	IPlayer* m_P1;
	IPlayer* m_P2;
	CRoundManager* m_RoundManager;
	CBlockManager* m_BlockManager;
	CHealthBar* m_P1HealthUI;
	CHealthBar* m_P2HealthUI;
};