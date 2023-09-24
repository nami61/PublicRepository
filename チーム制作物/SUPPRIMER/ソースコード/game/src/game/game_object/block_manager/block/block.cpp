#include "block.h"

const float IBlock::m_fall_speed = 5.0f;

IBlock::IBlock(aqua::IGameObject* parent, const std::string& name)
	: aqua::IGameObject(parent, name, "Block")
	, m_Position(aqua::CVector2::ZERO)
	, m_ReferencedFlag(false)
	, m_HitFlag(false)
	, m_InputFlag(false)
	, m_FallFlag(false)
{
}

void IBlock::Initialize(void)
{
	m_FieldPos.w = 0;
	m_FieldPos.h = 0;
	m_RotationSpeed = 0.0f;
}

void IBlock::Update(void)
{
	if (m_Position.y >= (float)aqua::GetWindowHeight())
		DeleteObject();
	if (m_FallFlag)
	{
		m_Position.y += m_fall_speed;
		m_Sprite.anchor.x = (float)m_Sprite.GetTextureWidth() / 2.0f;
		m_Sprite.anchor.y = (float)m_Sprite.GetTextureHeight() / 2.0f;
		m_Sprite.rotation += aqua::DegToRad(m_RotationSpeed);
	}

	m_Sprite.position = m_Position;
}

void IBlock::Draw(void)
{
	m_Sprite.Draw();
}

void IBlock::Finalize(void)
{
	m_Sprite.Delete();
}
