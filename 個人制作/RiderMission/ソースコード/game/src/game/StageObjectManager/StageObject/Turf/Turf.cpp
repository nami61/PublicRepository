#include "Turf.h"

CTurf::CTurf(aqua::IGameObject* parent)
	:IStageObject(parent, "Turf")
{
}

void CTurf::Initialize(aqua::CVector2 pos)
{
	m_Position = pos;

	m_Sprite.Create("data/texture/turf.png");

	IStageObject::Initialize();

	m_Size.x = (float)m_Sprite.GetTextureWidth();
	m_Size.y = (float)m_Sprite.GetTextureHeight();

	m_Category = STAGE_OBJECT_CATEGORY::FLOOR;
}

void CTurf::Update(void)
{
	if (m_Position.x <= (float)(-m_Sprite.GetTextureWidth()))
		m_ActiveFlag = false;

	m_Position.x -= m_Velocity.x;
	m_Sprite.position = m_Position;

	IStageObject::Update();
}

void CTurf::Draw(void)
{
	m_Sprite.Draw();

	IStageObject::Draw();
}

void CTurf::Finalize(void)
{
	m_Sprite.Delete();

	IStageObject::Finalize();
}
