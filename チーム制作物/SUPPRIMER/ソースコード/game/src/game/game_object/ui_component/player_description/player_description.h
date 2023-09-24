#pragma once

/*!
 *  @file       player_description.h
 *  @brief      プレイヤー説明UI
 *  @author     Roi Namisato
 *  @date       2023/09/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "../../player_manager/player/player_id.h"

 /*!
  *  @class      CPlayerDescription
  *
  *  @brief      プレイヤーディスクリプションクラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/06
  *
  *  @version    1.0
  */

class CPlayerDescription : public aqua::IGameObject
{
public:
	CPlayerDescription(aqua::IGameObject* parent);
	~CPlayerDescription(void) = default;

	void Initialize(aqua::controller::DEVICE_ID device);
	void Draw(PLAYER_ID id);
	void Finalize(void) override;
private:
	static const aqua::CVector2 m_p1_pos;
	static const aqua::CVector2 m_p2_pos;
	aqua::CSprite m_White;
	aqua::CSprite m_Blue;
	aqua::CSprite m_Green;
	aqua::CSprite m_Pink;
};