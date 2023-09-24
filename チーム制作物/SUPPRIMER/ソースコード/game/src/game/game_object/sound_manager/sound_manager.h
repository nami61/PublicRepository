#pragma once

/*!
 *  @file       sound_manager.h
 *  @brief      サウンド管理
 *  @author     Roi Namisato
 *  @date       2023/09/19
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

/*!
 *  @class      CSoundManager
 *
 *  @brief      サウンド管理クラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/09/19
 *
 *  @version    1.0
 */

enum class SOUND_ID
{
	TITLE_BGM,
	GAMEMAIN_BGM1,
	GAMEMAIN_BGM2,
	GAMEMAIN_BGM3,
	GAMEMAIN_BGM4,
	GAMEMAIN_BGM5,
	RESULT_BGM,
	COUNTER,
	DAMAGE,
	FADE_IN_SCORE,
	GAME_START,
	GAMEMAIN_ATTACK,
	GUARD,
	HEAL,
	PLAYER_SELECT,
	POISON,
	RESULT_FANFARE,
	RIBBON,
	ROUND_FINISH_ATTACK,
	TIME_OVER,
	VANISH_BLOCK,
};

class CSoundManager :public aqua::IGameObject
{
public:
	CSoundManager(aqua::IGameObject* parent);
	~CSoundManager(void) = default;

	void Initialize(void) override;

	void Finalize(void) override;


	void Play(SOUND_ID id) { m_Sounds[(int)id].Play(); }
	void Stop(SOUND_ID id) { m_Sounds[(int)id].Stop(); }

private:
	static const std::vector<std::string> m_sound_list;
	aqua::CSoundPlayer* m_Sounds;
};