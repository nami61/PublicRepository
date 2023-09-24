#include "green.h"

/*
 *  コンストラクタ
 */
CGreen::CGreen(aqua::IGameObject* parent)
	: IPlayer(parent, "Green")
{
}

/*
 *  初期化
 */
void CGreen::Initialize(void)
{
	m_AnmSprite.Create("data/animation/green.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  更新
 */
void CGreen::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  描画
 */
void CGreen::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  解放
 */
void CGreen::Finalize(void)
{
	m_AnmSprite.Delete();
}
