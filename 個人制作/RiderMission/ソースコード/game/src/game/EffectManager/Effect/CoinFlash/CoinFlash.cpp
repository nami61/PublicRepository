#include "CoinFlash.h"

CCoinFlash::CCoinFlash(aqua::IGameObject* parent)
	:IEffect(parent, "CoinFlash")
{
}

void CCoinFlash::Initialize(const aqua::CVector2& pos)
{
	m_Position = pos;

	m_Effect.Create("data/effect/coin_flash/coin_flash.efkefc");
	m_Effect.position = m_Position;
	m_Effect.scale.x = 100.0f;
	m_Effect.scale.y = 100.0f;
	m_Effect.Play();

	IGameObject::Initialize();
}

void CCoinFlash::Update(void)
{
	m_Effect.Update();

	m_Effect.position = m_Position;

	IGameObject::Update();
}

void CCoinFlash::Draw(void)
{
	m_Effect.Draw();

	IGameObject::Draw();
}

void CCoinFlash::Finalize(void)
{
	m_Effect.Delete();

	IGameObject::Finalize();
}
