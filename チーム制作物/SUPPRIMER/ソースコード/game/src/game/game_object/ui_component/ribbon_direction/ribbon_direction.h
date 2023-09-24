#pragma once

/*!
 *  @file       ribbon_direction.h
 *  @brief      リボン演出
 *  @author     Roi Namisato
 *  @date       2023/07/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

class CRoundManager;

/*!
 *  @class      CRibbonDirection
 *
 *  @brief      リボン演出クラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/07/26
 *
 *  @version    1.0
 */

class CRibbonDirection : public aqua::IGameObject
{
public:
	CRibbonDirection(aqua::IGameObject* parent);
	~CRibbonDirection(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void RibbonUpdate(void);
	
private:
	void ScreenIn(void);
	void Deray(void);
	void ScreenOut(void);

	enum class STATE
	{
		SCREEN_IN,
		DERAY,
		SCREEN_OUT,
	};

	static const aqua::CVector2 m_default_ribbon_position;
	static const aqua::CVector2 m_default_label_position;
	static const aqua::CVector2 m_move_label_pos;
	static const aqua::CVector2 m_start_position;
	aqua::CSprite m_RibbonFirst;
	aqua::CSprite m_RibbonSecond;
	aqua::CSprite m_RoundSprite;
	aqua::CLabel m_CurrentRoundLabel;
	aqua::CTimer m_RibbonInScreen;
	aqua::CTimer m_RibbonOutScreen;
	aqua::CTimer m_RibbonDeray;
	STATE m_State;
	CRoundManager* m_RoundManager;
};
