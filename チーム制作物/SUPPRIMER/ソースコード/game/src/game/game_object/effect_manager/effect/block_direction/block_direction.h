#pragma once

/*!
 *  @file       block_direction.h
 *  @brief      �u���b�N�̉��o
 *  @author     Roi Namisato
 *  @date       2023/08/09
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"
#include "../../../block_manager/block_manager.h"
#include "../../../block_manager/block/block_id.h"

 /*!
  *  @class      CBlockDirection
  *
  *  @brief      �u���b�N���o�N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/08/09
  *
  *  @version    1.0
  */

class CBlockDirection
	: public aqua::IGameObject
{
public:
	CBlockDirection(aqua::IGameObject* parent);
	~CBlockDirection(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
	void Create(BLOCK_ID id);

private:
	aqua::CTimer m_Timer;
};