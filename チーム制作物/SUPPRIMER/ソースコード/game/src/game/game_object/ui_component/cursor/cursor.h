#pragma once

/*!
 *  @file       cursor.h
 *  @brief      カーソルUI
 *  @author     Takami Shimizu
 *  @date       2023/07/04
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CCursor
  *
  *  @brief      カーソルクラス
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/04
  *
  *  @version    1.0
  */

class CCursor :public aqua::IGameObject
{
public:
	CCursor(aqua::IGameObject* parent);
	~CCursor() = default;

	void Initialize(aqua::controller::DEVICE_ID id);
	void Update(void)override;
	void Draw(void)override;
	void Finalize(void)override;

	void SetCursor(const aqua::CVector2& pos);

	// 点と円の判定
	void CheckHitCursor(const aqua::CVector2& pos, float radius, bool& hit_flag);
	// 点と矩形の判定
	void CheckHitCursor(const aqua::CVector2& pos, float width, float height, bool& hit_flag);
	// 壁の当たり判定
	void CheckHitWall(float left, float right, float top, float under);

private:
	static const float				m_default_threshold_value;

	bool							m_HitFlag;

	aqua::CVector2					m_CursorPosition;
	aqua::CVector2					m_Velocity;
	aqua::controller::DEVICE_ID		m_DeviceID;
	aqua::CSprite					m_CursorSprite;
};