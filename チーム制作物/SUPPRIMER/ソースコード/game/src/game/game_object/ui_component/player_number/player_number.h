#pragma once

/*!
 *  @file       player_number.h
 *  @brief      プレイヤーナンバーUI
 *  @author     Roi Namisato
 *  @date       2023/07/09
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CPlayerNumbar
  *
  *  @brief      プレイヤーナンバークラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/07/09
  *
  *  @version    1.0
  */

class CPlayerNumber
	: public aqua::IGameObject
{
public:
	CPlayerNumber(aqua::IGameObject* parent);
	~CPlayerNumber(void) = default;

	void Initialize(void) override;

	void Draw(void) override;

	void Finalize(void);
private:
	static const aqua::CVector2 m_default_p1_sprite_pos;
	static const aqua::CVector2 m_default_p2_sprite_pos;
	aqua::CSprite m_P1Sprite;
	aqua::CSprite m_P2Sprite;
};