#pragma once

#include "../effect.h"

class CCounter :public IEffect
{
public:
	CCounter(aqua::IGameObject* parent);
	~CCounter(void) override = default;

	void Initialize(const aqua::CVector2& pos) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
};