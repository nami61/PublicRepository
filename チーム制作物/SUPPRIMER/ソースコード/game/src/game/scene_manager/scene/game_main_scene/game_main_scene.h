#pragma once

/*!
 *  @file       game_main_scene.h
 *  @brief      ゲームメインシーン
 *  @author     Roi Namisato
 *  @date       2023/06/22
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "../scene.h"

/*!
 *  @class      CGameMainScene
 *
 *  @brief      ゲームメインシーンクラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/22
 *
 *  @version    1.0
 */

class CBlockManager;
class CEffectManager;
class CSoundManager;
class CDeviceCommonData;
class CCountdawnTimer;
class CRoundManager;
class CCursor;
class IPlayer;
class CBackground;
class CRibbonDirection;
class CHealthBar;
class CSkillUI;

class CGameMainScene :public IScene
{
public:
	CGameMainScene(aqua::IGameObject* parent);
	~CGameMainScene() = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

private:
	static const aqua::CVector2 m_default_p1_total_pos;
	static const aqua::CVector2 m_default_p2_total_pos;
	static const aqua::CVector2 m_default_p1_max_pos;
	static const aqua::CVector2 m_default_p2_max_pos;
	static const aqua::CVector2 m_default_p1_color_pos;
	static const aqua::CVector2 m_default_p2_color_pos;
	static const aqua::CVector2 m_default_p2_total_label_pos;
	static const aqua::CVector2 m_default_p2_max_label_pos;
	static const aqua::CVector2 m_default_p2_color_label_pos;
	static const float m_label_space;

	aqua::CSprite		m_Frame1;
	aqua::CSprite		m_Frame2;

	aqua::CSprite m_P1TotalSprite;
	aqua::CSprite m_P1MaxSprite;
	aqua::CSprite m_P1ColorBonusSprite;
	aqua::CSprite m_P2TotalSprite;
	aqua::CSprite m_P2MaxSprite;
	aqua::CSprite m_P2ColorBonusSprite;
	aqua::CLabel m_P1TotalLabel;
	aqua::CLabel m_P1MaxLabel;
	aqua::CLabel m_P1ColorBonusLabel;
	aqua::CLabel m_P2TotalLabel;
	aqua::CLabel m_P2MaxLabel;
	aqua::CLabel m_P2ColorBonusLabel;

	aqua::CSprite m_ControllerPanel;

	CCursor*			m_CursorP1;
	CCursor*			m_CursorP2;

	CBlockManager* m_BlockManager;
	CSoundManager* m_SoundManager;
	CEffectManager* m_EffectManager;
	CDeviceCommonData* m_Data;
	CRoundManager* m_RoundManager;
	CCountdawnTimer* m_CountdawnTimer;

	IPlayer* m_P1;
	IPlayer* m_P2;
	CBackground* m_P1BG;
	CBackground* m_P2BG;
	CHealthBar* m_P1HealthUI;
	CHealthBar* m_P2HealthUI;
	CSkillUI* m_P1SkillUI;
	CSkillUI* m_P2SkillUI;
};