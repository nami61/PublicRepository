#pragma once

/*!
 *  @file       blue_block.h
 *  @brief      �u���b�N
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "../block.h"

 /*!
  *  @class      IPlayer
  *
  *  @brief      �u���b�N�N���X
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/23
  *
  *  @version    1.0
  */

class CBlueBlock
	: public IBlock
{
public:
	CBlueBlock(aqua::IGameObject* parent);
	~CBlueBlock(void) override = default;
};