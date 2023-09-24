#pragma once

/*!
 *  @file       white_block.h
 *  @brief      ���u���b�N
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "../block.h"

 /*!
  *  @class      CWhiteBlock
  *
  *  @brief      ���u���b�N�N���X
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/23
  *
  *  @version    1.0
  */

class CWhiteBlock
	: public IBlock
{
public: 
	CWhiteBlock(aqua::IGameObject* parent);
	~CWhiteBlock(void) override = default;

};