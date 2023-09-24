#include "Effect.h"

IEffect::IEffect(aqua::IGameObject* parent, const std::string& name)
	: aqua::IGameObject(parent, name, "Effect")
{
}

void IEffect::Initialize(void)
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
}

void IEffect::Finalize(void)
{
}
