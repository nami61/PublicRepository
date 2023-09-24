#pragma once

#include "../StageObject.h"

class CStageObjectManager;

class CEnd :public IStageObject
{
public:
	CEnd(aqua::IGameObject* parent);
	~CEnd(void) override = default;

	void Initialize(aqua::CVector2 pos) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	bool m_IsAppear;
	CStageObjectManager* m_StageObjectManager;
};