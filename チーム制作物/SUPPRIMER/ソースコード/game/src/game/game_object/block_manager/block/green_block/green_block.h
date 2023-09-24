#pragma once

/*!
 *  @file       green_block.h
 *  @brief      緑ブロック
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "../block.h"

 /*!
  *  @class      CGreenBlock
  *
  *  @brief      緑ブロッククラス
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/23
  *
  *  @version    1.0
  */

class CGreenBlock
	: public IBlock
{
public:
	CGreenBlock(aqua::IGameObject* parent);
	~CGreenBlock(void) override = default;
};