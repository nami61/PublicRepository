#pragma once

/*!
 *  @file       effect.h
 *  @brief      エフェクト
 *  @author     Roi Namisato
 *  @date       2023/09/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      IEffect
  *
  *  @brief      エフェクトクラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/11
  *
  *  @version    1.0
  */

class IEffect :public aqua::IGameObject 
{
public:
	IEffect(aqua::IGameObject* parent, const std::string& name);
	~IEffect(void) = default;

	virtual void Initialize(const aqua::CVector2& pos);
	virtual void Update(void) override;
	virtual void Draw(void) override;
	virtual void Finalize(void) override;

protected:
	aqua::CEffect2D m_Effect;
};