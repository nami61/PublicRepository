#include "Stage.h"

const float CStage::m_grav = 88.2f;
const float CStage::m_default_bg_speed = 2.0f;
const float CStage::m_default_object_speed = 10.0f;

CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Stage")
{
}

void CStage::Initialize(void)
{
	m_Sprite = AQUA_NEW aqua::CSprite[(int)SPRITE::MAX];
	for (int spriteNumber = 0; spriteNumber < (int)SPRITE::MAX; ++spriteNumber)
	{
		m_Sprite[spriteNumber].Create("data/texture/bg.png");
		m_Sprite[spriteNumber].position = aqua::CVector2((float)(aqua::GetWindowWidth() * spriteNumber), 0.0f);
	}

	m_BGSpeed = m_default_bg_speed;
	m_StageObjectSpeed = m_default_object_speed;
	m_Velocity = aqua::CVector2(m_BGSpeed, 0.0f);
}

void CStage::Update(void)
{
	m_Sprite[(int)SPRITE::FIRST].position.x -= m_Velocity.x;

	if (m_Sprite[(int)SPRITE::FIRST].position.x <= (aqua::GetWindowWidth() * -1.0f))
		m_Sprite[(int)SPRITE::FIRST].position.x = 0.0f;

	m_Sprite[(int)SPRITE::SECOND].position.x = m_Sprite[(int)SPRITE::FIRST].position.x + m_Sprite[(int)SPRITE::FIRST].GetTextureWidth();
	m_Velocity = aqua::CVector2(m_BGSpeed, 0.0f);
}

void CStage::Draw(void)
{
	for (int spriteNumber = 0; spriteNumber < (int)SPRITE::MAX; ++spriteNumber)
		m_Sprite[spriteNumber].Draw();
}

void CStage::Finalize(void)
{
	//for (int spriteNumber = 0; spriteNumber < (int)SPRITE::MAX; ++spriteNumber)
		//m_Sprite[spriteNumber].Delete();
	AQUA_SAFE_DELETE_ARRAY(m_Sprite);
}
