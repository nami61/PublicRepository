#pragma once

/*!
 *  @file       continue.h
 *  @brief      コンテニューUI
 *  @author     Roi Namisato
 *  @date       2023/07/28
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CContinue
  *
  *  @brief      コンテニュークラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/07/28
  *
  *  @version    1.0
  */

class CSceneManager;
class CSoundManager;

class CContinue
	: public aqua::IGameObject
{
public:
	CContinue(aqua::IGameObject* parent);
	~CContinue(void) = default;
	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;
	void Setup(aqua::controller::DEVICE_ID id) { m_EnabledDevice = id; }

private:
	void Continue(void);
	void ExitGame(void);
	void SetUIPosition(void);

	enum class CURSOR_STATE
	{
		CONTINUE,
		EXITGAME,
	};

	static const aqua::CVector2 m_top_message_pos_p1;
	static const aqua::CVector2 m_top_message_pos_p2;
	static const aqua::CVector2 m_top_cursor_pos_p1;
	static const aqua::CVector2 m_top_cursor_pos_p2;
	bool m_ContinuousInput;
	aqua::CTimer m_CursorBoundTimer;
	aqua::CSprite m_Sprite;
	aqua::CLabel m_ContinueMessage;
	aqua::CLabel m_ExitGameMessage;
	aqua::controller::DEVICE_ID m_EnabledDevice;
	CURSOR_STATE m_State;
	CSceneManager* m_SM;
	CSoundManager* m_SoundManager;
};