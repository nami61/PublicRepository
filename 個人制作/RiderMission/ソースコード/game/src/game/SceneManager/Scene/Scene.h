#pragma once

#include "aqua.h"
#include "SceneID.h"

class IScene :public aqua::IGameObject
{
public:
	IScene(aqua::IGameObject* parent, const std::string& name);
	virtual ~IScene(void) = default;

	void Change(SCENE_ID id);

	void Push(SCENE_ID id);

	void Pop(void);

	void Reset(void);
};