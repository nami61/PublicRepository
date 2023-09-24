#pragma once

/*!
 *  @file       block.h
 *  @brief      ブロック
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"
#include "block_id.h"

 /*!
  *  @class      IBlock
  *
  *  @brief      ブロッククラス
  *
  *  @author     Takami Shimizu
  *
  *  @date       2023/07/23
  *
  *  @version    1.0
  */

class IBlock :public aqua::IGameObject
{
public:
	IBlock(aqua::IGameObject* parent, const std::string& name);
	~IBlock(void) = default;

	virtual void Initialize(void)	override;
	virtual void Update(void)		override;
	virtual void Draw(void)			override;
	virtual void Finalize(void)		override;

	void		SetID(BLOCK_ID id)	{ m_CurrentID = id; }
	BLOCK_ID	GetID(void)			{ return m_CurrentID; }
	void		SetPosition(const aqua::CVector2& position) { m_Position = position; }
	const aqua::CVector2&	GetPosition(void) { return m_Position; }
	float		GetTextureWidth(void)	{ return (float)m_Sprite.GetTextureWidth(); }
	float		GetTextureHeight(void)	{ return (float)m_Sprite.GetTextureHeight(); }
	void		SetReferenceFlag(bool flag)  { m_ReferencedFlag = flag; }
	bool		IsReferenced(void)		{ return m_ReferencedFlag; }
	void		SetFieldPos(int w_, int h_) { m_FieldPos.w = w_; m_FieldPos.h = h_; }
	int			GetFieldWidth(void) { return m_FieldPos.w; }
	int			GetFieldHeight(void) { return m_FieldPos.h; }
	bool&		GetInputFlag(void) { return m_InputFlag; }
	bool		IsInput(void) { return m_InputFlag; }
	bool&		GetHitFlag(void) { return m_HitFlag; }
	bool		IsHitCursor(void) { return m_HitFlag; }
	void		Fall(void) { m_FallFlag = true; }
	void		SetRotaSpeed(float rota_speed_) { m_RotationSpeed = rota_speed_; }
	aqua::CVector2 GetCenterPosition(void) { return m_Position + aqua::CVector2(GetTextureWidth() / 2.0f, GetTextureHeight() / 2.0f); }

protected:
	struct FIELD_ALLOC
	{
		int w;
		int h;
	};

	static const float m_fall_speed;
	bool m_HitFlag;
	bool m_InputFlag;
	bool m_ReferencedFlag;
	bool m_FallFlag;
	float m_RotationSpeed;
	aqua::CSprite	m_Sprite;
	aqua::CVector2  m_Position;
	BLOCK_ID		m_CurrentID;

	FIELD_ALLOC m_FieldPos;
};