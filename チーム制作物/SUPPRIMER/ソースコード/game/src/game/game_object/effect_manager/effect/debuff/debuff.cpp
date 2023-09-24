#include "debuff.h"

CDebuff::CDebuff(aqua::IGameObject* parent)
	:IEffect(parent, "Debuff")
{
}

void CDebuff::Initialize(const aqua::CVector2& pos)
{
	m_Effect.Create("data/effect/debuff.efkefc");
	m_Effect.position = pos;
	m_Effect.scale.x = 20.0f;
	m_Effect.scale.y = 20.0f;
	m_Effect.Play();
}

void CDebuff::Update(void)
{
	if (m_Effect.Finished())
		DeleteObject();

	m_Effect.Update();
}

void CDebuff::Draw(void)
{
	m_Effect.Draw();
}

void CDebuff::Finalize(void)
{
	m_Effect.Delete();
}
