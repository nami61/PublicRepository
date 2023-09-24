#include "cursor.h"
#include "../../../game_object/controller_stick_operation/controller_stick_operation.h"

const float CCursor::m_default_threshold_value = 0.7f;

CCursor::CCursor(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "Cursor")
	, m_CursorPosition(aqua::CVector2::ZERO)
	, m_Velocity(aqua::CVector2::ZERO)
	, m_HitFlag(false)
{
	m_CursorSprite.Create("data/pointer.png");
}

void CCursor::Initialize(aqua::controller::DEVICE_ID id)
{
	m_DeviceID = id;
	m_CursorSprite.color = 0xffffff00;
}

void CCursor::Update(void)
{
	CControllerStickOperation* controller = (CControllerStickOperation*)aqua::FindGameObject("ControllerStickOperation");

	if (controller->StickTriggerLeft(
		m_DeviceID, aqua::controller::STICK_DIRECTION::LEFT, m_default_threshold_value)
		)
	{
		m_CursorPosition.x -= 32.0f;
	}

	if (controller->StickTriggerLeft(
		m_DeviceID, aqua::controller::STICK_DIRECTION::RIGHT, m_default_threshold_value)
		)
	{
		m_CursorPosition.x += 32.0f;
	}

	if (controller->StickTriggerLeft(
		m_DeviceID, aqua::controller::STICK_DIRECTION::UP, m_default_threshold_value)
		)
	{
		m_CursorPosition.y -= 32.0f;
	}

	if (controller->StickTriggerLeft(
		m_DeviceID, aqua::controller::STICK_DIRECTION::DOWN, m_default_threshold_value)
		)
	{
		m_CursorPosition.y += 32.0f;
	}

	m_CursorSprite.position = m_CursorPosition;

	IGameObject::Update();
}

void CCursor::Draw(void)
{
	m_CursorSprite.Draw();
	IGameObject::Draw();
}

void CCursor::Finalize(void)
{
	m_CursorSprite.Delete();
	IGameObject::Finalize();

}

void CCursor::SetCursor(const aqua::CVector2& pos)
{
	m_CursorPosition = pos;
}

void CCursor::CheckHitCursor(const aqua::CVector2& pos, float radius, bool& hit_flag)
{
	//ìñÇΩÇËîªíËèàóù
	float a = (m_CursorPosition.x - (pos.x + radius));
	float b = (m_CursorPosition.y - (pos.y + radius));
	float c = std::sqrt(a * a + b * b);
	float d = radius;
	if (c <= d)
		hit_flag = true;
	else
		hit_flag = false;
}

void CCursor::CheckHitCursor(const aqua::CVector2& pos, float width, float height, bool& hit_flag)
{
	aqua::CVector2 cursor_center = aqua::CVector2(m_CursorPosition.x + (float)m_CursorSprite.GetTextureWidth() / 2.0f, m_CursorPosition.y + (float)m_CursorSprite.GetTextureHeight() / 2.0f);
	if (cursor_center.x >= pos.x &&
		cursor_center.x <= pos.x + width &&
		cursor_center.y >= pos.y &&
		cursor_center.y <= pos.y + height)
		hit_flag = true;
	else
		hit_flag = false;
}

void CCursor::CheckHitWall(float left, float right, float top, float under)
{
	if (m_CursorPosition.x <= left)
		m_CursorPosition.x = left;
	if (m_CursorPosition.x >= right - m_CursorSprite.GetTextureWidth())
		m_CursorPosition.x = right - m_CursorSprite.GetTextureWidth();
	if (m_CursorPosition.y <= top)
		m_CursorPosition.y = top;
	if (m_CursorPosition.y >= under - m_CursorSprite.GetTextureWidth())
		m_CursorPosition.y = under - m_CursorSprite.GetTextureWidth();
}
