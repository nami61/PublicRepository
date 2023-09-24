#include "vanish.h"

CVanish::CVanish(aqua::IGameObject* parent)
	:IEffect(parent, "Vanish")
{
}

void CVanish::Initialize(const aqua::CVector2& pos)
{
	m_Effect.Create("data/effect/block_expl.efkefc");
	m_SubEffect.Create("data/effect/block_expl_2.efkefc");

	m_Effect.position = pos;
	m_Effect.scale.x = 10.0f;
	m_Effect.scale.y = 10.0f;
	m_SubEffect.position = pos;
	m_SubEffect.scale.x = 23.0f;
	m_SubEffect.scale.y = 23.0f;

	m_Effect.Play();
	m_SubEffect.Play();
}

void CVanish::Update(void)
{
	if (m_Effect.Finished() && m_SubEffect.Finished())
		DeleteObject();

	m_Effect.Update();
	m_SubEffect.Update();
}

void CVanish::Draw(void)
{
	m_Effect.Draw();
	m_SubEffect.Draw();
}

void CVanish::Finalize(void)
{
	m_Effect.Delete();
	m_SubEffect.Delete();
}
