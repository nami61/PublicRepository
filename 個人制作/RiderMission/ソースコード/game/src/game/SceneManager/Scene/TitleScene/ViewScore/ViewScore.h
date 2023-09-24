#pragma once

#include "../../Scene.h"

class CScoreManager;

class CViewScore :public IScene
{
public:
	CViewScore(aqua::IGameObject* parent);
	~CViewScore(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:

	static const aqua::CVector2 m_default_score_pos;
	static const aqua::CVector2 m_default_label_pos;
	aqua::CBoxPrimitive m_Plane;
	CScoreManager* m_ScoreManager;
	aqua::CLabel m_Message;
	aqua::CLabel m_Score;
};