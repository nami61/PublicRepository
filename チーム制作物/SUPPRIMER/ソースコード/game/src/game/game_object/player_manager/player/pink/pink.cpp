#include "pink.h"

/*
 *  コンストラクタ
 */
CPink::CPink(aqua::IGameObject* parent)
	: IPlayer(parent, "Pink")
{
}

/*
 *  初期化
 */
void CPink::Initialize(void)
{
	m_AnmSprite.Create("data/animation/pink.ass");
	m_AnmSprite.position = m_Position;
}

/*
 *  更新
 */
void CPink::Update(void)
{
	m_AnmSprite.Update();
	m_AnmSprite.position = m_Position;
}

/*
 *  描画
 */
void CPink::Draw(void)
{
	m_AnmSprite.Draw();
}

/*
 *  解放
 */
void CPink::Finalize(void)
{
	m_AnmSprite.Delete();
}
