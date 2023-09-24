#include "GameMainScene.h"
#include "../../../SoundManager/SoundManager.h"
#include "../../../Stage/Stage.h"
#include "../../../StageObjectManager/StageObjectManager.h"
#include "../../../Player/Player.h"
#include "../../../UIComponent/StartMessage/StartMessage.h"
#include "../../../UIComponent/CurrentScoreUI/CurrentScoreUI.h"
#include "../../../UIComponent/GoalEffect/GoalEffect.h"
#include "../../../UIComponent/ControlPanel/ControlPanel.h"

CGameMainScene::CGameMainScene(aqua::IGameObject* parent)
    :IScene(parent, "GameMainScene")
{
}

void CGameMainScene::Initialize(void)
{
    m_SoundManager = (CSoundManager*)aqua::FindGameObject("SoundManager");
    m_Stage = aqua::CreateGameObject<CStage>(this);
    m_StageObjectManager = aqua::CreateGameObject<CStageObjectManager>(this);
    m_Player = aqua::CreateGameObject<CPlayer>(this);
    aqua::CreateGameObject<CCurrentScoreUI>(this);
    m_ControlPanel = aqua::CreateGameObject<CControlPanelUI>(this);
    m_ControlPanel->Initialize();
    aqua::CreateGameObject<CStartMessageUI>(this);
    m_GoalEffect = aqua::CreateGameObject<CGoalEffect>(this);
    m_GoalEffect->SetGameObjectState(aqua::GAME_OBJECT_STATE::WAIT);
    IGameObject::Initialize();

    m_SoundManager->Play(SOUND_ID::GAME_MAIN_BGM);
}

void CGameMainScene::Update(void)
{
    if (!m_Player->IsActive())
    {
        Change(SCENE_ID::RESULT);
        m_SoundManager->Stop(SOUND_ID::GAME_MAIN_BGM);
    }

    if(m_StageObjectManager->IsEndGame())
        m_GoalEffect->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);

    if (m_GoalEffect->GetGameObjectState() == aqua::GAME_OBJECT_STATE::ACTIVE)
    {
        if (m_GoalEffect->FinishEffect())
        {
            Change(SCENE_ID::RESULT);
            m_SoundManager->Stop(SOUND_ID::GAME_MAIN_BGM);
        }
    }

    if (aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::MIDDLE))
        Push(SCENE_ID::PAUSE);

    IGameObject::Update();
}

void CGameMainScene::Draw(void)
{
    m_ControlPanel->Draw();
    IGameObject::Draw();
}

void CGameMainScene::Finalize(void)
{
    m_ControlPanel->Finalize();
    IGameObject::Finalize();
}
