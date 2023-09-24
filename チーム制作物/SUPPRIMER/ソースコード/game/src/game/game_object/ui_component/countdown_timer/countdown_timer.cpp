#include "countdown_timer.h"

const aqua::CVector2 CCountdawnTimer::m_circle_pos = aqua::CVector2(960.0f, 500.0f);
const aqua::CVector2 CCountdawnTimer::m_label_pos = aqua::CVector2(922.0f, 470.0f);

CCountdawnTimer::CCountdawnTimer(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "CountdawnTimer")
{
}

void CCountdawnTimer::Initialize(void)
{
	Label.Create(64, 2);
	Label.text = "";
	Label.position = m_label_pos;
	m_CurrentTime = 0;
	m_Limit = 0;
	Sprite.Create("data/circle.png");
}

void CCountdawnTimer::Update(void)
{
	if ((int)m_CurrentTime < 10)
		Label.text = "0" + std::to_string((int)m_CurrentTime);
	else
		Label.text = std::to_string((int)m_CurrentTime);
}

void CCountdawnTimer::Draw(void)
{
	Label.Draw();
	float current_parcent = (m_CurrentTime / m_Limit) * 100.0f;
	DrawCircleGaugeF(m_circle_pos.x, m_circle_pos.y, (double)current_parcent, Sprite.GetResourceHandle());
}

void CCountdawnTimer::Finalize(void)
{
	Label.Delete();
	Sprite.Delete();
}
