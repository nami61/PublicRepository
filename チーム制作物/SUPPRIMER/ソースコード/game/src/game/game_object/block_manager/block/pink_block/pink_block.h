#pragma once

/*!
 *  @file       pink_block.h
 *  @brief      ピンクブロック
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "../block.h"

 /*!
  *  @class      CPinkBlock
  *
  *  @brief      ピンクブロッククラス
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/23
  *
  *  @version    1.0
  */

class CPinkBlock
	: public IBlock
{
public:
	CPinkBlock(aqua::IGameObject* parent);
	~CPinkBlock() override = default;
};