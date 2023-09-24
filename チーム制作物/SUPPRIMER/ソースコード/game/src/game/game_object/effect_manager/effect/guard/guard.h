#pragma once

/*!
 *  @file       guard.h
 *  @brief      �K�[�h�G�t�F�N�g
 *  @author     Roi Namisato
 *  @date       2023/09/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../effect.h"

 /*!
  *  @class      CGuard
  *
  *  @brief      �K�[�h�N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/11
  *
  *  @version    1.0
  */

class CGuard : public IEffect
{
public:
	CGuard(aqua::IGameObject* parent);
	~CGuard(void) override = default;

	void Initialize(const aqua::CVector2& pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
};