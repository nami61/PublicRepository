#pragma once

/*!
 *  @file       demo_scene.h
 *  @brief      デモシーン
 *  @author     Roi Namisato
 *  @date       2023/09/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../../scene.h"

 /*!
  *  @class      CDemoScene
  *
  *  @brief      デモシーンクラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/09/20
  *
  *  @version    1.0
  */
class CDemoScene :public IScene 
{
public:
	CDemoScene(aqua::IGameObject* parent);
	~CDemoScene(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	aqua::CTimer m_Timer;
	aqua::CLabel m_DemoLabel;
	bool TriggerAll(aqua::controller::DEVICE_ID device);
	bool m_SuspendedFlag;
	aqua::CVideoPlayer m_DemoMovie;
};