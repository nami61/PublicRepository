#pragma once

/*!
 *  @file       debuff.h
 *  @brief      �f�o�t�G�t�F�N�g
 *  @author     Roi Namisato
 *  @date       2023/09/11
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../effect.h"

 /*!
  *  @class      CVanish
  *
  *  @brief      �o�j�b�V���N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/11
  *
  *  @version    1.0
  */

class CDebuff :public IEffect
{
public:
	CDebuff(aqua::IGameObject* parent);
	~CDebuff(void) override = default;

	void Initialize(const aqua::CVector2& pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
};