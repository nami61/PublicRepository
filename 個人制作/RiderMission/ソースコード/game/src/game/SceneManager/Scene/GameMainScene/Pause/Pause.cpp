#include "Pause.h"
#include "../../../../ScoreManager/ScoreManager.h"
#include "../../../../SoundManager/SoundManager.h"

const int CPause::m_message_size = 64;
const aqua::CVector2 CPause::m_default_pause_message_pos = aqua::CVector2(360.0f, 100.0f);
const aqua::CVector2 CPause::m_default_return_message_pos = aqua::CVector2(300.0f, 300.0f);
const aqua::CVector2 CPause::m_default_continue_message_pos = aqua::CVector2(300.0f, 400.0f);
const aqua::CVector2 CPause::m_default_finish_game_message_pos = aqua::CVector2(300.0f, 500.0f);

CPause::CPause(aqua::IGameObject* parent)
	:IScene(parent, "Pause")
{
}

void CPause::Initialize(void)
{
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_ScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	m_BackPlane.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), 0x80000000);
	m_PauseMessage.Create(m_message_size * 2, 1, true, aqua::FONT_FAMILY_ID::HG_SOUEIKAKUPOP);
	m_PauseMessage.text = "P A U S E";
	m_PauseMessage.position = m_default_pause_message_pos;
	m_ReturnMessage.Create(m_message_size);
	m_ReturnMessage.text = "ゲームに戻る　";
	m_ReturnMessage.position = m_default_return_message_pos;
	m_ContinueMessage.Create(m_message_size);
	m_ContinueMessage.text = "コンテニュー";
	m_ContinueMessage.position = m_default_continue_message_pos;
	m_FinishGameMessage.Create(m_message_size);
	m_FinishGameMessage.text = "タイトルに戻る";
	m_FinishGameMessage.position = m_default_finish_game_message_pos;
	m_CursorBox.Setup(aqua::CVector2::ZERO, (float)m_ReturnMessage.GetTextWidth(), m_message_size, 0x80ffffff);

	m_State = STATE::RETURN;
}

void CPause::Update(void)
{
	int w = aqua::mouse::GetWheel();

	if (w < 0)
		m_State = (STATE)(((int)m_State + 1) % 3);
	if (w > 0)
	{
		if ((int)m_State <= 0)
			m_State = STATE::FINISH;
		else
			m_State = (STATE)(((int)m_State - 1));
	}

	switch (m_State)
	{
	case CPause::STATE::RETURN: ReturnToGameScreen(); break;
	case CPause::STATE::CONTINUE: Continue(); break;
	case CPause::STATE::FINISH: FinishGame(); break;
	}
}

void CPause::Draw(void)
{
	m_BackPlane.Draw();
	m_CursorBox.Draw();
	m_PauseMessage.Draw();
	m_ReturnMessage.Draw();
	m_ContinueMessage.Draw();
	m_FinishGameMessage.Draw();
}

void CPause::Finalize(void)
{
	m_PauseMessage.Delete();
	m_ReturnMessage.Delete();
	m_ContinueMessage.Delete();
	m_FinishGameMessage.Delete();
}

void CPause::ReturnToGameScreen(void)
{
	m_CursorBox.position = m_default_return_message_pos;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		Pop();
}

void CPause::Continue(void)
{
	m_CursorBox.position = m_default_continue_message_pos;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		m_ScoreManager->ResetScore();
		m_SoundManager->Stop(SOUND_ID::GAME_MAIN_BGM);
		Reset();
	}
}

void CPause::FinishGame(void)
{
	m_CursorBox.position = m_default_finish_game_message_pos;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		m_ScoreManager->ResetScore();
		m_SoundManager->Stop(SOUND_ID::GAME_MAIN_BGM);
		Pop();
		Change(SCENE_ID::TITLE);
	}

}
