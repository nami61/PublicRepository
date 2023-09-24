#include "select_button.h"

/*
 *  コンストラクタ
 */
CSelectButton::CSelectButton(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "SelectButton")
	, m_ClickFlag(false)
{
}

/*
 *  更新
 */
void CSelectButton::Update(void)
{
#if 0
	m_ClickFlag = false;
	CheckHitMouse();	// ボタンに触れているか
	if (m_HitMouseFlag)
	{
		using namespace aqua::mouse;
		m_Sprite.color = 0xffff00ff;
		if(Trigger(BUTTON_ID::LEFT))
			m_ClickMouseFlag = true;	// マウスの入力状態を保持
		if (m_ClickMouseFlag)
		{
			if (Button(BUTTON_ID::LEFT))
				m_Sprite.color = 0xff800080;

			if (Released(BUTTON_ID::LEFT))
			{
				m_ClickFlag = true;
			}
		}
	}
	else
	{
		m_Sprite.color = 0xffffffff;
		m_ClickMouseFlag = false;
	}
	m_ClickFlag = false;
	{
		using namespace aqua::controller;
		if (Trigger(BUTTON_ID::LEFT))
			m_ClickMouseFlag = true;	// マウスの入力状態を保持
		if (m_ClickMouseFlag)
		{
			if (Button(BUTTON_ID::LEFT))
				m_Sprite.color = 0xff800080;

			if (Released(BUTTON_ID::LEFT))
			{
				m_ClickFlag = true;
			}
		}
	}
	else
	{
		m_Sprite.color = 0xffffffff;
		m_ClickMouseFlag = false;
	}
#endif

}

/*
 *  描画
 */
void CSelectButton::Draw(void)
{
	m_Sprite.Draw();
}

/*
 *  生成
 */
void CSelectButton::Create(aqua::CVector2 position, bool reverse_direction)
{
	m_Position = position;

	Initialize();

	if (!reverse_direction) return;
	// 画像反転処理
	m_Sprite.anchor = aqua::CVector2(m_Sprite.GetTextureWidth() / 2.0f, m_Sprite.GetTextureHeight() / 2.0f);
	m_Sprite.scale.x = -1.0f;
}

void CSelectButton::Create(aqua::CVector2 position, bool reverse_direction, aqua::controller::DEVICE_ID device)
{
	m_Position = position;
	m_DeviceId = device;

	Initialize();

	if (!reverse_direction) return;
	// 画像反転処理
	m_Sprite.anchor = aqua::CVector2(m_Sprite.GetTextureWidth() / 2.0f, m_Sprite.GetTextureHeight() / 2.0f);
	m_Sprite.scale.x = -1.0f;
}

/*
 *  削除
 */
void CSelectButton::Delete(void)
{
	Finalize();
}

/*
 *  初期化
 */
void CSelectButton::Initialize(void)
{
	m_Sprite.Create("data/select_button.png");
	m_Sprite.position = m_Position;
	//m_HitMouseFlag = false;
}

/*
 *  解放
 */
void CSelectButton::Finalize(void)
{
	m_Sprite.Delete();

	IGameObject::Finalize();
}

/*
 *  マウスカーソルとの当たり判定
 */
//void CSelectButton::CheckHitMouse(void)
//{
//	aqua::CVector2 mpos;
//
//	mpos.x = (float)aqua::mouse::GetCursorPos().x;
//	mpos.y = (float)aqua::mouse::GetCursorPos().y;
//
//	float a = (mpos.x - (m_Position.x + m_Sprite.GetTextureWidth() / 2.0f));
//	float b = (mpos.y - (m_Position.y + m_Sprite.GetTextureHeight() / 2.0f));
//	float c = std::sqrt(a * a + b * b);
//	float d = m_Sprite.GetTextureWidth() / 2.0f;
//	if (c <= d)
//		m_HitMouseFlag = true;
//	else
//		m_HitMouseFlag = false;
//}
