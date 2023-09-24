#include "title_logo.h"

const aqua::CVector2 CTitleLogo::m_default_sprite_position	= aqua::CVector2(550, 50);	//! ���S�̏����ʒu
const aqua::CVector2 CTitleLogo::m_default_message_position = aqua::CVector2(610, 850); //! ���b�Z�[�W�̏����ʒu

/*
 *  �R���X�g���N�^
 */
CTitleLogo::CTitleLogo(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "TitleLogo")
{
}

/*
 *  ������
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
 *  �X�V
 */
void CTitleLogo::Update(void)
{
}

/*
 *  �`��
 */
void CTitleLogo::Draw(void)
{
	//m_Plane.Draw();
	m_Sprite.Draw();
	m_StartMessage.Draw();
}

/*
 *  ���
 */
void CTitleLogo::Finalize(void)
{
	m_Sprite.Delete();
	m_StartMessage.Delete();
}
