
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2020/04/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "scene_manager/scene_manager.h"
#include "game_object/sound_manager/sound_manager.h"
#include "game_object/effect_manager/effect_manager.h"
#include "game_object/device_common_data/device_common_data.h"
#include "game_object/controller_stick_operation/controller_stick_operation.h"

const unsigned int CGame::m_clear_color = 0xff000000;

/*
 *  コンストラクタ
 */
CGame::
CGame(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "Game")
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    SetMouseDispFlag(false);
    aqua::CreateGameObject<CControllerStickOperation>(this);
    aqua::CreateGameObject<CDeviceCommonData>(this);
    aqua::CreateGameObject<CEffectManager>(this);
    aqua::CreateGameObject<CSoundManager>(this);
    aqua::CreateGameObject<CSceneManager>(this);

    IGameObject::Initialize();
}

/*
 *  更新
 */
void
CGame::
Update(void)
{
    IGameObject::Update();
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_clear_color);

    IGameObject::Draw();
}

/*
 *  解放
 */
void
CGame::
Finalize(void)
{
    IGameObject::Finalize();
}
