#include "green.h"

/*
 *  �R���X�g���N�^
 */
CGreen::CGreen(aqua::IGameObject* parent)
	: IPlayer(parent, "Green")
{
}

/*
 *  ������
 */
void CGreen::Initialize(void)
{
	m_AnmSprite.Create("data/animation/green.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  �X�V
 */
void CGreen::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  �`��
 */
void CGreen::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  ���
 */
void CGreen::Finalize(void)
{
	m_AnmSprite.Delete();
}
