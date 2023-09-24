
/*!
 *  @file       scene_manager.cpp
 *  @brief      �V�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "scene_manager.h"
#include "scene\title_scene\title_scene.h"
#include "scene\game_main_scene\game_main_scene.h"
#include "scene\game_main_scene\result_scene\result_scene.h"
#include "scene\game_main_scene\round_finish\round_finish.h"
#include "scene\title_scene\demo_scene\demo_scene.h"

const float CSceneManager::m_fade_speed = 255.0f;

/*
 *  �R���X�g���N�^
 */
CSceneManager::
CSceneManager(aqua::IGameObject* parent)
    : aqua::IGameObject(parent, "SceneManager")
    , m_CurrentSceneID(SCENE_ID::DUMMY)
    , m_NextSceneID(SCENE_ID::DUMMY)
    , m_PushSceneID(SCENE_ID::DUMMY)
    , m_State(STATE::SCENE_IN)
    , m_PushFlag(false)
{
}

/*
 *  ������
 */
void
CSceneManager::
Initialize(void)
{
    m_FadePlane.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), aqua::CColor::BLACK);

    Create(SCENE_ID::TITLE);

    m_State = STATE::SCENE_IN;

    m_PushFlag = false;
}

/*
 *  �X�V
 */
void
CSceneManager::
Update(void)
{
    switch (m_State)
    {
    case STATE::SCENE_IN:        SceneIn();             break;
    case STATE::SCENE_UPDATA:    SceneUpdate();         break;
    case STATE::SCENE_OUT:       SceneOut();            break;
    case STATE::SCENE_CHANGE:    SceneChange();         break;
    }
}

/*
 *  �`��
 */
void
CSceneManager::
Draw(void)
{
    IGameObject::Draw();

    m_FadePlane.Draw();
}

/*
 *  ���
 */
void
CSceneManager::
Finalize(void)
{
    IGameObject::Finalize();
}

/*
 *  �V�[���̕ύX
 */
void
CSceneManager::
Change(SCENE_ID id)
{
    m_NextSceneID = id;
}

/*
 *  �V�[�����X�^�b�N����
 */
void
CSceneManager::
Push(SCENE_ID id)
{
    if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

    m_PushFlag = true;

    m_PushSceneID = id;
}

/*
 *  �X�^�b�N�����V�[�������o��
 */
void
CSceneManager::
Pop(void)
{
    if (m_ChildObjectList.size() <= 1)
        return;

    aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

    IScene* scene = (IScene*)(*it);

    scene->DeleteObject();

    scene = (IScene*)(*(++it));

    scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

/*
 *  ���݂̃V�[�������Z�b�g����
 */
void
CSceneManager::
Reset(void)
{
    m_NextSceneID = m_CurrentSceneID;

    m_CurrentSceneID = SCENE_ID::DUMMY;
}

/*
 *  �V�[���̐���
 */
void
CSceneManager::
Create(SCENE_ID id)
{
    IScene* scene = nullptr;

    switch (id)
    {
    case SCENE_ID::TITLE:        scene = aqua::CreateGameObject<CTitleScene>(this);        break;
    case SCENE_ID::GAMEMAIN:     scene = aqua::CreateGameObject<CGameMainScene>(this);     break;
    case SCENE_ID::RESULT:       scene = aqua::CreateGameObject<CResultScene>(this);       break;
    case SCENE_ID::ROUND_FINISH: scene = aqua::CreateGameObject<CRoundFinishScene>(this);  break;
    case SCENE_ID::DEMO:         scene = aqua::CreateGameObject<CDemoScene>(this);         break;
    }

    AQUA_ASSERT(scene, "�V�[���������ł��܂���ł����B");

    scene->Initialize();

    scene->Update();
}

/*
 *  �V�[���̍폜
 */
void
CSceneManager::
Delete(void)
{
    IGameObject::Finalize();
}

/*
 *  �V�[���J�n���o
 */
void
CSceneManager::
SceneIn(void)
{
    float alpha = (float)m_FadePlane.color.alpha;

    alpha -= m_fade_speed * aqua::GetDeltaTime();

    if (alpha < 0.0f)
    {
        alpha = 0.0f;

        m_State = STATE::SCENE_UPDATA;
    }

    m_FadePlane.color.alpha = (unsigned char)alpha;
}

/*
 *  �V�[���X�V
 */
void
CSceneManager::
SceneUpdate(void)
{
    if (m_PushFlag)
    {
        aqua::GAME_OBJECT_LIST::reverse_iterator it = m_ChildObjectList.rbegin();

        IScene* scene = (IScene*)(*it);

        scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);

        Create(m_PushSceneID);

        m_PushSceneID = SCENE_ID::DUMMY;

        m_PushFlag = false;
    }

    IGameObject::Update();

    if (m_CurrentSceneID != m_NextSceneID)
        m_State = STATE::SCENE_OUT;
}

/*
 *  �V�[���I�����o
 */
void
CSceneManager::
SceneOut(void)
{
    float alpha = (float)m_FadePlane.color.alpha;

    alpha += m_fade_speed * aqua::GetDeltaTime();

    if (alpha > (float)aqua::CColor::MAX_COLOR)
    {
        alpha = (float)aqua::CColor::MAX_COLOR;

        m_State = STATE::SCENE_CHANGE;
    }

    m_FadePlane.color.alpha = (unsigned char)alpha;
}

/*
 *  �V�[���ύX
 */
void
CSceneManager::
SceneChange(void)
{
    Delete();

    Create(m_NextSceneID);

    m_CurrentSceneID = m_NextSceneID;

    m_State = STATE::SCENE_IN;
}
