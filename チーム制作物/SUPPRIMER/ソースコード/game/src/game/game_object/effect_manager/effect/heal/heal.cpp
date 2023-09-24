#include "heal.h"

CHeal::CHeal(aqua::IGameObject* parent)
	:IEffect(parent, "Heal")
{
}

void CHeal::Initialize(const aqua::CVector2& pos)
{
	m_Effect.Create("data/effect/heal.efkefc");
	m_Effect.position = pos;
	m_Effect.scale.x = 20.0f;
	m_Effect.scale.y = 20.0f;
	m_Effect.Play();
}

void CHeal::Update(void)
{
	if (m_Effect.Finished())
		DeleteObject();

	m_Effect.Update();
}

void CHeal::Draw(void)
{
	m_Effect.Draw();
}

void CHeal::Finalize(void)
{
	m_Effect.Delete();
}
