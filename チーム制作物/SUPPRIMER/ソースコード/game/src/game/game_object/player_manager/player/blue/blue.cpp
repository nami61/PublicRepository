#include "blue.h"

/*
 *  コンストラクタ
 */
CBlue::CBlue(aqua::IGameObject* parent)
	: IPlayer(parent, "Blue")
{
}

/*
 *  初期化
 */
void CBlue::Initialize(void)
{
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
	m_AnmSprite.Create("data/animation/blue.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  更新
 */
void CBlue::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  描画
 */
void CBlue::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  解放
 */
void CBlue::Finalize(void)
{
	m_AnmSprite.Delete();
}
