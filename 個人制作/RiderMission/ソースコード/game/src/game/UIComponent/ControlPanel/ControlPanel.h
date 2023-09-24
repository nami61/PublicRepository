#pragma once

#include "aqua.h"

class CControlPanelUI :public aqua::IGameObject
{
public:
	CControlPanelUI(aqua::IGameObject* parent);
	~CControlPanelUI(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	static const aqua::CVector2 m_default_position;
	aqua::CSprite m_Sprite;
	aqua::CBoxPrimitive m_BackPlane;
};