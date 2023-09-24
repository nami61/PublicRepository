#include "Scene.h"
#include "../SceneManager.h"

IScene::IScene(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, name, "Scene")
{
}

void IScene::Change(SCENE_ID id)
{
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Change(id);
}

void IScene::Push(SCENE_ID id)
{
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Push(id);
}

void IScene::Pop(void)
{
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Pop();
}

void IScene::Reset(void)
{
	CSceneManager* sm = (CSceneManager*)GetParent();

	sm->Reset();
}
