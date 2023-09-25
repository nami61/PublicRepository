#include "game_main_scene.h"
#include "game/game_object/block_manager/block_manager.h"
#include "game/game_object/sound_manager/sound_manager.h"
#include "game/game_object/effect_manager/effect_manager.h"
#include "game/game_object/device_common_data/device_common_data.h"
#include "game/game_object/player_manager/player_manager.h"
#include "game/game_object/round_manager/round_manager.h"
#include "game/game_object/ui_component/cursor/cursor.h"
#include "game/game_object/ui_component/health_bar/health_bar.h"
#include "game/game_object/ui_component/skill_ui/skill_ui.h"
#include "game/game_object/ui_component/countdown_timer/countdown_timer.h"
#include "game/game_object/ui_component/background/background.h"

const aqua::CVector2 CGameMainScene::m_default_p1_total_pos = aqua::CVector2(50.0f, 0.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_total_pos = aqua::CVector2(1720.0f, 0.0f);
const aqua::CVector2 CGameMainScene::m_default_p1_max_pos = aqua::CVector2(50.0f, 50.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_max_pos = aqua::CVector2(1720.0f, 50.0f);
const aqua::CVector2 CGameMainScene::m_default_p1_color_pos = aqua::CVector2(50.0f, 100.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_color_pos = aqua::CVector2(1720.0f, 100.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_total_label_pos = aqua::CVector2(1600.0f,0.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_max_label_pos = aqua::CVector2(1600.0f, 50.0f);
const aqua::CVector2 CGameMainScene::m_default_p2_color_label_pos = aqua::CVector2(1600.0f, 100.0f);
const float CGameMainScene::m_label_space = 100.0f;

// コンストラクタ
CGameMainScene::CGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
{
}

// 初期化
void CGameMainScene::Initialize(void)
{
	m_Data = (CDeviceCommonData*)aqua::FindGameObject("DeviceCommonData");
	m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_P1BG = aqua::CreateGameObject<CBackground>(this);
	m_P2BG = aqua::CreateGameObject<CBackground>(this);
	CPlayerManager* pm = aqua::CreateGameObject<CPlayerManager>(this);
	m_BlockManager = aqua::CreateGameObject<CBlockManager>(this);
	m_P1 = pm->Create(m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1), aqua::controller::DEVICE_ID::P1);
	m_P2 = pm->Create(m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2), aqua::controller::DEVICE_ID::P2);
	m_Data->SetMaxLife(aqua::controller::DEVICE_ID::P1, m_P1->GetMaxLife());
	m_Data->SetMaxLife(aqua::controller::DEVICE_ID::P2, m_P2->GetMaxLife());
	m_RoundManager = aqua::CreateGameObject<CRoundManager>(this);
	m_P1HealthUI = aqua::CreateGameObject<CHealthBar>(this);
	m_P2HealthUI = aqua::CreateGameObject<CHealthBar>(this);
	m_P1SkillUI = aqua::CreateGameObject<CSkillUI>(this);
	m_P2SkillUI = aqua::CreateGameObject<CSkillUI>(this);
	m_CursorP1 = aqua::CreateGameObject<CCursor>(this);
	m_CursorP2 = aqua::CreateGameObject<CCursor>(this);
	m_CountdawnTimer = aqua::CreateGameObject<CCountdawnTimer>(this);
	m_P1BG->Initialize(aqua::controller::DEVICE_ID::P1, m_P1->GetPlayerID());
	m_P2BG->Initialize(aqua::controller::DEVICE_ID::P2, m_P2->GetPlayerID());
	m_P1HealthUI->Initialize(m_P1, aqua::controller::DEVICE_ID::P1, aqua::CVector2(405.0f, 800.0f));
	m_P2HealthUI->Initialize(m_P2, aqua::controller::DEVICE_ID::P2, aqua::CVector2(1500.0f, 800.0f));
	m_P1SkillUI->Initialize(m_P1, m_P2, aqua::CVector2(400.0f, 860.0f));
	m_P2SkillUI->Initialize(m_P2, m_P1, aqua::CVector2(1100.0f, 860.0f));
	IGameObject::Initialize();
	m_CountdawnTimer->SetLimit(m_RoundManager->GetLimitTime());
	m_Frame1.Create("data/frame.png");
	m_Frame1.position = aqua::CVector2(300.0f, 221.0f);
	m_Frame1.color = 0x50ffffff;
	m_Frame2.Create("data/frame.png");
	m_Frame2.position = aqua::CVector2(1100.0f, 221.0f);
	m_Frame2.color = 0x50ffffff;
	m_P1TotalSprite.Create("data/total_text.png");		m_P2TotalSprite.Create("data/total_text.png");
	m_P1MaxSprite.Create("data/max_text.png");			m_P2MaxSprite.Create("data/max_text.png");
	m_P1ColorBonusSprite.Create("data/color_text.png"); m_P2ColorBonusSprite.Create("data/color_text.png");
	m_P1TotalLabel.Create(48);		m_P2TotalLabel.Create(48);
	m_P1MaxLabel.Create(48);		m_P2MaxLabel.Create(48);
	m_P1ColorBonusLabel.Create(48); m_P2ColorBonusLabel.Create(48);
	m_P1TotalLabel.text = "0";		m_P2TotalLabel.text = "0";
	m_P1MaxLabel.text = "0";		m_P2MaxLabel.text = "0";
	m_P1ColorBonusLabel.text = "0"; m_P2ColorBonusLabel.text = "0";
	m_P1TotalSprite.position = m_default_p1_total_pos; m_P2TotalSprite.position = m_default_p2_total_pos;
	m_P1MaxSprite.position = m_default_p1_max_pos; m_P2MaxSprite.position = m_default_p2_max_pos;
	m_P1ColorBonusSprite.position = m_default_p1_color_pos; m_P2ColorBonusSprite.position = m_default_p2_color_pos;
	m_P1TotalLabel.position = aqua::CVector2(m_default_p1_total_pos.x + ((float)m_P1TotalSprite.GetTextureWidth() * 0.5f) + m_label_space, m_default_p1_total_pos.y + 10.0f);
	m_P2TotalLabel.position = m_default_p2_total_label_pos;
	m_P1MaxLabel.position = aqua::CVector2(m_default_p1_max_pos.x + ((float)m_P1MaxSprite.GetTextureWidth() * 0.5f) + m_label_space, m_default_p1_max_pos.y + 10.0f);
	m_P2MaxLabel.position = m_default_p2_max_label_pos;
	m_P1ColorBonusLabel.position = aqua::CVector2(m_default_p1_color_pos.x + ((float)m_P1ColorBonusSprite.GetTextureWidth() * 0.5f) + m_label_space, m_default_p1_color_pos.y + 10.0f);
	m_P2ColorBonusLabel.position = m_default_p2_color_label_pos;
	aqua::CVector2 scale = aqua::CVector2(0.5f, 0.5f);
	m_P1TotalSprite.scale = scale; m_P2TotalSprite.scale = scale;
	m_P1MaxSprite.scale = scale; m_P2MaxSprite.scale = scale;
	m_P1ColorBonusSprite.scale = scale; m_P2ColorBonusSprite.scale = scale;
	m_BlockManager->Initialize(m_CursorP1, m_CursorP2);
	m_CursorP1->Initialize(aqua::controller::DEVICE_ID::P1);
	m_CursorP2->Initialize(aqua::controller::DEVICE_ID::P2);
	m_CursorP1->SetCursor(aqua::CVector2(313.0f, 235.0f));
	m_CursorP2->SetCursor(aqua::CVector2(1113.0f, 235.0f));
	m_ControllerPanel.Create("data/main_context.png");
	m_ControllerPanel.position = aqua::CVector2(500.0f, 900.0f);

	if (m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::WHITE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::GREEN ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::GREEN &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::WHITE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::GREEN &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::GREEN)
	{
		m_SoundManager->Play(SOUND_ID::GAMEMAIN_BGM1);
	}

	if (m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::PINK &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::GREEN ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::GREEN &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::PINK ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::PINK &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::PINK)
	{
		m_SoundManager->Play(SOUND_ID::GAMEMAIN_BGM2);
	}

	if (m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::PINK &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::WHITE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::WHITE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::PINK ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::PINK &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::BLUE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::BLUE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::PINK)
	{
		m_SoundManager->Play(SOUND_ID::GAMEMAIN_BGM3);
	}

	if (m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::BLUE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::GREEN ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::GREEN &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::BLUE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::BLUE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::BLUE)
	{
		m_SoundManager->Play(SOUND_ID::GAMEMAIN_BGM4);
	}

	if (m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::BLUE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::WHITE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::WHITE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::BLUE ||
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1) == PLAYER_ID::WHITE &&
		m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2) == PLAYER_ID::WHITE)
	{
		m_SoundManager->Play(SOUND_ID::GAMEMAIN_BGM5);
	}
}

// 更新
void CGameMainScene::Update(void)
{
	if (m_P1->IsDead())
	{
		m_Data->SetWinner(aqua::controller::DEVICE_ID::P2, m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2));
		Push(SCENE_ID::RESULT);
	}

	if (m_P2->IsDead())
	{
		m_Data->SetWinner(aqua::controller::DEVICE_ID::P1, m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1));
		Push(SCENE_ID::RESULT);
	}

	m_P1TotalLabel.text = std::to_string(m_Data->GetTotalVanishedBlocks(aqua::controller::DEVICE_ID::P1));
	m_P2TotalLabel.text = std::to_string(m_Data->GetTotalVanishedBlocks(aqua::controller::DEVICE_ID::P2));
	m_P1MaxLabel.text = std::to_string(m_Data->GetMaxVanishedBlocks(aqua::controller::DEVICE_ID::P1));
	m_P2MaxLabel.text = std::to_string(m_Data->GetMaxVanishedBlocks(aqua::controller::DEVICE_ID::P2));
	m_P1ColorBonusLabel.text = std::to_string(m_Data->GetColorBonus(aqua::controller::DEVICE_ID::P1));
	m_P2ColorBonusLabel.text = std::to_string(m_Data->GetColorBonus(aqua::controller::DEVICE_ID::P2));
	if (m_RoundManager->IsFinishedRound())
	{
		if(m_P1->GetLife() < m_P2->GetLife())
			m_Data->SetWinner(aqua::controller::DEVICE_ID::P2, m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2));
		else
			m_Data->SetWinner(aqua::controller::DEVICE_ID::P1, m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1));
		m_SoundManager->Stop(SOUND_ID::GAMEMAIN_BGM1);
		m_SoundManager->Stop(SOUND_ID::GAMEMAIN_BGM2);
		m_SoundManager->Stop(SOUND_ID::GAMEMAIN_BGM3);
		m_SoundManager->Stop(SOUND_ID::GAMEMAIN_BGM4);
		m_SoundManager->Stop(SOUND_ID::GAMEMAIN_BGM5);
		m_RoundManager->ResetCount();
		m_RoundManager->ResetTimer();
		Push(SCENE_ID::RESULT);
	}

	m_CountdawnTimer->SetTime(m_RoundManager->GetLimitTime() - m_RoundManager->GetCurrentElapsedTime());
	if (m_RoundManager->IsFinishedTimer())
	{
		m_Data->SetLife(aqua::controller::DEVICE_ID::P1, m_P1->GetLife());
		m_Data->SetLife(aqua::controller::DEVICE_ID::P2, m_P2->GetLife());
		Push(SCENE_ID::ROUND_FINISH);
		m_RoundManager->AddRounds();
		m_RoundManager->ResetTimer();
	}

	m_CursorP1->CheckHitWall(313.0f, 814.0f, 235.0f, 736.0f);
	m_CursorP2->CheckHitWall(1113.0f, 1606.0f, 235.0f, 736.0f);

	m_P2->Damage(m_P1->Counter());
	m_P1->Damage(m_P2->Counter());
	m_P2->Damage(m_P1->Attack(m_BlockManager->GetVanishedBlocks(aqua::controller::DEVICE_ID::P1) + m_Data->GetVanishedBonus(aqua::controller::DEVICE_ID::P1), m_BlockManager->GetCurrentVanishedBlock(aqua::controller::DEVICE_ID::P1), m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P1)), m_P1->GetPoisonAttack());
	m_P1->Damage(m_P2->Attack(m_BlockManager->GetVanishedBlocks(aqua::controller::DEVICE_ID::P2) + m_Data->GetVanishedBonus(aqua::controller::DEVICE_ID::P2), m_BlockManager->GetCurrentVanishedBlock(aqua::controller::DEVICE_ID::P2), m_Data->GetPlayerID(aqua::controller::DEVICE_ID::P2)), m_P2->GetPoisonAttack());
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::E))
		m_EffectManager->Create(EFFECT_ID::DEBUFF, aqua::CVector2(100.0f, 100.0f));
	IGameObject::Update();
}

// 描画
void CGameMainScene::Draw(void)
{
	m_P1BG->Draw();
	m_P2BG->Draw();
	m_Frame1.Draw();
	m_Frame2.Draw();
	m_P1TotalSprite.Draw();
	m_P2TotalSprite.Draw();
	m_P1MaxSprite.Draw();
	m_P2MaxSprite.Draw();
	m_P1ColorBonusSprite.Draw();
	m_P2ColorBonusSprite.Draw();
	m_P1TotalLabel.Draw();
	m_P2TotalLabel.Draw();
	m_P1MaxLabel.Draw();
	m_P2MaxLabel.Draw();
	m_P1ColorBonusLabel.Draw();
	m_P2ColorBonusLabel.Draw();
	m_P1HealthUI->Draw();
	m_P2HealthUI->Draw();
	m_P1SkillUI->Draw();
	m_P2SkillUI->Draw();
	m_ControllerPanel.Draw();
	m_CountdawnTimer->Draw();
	m_P1->Draw();
	m_P2->Draw();
	m_BlockManager->Draw();
	m_EffectManager->Draw();
	m_CursorP1->Draw();
	m_CursorP2->Draw();
}

// 解放
void CGameMainScene::Finalize(void)
{
	m_Frame1.Delete();
	m_Frame2.Delete();
	m_P1TotalSprite.Delete();
	m_P2TotalSprite.Delete();
	m_P1MaxSprite.Delete();
	m_P2MaxSprite.Delete();
	m_P1ColorBonusSprite.Delete();
	m_P2ColorBonusSprite.Delete();
	m_P1TotalLabel.Delete();
	m_P2TotalLabel.Delete();
	m_P1MaxLabel.Delete();
	m_P2MaxLabel.Delete();
	m_P1ColorBonusLabel.Delete();
	m_P2ColorBonusLabel.Delete();
	m_ControllerPanel.Delete();
	IGameObject::Finalize();
}
