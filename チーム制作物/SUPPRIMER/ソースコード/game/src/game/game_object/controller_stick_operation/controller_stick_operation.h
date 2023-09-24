#pragma once

/*!
 *  @file       controller_stick_operation.h
 *  @brief      コンロトローラーのステック操作
 *  @author     Roi Namisato
 *  @date       2023/09/15
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CControllerStickOperation
  *
  *  @brief      コントローラーステッククラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/15
  *
  *  @version    1.0
  */

class CControllerStickOperation : public aqua::IGameObject
{
public:
	CControllerStickOperation(aqua::IGameObject* parent);
	~CControllerStickOperation(void) = default;

	void Update(void) override;

	bool StickTriggerLeft(aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction, float threshold);
	
	bool StickButtonLeft(aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction, float threshold);

	bool StickTriggerLeftAll(aqua::controller::DEVICE_ID device, float threshold);

private:
	aqua::CVector2 m_Stick[(int)aqua::controller::DEVICE_ID::MAX];
	aqua::CVector2 m_StickPreview[(int)aqua::controller::DEVICE_ID::MAX];
};