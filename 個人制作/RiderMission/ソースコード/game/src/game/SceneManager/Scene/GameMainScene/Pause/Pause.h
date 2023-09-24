#pragma once

#include "../../Scene.h"

class CScoreManager;
class CSoundManager;

class CPause :public IScene
{
public:
	CPause(aqua::IGameObject* parent);
	~CPause(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	void ReturnToGameScreen(void);
	void Continue(void);
	void FinishGame(void);

	enum class STATE
	{
		RETURN,
		CONTINUE,
		FINISH,
	};

	static const int m_message_size;
	static const aqua::CVector2 m_default_pause_message_pos;
	static const aqua::CVector2 m_default_return_message_pos;
	static const aqua::CVector2 m_default_continue_message_pos;
	static const aqua::CVector2 m_default_finish_game_message_pos;
	aqua::CBoxPrimitive m_BackPlane;
	aqua::CBoxPrimitive m_CursorBox;
	aqua::CLabel m_PauseMessage;
	aqua::CLabel m_ReturnMessage;
	aqua::CLabel m_ContinueMessage;
	aqua::CLabel m_FinishGameMessage;
	STATE m_State;
	CScoreManager* m_ScoreManager;
	CSoundManager* m_SoundManager;
};
