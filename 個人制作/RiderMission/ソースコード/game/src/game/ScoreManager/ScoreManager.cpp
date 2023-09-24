#include "ScoreManager.h"

const int CScoreManager::m_max_count_score = 99999;
const int CScoreManager::m_default_score = 0;
const int CScoreManager::m_max_digit = 5;

CScoreManager::CScoreManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "ScoreManager")
	, m_CurrentScore(0)
	, m_HiScore(0)
{
}

void CScoreManager::Initialize(void)
{
}

void CScoreManager::Update(void)
{
	if (!(m_CurrentScore < m_max_count_score))
		m_CurrentScore = m_max_count_score;
}

void CScoreManager::Finalize(void)
{
}

void CScoreManager::UpdateHiScore(void)
{
	if (m_HiScore < m_CurrentScore)
		m_HiScore = m_CurrentScore;
}
