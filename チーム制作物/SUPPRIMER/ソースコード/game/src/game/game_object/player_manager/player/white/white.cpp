#include "white.h"

/*
 *  コンストラクタ
 */
CWhite::CWhite(aqua::IGameObject* parent)
	: IPlayer(parent, "White")
{
}

/*
 *  初期化
 */
void CWhite::Initialize(void)
{
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_AnmSprite.Create("data/animation/white.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  更新
 */
void CWhite::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  描画
 */
void CWhite::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  解放
 */
void CWhite::Finalize(void)
{
	m_AnmSprite.Delete();
}
