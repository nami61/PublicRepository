#include "round_finish.h"
#include "../../../../game_object/device_common_data/device_common_data.h"
#include "../../../../game_object/player_manager/player_manager.h"
#include "../../../../game_object/round_manager/round_manager.h"
#include "../../../../game_object/translate/translate.h"
#include "../../../../game_object/ui_component/ribbon_direction/ribbon_direction.h"
#include "../../../../game_object/ui_component/health_bar/health_bar.h"
#include "../../../../game_object/block_manager/block_manager.h"

const aqua::CVector2 CRoundFinishScene::m_default_p1_pos = aqua::CVector2(150.0f, 550.0f);
const aqua::CVector2 CRoundFinishScene::m_default_p2_pos = aqua::CVector2(1450.0f, 550.0f);
const aqua::CVector2 CRoundFinishScene::m_p1_health_pos = aqua::CVector2(405.0f, 800.0f);
const aqua::CVector2 CRoundFinishScene::m_p2_health_pos = aqua::CVector2(1500.0f, 800.0f);
const aqua::CVector2 CRoundFinishScene::m_p1_max_sprite_pos = aqua::CVector2(130.0f, 300.0f);
const aqua::CVector2 CRoundFinishScene::m_p2_max_sprite_pos = aqua::CVector2(1450.0f, 300.0f);
const aqua::CVector2 CRoundFinishScene::m_p1_color_bonus_sprite_pos = aqua::CVector2(130.0f, 400.0f);
const aqua::CVector2 CRoundFinishScene::m_p2_color_bonus_sprite_pos = aqua::CVector2(1400.0f, 400.0f);
const aqua::CVector2 CRoundFinishScene::m_p1_max_value_pos = aqua::CVector2(430.0f, 300.0f);
const aqua::CVector2 CRoundFinishScene::m_p2_max_value_pos = aqua::CVector2(1100.0f,300.0f);
const aqua::CVector2 CRoundFinishScene::m_p1_color_value_pos = aqua::CVector2(430.0f, 400.0f);
const aqua::CVector2 CRoundFinishScene::m_p2_color_value_pos = aqua::CVector2(1100.0f, 400.0f);
const float CRoundFinishScene::m_deray_interval = 0.2f;

CRoundFinishScene::CRoundFinishScene(aqua::IGameObject* parent)
	: IScene(parent, "RoundFinish")
{
}

void CRoundFinishScene::Initialize(void)
{
	m_CommonData = (CDeviceCommonData*)aqua::FindGameObject("DeviceCommonData");
	m_BlockManager = (CBlockManager*)aqua::FindGameObject("BlockManager");
	m_RoundManager = (CRoundManager*)aqua::FindGameObject("RoundManager");
	m_PlayerManager = aqua::CreateGameObject<CPlayerManager>(this);
	m_P1 = m_PlayerManager->Create(m_CommonData->GetPlayerID(aqua::controller::DEVICE_ID::P1), aqua::controller::DEVICE_ID::P1);
	m_P2 = m_PlayerManager->Create(m_CommonData->GetPlayerID(aqua::controller::DEVICE_ID::P2), aqua::controller::DEVICE_ID::P2);
	m_P1HealthUI = aqua::CreateGameObject<CHealthBar>(this);
	m_P1HealthUI->Initialize(m_CommonData->GetLife(aqua::controller::DEVICE_ID::P1), m_CommonData->GetMaxLife(aqua::controller::DEVICE_ID::P1), aqua::controller::DEVICE_ID::P1, m_p1_health_pos);
	m_P2HealthUI = aqua::CreateGameObject<CHealthBar>(this);
	m_P2HealthUI->Initialize(m_CommonData->GetLife(aqua::controller::DEVICE_ID::P2), m_CommonData->GetMaxLife(aqua::controller::DEVICE_ID::P2), aqua::controller::DEVICE_ID::P2, m_p2_health_pos);
	IGameObject::Initialize();
	m_P1->SetPosition(m_default_p1_pos);
	m_P2->SetPosition(m_default_p2_pos);
	StateLabel.Create(64);
	Message.Create(64);
	Message.position.y = 64.0f;
	Message.text = "Push Q Key";
	m_State = STATE::APPEAR;
	m_Plane.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), 0x80000000);
	for (int i = 0; i < m_RoundManager->GetMaxRounds(); ++i)
	{
		aqua::CSprite sprite;
		std::string line;
		line = "data/round" + std::to_string(i + 1) + "_sub.png";
		sprite.Create(line);
		sprite.position = aqua::CVector2::ZERO;
		m_RoundSprites.push_back(sprite);
	}
	m_P1MaxSprite.Create("data/max_text.png");
	m_P1ColorBonusSprite.Create("data/color_text.png");
	m_P2MaxSprite.Create("data/max_text.png");
	m_P2ColorBonusSprite.Create("data/color_text.png");
	m_P1MaxLabel.Create(96, 0, true, aqua::FONT_FAMILY_ID::CASCADIA_CODE);
	m_P2MaxLabel.Create(96, 0, true, aqua::FONT_FAMILY_ID::CASCADIA_CODE);
	m_P1ColorBonusLabel.Create(96,0,true,aqua::FONT_FAMILY_ID::CASCADIA_CODE);
	m_P2ColorBonusLabel.Create(96,0,true,aqua::FONT_FAMILY_ID::CASCADIA_CODE);
	m_P1MaxLabel.text = std::to_string(m_CommonData->GetMaxVanishedBlocks(aqua::controller::DEVICE_ID::P1)) + "Å~1.1";
	m_P2MaxLabel.text = std::to_string(m_CommonData->GetMaxVanishedBlocks(aqua::controller::DEVICE_ID::P2)) + "Å~1.1";
	m_P1ColorBonusLabel.text = std::to_string(m_CommonData->GetColorBonus(aqua::controller::DEVICE_ID::P1)) + "Å~1.2";
	m_P2ColorBonusLabel.text = std::to_string(m_CommonData->GetColorBonus(aqua::controller::DEVICE_ID::P2)) + "Å~1.2";
	m_P1MaxSprite.position = aqua::CVector2(0.0f, m_p1_max_sprite_pos.y);
	m_P1ColorBonusSprite.position = aqua::CVector2(0.0f, m_p1_color_bonus_sprite_pos.y);
	m_P2MaxSprite.position = aqua::CVector2((float)aqua::GetWindowWidth() - (float)m_P2MaxSprite.GetTextureWidth(), m_p2_max_sprite_pos.y);
	m_P2ColorBonusSprite.position = aqua::CVector2((float)aqua::GetWindowWidth() - (float)m_P2ColorBonusSprite.GetTextureWidth(), m_p2_color_bonus_sprite_pos.y);
	m_P1MaxLabel.position.y = m_p1_max_value_pos.y;
	m_P2MaxLabel.position.y = m_p2_max_value_pos.y;
	m_P1ColorBonusLabel.position.y = m_p1_color_value_pos.y;
	m_P2ColorBonusLabel.position.y = m_p2_color_value_pos.y;
	m_FadeInTimer.Setup(8.0f);
	m_FadeInTimerSecond.Setup(8.0f);
	m_FadeOutTimer.Setup(5.0f);
	m_Deray.Setup(m_deray_interval);
	m_DerayCount = 0;
}

void CRoundFinishScene::Update(void)
{
	switch (m_State)
	{
	case CRoundFinishScene::STATE::APPEAR: Appear(); break;
	case CRoundFinishScene::STATE::ATTACK: Attack(); break;
	case CRoundFinishScene::STATE::EXIT: Exit(); break;
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::R))
		aqua::CreateGameObject<CRibbonDirection>(this)->Initialize();

	IGameObject::Update();
}

void CRoundFinishScene::Draw(void)
{
	m_Plane.Draw();
	m_P1->Draw();
	m_P2->Draw();
	//StateLabel.Draw();
	//Message.Draw();
	m_RoundSprites.at(m_RoundManager->GetCurrentRounds() - 1).Draw();
	m_P1MaxSprite.Draw();
	m_P1ColorBonusSprite.Draw();
	m_P2MaxSprite.Draw();
	m_P2ColorBonusSprite.Draw();
	m_P1MaxLabel.Draw();
	m_P2MaxLabel.Draw();
	m_P1ColorBonusLabel.Draw();
	m_P2ColorBonusLabel.Draw();
	m_P1HealthUI->Draw();
	m_P2HealthUI->Draw();
}

void CRoundFinishScene::Finalize(void)
{
	StateLabel.Delete();
	Message.Delete();
	m_P1->Finalize();
	m_P2->Finalize();
	m_PlayerManager->Finalize();
	m_P1MaxSprite.Delete();
	m_P1ColorBonusSprite.Delete();
	m_P2MaxSprite.Delete();
	m_P2ColorBonusSprite.Delete();
	m_P1MaxLabel.Delete();
	m_P2MaxLabel.Delete();
	m_P1ColorBonusLabel.Delete();
	m_P2ColorBonusLabel.Delete();
	IGameObject::Finalize();
}

void CRoundFinishScene::Appear(void)
{
	StateLabel.text = "STATE::Apper";
	m_Deray.Update();
	if (m_Deray.Finished() && m_DerayCount < 1)
	{
		m_Deray.Reset();
		++m_DerayCount;
	}
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_P1MaxSprite.position.x, (float)-m_P1MaxSprite.GetTextureWidth(), m_p1_max_sprite_pos.x, m_FadeInTimer);
	translate->Translate(m_P2MaxSprite.position.x, (float) m_P2MaxSprite.GetTextureWidth(), m_p2_max_sprite_pos.x, m_FadeInTimer);
	translate->Translate(m_P1MaxLabel.position.x, (float)-m_P1MaxLabel.GetTextWidth(), m_p1_max_value_pos.x, m_FadeInTimer);
	translate->Translate(m_P2MaxLabel.position.x, (float) m_P2MaxLabel.GetTextWidth(), m_p2_max_value_pos.x, m_FadeInTimer);
	if (m_DerayCount >= 1)
	{
		translate = aqua::CreateGameObject<CTranslate>(this);
		translate->Translate(m_P1ColorBonusSprite.position.x, (float)-m_P1ColorBonusSprite.GetTextureWidth(), m_p1_color_bonus_sprite_pos.x, m_FadeInTimerSecond);
		translate->Translate(m_P2ColorBonusSprite.position.x, (float) m_P2ColorBonusSprite.GetTextureWidth(), m_p2_color_bonus_sprite_pos.x, m_FadeInTimerSecond);
		translate->Translate(m_P1ColorBonusLabel.position.x, (float)-m_P1ColorBonusLabel.GetTextWidth(), m_p1_color_value_pos.x, m_FadeInTimerSecond);
		translate->Translate(m_P2ColorBonusLabel.position.x, (float) m_P2ColorBonusLabel.GetTextWidth(), m_p2_color_value_pos.x, m_FadeInTimerSecond);
	}
	
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Q) || m_FadeInTimerSecond.Finished())
		m_State = STATE::ATTACK;
}

void CRoundFinishScene::Attack(void)
{
	StateLabel.text = "STATE::Attack";
	//if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Q))
		m_State = STATE::EXIT;
}

void CRoundFinishScene::Exit(void)
{
	StateLabel.text = "STATE::Exit";

	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_P1MaxSprite.position.x, m_p1_max_sprite_pos.x, (float)-m_P1MaxSprite.GetTextureWidth(), m_FadeOutTimer);
	translate->Translate(m_P2MaxSprite.position.x, m_p2_max_sprite_pos.x, (float) aqua::GetWindowWidth(), m_FadeOutTimer);
	translate->Translate(m_P1ColorBonusSprite.position.x, m_p1_color_bonus_sprite_pos.x, (float)-m_P1ColorBonusSprite.GetTextureWidth(), m_FadeOutTimer);
	translate->Translate(m_P2ColorBonusSprite.position.x, m_p2_color_bonus_sprite_pos.x, (float) aqua::GetWindowWidth(), m_FadeOutTimer);
	translate->Translate(m_P1MaxLabel.position.x, m_p1_max_value_pos.x, (float)-m_P1MaxLabel.GetTextWidth(), m_FadeOutTimer);
	translate->Translate(m_P2MaxLabel.position.x, m_p2_max_value_pos.x, (float)aqua::GetWindowWidth(), m_FadeOutTimer);
	translate->Translate(m_P1ColorBonusLabel.position.x, m_p1_color_value_pos.x, (float)-m_P1ColorBonusLabel.GetTextWidth(), m_FadeOutTimer);
	translate->Translate(m_P2ColorBonusLabel.position.x, m_p2_color_value_pos.x, (float)aqua::GetWindowWidth(), m_FadeOutTimer);
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::Q) || m_FadeOutTimer.Finished())
	{
		Pop();
		m_BlockManager->Reset();
		m_CommonData->ResetScore();
	}
}
