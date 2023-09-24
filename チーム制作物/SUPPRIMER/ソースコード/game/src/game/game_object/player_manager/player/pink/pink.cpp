#include "pink.h"

/*
 *  �R���X�g���N�^
 */
CPink::CPink(aqua::IGameObject* parent)
	: IPlayer(parent, "Pink")
{
}

/*
 *  ������
 */
void CPink::Initialize(void)
{
	m_AnmSprite.Create("data/animation/pink.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  �X�V
 */
void CPink::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  �`��
 */
void CPink::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  ���
 */
void CPink::Finalize(void)
{
	m_AnmSprite.Delete();
}
