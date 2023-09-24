#pragma once

/*!
 *  @file       skill_ui.h
 *  @brief      スキルUI
 *  @author     Takami Shimizu
 *  @date       2023/09/18
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"

class IPlayer;

/*!
 *  @class      CSkillUI
 *
 *  @brief      スキルUIクラス
 *
 *  @author     Takami Shimizu
 *
 *  @date       2023/09/18
 *
 *  @version    1.0
 */

class CSkillUI :public aqua::IGameObject
{
public:
	CSkillUI(aqua::IGameObject* parent);
	~CSkillUI() = default;

	void Initialize(IPlayer* player, IPlayer* opponent, const aqua::CVector2& pos);
	void Update(void)override;
	void Draw(void)override;
	void Finalize(void)override;

private:
	aqua::CSprite	m_SkillWhiteSprite;
	aqua::CSprite	m_SkillBlueSprite;
	aqua::CSprite	m_SkillGreenSprite;

	IPlayer* m_Player;
	IPlayer* m_Opponent;
};