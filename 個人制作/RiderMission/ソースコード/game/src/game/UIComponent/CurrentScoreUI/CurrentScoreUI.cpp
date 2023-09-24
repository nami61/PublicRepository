#include "CurrentScoreUI.h"
#include "../../ScoreManager/ScoreManager.h"

const int CCurrentScoreUI::m_default_score = 0;
const int CCurrentScoreUI::m_max_score_digit = 5;
const int CCurrentScoreUI::m_decimal_number = 10;
const aqua::CVector2 CCurrentScoreUI::m_default_plane_pos = aqua::CVector2(50.0f, 30.0f);
const aqua::CVector2 CCurrentScoreUI::m_default_score_pos = aqua::CVector2(162.0f, 42.0f);

CCurrentScoreUI::CCurrentScoreUI(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CurrentScoreUI")
{
}

void CCurrentScoreUI::Initialize(void)
{
	m_Score = m_default_score;

	m_ScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");

	m_ScoreLabel.Create(32);

	m_ScoreLabel.position = m_default_score_pos;

	m_ScoreSprite = AQUA_NEW aqua::CSprite[m_max_score_digit];

	for (int i = 0; i < m_max_score_digit; ++i)
	{
		m_ScoreSprite[i].Create("data/texture/number_for_gamemain.png");

		int digitWidth = m_ScoreSprite[i].GetTextureWidth() / m_decimal_number;
		m_ScoreSprite[i].rect.right = (int)digitWidth;

		m_ScoreSprite[i].position = m_default_score_pos - aqua::CVector2((float)(digitWidth * i), 0.0f);

		if (i == 0) continue;
		m_ScoreSprite[i].visible = false;
	}

	m_Plane.Create("data/texture/score_frame.png");

	m_Plane.position = m_default_plane_pos;
}

void CCurrentScoreUI::Update(void)
{
	m_Score = m_ScoreManager->GetCurrentScore();

	m_ScoreLabel.text = std::to_string(m_Score);

	RectSetting();

	ScoreDigitSetting();
}

void CCurrentScoreUI::Draw(void)
{
	m_Plane.Draw();

	for (int i = 0; i < m_max_score_digit; ++i)
		m_ScoreSprite[i].Draw();
}

void CCurrentScoreUI::Finalize(void)
{
	m_Plane.Delete();

	//for (int i = 0; i < m_max_score_digit; ++i)
		//m_ScoreSprite[i].Delete();
	AQUA_SAFE_DELETE_ARRAY(m_ScoreSprite);

	m_ScoreLabel.Delete();
}

void CCurrentScoreUI::RectSetting(void)
{
	int maxCount = m_ScoreManager->GetMaxCountScore();
	if (!(m_Score < maxCount)) return;

	int digitWidth = m_ScoreSprite[0].GetTextureWidth() / 10;
	for (int i = 0; i < m_max_score_digit; ++i)
	{
		int n = (int)std::pow(m_decimal_number, i);
		m_ScoreSprite[i].rect.left = digitWidth * ((m_Score / n) % m_decimal_number);
		m_ScoreSprite[i].rect.right = m_ScoreSprite[i].rect.left + digitWidth;
	}
}

void CCurrentScoreUI::ScoreDigitSetting(void)
{
	if (m_Score < 10) return;
		m_ScoreSprite[1].visible = true;
	if (m_Score < 100) return;
		m_ScoreSprite[2].visible = true;
	if (m_Score < 1000) return;
		m_ScoreSprite[3].visible = true;
	if (m_Score < 10000) return;
		m_ScoreSprite[4].visible = true;
}
