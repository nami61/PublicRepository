#include "guard.h"

CGuard::CGuard(aqua::IGameObject* parent)
	:IEffect(parent, "Guard")
{
}

void CGuard::Initialize(const aqua::CVector2& pos)
{
	m_Effect.Create("data/effect/armor.efkefc");
	m_Effect.position = pos;
	m_Effect.scale.x = 10.0f;
	m_Effect.scale.y = 10.0f;
	m_Effect.Play();
}

void CGuard::Update(void)
{
	if (m_Effect.Finished())
		DeleteObject();

	m_Effect.Update();
}

void CGuard::Draw(void)
{
	m_Effect.Draw();
}

void CGuard::Finalize(void)
{
	m_Effect.Delete();
}
