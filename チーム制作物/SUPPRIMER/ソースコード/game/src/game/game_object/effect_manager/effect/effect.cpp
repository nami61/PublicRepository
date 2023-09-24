#include "effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, name, "Effect")
{
}

void IEffect::Initialize(const aqua::CVector2& pos)
{
	(void)pos;
}

void IEffect::Update(void)
{
}

void IEffect::Draw(void)
{
	m_Effect.Draw();
}

void IEffect::Finalize(void)
{
	m_Effect.Delete();
}
