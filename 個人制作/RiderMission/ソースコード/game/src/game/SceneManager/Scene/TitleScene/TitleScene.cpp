#include "TitleScene.h"
#include "../../../ScoreManager/ScoreManager.h"
#include "../../../SoundManager/SoundManager.h"
#include "../../../EffectManager/EffectManager.h"
#include "../../../UIComponent/TitleLogo/TitleLogo.h"
#include "../../../Translate/Translate.h"

const int CTitleScene::m_message_size = 64;
const float CTitleScene::m_cursor_animation_interval = 2.0f;
const aqua::CVector2 CTitleScene::m_message_pos = aqua::CVector2(500.0f, 200.0f);
const aqua::CVector2 CTitleScene::m_message_space = aqua::CVector2(0.0f, 80.0f);
const aqua::CVector2 CTitleScene::m_cursor_space = aqua::CVector2((float)m_message_size, 0.0f);
const aqua::CVector2 CTitleScene::m_default_title_logo_pos = aqua::CVector2(300.0f, 100.0f);

CTitleScene::CTitleScene(aqua::IGameObject* parent)
	:IScene(parent, "TitleScene")
{
}

void CTitleScene::Initialize(void)
{
	m_TitleLogo = aqua::CreateGameObject<CTitleLogo>(this);
	m_TitleLogo->Initialize();
	m_CurrentScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	m_Surface.Create((int)aqua::GetWindowWidth(), (int)aqua::GetWindowHeight(),true);
	m_SurfaceSprite.Create(m_Surface);
	m_SurfaceSprite.scale = aqua::CVector2::ZERO;
	m_TranslateFlag = true;
	m_TranslateTimer.Setup(3.0f);
	m_ControlPanelFadeTimer.Setup(3.0f);
	m_ControlPanelWaitTimer.Setup(1.0f);
	m_ControlPanelAppearTimer.SetLimit(2.0f);

	m_BackGroundSprite.Create("data/texture/forest_hd.png");
	m_ControlPanel.Create("data/texture/control_panel_wheel.png");
	m_ControlPanel.position = aqua::CVector2(500.0f, 440.0f);
	m_ControlPanel.color.alpha = 0x00;

	m_CurrentSelectionBar.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), m_message_size, 0x00ffffff);

	//メッセージ処理
	{
		m_BackPanel.Setup(aqua::CVector2(0.0f, 150.0f), (float)aqua::GetWindowWidth(), 400.0f, 0x80000000);

		m_StartMessage.Create(m_message_size);
		m_StartMessage.text = "ゲームスタート";
		m_StartMessage.position = m_message_pos;

		m_ViewScore.Create(m_message_size);
		m_ViewScore.text = "スコア表示";
		m_ViewScore.position = m_StartMessage.position + m_message_space;

		m_EndMessage.Create(m_message_size);
		m_EndMessage.text = "ゲーム終了";
		m_EndMessage.position = m_ViewScore.position + m_message_space;
	}

	m_CursorTimer.Setup(m_cursor_animation_interval);

	m_State = CURSOR_STATE::GAME_START;
	m_CurrentState = m_State;
	m_SceneState = SCENE_STATE::TITLE_IN;

	m_SoundManager->Play(SOUND_ID::TITLE_BGM);

	m_FadeTimer.Setup(0.2f);
}

void CTitleScene::Update(void)
{
	switch (m_SceneState)
	{
	case SCENE_STATE::TITLE_IN: TitleIn(); break;
	case SCENE_STATE::TITLE_UPDATE: TitleUpdate(); break;
	}

	IGameObject::Update();
}

void CTitleScene::Draw(void)
{
	m_BackGroundSprite.Draw();
	if (this->GetGameObjectState() == aqua::GAME_OBJECT_STATE::WAIT) return;

	switch (m_SceneState)
	{
	case SCENE_STATE::TITLE_IN: 
		m_TitleLogo->Draw();

		break;
	case SCENE_STATE::TITLE_UPDATE:
		m_Surface.Begin();

		m_BackPanel.Draw();
		m_ControlPanel.Draw();
		m_CurrentSelectionBar.Draw();
		m_StartMessage.Draw();
		m_ViewScore.Draw();
		m_EndMessage.Draw();
		m_Surface.End();

		break;
	}
	m_SurfaceSprite.Draw();
}

void CTitleScene::Finalize(void)
{
	m_TitleLogo->Finalize();

	m_Surface.Delete();
	m_SurfaceSprite.Delete();

	m_BackGroundSprite.Delete();
	m_ControlPanel.Delete();

	m_StartMessage.Delete();
	m_ViewScore.Delete();
	m_EndMessage.Delete();

	IGameObject::Finalize();
}

void CTitleScene::TitleIn(void)
{
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		m_SceneState = SCENE_STATE::TITLE_UPDATE;
}

void CTitleScene::TitleUpdate(void)
{
	m_SurfaceSprite.anchor = aqua::CVector2(m_SurfaceSprite.GetTextureWidth() / 2.0f, m_SurfaceSprite.GetTextureHeight() / 2.0f);
	if (m_TranslateFlag)
	{
		m_TranslateTimer.Update();
		if (m_TranslateTimer.Finished())
		{
			m_TranslateFlag = false;
			m_SurfaceSprite.scale.x = 1.0f;
			m_SurfaceSprite.scale.y = 1.0f;
		}
		CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
		translate->Translate(m_SurfaceSprite.scale.x, 0.0f, 1.0f, m_TranslateTimer, false, DIRECTION_MODE::IN_EXP);
		translate->Translate(m_SurfaceSprite.scale.y, 0.0f, 1.0f, m_TranslateTimer, false, DIRECTION_MODE::LINEAR);
	}
	else
	{
		switch (m_State)
		{
		case CTitleScene::CURSOR_STATE::GAME_START:		 GameStart();	   break;
		case CTitleScene::CURSOR_STATE::VIEW_SCORE:		 ViewScore();	   break;
		case CTitleScene::CURSOR_STATE::GAME_END:		 GameEnd();		   break;
		}

		float angle = ((m_CursorTimer.GetTime() / m_CursorTimer.GetLimit()) * 360.0f);

		m_CursorTimer.Update();
		if (m_CursorTimer.Finished() || m_CurrentState != m_State)
		{
			m_CursorTimer.Reset();

			if (m_CurrentState != m_State)
				m_CurrentState = m_State;
		}

		m_FadeTimer.Update();
		m_CurrentSelectionBar.width = aqua::easing::OutExp(m_FadeTimer.GetTime(), m_FadeTimer.GetLimit(), 0.0f, (float)aqua::GetWindowWidth());

		if (m_FadeTimer.Finished())
		{
			m_CurrentSelectionBar.width = (float)aqua::GetWindowWidth();
			m_CurrentSelectionBar.color.alpha = (unsigned char)(abs(cosf(aqua::DegToRad(angle))) * 100);
		}
		else
		{
			m_CurrentSelectionBar.color.alpha = (unsigned char)aqua::easing::InExp(m_FadeTimer.GetTime(), m_FadeTimer.GetLimit(), 40, 100);
		}

		int w = aqua::mouse::GetWheel();

		if (w < 0)
		{
			m_FadeTimer.Reset();
			m_SoundManager->Play(SOUND_ID::CURSOR_SELECT);
			m_State = (CURSOR_STATE)(((int)m_State + 1) % 3);
		}
		if (w > 0)
		{
			m_FadeTimer.Reset();
			m_SoundManager->Play(SOUND_ID::CURSOR_SELECT);
			if ((int)m_State <= 0)
				m_State = CURSOR_STATE::GAME_END;
			else m_State = (CURSOR_STATE)(((int)m_State - 1));
		}
	}

	m_ControlPanelWaitTimer.Update();
	if (m_ControlPanelWaitTimer.Finished())
	{
		if (m_ControlPanelAppearTimer.Finished())
		{
			float angle = (m_ControlPanelFadeTimer.GetTime() / m_ControlPanelFadeTimer.GetLimit() * 360.0f);
			m_ControlPanelFadeTimer.Update();
			if (m_ControlPanelFadeTimer.Finished())
			{
				m_ControlPanelWaitTimer.Reset();
				m_ControlPanelFadeTimer.Reset();
			}
			m_ControlPanel.color.alpha = (unsigned char)abs(cosf(aqua::DegToRad(angle)) * 255.0f);
		}
		else
		{
			CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
			m_ControlPanelAppearTimer.Update();
			float alpha = 0.0f;
			translate->Translate(alpha, 0.0f, 255.0f, m_ControlPanelAppearTimer);
			m_ControlPanel.color.alpha = (unsigned char)alpha;
			if (m_ControlPanelAppearTimer.Finished())
				m_ControlPanelWaitTimer.Reset();
		}
	}
}

void CTitleScene::GameStart(void)
{
	m_CurrentSelectionBar.position.y = m_StartMessage.position.y - m_cursor_space.y;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		m_SoundManager->Stop(SOUND_ID::TITLE_BGM);
		m_SoundManager->Play(SOUND_ID::SCENE_CHANGE);
		Change(SCENE_ID::GAMEMAIN);
	}
}

void CTitleScene::ViewScore(void)
{
	m_CurrentSelectionBar.position.y = m_ViewScore.position.y - m_cursor_space.y;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
	{
		Push(SCENE_ID::VIEW_SCORE);
		m_SoundManager->Play(SOUND_ID::VIEW_SCORE);
	}
}

void CTitleScene::GameEnd(void)
{
	m_CurrentSelectionBar.position.y = m_EndMessage.position.y - m_cursor_space.y;
	if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		Push(SCENE_ID::CONFIRM_EXIT);
}
