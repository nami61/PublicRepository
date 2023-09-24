#pragma once

/*!
 *  @file       cursor.h
 *  @brief      �J�[�\��UI
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
  *  @brief      �J�[�\���N���X
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

	// �_�Ɖ~�̔���
	void CheckHitCursor(const aqua::CVector2& pos, float radius, bool& hit_flag);
	// �_�Ƌ�`�̔���
	void CheckHitCursor(const aqua::CVector2& pos, float width, float height, bool& hit_flag);
	// �ǂ̓����蔻��
	void CheckHitWall(float left, float right, float top, float under);

private:
	static const float				m_default_threshold_value;

	bool							m_HitFlag;

	aqua::CVector2					m_CursorPosition;
	aqua::CVector2					m_Velocity;
	aqua::controller::DEVICE_ID		m_DeviceID;
	aqua::CSprite					m_CursorSprite;
};