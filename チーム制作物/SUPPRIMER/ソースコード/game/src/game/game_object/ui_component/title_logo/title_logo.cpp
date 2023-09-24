#include "title_logo.h"

const aqua::CVector2 CTitleLogo::m_default_sprite_position	= aqua::CVector2(550, 50);	//! ロゴの初期位置
const aqua::CVector2 CTitleLogo::m_default_message_position = aqua::CVector2(610, 850); //! メッセージの初期位置

/*
 *  コンストラクタ
 */
CTitleLogo::CTitleLogo(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "TitleLogo")
{
}

/*
 *  初期化
 */
void CTitleLogo::Initialize(void)
{
	m_Sprite.Create("data/title.png");
	m_Sprite.position = m_default_sprite_position;
	m_Plane.Setup(m_Sprite.position, (float)m_Sprite.GetTextureWidth(), (float)m_Sprite.GetTextureHeight(), 0x80ffffff);
	m_StartMessage.Create("data/title_text.png");
	m_StartMessage.position = m_default_message_position;
}

/*
 *  更新
 */
void CTitleLogo::Update(void)
{
}

/*
 *  描画
 */
void CTitleLogo::Draw(void)
{
	//m_Plane.Draw();
	m_Sprite.Draw();
	m_StartMessage.Draw();
}

/*
 *  解放
 */
void CTitleLogo::Finalize(void)
{
	m_Sprite.Delete();
	m_StartMessage.Delete();
}
