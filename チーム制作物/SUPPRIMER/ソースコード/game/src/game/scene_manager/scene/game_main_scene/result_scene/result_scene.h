#pragma once

/*!
 *  @file       result_scene.h
 *  @brief      リザルトシーン
 *  @author     Roi Namisato
 *  @date       2023/06/22
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../../scene.h"

class CPlayerManager;
class CDeviceCommonData;
class IPlayer;
class CPlayerPrev;

/*!
 *  @class      CResultScene
 *
 *  @brief      リザルトシーンクラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/22
 *
 *  @version    1.0
 */

class CResultScene
	: public IScene
{
public:
	CResultScene(aqua::IGameObject* parent);
	~CResultScene(void) override = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	static const aqua::CVector2 m_default_P1_pos;
	static const aqua::CVector2 m_default_P2_pos;
	aqua::CBoxPrimitive m_BackGround;
	aqua::CSprite m_LineSprite;
	aqua::CLabel m_WinnerLabel;
	CDeviceCommonData* m_Data;
	CPlayerPrev* m_WinnerPrev;
};