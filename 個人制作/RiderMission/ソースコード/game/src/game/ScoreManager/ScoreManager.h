#pragma once

#include "aqua.h"

class CScoreManager :public aqua::IGameObject
{
public:
	CScoreManager(aqua::IGameObject* parent);
	~CScoreManager(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Finalize(void) override;

	void AddScore(int score) { m_CurrentScore += score; }

	int GetCurrentScore(void) { return m_CurrentScore; }

	int GetHiScore(void) { return m_HiScore; }

	int GetMaxCountScore(void) { return m_max_count_score; }

	int GetMaxDigit(void) { return m_max_digit; }

	void UpdateHiScore(void);

	void ResetScore(void) { m_CurrentScore = 0; }

private:
	static const int m_max_count_score;
	static const int m_default_score;
	static const int m_max_digit;
	int m_CurrentScore;
	int m_HiScore;
};