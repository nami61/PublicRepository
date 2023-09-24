#include "ribbon_direction.h"
#include "../../translate/translate.h"
#include "../../round_manager/round_manager.h"

const aqua::CVector2 CRibbonDirection::m_default_ribbon_position = aqua::CVector2(0.0f, 600.0f);
const aqua::CVector2 CRibbonDirection::m_default_label_position = aqua::CVector2(790.0f, 550.0f);
const aqua::CVector2 CRibbonDirection::m_move_label_pos = aqua::CVector2(810.0f, 600.0f);
const aqua::CVector2 CRibbonDirection::m_start_position = aqua::CVector2(1980.0f, 600.0f);

CRibbonDirection::CRibbonDirection(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "RibbonDirection")
{
}

void CRibbonDirection::Initialize(void)
{
	m_RoundManager = (CRoundManager*)aqua::FindGameObject("RoundManager");
	m_RibbonFirst.Create("data/ribbon2.png");
	m_RibbonSecond.Create("data/ribbon2.png");
	m_RoundSprite.Create("data/round1.png");
	m_RoundSprite.position.y = m_default_label_position.y;
	m_RoundSprite.scale = aqua::CVector2(0.5f, 0.5f);
	m_CurrentRoundLabel.Create(64, 4, true, aqua::FONT_FAMILY_ID::HG_SOUEIKAKUPOP);
	m_CurrentRoundLabel.color = 0xffff00ff;
	m_CurrentRoundLabel.edge_color = 0xff00ffff;
	m_RibbonFirst.position.y = m_default_ribbon_position.y;
	m_RibbonSecond.position.y = m_default_ribbon_position.y;
	m_CurrentRoundLabel.position.y = m_default_label_position.y;
	m_RibbonInScreen.Setup(1.0f);
	m_RibbonDeray.Setup(1.0f);
	m_RibbonOutScreen.Setup(3.0f);

	m_State = STATE::SCREEN_IN;
}

void CRibbonDirection::Update(void)
{
	RibbonUpdate();
	IGameObject::Update();
}

void CRibbonDirection::Draw(void)
{
	m_RibbonFirst.Draw();
	m_RibbonSecond.Draw();
	m_RoundSprite.Draw();
	//m_CurrentRoundLabel.Draw();
}

void CRibbonDirection::Finalize(void)
{
	m_RibbonFirst.Delete(); 
	m_RibbonSecond.Delete();
	m_RoundSprite.Delete();
	m_CurrentRoundLabel.Delete();
	IGameObject::Finalize();
}

void CRibbonDirection::RibbonUpdate(void)
{
	switch (m_State)
	{
	case STATE::SCREEN_IN: ScreenIn(); break;
	case STATE::DERAY: Deray(); break;
	case STATE::SCREEN_OUT: ScreenOut(); break;
	}
}

void CRibbonDirection::ScreenIn(void)
{
	if (m_RibbonInScreen.Finished())
		m_State = STATE::DERAY;
	m_CurrentRoundLabel.text = "ROUND  " + std::to_string(m_RoundManager->GetCurrentRounds());
	m_RibbonInScreen.Update();
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RibbonFirst.position.x, m_start_position.x, m_default_ribbon_position.x, m_RibbonInScreen, false, EASING::IN_EXP);
	translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RibbonSecond.position.x, m_start_position.x, m_default_ribbon_position.x, m_RibbonInScreen, false, EASING::IN_EXP);
	//translate = aqua::CreateGameObject<CTranslate>(this);
	//translate->Translate(m_CurrentRoundLabel.position.x, m_start_position.x, m_default_label_position.x, m_RibbonInScreen, false, EASING::IN_EXP);
	translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RoundSprite.position.x, m_start_position.x, m_default_label_position.x, m_RibbonInScreen, false, EASING::IN_EXP);

}

void CRibbonDirection::Deray(void)
{
	if (m_RibbonDeray.Finished())
		m_State = STATE::SCREEN_OUT;
	m_RibbonDeray.Update();
	//m_CurrentRoundLabel.position.x += 1.0f;
	m_RoundSprite.position.x += 1.0f;
	//CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	//translate->Translate(m_CurrentRoundLabel.position.x, m_default_ribbon_position.x, m_move_label_pos.x, m_RibbonDeray, false, EASING::IN_EXP);
}

void CRibbonDirection::ScreenOut(void)
{
	if (m_RibbonOutScreen.Finished())
		DeleteObject();
	m_RibbonOutScreen.Update();
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RibbonFirst.position.x, m_default_ribbon_position.x, (float)m_RibbonFirst.GetTextureWidth() + (float)aqua::GetWindowWidth(), m_RibbonOutScreen, false, EASING::OUT_EXP);
	translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RibbonSecond.position.x, m_default_ribbon_position.x, (float)m_RibbonSecond.GetTextureWidth() + (float)aqua::GetWindowWidth(), m_RibbonOutScreen, false, EASING::OUT_EXP);
	//translate = aqua::CreateGameObject<CTranslate>(this);
	//translate->Translate(m_CurrentRoundLabel.position.x, m_move_label_pos.x, (float)m_CurrentRoundLabel.GetTextWidth() + (float)aqua::GetWindowWidth(), m_RibbonOutScreen, false, EASING::OUT_EXP);
	translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_RoundSprite.position.x, m_move_label_pos.x, (float)m_RoundSprite.GetTextureWidth() + (float)aqua::GetWindowWidth(), m_RibbonOutScreen, false, EASING::OUT_EXP);
}
