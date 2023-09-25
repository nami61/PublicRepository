#include "white.h"

/*
 *  �R���X�g���N�^
 */
CWhite::CWhite(aqua::IGameObject* parent)
	: IPlayer(parent, "White")
{
}

/*
 *  ������
 */
void CWhite::Initialize(void)
{
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_AnmSprite.Create("data/animation/white.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  �X�V
 */
void CWhite::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  �`��
 */
void CWhite::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  ���
 */
void CWhite::Finalize(void)
{
	m_AnmSprite.Delete();
}
