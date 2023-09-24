#include "Fire.h"
#include  "../../../Player/Player.h"
#include "../../../SoundManager/SoundManager.h"
#include "../../../Collision/Collision.h"

const int CFire::m_default_damage = 1;

CFire::CFire(aqua::IGameObject* parent)
	:IStageObject(parent, "Fire")
{
}

void CFire::Initialize(aqua::CVector2 pos)
{
	m_Position = pos;

	IStageObject::Initialize();

	m_AnmSprite.Create("data/animation/fire.ass");

	m_Size.x = (float)m_AnmSprite.GetFrameWidth();
	m_Size.y = (float)m_AnmSprite.GetFrameHeight();

	m_Category = STAGE_OBJECT_CATEGORY::OBSTACLE;

	m_Damage = m_default_damage;

	m_IsAppear = false;

	m_Player = (CPlayer*)aqua::FindGameObject("Player");

	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
}

void CFire::Update(void)
{
	if (m_Position.x <= (float)(-m_AnmSprite.GetFrameWidth()))
		m_ActiveFlag = false;

	m_AnmSprite.Update();

	if (IsHitPlayer())
	{
		m_Player->Damage(m_Damage);
		m_SoundManager->Play(SOUND_ID::DAMAGE);
	}
		
	m_Position.x -= m_Velocity.x;
	if (m_Position.x < (aqua::GetWindowWidth() + m_AnmSprite.GetFrameWidth()) && !m_IsAppear)
	{
		m_IsAppear = true;
		m_SoundManager->Play(SOUND_ID::FIRE_APPEAR);
	}

	m_AnmSprite.position = m_Position;

	IStageObject::Update();
}

void CFire::Draw(void)
{
	m_AnmSprite.Draw();

	IStageObject::Draw();
}

void CFire::Finalize(void)
{
	m_AnmSprite.Delete();

	IStageObject::Finalize();
}

bool CFire::IsHitPlayer(void)
{
	float radius = m_AnmSprite.GetFrameWidth() / 3.5f;
	if (collision::CircleAndRectangle(m_Position, radius, m_Player->GetPosition(), m_Player->GetSize()))
		return true;

	return false;
}
