#pragma once

#include "../StageObject.h"

class CPlayer;
class CScoreManager;
class CSoundManager;
class CEffectManager;

class CCoin :public IStageObject
{
public:
	CCoin(aqua::IGameObject* parent);
	~CCoin(void) override = default;

	void Initialize(aqua::CVector2 pos) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void Animation(void);

	int GetScore(void) { return m_Score; }

	aqua::CVector2& GetPosition(void) { return m_Position; }

	bool IsHitPlayer(void);

private:
	enum class ANIMATION_STATE
	{
		WAIT,
		RISING,
		END,
	};

	static const int m_default_score;
	static const float m_rising_speed;
	static const float m_upper_limit;
	int m_Score;
	bool m_Enabled;
	aqua::CAnimationSprite m_AnmSprite;
	aqua::CTimer m_RisingTimer;
	CPlayer* m_Player;
	CScoreManager* m_ScoreManager;
	CSoundManager* m_SoundManager;
	aqua::CEffect2D m_Effect;
	ANIMATION_STATE m_State;
};