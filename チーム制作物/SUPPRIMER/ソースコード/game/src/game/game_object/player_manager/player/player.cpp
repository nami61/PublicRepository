#include "player.h"
#include "white/white.h"

const int IPlayer::m_max_life = 500;

/*
 *  �R���X�g���N�^
 */
IPlayer::IPlayer(aqua::IGameObject* parent, const std::string& name)
	: aqua::IGameObject(parent, name, "Player")
	, m_ReadyFlag(false)
	, m_Life(m_max_life)
	, m_CounterValue(0)
	, m_GuardValue(0)
	, m_AtkDownValue(0)
	, m_CounterState(false)
	, m_GuardState(false)
	, m_PoisonState(false)
	, m_PoisonAttack(false)
	, m_State(STATE::ACTIVE)
{
}

/*
 *  ������
 */
void IPlayer::Initialize(void)
{
}

/*
 *  �X�V
 */
void IPlayer::Update(void)
{
}

/*
 *  �`��
 */
void IPlayer::Draw(void)
{
}

/*
 *  ���
 */
void IPlayer::Finalize(void)
{
}

void IPlayer::Damage(int damage)
{
	if (damage <= 0) return;
	m_Life -= damage;
	if (m_Life <= 0)
	{
		m_State = STATE::DEAD;
		m_Life = 0;
	}
}

void IPlayer::Damage(int damage, bool& poison_attack)
{
	if (damage <= 0) return;
	int damage_buffer = 0;

	if (poison_attack)
	{
		m_PoisonState = true;
		poison_attack = false;
	}

	if (m_GuardState && m_PlayerID == PLAYER_ID::BLUE)
	{
		m_GuardValue = 0.6f;
		m_GuardState = false;
	}
	else if (m_GuardState && !(m_PlayerID == PLAYER_ID::BLUE))
	{
		m_GuardValue = 0.8f;
		m_GuardState = false;
	}
	else
		m_GuardValue = 1.0f;
	damage_buffer = (int)((float)damage * m_GuardValue);
	m_Life -= damage_buffer;

	if (m_Life <= 0)
	{
		m_State = STATE::DEAD;
		m_Life = 0;
	}

	if (m_CounterState && m_PlayerID == PLAYER_ID::WHITE)
		m_CounterValue = (int)((float)damage_buffer * 0.5f);
	else if (m_CounterState && !(m_PlayerID == PLAYER_ID::WHITE))
		m_CounterValue = (int)((float)damage_buffer * 0.2f);
	else
		m_CounterValue = 0;
}

int IPlayer::Counter(void)
{
	int counter = 0;

	if (m_CounterValue > 0)
	{
		counter = m_CounterValue;
		m_CounterValue = 0;
		m_CounterState = false;
	}

	return counter;
}

void IPlayer::Heal(int heal)
{
	if (heal <= 0) return;
	m_Life += heal;
	if (m_Life > m_max_life)
		m_Life = m_max_life;
}

int IPlayer::Attack(int blocks, BLOCK_ID b_id, PLAYER_ID p_id)
{
	float atk = (float)blocks;

	if (b_id == BLOCK_ID::WHITE)
		m_CounterState = true;
	if (b_id == BLOCK_ID::BLUE)
		m_GuardState = true;
	if (b_id == BLOCK_ID::GREEN)
		m_PoisonAttack = true;
	if (b_id == BLOCK_ID::PINK)
		Heal(blocks);

	if (m_PoisonState && atk != 0)
	{
		if (p_id == PLAYER_ID::GREEN)
			atk *= 0.5f;
		else
			atk *= 0.7f;
		m_PoisonState = false;
	}

	return (int)atk;
}

