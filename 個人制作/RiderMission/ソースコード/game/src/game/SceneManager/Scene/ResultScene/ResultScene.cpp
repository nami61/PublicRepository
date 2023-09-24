#include "ResultScene.h"
#include "../../../SoundManager/SoundManager.h"
#include "../../../ScoreManager/ScoreManager.h"

const int CResultScene::m_max_score_digit = 5;
const int CResultScene::m_decimal_number = 10;
const float CResultScene::m_easing_limit = 1.0f;
const aqua::CVector2 CResultScene::m_default_score_pos = aqua::CVector2(900.0f, 250.0f);

CResultScene::CResultScene(aqua::IGameObject* parent)
	:IScene(parent, "ResultScene")
{
}

void CResultScene::Initialize(void)
{
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_ScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");

	IGameObject::Initialize();

	m_NumberSprite = AQUA_NEW aqua::CSprite[m_max_score_digit];

	for (int spriteNumber = 0; spriteNumber < m_max_score_digit; ++spriteNumber)
	{
		m_NumberSprite[spriteNumber].Create("data/texture/number_for_result.png");
		m_NumberSprite[spriteNumber].position = m_default_score_pos;
		float width = (float)(m_NumberSprite[spriteNumber].GetTextureWidth() / m_decimal_number);
		float height = (float)m_NumberSprite[spriteNumber].GetTextureHeight();
		m_NumberSprite[spriteNumber].position.x -= (width * spriteNumber);
		m_NumberSprite[spriteNumber].rect = aqua::CRect(0, 0, (int)width, (int)height);
		m_NumberSprite[spriteNumber].visible = false;
	}

	m_BGSprite.Create("data/texture/forest_hd.png");

	m_EasingTimer.Setup(m_easing_limit);

	m_ScoreMessage.Create(64);
	m_ScoreMessage.text = "Total Score";
	m_ScoreMessage.position = aqua::CVector2(150.0f, 150.0f);

	m_RetryMessage.Create(64);
	m_RetryMessage.text = "コンテニュー";
	m_RetryMessage.position = aqua::CVector2(100.0f, 500.0f);

	m_ReturnToTitleMessage.Create(64);
	m_ReturnToTitleMessage.text = "タイトルへ戻る";
	m_ReturnToTitleMessage.position = aqua::CVector2(600.0f, 500.0f);

	m_CursorBox.Setup(aqua::CVector2::ZERO, (float)m_ReturnToTitleMessage.GetTextWidth(), 64.0f, 0x50ffffff);
	m_BackPlane.Setup(aqua::CVector2(0.0f, 100.0f), (float)aqua::GetWindowWidth(), 500.0f, 0x80000000);

	m_Score = 0;

	m_State = CURSOR_STATE::CONTINUE;

	m_IsFinish = false;

	m_ScoreManager->UpdateHiScore();

	m_SoundManager->Play(SOUND_ID::RESULT_BGM);
}

void CResultScene::Update(void)
{
	if ((aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RETURN) || (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))) && m_IsFinish)
	{
		if (m_State == CURSOR_STATE::CONTINUE)
		{
			Change(SCENE_ID::GAMEMAIN);
			m_SoundManager->Stop(SOUND_ID::RESULT_BGM);
			m_ScoreManager->ResetScore();
		}
		if (m_State == CURSOR_STATE::RETURN_TO_TITLE)
		{
			Change(SCENE_ID::TITLE);
			m_SoundManager->Stop(SOUND_ID::RESULT_BGM);
			m_ScoreManager->ResetScore();
		}
	}

	int w = aqua::mouse::GetWheel();
	if (w != 0)
	{
		m_State = (CURSOR_STATE)(((int)m_State + 1) % 2);
	}

	switch (m_State)
	{
	case CResultScene::CURSOR_STATE::CONTINUE: m_CursorBox.position = aqua::CVector2(100.0f, 500.0f);
		break;
	case CResultScene::CURSOR_STATE::RETURN_TO_TITLE: m_CursorBox.position = aqua::CVector2(600.0f, 500.0f);
		break;
	}

	RectSetting();

	ScoreDigitSetting();

	m_EasingTimer.Update();

	float score = (aqua::easing::InCirc(m_EasingTimer.GetTime(), m_EasingTimer.GetLimit()) * m_ScoreManager->GetCurrentScore());
	m_Score = (int)score;

	if (m_EasingTimer.Finished())
	{
		m_Score = m_ScoreManager->GetCurrentScore();
		m_IsFinish = true;
	}
}

void CResultScene::Draw(void)
{
	m_BGSprite.Draw();
	m_BackPlane.Draw();
	m_CursorBox.Draw();
	m_RetryMessage.Draw();
	m_ReturnToTitleMessage.Draw();
	m_ScoreMessage.Draw();

	for(int spriteNumber = 0; spriteNumber < m_max_score_digit; ++spriteNumber)
		m_NumberSprite[spriteNumber].Draw();
}

void CResultScene::Finalize(void)
{
	m_BGSprite.Delete();

	m_ScoreMessage.Delete();
	m_RetryMessage.Delete();
	m_ReturnToTitleMessage.Delete();

	AQUA_SAFE_DELETE_ARRAY(m_NumberSprite);
	IGameObject::Finalize();
}

void CResultScene::RectSetting(void)
{
	int maxCount = m_ScoreManager->GetMaxCountScore();
	if (!(m_Score < maxCount)) return;

	int digitWidth = m_NumberSprite[0].GetTextureWidth() / 10;
	for (int i = 0; i < m_max_score_digit; ++i)
	{
		int n = (int)std::pow(m_decimal_number, i);
		m_NumberSprite[i].rect.left = digitWidth * ((m_Score / n) % m_decimal_number);
		m_NumberSprite[i].rect.right = m_NumberSprite[i].rect.left + digitWidth;
	}
}

void CResultScene::ScoreDigitSetting(void)
{
	m_NumberSprite[0].visible = true;
	if (m_Score < 10) return;
	m_NumberSprite[1].visible = true;
	if (m_Score < 100) return;
	m_NumberSprite[2].visible = true;
	if (m_Score < 1000) return;
	m_NumberSprite[3].visible = true;
	if (m_Score < 10000) return;
	m_NumberSprite[4].visible = true;
}