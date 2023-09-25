#include "counter.h"

CCounter::CCounter(aqua::IGameObject* parent)
	:IEffect(parent, "Counter")
{
}

void CCounter::Initialize(const aqua::CVector2& pos)
{
	m_Effect.Create("data/effect/counter.efkefc");
	m_Effect.position = pos;
	m_Effect.scale.x = 20.0f;
	m_Effect.scale.y = 20.0f;
	m_Effect.color = 0xff00ffff;
	m_Effect.Play();
}

void CCounter::Update(void)
{
	if (m_Effect.Finished())
		DeleteObject();

	m_Effect.Update();
}

void CCounter::Draw(void)
{
	m_Effect.Draw();
}

void CCounter::Finalize(void)
{
	m_Effect.Delete();
}