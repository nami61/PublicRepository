#include "SoundManager.h"

const CSoundManager::SOUND_LIST CSoundManager::m_sound_list
{
	"data/sound/bgm/title.mp3",
	"data/sound/bgm/game_main.mp3",
	"data/sound/bgm/result.mp3",
	"data/sound/se/cursor_decision.mp3",
	"data/sound/se/cursor_select.mp3",
	"data/sound/se/damage.mp3",
	"data/sound/se/end_view_score.mp3",
	"data/sound/se/fire_appear.mp3",
	"data/sound/se/get_coin.mp3",
	"data/sound/se/not_selectable.mp3",
	"data/sound/se/scene_change.mp3",
	"data/sound/se/view_score.mp3",
};

CSoundManager::CSoundManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SoundManager")
{
}

void CSoundManager::Initialize(void)
{
	m_Sound = AQUA_NEW aqua::CSoundPlayer[m_sound_list.size()];

	for (int soundNumber = 0; soundNumber < m_sound_list.size(); ++soundNumber)
	{
		std::string line = m_sound_list.at(soundNumber);
		if (line.substr(11, 3) == "bgm")
			m_Sound[soundNumber].Create(line, true);
		else if (line.substr(11, 2) == "se")
			m_Sound[soundNumber].Create(line, false);
		else
			AQUA_ASSERT(false, line + "‚ÌŽæ“¾‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
	}
}

void CSoundManager::Finalize(void)
{
	for (int soundNumber = 0; soundNumber < m_sound_list.size(); ++soundNumber)
		m_Sound[soundNumber].Delete();

	AQUA_SAFE_DELETE(m_Sound);
}
