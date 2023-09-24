#include "TitleLogo.h"
#include "../../Translate/Translate.h"

const aqua::CVector2 CTitleLogo::m_default_logo_pos = aqua::CVector2(380.0f, 150.0f);
const aqua::CVector2 CTitleLogo::m_logo_start_pos = aqua::CVector2(-550.0f, -250.0f);
const aqua::CVector2 CTitleLogo::m_default_player_pos = aqua::CVector2(830.0f, 130.0f);
const aqua::CVector2 CTitleLogo::m_default_effect_pos = aqua::CVector2(500.0f, 100.0f);

CTitleLogo::CTitleLogo(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "TitleLogo")
{
}

void CTitleLogo::Initialize(void)
{
	m_BackPlane.Setup(aqua::CVector2(0.0f, 100.0f), (float)aqua::GetWindowWidth(), 400.0f, 0x80000000);
	m_TitleLogo.Create("data/texture/title_logo.png");
	m_TitleLogo.position = m_logo_start_pos;
	m_TitleLogoShadow.Create("data/texture/title_logo_shadow.png");
	m_TitleLogoShadow.position = m_default_logo_pos;
	m_Player.Create("data/texture/title_logo_player.png");
	m_Player.position = m_default_player_pos;
	m_PlayerEffect.Create("data/texture/title_logo_effect.png");
	m_PlayerEffect.position = m_default_effect_pos;
	m_PlayerEffect.rect.right = 0;
	m_ClickMessage.Create(50, 2);
	m_ClickMessage.text = "Click Start";
	m_ClickMessage.position = aqua::CVector2(450.0f, 500.0f);
	m_ClickMessage.color = 0xffffffff;
	m_ClickMessage.edge_color = 0xffff7f50;
	m_TranslateTimer.Setup(4.0f);
	m_FadeTimer.Setup(5.0f);
	m_RectTimer.Setup(2.0f);
}

void CTitleLogo::Update(void)
{
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_TitleLogo.position.x, m_logo_start_pos.x, m_default_logo_pos.x, m_TranslateTimer, false, DIRECTION_MODE::OUT_QUART);
	translate->Translate(m_TitleLogo.position.y, m_logo_start_pos.y, m_default_logo_pos.y, m_TranslateTimer, false, DIRECTION_MODE::OUT_BOUNCE);
	if (translate->Finished())
	{
		translate = aqua::CreateGameObject<CTranslate>(this);
		translate->Translate(m_PlayerEffect.rect.right, m_PlayerEffect.rect.left, m_PlayerEffect.GetTextureWidth(), m_RectTimer);
			if (translate->Finished())
		{
			translate = aqua::CreateGameObject<CTranslate>(this);
			translate->FadeDirection(m_TitleLogo.color, m_FadeTimer, 150, 255);
			translate->FadeDirection(m_ClickMessage.color, m_FadeTimer);
		}
	}
}

void CTitleLogo::Draw(void)
{
	m_BackPlane.Draw();
	m_PlayerEffect.Draw();
	m_Player.Draw();
	m_TitleLogoShadow.Draw();
	m_TitleLogo.Draw();
	m_ClickMessage.Draw();
	IGameObject::Draw();
}

void CTitleLogo::Finalize(void)
{
	m_TitleLogo.Delete();
	m_TitleLogoShadow.Delete();
	m_Player.Delete();
	m_PlayerEffect.Delete();
	m_ClickMessage.Delete();
	IGameObject::Finalize();
}
