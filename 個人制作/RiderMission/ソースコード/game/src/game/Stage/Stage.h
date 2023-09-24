#pragma once

#include "aqua.h"

class CStage :public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	float GetGrav(void) { return m_grav; }

	float GetStageObjectSpeed(void) { return m_StageObjectSpeed; }

private:
	enum class SPRITE
	{
		FIRST,
		SECOND,
		MAX,
	};

	aqua::CSprite* m_Sprite;
	aqua::CVector2 m_Velocity;
	static const float m_grav;
	static const float m_default_bg_speed;
	static const float m_default_object_speed;
	static const float m_add_speed;
	float m_BGSpeed;
	float m_StageObjectSpeed;
};