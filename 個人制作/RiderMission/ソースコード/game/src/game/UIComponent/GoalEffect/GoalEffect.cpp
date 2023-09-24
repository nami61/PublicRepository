#include "GoalEffect.h"

const float CGoalEffect::m_easing_limit = 1.5f;

CGoalEffect::CGoalEffect(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "GoalEffect")
{
}

void CGoalEffect::Initialize(void)
{
	m_PlaneTop.Create("data/texture/bg_black.png");
	m_PlaneBottom.Create("data/texture/bg_black.png");
	m_PlaneBottom.position = aqua::CVector2(0.0f, (float)aqua::GetWindowHeight() / 2.0f);

	m_PlaneTop.anchor = aqua::CVector2((float)m_PlaneTop.GetTextureWidth() / 2.0f, 0.0f);
	m_PlaneBottom.anchor = aqua::CVector2((float)m_PlaneBottom.GetTextureWidth() / 2.0f, (float)m_PlaneBottom.GetTextureHeight());

	m_PlaneTop.scale.y = 0.0f;
	m_PlaneBottom.scale.y = 0.0f;

	m_WaitTime.Setup(m_easing_limit);

	m_FinishFlag = false;
}

void CGoalEffect::Update(void)
{
	m_WaitTime.Update();
	float easing = aqua::easing::OutBounce(m_WaitTime.GetTime(), m_WaitTime.GetLimit());

	if (m_WaitTime.Finished())
	{
		m_PlaneTop.scale.y = 1.0f;
		m_PlaneBottom.scale.y = 1.0f;
		m_FinishFlag = true;
	}

	m_PlaneTop.scale.y = easing;
	m_PlaneBottom.scale.y = easing;

}

void CGoalEffect::Draw(void)
{
	m_PlaneTop.Draw();
	m_PlaneBottom.Draw();
}

bool CGoalEffect::FinishEffect(void)
{
	return m_FinishFlag;
}
