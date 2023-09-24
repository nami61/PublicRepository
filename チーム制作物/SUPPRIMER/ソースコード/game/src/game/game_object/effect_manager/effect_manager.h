#pragma once

/*!
 *  @file       effect_manager.h
 *  @brief      エフェクトマネージャー
 *  @author     Roi Namisato
 *  @date       2023/09/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"
#include "effect/effect_id.h"

 /*!
  *  @class      CEffectManager
  *
  *  @brief      エフェクトマネージャークラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/11
  *
  *  @version    1.0
  */

class CEffectManager :public aqua::IGameObject
{
public:
	CEffectManager(aqua::IGameObject* parent);
	~CEffectManager(void) = default;

	void Create(EFFECT_ID id, const aqua::CVector2& pos);
};