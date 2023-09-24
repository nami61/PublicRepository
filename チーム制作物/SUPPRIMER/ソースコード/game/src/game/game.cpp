
/*!
 *  @file       game.cpp
 *  @brief      �Q�[���Ǘ�
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
 *  �R���X�g���N�^
 */
CGame::
CGame(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "Game")
{
}

/*
 *  ������
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
 *  �X�V
 */
void
CGame::
Update(void)
{
    IGameObject::Update();
}

/*
 *  �`��
 */
void
CGame::
Draw(void)
{
    // ��ʂ̃N���A
    aqua::Clear(m_clear_color);

    IGameObject::Draw();
}

/*
 *  ���
 */
void
CGame::
Finalize(void)
{
    IGameObject::Finalize();
}
