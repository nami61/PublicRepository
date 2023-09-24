#pragma once

#include "aqua.h"
#include "Effect/EffectID.h"

class CEffectManager :public aqua::IGameObject
{
public:
	CEffectManager(aqua::IGameObject* parent);
	~CEffectManager(void) = default;

	void Create(EFFECT_ID id, const aqua::CVector2& pos);
};