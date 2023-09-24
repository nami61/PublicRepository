#pragma once

#include "../Effect.h"

class CCoinFlash :public IEffect
{
public:
	CCoinFlash(aqua::IGameObject* parent);
	~CCoinFlash(void) override = default;

	void Initialize(const aqua::CVector2& pos);
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	aqua::CEffect2D m_Effect;
};