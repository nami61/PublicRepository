#pragma once

/*!
 *  @file       health_bar.h
 *  @brief      体力UI
 *  @author     Roi Namisato
 *  @date       2023/07/14
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CHealthBar
  *
  *  @brief      ヘルスバークラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/07/14
  *
  *  @version    1.0
  */

class IPlayer;

class CHealthBar
	: public aqua::IGameObject
{
public:
	CHealthBar(aqua::IGameObject* parent);
	~CHealthBar(void) = default;

	void Initialize(IPlayer* player, aqua::controller::DEVICE_ID device, aqua::CVector2 pos);
	void Initialize(int life, int max_life, aqua::controller::DEVICE_ID device, aqua::CVector2 pos);
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	static const aqua::CVector2 m_p1_label_pos;
	static const aqua::CVector2 m_p2_label_pos;
	void Translate(void);
	float m_PreScaleX;
	int m_Life;
	int m_MaxLife;
	bool m_TranslateFlag;
	aqua::CSprite m_Health;
	aqua::CSprite m_HealthBack;
	aqua::CSprite m_Damage;
	aqua::CSprite m_HealthFrame;
	aqua::CSprite m_HealthBar;
	aqua::CLabel m_HealthLabel;
	aqua::CTimer m_DamageTimer;
	aqua::CSurface m_Screen;
	aqua::CSprite m_Sc;
	IPlayer* m_Player;
};