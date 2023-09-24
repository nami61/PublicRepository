#include "result_scene.h"
#include "../../../../game_object/ui_component/continue/continue.h"
#include "../../../../game_object/player_manager/player_manager.h"
#include "../../../../game_object/device_common_data/device_common_data.h"
#include "../../../../game_object/ui_component/player_prev/player_prev.h"

const aqua::CVector2 CResultScene::m_default_P1_pos = aqua::CVector2(300.0f, 300.0f);
const aqua::CVector2 CResultScene::m_default_P2_pos = aqua::CVector2(1400.0f, 300.0f);

CResultScene::CResultScene(aqua::IGameObject* parent)
	: IScene(parent, "ResultScene")
{
}

void CResultScene::Initialize(void)
{
	m_Data = (CDeviceCommonData*)aqua::FindGameObject("DeviceCommonData");
	m_WinnerPrev = aqua::CreateGameObject<CPlayerPrev>(this);
	aqua::CreateGameObject<CContinue>(this)->Setup(m_Data->GetWinnerDevice());
	if (m_Data->GetWinnerDevice() == aqua::controller::DEVICE_ID::P1)
	{
		m_WinnerPrev->Initialize(m_default_P1_pos);
		m_LineSprite.Create("data/line_P1win.png");
	}
	else if (m_Data->GetWinnerDevice() == aqua::controller::DEVICE_ID::P2)
	{
		m_WinnerPrev->Initialize(m_default_P2_pos);
		m_LineSprite.Create("data/line_P2win.png");
	}
	IGameObject::Initialize();
	m_WinnerLabel.Create(128, 0, true, aqua::FONT_FAMILY_ID::MS_GOTHIC);
	m_WinnerLabel.text = std::to_string((int)m_Data->GetWinnerDevice() + 1) + "P WIN!!";
	m_BackGround.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), 0x80000000);
}

void CResultScene::Update(void)
{
	IGameObject::Update();
}

void CResultScene::Draw(void)
{
	m_BackGround.Draw();
	m_LineSprite.Draw();
	m_WinnerLabel.Draw();
	m_WinnerPrev->Draw(m_Data->GetWinner(), m_Data->GetWinnerDevice());
	IGameObject::Draw();
}

void CResultScene::Finalize(void)
{
	m_LineSprite.Delete();
	m_WinnerLabel.Delete();
	IGameObject::Finalize();
}
