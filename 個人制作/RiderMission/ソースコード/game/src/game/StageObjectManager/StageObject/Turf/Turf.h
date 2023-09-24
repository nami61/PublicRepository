#pragma once

#include "../StageObject.h"

class CTurf :public IStageObject
{
public:
	CTurf(aqua::IGameObject* parent);
	~CTurf(void) override = default;

	void Initialize(aqua::CVector2 pos) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	aqua::CSprite m_Sprite;
};