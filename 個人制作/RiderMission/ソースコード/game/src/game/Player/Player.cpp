#include "Player.h"
#include "../Stage/Stage.h"
#include "../StageObjectManager/StageObjectManager.h"

const aqua::CVector2 CPlayer::m_default_pos = aqua::CVector2(100.0f, 0.0f);
const int CPlayer::m_max_jump_count = 1;
const int CPlayer::m_default_max_life = 1;
const float CPlayer::m_fall_limit = 0.2f;
const float CPlayer::m_easing_limit = 0.5f;
const float CPlayer::m_max_fall_speed = 1200.0f;
const float CPlayer::m_jump_power = 1500.0f;

CPlayer::CPlayer(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Player")
{
}

void CPlayer::Initialize(void)
{
	m_Stage = (CStage*)aqua::FindGameObject("Stage");
	m_StageObjectManager = (CStageObjectManager*)aqua::FindGameObject("StageObjectManager");

	m_Position = m_default_pos;
	m_AnmSprite.Create("data/animation/player.ass");
	m_AnmSprite.position = m_Position;

	m_Size.x = (float)m_AnmSprite.GetFrameWidth();
	m_Size.y = (float)m_AnmSprite.GetFrameHeight();

	m_Velocity.y = 0.0f;
	m_AirJumpCount = 0;

	m_Life = m_MaxLife = m_default_max_life;

	m_LandingFlag = false;
	m_FallFlag = false;
	m_ActiveFlag = true;

	m_FallTimer.Setup(m_fall_limit);
	m_EasingTimer.Setup(m_easing_limit);

	IGameObject::Initialize();
}

void CPlayer::Update(void)
{
	if (m_LandingFlag)
		m_AnmSprite.Change((int)ANM_STATE::RUN);
	else
		m_AnmSprite.Change((int)ANM_STATE::JUMP);
		
	m_AnmSprite.Update();

	if (!m_LandingFlag)
		m_Velocity.y += m_Stage->GetGrav();
	else
	{
		m_Velocity.y = 0.0f;
		m_AirJumpCount = 0;
	}

	if (m_Velocity.y > m_max_fall_speed)
		m_Velocity.y = m_max_fall_speed;

	Fall();

	Jump();

	float deadLine = (float)aqua::GetWindowHeight() + m_Size.y;
	if (m_Position.y >= deadLine)
		m_ActiveFlag = false;

	if (m_Life == 0)
		m_ActiveFlag = false;

	m_StageObjectManager->PlayerCast(m_Position, m_Velocity.y * aqua::GetDeltaTime(), m_Size.x, m_Size.y, m_FallFlag, m_Position, m_LandingFlag);

	m_AnmSprite.position = m_Position;

	IGameObject::Update();
}

void CPlayer::Draw(void)
{
	m_AnmSprite.Draw();
}

void CPlayer::Finalize(void)
{
	m_AnmSprite.Delete();
}

void CPlayer::Jump(void)
{
	if (m_AirJumpCount >= m_max_jump_count) return;

	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		if (!m_LandingFlag)
			++m_AirJumpCount;

		m_Velocity.y = -m_jump_power;
	}
}

void CPlayer::Fall(void)
{
	if (!m_StageObjectManager->FindGround(m_Position, m_Size.x, m_Size.y)) return;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::RIGHT))
	{
		if (m_LandingFlag)
		{
			m_FallFlag = true;
			m_FallTimer.Reset();
		}
	}

	if (m_FallFlag)
	{
		m_FallTimer.Update();
		if (m_FallTimer.Finished())
		{
			m_FallFlag = false;
			m_FallTimer.Reset();
		}
	}
}

void CPlayer::Damage(int damage)
{
	if (damage <= 0) return;

	m_Life -= damage;

	if (m_Life <= 0)
		m_Life = 0;
}
