#include "round_manager.h"

const float CRoundManager::m_default_round_time = 30.0f;
const int CRoundManager::m_max_rounds = 3;

CRoundManager::CRoundManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "RoundManager")
	, m_CurrentRounds(0)
{
}

void CRoundManager::Initialize(void)
{
	m_Timer.Setup(m_default_round_time);
}

void CRoundManager::Update(void)
{
	m_Timer.Update();
}

void CRoundManager::Finalize(void)
{
}
