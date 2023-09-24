#include "continue.h"
#include "../../../scene_manager/scene_manager.h"
#include "../../sound_manager/sound_manager.h"

const aqua::CVector2 CContinue::m_top_message_pos_p1 = aqua::CVector2(300.0f, 700.0f);
const aqua::CVector2 CContinue::m_top_message_pos_p2 = aqua::CVector2(400.0f, 700.0f);
const aqua::CVector2 CContinue::m_top_cursor_pos_p1 = aqua::CVector2(100.0f, 700.0f);
const aqua::CVector2 CContinue::m_top_cursor_pos_p2 = aqua::CVector2(200.0f, 700.0f);

CContinue::CContinue(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Continue")
	, m_ContinuousInput(false)
{
}

void CContinue::Initialize(void)
{
	m_Sprite.Create("data/select_button.png");
	m_ContinueMessage.Create(96);
	m_ExitGameMessage.Create(96);
	m_ContinueMessage.text = "もう一度バトル！";
	m_ExitGameMessage.text = "タイトルへ";
	SetUIPosition();
	m_Sprite.anchor.x = (float)m_Sprite.GetTextureWidth() / 2.0f;
	m_Sprite.anchor.y = (float)m_Sprite.GetTextureHeight() / 2.0f;
	m_Sprite.scale.x = -1.0f;
	m_CursorBoundTimer.Setup(2.0f);
	m_State = CURSOR_STATE::CONTINUE;
	m_SM = (CSceneManager*)aqua::FindGameObject("SceneManager");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_SoundManager->Play(SOUND_ID::RESULT_BGM);
}

void CContinue::Update(void)
{
	m_CursorBoundTimer.Update();
	if (m_CursorBoundTimer.Finished())
		m_CursorBoundTimer.Reset();
	float angle = (m_CursorBoundTimer.GetTime() / m_CursorBoundTimer.GetLimit()) * 360.0f;
	float range = std::abs(std::sinf(aqua::DegToRad(angle))) * 100.0f;
	float scale = std::cosf(aqua::DegToRad(angle));
	if(m_EnabledDevice == aqua::controller::DEVICE_ID::P1)
		m_Sprite.position.x = m_top_cursor_pos_p1.x + range;
	else if(m_EnabledDevice == aqua::controller::DEVICE_ID::P2)
		m_Sprite.position.x = m_top_cursor_pos_p2.x + range;
	m_Sprite.scale.y = scale;

	switch (m_State)
	{
	case CContinue::CURSOR_STATE::CONTINUE: Continue();	break;
	case CContinue::CURSOR_STATE::EXITGAME: ExitGame(); break;
	}

	using namespace aqua::controller;
	
	int input = 0;
	input = (GetAnalogStickLeft(m_EnabledDevice).y >= 0.7f) - (GetAnalogStickLeft(m_EnabledDevice).y <= -0.7f);
	{
		if(input == 0)
			m_ContinuousInput = false;
		if (input < 0)
		{
			input = -1;
			if (m_ContinuousInput) return;
			m_State = (CURSOR_STATE)((int)m_State - 1);
			if ((int)m_State < 0)
				m_State = CURSOR_STATE::EXITGAME;
			m_ContinuousInput = true;
		}
		if (input > 0)
		{
			input = 1;
			if (m_ContinuousInput) return;
			m_State = (CURSOR_STATE)((int)m_State + 1);
			if ((int)m_State > 1)
				m_State = CURSOR_STATE::CONTINUE;
			m_ContinuousInput = true;
		}
	}
}

void CContinue::Draw(void)
{
	m_Sprite.Draw();
	m_ContinueMessage.Draw();
	m_ExitGameMessage.Draw();
}

void CContinue::Finalize(void)
{
	m_Sprite.Delete();
	m_ContinueMessage.Delete();
	m_ExitGameMessage.Delete();
}

void CContinue::Continue(void)
{
	m_Sprite.position.y = m_ContinueMessage.position.y;

	using namespace aqua::controller;
	bool trigger = Trigger(m_EnabledDevice, BUTTON_ID::A);
	if(trigger || aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RETURN))
	{
		m_SoundManager->Stop(SOUND_ID::RESULT_BGM);
		m_SM->Pop();
		m_SM->Reset();
	}
}

void CContinue::ExitGame(void)
{
	m_Sprite.position.y = m_ExitGameMessage.position.y;
	
	using namespace aqua::controller;
	bool trigger = Trigger(m_EnabledDevice, BUTTON_ID::A);
	if (trigger)
	{
		m_SoundManager->Stop(SOUND_ID::RESULT_BGM);
		m_SM->Pop();
		m_SM->Change(SCENE_ID::TITLE);
	}
}

void CContinue::SetUIPosition(void)
{
	switch (m_EnabledDevice)
	{
	using namespace aqua::controller;
	case DEVICE_ID::P1: 
		m_Sprite.position = m_top_cursor_pos_p1;
		m_ContinueMessage.position = m_top_message_pos_p1;
		m_ExitGameMessage.position = m_ContinueMessage.position + aqua::CVector2(0.0f, (float)m_ExitGameMessage.GetFontHeight());
	break;
	case DEVICE_ID::P2:
		m_Sprite.position = m_top_cursor_pos_p2;
		m_ContinueMessage.position = m_top_message_pos_p2;
		m_ExitGameMessage.position = m_ContinueMessage.position + aqua::CVector2(0.0f, (float)m_ExitGameMessage.GetFontHeight());
	break;
	}
}
