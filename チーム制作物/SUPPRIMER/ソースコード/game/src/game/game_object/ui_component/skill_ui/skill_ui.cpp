#include "skill_ui.h"
#include "../../player_manager/player/player.h"

CSkillUI::CSkillUI(aqua::IGameObject* parent)
	:IGameObject(parent, "SkillUI")
{
}

void CSkillUI::Initialize(IPlayer* player, IPlayer* opponent, const aqua::CVector2& pos)
{
	m_SkillWhiteSprite.Create("data/counter_icon.png");
	m_SkillBlueSprite.Create("data/guard_icon.png");
	m_SkillGreenSprite.Create("data/debuff_icon.png");

	m_SkillWhiteSprite.position = pos;
	m_SkillBlueSprite.position = aqua::CVector2(pos.x + 40, pos.y);
	m_SkillGreenSprite.position = aqua::CVector2(pos.x + 80, pos.y);

	m_Player = player;
	m_Opponent = opponent;
}

void CSkillUI::Update(void)
{
	if (m_Player->GetCounterState())
		m_SkillWhiteSprite.visible = true;
	else
		m_SkillWhiteSprite.visible = false;

	if (m_Player->GetGuardState())
		m_SkillBlueSprite.visible = true;
	else
		m_SkillBlueSprite.visible = false;

	if (m_Player->GetPoisonState())
		m_SkillGreenSprite.visible = true;
	else
		m_SkillGreenSprite.visible = false;
}

void CSkillUI::Draw(void)
{
	m_SkillWhiteSprite.Draw();
	m_SkillBlueSprite.Draw();
	m_SkillGreenSprite.Draw();
}

void CSkillUI::Finalize(void)
{
	m_SkillWhiteSprite.Delete();
	m_SkillBlueSprite.Delete();
	m_SkillGreenSprite.Delete();
}
