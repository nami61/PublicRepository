#include "title_scene.h"
#include "../../../game_object/player_manager/player_manager.h"
#include "../../../game_object/ui_component/title_logo/title_logo.h"
#include "../../../game_object/ui_component/player_number/player_number.h"
#include "../../../game_object/ui_component/player_prev/player_prev.h"
#include "../../../game_object/ui_component/background/background.h"
#include "../../../game_object/ui_component/player_description/player_description.h"
#include "../../../game_object/device_common_data/device_common_data.h"
#include "../../../game_object/effect_manager/effect/block_direction/block_direction.h"
#include "../../../game_object/controller_stick_operation/controller_stick_operation.h"
#include "../../../game_object/translate/translate.h"
#include "../../../game_object/sound_manager/sound_manager.h"

const float CTitleScene::m_default_threshold_value = 0.7f;
const aqua::CVector2 CTitleScene::m_p1_default_pos = aqua::CVector2(150.0f, 500.0f);
const aqua::CVector2 CTitleScene::m_p2_default_pos = aqua::CVector2(1750.0f, 500.0f);
const aqua::CVector2 CTitleScene::m_p1_ready_pos = aqua::CVector2(50.0f, 530.0f);
const aqua::CVector2 CTitleScene::m_p2_ready_pos = aqua::CVector2(1550.0f, 530.0f);
const aqua::CVector2 CTitleScene::m_controller_panel_pos = aqua::CVector2(350.0f, 950.0f);

/*
 *  コンストラクタ
 */
CTitleScene::
CTitleScene(aqua::IGameObject* parent)
	: IScene(parent, "TitleScene")
{
}

/*
 *  初期化
 */
void
CTitleScene::
Initialize(void)
{
	m_BG = aqua::CreateGameObject<CBackground>(this);
	m_BG->TitleInit();
	m_BlockDirection = aqua::CreateGameObject<CBlockDirection>(this);
	m_TitleLogo = aqua::CreateGameObject<CTitleLogo>(this);
	m_PlayerNumber = aqua::CreateGameObject<CPlayerNumber>(this);
	m_PlayerManager = aqua::CreateGameObject<CPlayerManager>(this);
	IGameObject::Initialize();
	m_P1Description = aqua::CreateGameObject<CPlayerDescription>(this);
	m_P2Description = aqua::CreateGameObject<CPlayerDescription>(this);
	m_P1Prev = aqua::CreateGameObject<CPlayerPrev>(this);
	m_P2Prev = aqua::CreateGameObject<CPlayerPrev>(this);
	m_P1Description->Initialize(aqua::controller::DEVICE_ID::P1);
	m_P2Description->Initialize(aqua::controller::DEVICE_ID::P2);
	m_P1Prev->Initialize(m_p1_default_pos);
	m_P2Prev->Initialize(m_p2_default_pos);

	m_CommonData = (CDeviceCommonData*)aqua::FindGameObject("DeviceCommonData");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");

	m_CurrentIDP1 = m_CurrentIDP2 = PLAYER_ID::WHITE;
	m_ControllerPanel.Create("data/title_context.png");
	m_ControllerPanel.position = m_controller_panel_pos;
	m_P1ReadySprite.Create("data/select.png");
	m_P1ReadySprite.color = 0xffff0000;
	m_P2ReadySprite.Create("data/select.png");
	m_P2ReadySprite.color = 0xff0000ff;
	m_P1ReadySprite.position = m_p1_ready_pos;
	m_P2ReadySprite.position = m_p2_ready_pos;
	m_P1ReadyPlane.Setup(m_P1ReadySprite.position, (float)m_P1ReadySprite.GetTextureWidth(), (float)m_P1ReadySprite.GetTextureHeight(), 0xffffffff);
	m_P2ReadyPlane.Setup(m_P2ReadySprite.position, (float)m_P2ReadySprite.GetTextureWidth(), (float)m_P2ReadySprite.GetTextureHeight(), 0xffffffff);
	m_FadeTimer.Setup(8.0f);
	m_ContinuousInputP1 = false;
	m_ContinuousInputP2 = false;
	m_P1DecisionFlag = false;
	m_P2DecisionFlag = false;
	m_ChangeDemoSceneTimer.Setup(30.0f);
	m_SoundManager->Play(SOUND_ID::TITLE_BGM);
}

/*
 *  更新
 */
void
CTitleScene::
Update(void)
{
#ifdef AQUA_DEBUG
	// gamepad使えない時用
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::N))
	{
		m_CommonData->SetPlayerID(aqua::controller::DEVICE_ID::P1, m_CurrentIDP1);
		m_CommonData->SetPlayerID(aqua::controller::DEVICE_ID::P2, m_CurrentIDP2);
		m_SoundManager->Stop(SOUND_ID::TITLE_BGM);
		Change(SCENE_ID::GAMEMAIN);
	}
#endif // AQUA_DEBUG

	m_ChangeDemoSceneTimer.Update();
	if (m_ChangeDemoSceneTimer.Finished())
	{
		m_SoundManager->Stop(SOUND_ID::TITLE_BGM);
		Change(SCENE_ID::DEMO);
	}
	if (m_P1DecisionFlag && m_P2DecisionFlag)
	{
		using namespace aqua::controller;
		if (Trigger(DEVICE_ID::P1, BUTTON_ID::A) || Trigger(DEVICE_ID::P2, BUTTON_ID::A))
		{
			m_CommonData->SetPlayerID(aqua::controller::DEVICE_ID::P1, m_CurrentIDP1);
			m_CommonData->SetPlayerID(aqua::controller::DEVICE_ID::P2, m_CurrentIDP2);
			m_SoundManager->Stop(SOUND_ID::TITLE_BGM);
			Change(SCENE_ID::GAMEMAIN);
		}
	}

	if (m_P1DecisionFlag)
	{
		if (aqua::controller::Trigger(aqua::controller::DEVICE_ID::P1, aqua::controller::BUTTON_ID::B))
		{
			m_ChangeDemoSceneTimer.Reset();
			m_P1DecisionFlag = false;
		}
	}
	else
	{
		if (aqua::controller::Trigger(aqua::controller::DEVICE_ID::P1, aqua::controller::BUTTON_ID::A))
		{
			m_ChangeDemoSceneTimer.Reset();
			m_P1DecisionFlag = true;
		}
	}
	if (m_P2DecisionFlag)
	{
		if (aqua::controller::Trigger(aqua::controller::DEVICE_ID::P2, aqua::controller::BUTTON_ID::B))
		{
			m_ChangeDemoSceneTimer.Reset();
			m_P2DecisionFlag = false;
		}
	}
	else
	{
		if (aqua::controller::Trigger(aqua::controller::DEVICE_ID::P2, aqua::controller::BUTTON_ID::A))
		{
			m_ChangeDemoSceneTimer.Reset();
			m_P2DecisionFlag = true;
		}
	}

	ChangeDrawPlayer();

	m_FadeTimer.Update();
	if (m_FadeTimer.Finished())
		m_FadeTimer.Reset();
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->FadeDirection(m_P1ReadyPlane.color, m_FadeTimer, 0, 128, DIRECTION_ID::SIN);
	translate->FadeDirection(m_P2ReadyPlane.color, m_FadeTimer, 0, 128, DIRECTION_ID::SIN);

	IGameObject::Update();
}

/*
 *  描画
 */
void
CTitleScene::
Draw(void)
{
	m_BG->Draw();
	m_BlockDirection->Draw();
	m_TitleLogo->Draw();
	m_PlayerNumber->Draw();
	m_P1Prev->Draw(m_CurrentIDP1, aqua::controller::DEVICE_ID::P1);
	m_P2Prev->Draw(m_CurrentIDP2, aqua::controller::DEVICE_ID::P2);
	m_P1Description->Draw(m_CurrentIDP1);
	m_P2Description->Draw(m_CurrentIDP2);
	m_ControllerPanel.Draw();
	if (m_P1DecisionFlag)
	{
		m_P1ReadyPlane.Draw();
		m_P1ReadySprite.Draw();
	}
	if (m_P2DecisionFlag)
	{
		m_P2ReadyPlane.Draw();
		m_P2ReadySprite.Draw();
	}
}

/*
 *  解放
 */
void
CTitleScene::
Finalize(void)
{
	m_P1ReadySprite.Delete();
	m_P2ReadySprite.Delete();
	m_ControllerPanel.Delete();
	IGameObject::Finalize();
}

/*
 *  描画するプレイヤーの変更
 */
void CTitleScene::ChangeDrawPlayer(void)
{
	using namespace aqua::controller;
	CControllerStickOperation* controller = (CControllerStickOperation*)aqua::FindGameObject("ControllerStickOperation");

	if (!m_P1DecisionFlag)
	{
		if (controller->StickTriggerLeft(DEVICE_ID::P1, STICK_DIRECTION::LEFT, m_default_threshold_value))
		{
			m_CurrentIDP1 = (PLAYER_ID)((int)m_CurrentIDP1 - 1);
			if ((int)m_CurrentIDP1 < 0)
				m_CurrentIDP1 = PLAYER_ID::PINK;
			m_ChangeDemoSceneTimer.Reset();
		}

		if (controller->StickTriggerLeft(DEVICE_ID::P1, STICK_DIRECTION::RIGHT, m_default_threshold_value))
		{
			m_CurrentIDP1 = (PLAYER_ID)((int)m_CurrentIDP1 + 1);
			if ((int)m_CurrentIDP1 >= (int)PLAYER_ID::MAX)
				m_CurrentIDP1 = PLAYER_ID::WHITE;
			m_ChangeDemoSceneTimer.Reset();
		}
	}

	if (!m_P2DecisionFlag)
	{
		if (controller->StickTriggerLeft(DEVICE_ID::P2, STICK_DIRECTION::LEFT, m_default_threshold_value))
		{
			m_CurrentIDP2 = (PLAYER_ID)((int)m_CurrentIDP2 - 1);
			if ((int)m_CurrentIDP2 < 0)
				m_CurrentIDP2 = PLAYER_ID::PINK;
			m_ChangeDemoSceneTimer.Reset();
		}

		if (controller->StickTriggerLeft(DEVICE_ID::P2, STICK_DIRECTION::RIGHT, m_default_threshold_value))
		{
			m_CurrentIDP2 = (PLAYER_ID)((int)m_CurrentIDP2 + 1);
			if ((int)m_CurrentIDP2 >= (int)PLAYER_ID::MAX)
				m_CurrentIDP2 = PLAYER_ID::WHITE;
			m_ChangeDemoSceneTimer.Reset();
		}
	}
}
