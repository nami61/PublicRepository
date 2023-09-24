#pragma once

/*!
 *  @file       round_manager.h
 *  @brief      ラウンド管理
 *  @author     Roi Namisato
 *  @date       2023/08/17
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

 /*!
  *  @class      CRoundManager
  *
  *  @brief      ラウンド管理クラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/08/17
  *
  *  @version    1.0
  */

class CRoundManager :public aqua::IGameObject
{
public:
	CRoundManager(aqua::IGameObject* parent);
	~CRoundManager(void) = default;

	void Initialize(void) override;
	void Update(void) override;
	void Finalize(void) override;
	void ResetTimer(void) { m_Timer.Reset(); }
	void ResetCount(void) { m_CurrentRounds = 0; }
	void AddRounds(void) { ++m_CurrentRounds; }
	int GetMaxRounds(void) { return m_max_rounds; }
	int GetCurrentRounds(void) { return m_CurrentRounds; }
	float GetCurrentElapsedTime(void) { return m_Timer.GetTime(); }
	float GetLimitTime(void) { return m_Timer.GetLimit(); }
	bool IsFinishedTimer(void) { return m_Timer.Finished(); }
	bool IsFinishedRound(void) { return (m_CurrentRounds == m_max_rounds); }

private:
	static const float m_default_round_time;
	static const int m_max_rounds;
	aqua::CTimer m_Timer;
	int m_CurrentRounds;
};