#pragma once

#include "../Scene.h"

class CSoundManager;
class CScoreManager;

class CResultScene :public IScene
{
public:
	CResultScene(aqua::IGameObject* parent);
	~CResultScene(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	void RectSetting(void);

	void ScoreDigitSetting(void);

	enum class CURSOR_STATE
	{
		CONTINUE,
		RETURN_TO_TITLE,
	};

	static const int m_max_score_digit;
	static const int m_decimal_number;
	static const float m_easing_limit;
	static const aqua::CVector2 m_default_score_pos;
	int m_Score;
	bool m_IsFinish;
	CURSOR_STATE m_State;
	aqua::CSprite* m_NumberSprite;
	aqua::CSprite m_BGSprite;
	aqua::CTimer m_EasingTimer;
	aqua::CLabel m_ScoreMessage;
	aqua::CLabel m_RetryMessage;
	aqua::CLabel m_ReturnToTitleMessage;
	aqua::CBoxPrimitive m_BackPlane;
	aqua::CBoxPrimitive m_CursorBox;
	CSoundManager* m_SoundManager;
	CScoreManager* m_ScoreManager;
};