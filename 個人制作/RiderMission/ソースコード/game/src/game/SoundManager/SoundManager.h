#pragma once

#include "aqua.h"

enum class SOUND_ID
{
	TITLE_BGM,
	GAME_MAIN_BGM,
	RESULT_BGM,
	CURSOR_DICISION,
	CURSOR_SELECT,
	DAMAGE,
	END_VIEW_SCORE,
	FIRE_APPEAR,
	GET_COIN,
	NOT_SELECTABEL,
	SCENE_CHANGE,
	VIEW_SCORE,
};

class CSoundManager :public aqua::IGameObject
{
public:
	CSoundManager(aqua::IGameObject* parent);
	~CSoundManager(void) = default;

	void Initialize(void) override;

	void Finalize(void) override;

	void Play(SOUND_ID id) { m_Sound[(int)id].Play(); }

	void Stop(SOUND_ID id) { m_Sound[(int)id].Stop(); }

private:
	using SOUND_LIST = std::vector<std::string>;
	static const SOUND_LIST m_sound_list;

	aqua::CSoundPlayer* m_Sound;
};