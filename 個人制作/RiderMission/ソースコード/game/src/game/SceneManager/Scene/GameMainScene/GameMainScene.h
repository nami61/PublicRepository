#pragma once

#include "../Scene.h"

class CStage;
class CPlayer;
class CStageObjectManager;
class CSoundManager;
class CGoalEffect;
class CControlPanelUI;

class CGameMainScene :public IScene
{
public:
	CGameMainScene(aqua::IGameObject* parent);
	~CGameMainScene(void) override = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	CStage* m_Stage;
	CPlayer* m_Player;
	CStageObjectManager* m_StageObjectManager;
	CSoundManager* m_SoundManager;
	CGoalEffect* m_GoalEffect;
	CControlPanelUI* m_ControlPanel;
};