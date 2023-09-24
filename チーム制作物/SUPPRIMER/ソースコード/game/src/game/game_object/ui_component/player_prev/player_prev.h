#pragma once

/*!
 *  @file       player_prev.h
 *  @brief      �v���C���[�v���r���[�p
 *  @author     Roi Namisato
 *  @date       2023/08/27
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "../../player_manager/player/player_id.h"

 /*!
  *  @class      CPlayerPrev
  *
  *  @brief      �v���C���[�v���r���[�N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/08/27
  *
  *  @version    1.0
  */

class CPlayerPrev : public aqua::IGameObject
{
public:
	CPlayerPrev(aqua::IGameObject* parent);
	~CPlayerPrev(void) = default;

	void Initialize(aqua::CVector2 pos);
	void Draw(PLAYER_ID id, aqua::controller::DEVICE_ID device);
	void Finalize(void) override;

private:
	aqua::CAnimationSprite m_White;
	aqua::CAnimationSprite m_Pink;
	aqua::CAnimationSprite m_Blue;
	aqua::CAnimationSprite m_Green;
};