#include "sound_manager.h"

const std::vector<std::string> CSoundManager::m_sound_list = 
{
	"data/sound/bgm/title_bgm.mp3",
	"data/sound/bgm/gamemain_bgm1.mp3",
	"data/sound/bgm/gamemain_bgm2.mp3",
	"data/sound/bgm/gamemain_bgm3.mp3",
	"data/sound/bgm/gamemain_bgm4.mp3",
	"data/sound/bgm/gamemain_bgm5.mp3",
	"data/sound/bgm/result_bgm.mp3",
	"data/sound/se/counter.mp3",
	"data/sound/se/damage.mp3",
	"data/sound/se/fade_in_score.mp3",
	"data/sound/se/game_start.mp3",
	"data/sound/se/gamemain_attack.mp3",
	"data/sound/se/guard.mp3",
	"data/sound/se/heal.mp3",
	"data/sound/se/player_select.mp3",
	"data/sound/se/poison.mp3",
	"data/sound/se/result_fanfare.mp3",
	"data/sound/se/ribbon.mp3",
	"data/sound/se/round_finish_attack.mp3",
	"data/sound/se/time_over.mp3",
	"data/sound/se/vanish_block.mp3",
};

CSoundManager::CSoundManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SoundManager")
{
}

void CSoundManager::Initialize(void)
{
	m_Sounds = AQUA_NEW aqua::CSoundPlayer[m_sound_list.size()];

	for (int i = 0; i < m_sound_list.size(); ++i)
	{
		std::string line = m_sound_list.at(i);
		if (line.substr(11, 3) == "bgm")
			m_Sounds[i].Create(line, true);
		else if (line.substr(11, 2) == "se")
			m_Sounds[i].Create(line, false);
		else
			AQUA_ASSERT(false, line + "‚Ìæ“¾‚É¸”s‚µ‚Ü‚µ‚½B");
	}
}

void CSoundManager::Finalize(void)
{
	for(int i = 0; i < m_sound_list.size(); ++i)
		m_Sounds[i].Delete();
	AQUA_SAFE_DELETE(m_Sounds);
}
