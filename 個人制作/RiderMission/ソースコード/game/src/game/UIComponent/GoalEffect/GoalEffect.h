#pragma once

#include "aqua.h"

class CGoalEffect :public aqua::IGameObject
{
public:
	CGoalEffect(aqua::IGameObject* parent);
	~CGoalEffect(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	bool FinishEffect(void);

private:
	static const float m_easing_limit;
	aqua::CSprite m_PlaneTop;
	aqua::CSprite m_PlaneBottom;
	aqua::CTimer m_WaitTime;
	bool m_FinishFlag;
};