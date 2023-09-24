#pragma once

/*!
 *  @file       background.h
 *  @brief      バックグランドUI
 *  @author     Roi Namisato
 *  @date       2023/06/29
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "../../player_manager/player/player_id.h"

/*!
 *  @class      CBackground
 *
 *  @brief      バックグランドクラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/29
 *
 *  @version    1.0
 */

class CBackground : public aqua::IGameObject
{
public:
	CBackground(aqua::IGameObject* parent);
	~CBackground(void) = default;

	void TitleInit(void);
	void Initialize(aqua::controller::DEVICE_ID device, PLAYER_ID id);
	void Draw(void);
	void Finalize(void);

private:
	enum class BACKGROUND
	{
		HOUSE,
		LIBRARY,
		STAR,
		THRONE,
		WOOD,
	};
	static const int m_max_backgrounds;
	aqua::CSprite m_Background;
};