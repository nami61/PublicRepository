
/*!
 *  @file       scene.cpp
 *  @brief      �V�[��
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "scene.h"
#include "..\scene_manager.h"

const std::string   IScene::m_scene_category = "Scene";

/*
 *  �R���X�g���N�^
 */
IScene::
IScene(aqua::IGameObject* parent, const std::string& object_name)
    : aqua::IGameObject(parent, object_name, m_scene_category)
{
}

/*
 *  �V�[���̕ύX
 */
void
IScene::
Change(SCENE_ID id)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Change(id);
}

/*
 *  �V�[�����X�^�b�N����
 */
void
IScene::
Push(SCENE_ID id)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Push(id);
}

/*
 *  �X�^�b�N���ꂽ�V�[�������o��
 */
void
IScene::
Pop(void)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Pop();
}

/*
 *  �V�[�������Z�b�g����
 */
void
IScene::
Reset(void)
{
    CSceneManager* sm = (CSceneManager*)GetParent();

    sm->Reset();
}
