#pragma once

/*!
 *  @file       countdown_timer.h
 *  @brief      カウントダウンUI
 *  @author     Roi Namisato
 *  @date       2023/08/17
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CCountdawnTimer
  *
  *  @brief      カウントダウンタイマークラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/08/17
  *
  *  @version    1.0
  */

class CCountdawnTimer :public aqua::IGameObject
{
public:
	CCountdawnTimer(aqua::IGameObject* parent);
	~CCountdawnTimer(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
	void SetTime(float time) { m_CurrentTime = time; }
	void SetLimit(float limit) { m_Limit = limit; }
	
private:
	static const aqua::CVector2 m_circle_pos;
	static const aqua::CVector2 m_label_pos;
	aqua::CLabel Label;
	aqua::CSprite Sprite;
	float m_CurrentTime;
	float m_Limit;
};