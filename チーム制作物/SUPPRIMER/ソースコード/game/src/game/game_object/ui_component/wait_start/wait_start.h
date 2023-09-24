#pragma once

/*!
 *  @file       wati_start.h
 *  @brief      �Q�[���J�n�m�FUI
 *  @author     Roi Namisato
 *  @date       2023/07/29
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CWaitStart
  *
  *  @brief      �E�F�C�g�X�^�[�g�N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/07/29
  *
  *  @version    1.0
  */

class CWaitStart :
	public aqua::IGameObject
{
public:
	CWaitStart(aqua::IGameObject* parent);
	~CWaitStart(void) = default;


};