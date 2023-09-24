#include "SceneManager.h"
#include "Scene/TitleScene/TitleScene.h"
#include "Scene/TitleScene/UseForTitleScene.h"
#include "Scene/GameMainScene/GameMainScene.h"
#include "Scene/GameMainScene/Pause/Pause.h"
#include "Scene/ResultScene/ResultScene.h"

const float CSceneManager::m_fade_speed = 255.0f;

CSceneManager::CSceneManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "SceneManager")
	, m_CurrentSceneID(SCENE_ID::DUMMY)
	, m_NextSceneID(SCENE_ID::DUMMY)
	, m_PushSceneID(SCENE_ID::DUMMY)
	, m_State(STATE::SCENE_IN)
	, m_PushFlag(false)
{
}

void CSceneManager::Initialize(void)
{
	m_FadePlane.Setup(aqua::CVector2::ZERO, (float)aqua::GetWindowWidth(), (float)aqua::GetWindowHeight(), aqua::CColor::BLACK);

	Create(SCENE_ID::TITLE);

	m_State = STATE::SCENE_IN;

	m_PushFlag = false;
}

void CSceneManager::Update(void)
{
	switch (m_State)
	{
	case STATE::SCENE_IN:        SceneIn();             break;
	case STATE::SCENE_UPDATE:    SceneUpdate();         break;
	case STATE::SCENE_OUT:       SceneOut();            break;
	case STATE::SCENE_CHANGE:    SceneChange();         break;
	}
}

void CSceneManager::Draw(void)
{
	IGameObject::Draw();

	m_FadePlane.Draw();
}

void CSceneManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CSceneManager::Change(SCENE_ID id)
{
	m_NextSceneID = id;
}

void CSceneManager::Push(SCENE_ID id)
{
	if (m_PushFlag || m_PushSceneID != SCENE_ID::DUMMY) return;

	m_PushFlag = true;

	m_PushSceneID = id;
}

void CSceneManager::Pop(void)
{
	if (m_ChildObjectList.size() <= 1)
		return;

	auto it = m_ChildObjectList.rbegin();

	IScene* scene = (IScene*)(*it);

	scene->DeleteObject();

	scene = (IScene*)(*(++it));

	scene->SetGameObjectState(aqua::GAME_OBJECT_STATE::ACTIVE);
}

void CSceneManager::Reset(void)
{
	m_NextSceneID = m_CurrentSceneID;

	m_CurrentSceneID = SCENE_ID::DUMMY;
}

void CSceneManager::Create(SCENE_ID id)
{
	IScene* scene = nullptr;

	switch (id)
	{
	case SCENE_ID::TITLE:        scene = aqua::CreateGameObject<CTitleScene>(this);        break;
	case SCENE_ID::VIEW_SCORE:   scene = aqua::CreateGameObject<CViewScore>(this);		   break;
	case SCENE_ID::CONFIRM_EXIT: scene = aqua::CreateGameObject<CConfirmExit>(this);	   break;
	case SCENE_ID::GAMEMAIN:     scene = aqua::CreateGameObject<CGameMainScene>(this);     break;
	case SCENE_ID::PAUSE:		 scene = aqua::CreateGameObject<CPause>(this);			   break;
	case SCENE_ID::RESULT:       scene = aqua::CreateGameObject<CResultScene>(this);       break;
	}

	AQUA_ASSERT(scene, "ƒV[ƒ“‚ª¶¬‚Å‚«‚Ü‚¹‚ñ‚Å‚µ‚½B");

	scene->Initialize();

	scene->Update();
}

void CSceneManager::Delete(void)
{
	IGameObject::Finalize();
}

void CSceneManager::SceneIn(void)
{
	float alpha = (float)m_FadePlane.color.alpha;

	alpha -= m_fade_speed * aqua::GetDeltaTime();

	if (alpha < 0.0f)
	{
		alpha = 0.0f;

		m_State = STATE::SCENE_UPDATE;
	}

	m_FadePlane.color.alpha = (unsigned char)alpha;
}

void CSceneManager::SceneUpdate(void)
{
	if (m_PushFlag)
	{
		auto it = m_ChildObjectList.rbegin();

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

void CSceneManager::SceneOut(void)
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

void CSceneManager::SceneChange(void)
{
	Delete();

	Create(m_NextSceneID);

	m_CurrentSceneID = m_NextSceneID;

	m_State = STATE::SCENE_IN;
}
