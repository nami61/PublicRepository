#include "blue.h"

/*
 *  �R���X�g���N�^
 */
CBlue::CBlue(aqua::IGameObject* parent)
	: IPlayer(parent, "Blue")
{
}

/*
 *  ������
 */
void CBlue::Initialize(void)
{
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_AnmSprite.Create("data/animation/blue.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  �X�V
 */
void CBlue::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  �`��
 */
void CBlue::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  ���
 */
void CBlue::Finalize(void)
{
	m_AnmSprite.Delete();
}
