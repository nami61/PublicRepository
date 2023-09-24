#pragma once

/*!
 *  @file       white_block.h
 *  @brief      白ブロック
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
  *  @brief      白ブロッククラス
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