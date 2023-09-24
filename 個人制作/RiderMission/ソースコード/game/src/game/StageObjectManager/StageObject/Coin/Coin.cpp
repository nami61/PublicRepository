#include "Coin.h"
#include "../../../Player/Player.h"
#include "../../../ScoreManager/ScoreManager.h"
#include "../../../SoundManager/SoundManager.h"
#include "../../../EffectManager/EffectManager.h"
#include "../../../Collision/Collision.h"

const int CCoin::m_default_score = 100;
const float CCoin::m_rising_speed = 10.0f;
const float CCoin::m_upper_limit = 200.0f;

CCoin::CCoin(aqua::IGameObject* parent)
	:IStageObject(parent, "Coin")
{
}

void CCoin::Initialize(aqua::CVector2 pos)
{
	m_Position = pos;

	IStageObject::Initialize();

	m_AnmSprite.Create("data/animation/coin.ass");

	m_Score = m_default_score;

	m_Enabled = true;

	m_RisingTimer.Setup(0.17f);

	m_State = ANIMATION_STATE::WAIT;

	m_Category = STAGE_OBJECT_CATEGORY::ITEM;

	m_Player = (CPlayer*)aqua::FindGameObject("Player");

	m_ScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");

	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	m_Effect.Create("data/effect/coin_flash/coin_flash.efkefc");
	m_Effect.scale.x = 30.0f;
	m_Effect.scale.y = 30.0f;
	m_Effect.Play();
}

void CCoin::Update(void)
{
	m_Effect.Update();
	if (m_Effect.Finished())
		m_Effect.Play();

	if (IsHitPlayer() && m_Enabled)
	{
		m_Effect.visible = false;
		m_SoundManager->Play(SOUND_ID::GET_COIN);
		m_ScoreManager->AddScore(m_Score);
		m_State = ANIMATION_STATE::RISING;
		m_Enabled = false;
	}

	//Animation();

	if (m_State == ANIMATION_STATE::END)
		m_ActiveFlag = false;

	m_AnmSprite.Update();

	if (m_State == ANIMATION_STATE::RISING)
	{
		m_RisingTimer.Update();
		m_AnmSprite.Change("rising");
		if (m_RisingTimer.Finished())
			m_State = ANIMATION_STATE::END;

		m_Position.y -= m_rising_speed;
	}

	m_Position.x -= m_Velocity.x;
	m_AnmSprite.position = m_Position;
	m_Effect.position = m_Position + aqua::CVector2(m_AnmSprite.GetFrameWidth() / 2.0f, m_AnmSprite.GetFrameHeight() / 2.0f);

	IStageObject::Update();
}

void CCoin::Draw(void)
{
	m_AnmSprite.Draw();
	m_Effect.Draw();

	IStageObject::Draw();
}

void CCoin::Finalize(void)
{
	m_AnmSprite.Delete();
	m_Effect.Delete();

	IStageObject::Finalize();
}

void CCoin::Animation(void)
{
	if (m_State == ANIMATION_STATE::END) 
		m_ActiveFlag = false;

	m_AnmSprite.Update();

	if (m_State == ANIMATION_STATE::WAIT) return;

	m_AnmSprite.Change("rising");
}

bool CCoin::IsHitPlayer(void)
{
	float radius = m_AnmSprite.GetFrameWidth() / 2.0f;
	if(collision::CircleAndRectangle(m_Position, radius, m_Player->GetPosition(), m_Player->GetSize()))
		return true;

	return false;
}
