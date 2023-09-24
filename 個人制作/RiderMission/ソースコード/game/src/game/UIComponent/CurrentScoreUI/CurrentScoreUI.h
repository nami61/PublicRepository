#pragma once

#include "aqua.h"

class CScoreManager;

class CCurrentScoreUI :public aqua::IGameObject
{
public:
	CCurrentScoreUI(aqua::IGameObject* parent);
	~CCurrentScoreUI(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	void RectSetting(void);

	void ScoreDigitSetting(void);

	static const int m_default_score;
	static const int m_max_score_digit;
	static const int m_decimal_number;
	static const aqua::CVector2 m_default_plane_pos;
	static const aqua::CVector2 m_default_score_pos;
	int m_Score;
	aqua::CLabel m_ScoreLabel;
	aqua::CSprite* m_ScoreSprite;
	aqua::CVector2 m_ScorePos;
	aqua::CSprite m_Plane;
	aqua::CVector2 m_PlanePos;
	CScoreManager* m_ScoreManager;
};