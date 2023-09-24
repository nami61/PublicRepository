#pragma once

#include "aqua.h"

class CStage;
class CStageObjectManager;

class CPlayer :public aqua::IGameObject
{
public:
	CPlayer(aqua::IGameObject* parent);
	~CPlayer(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void Damage(int damage);

	aqua::CVector2 GetPosition(void) { return m_Position; }

	aqua::CVector2 GetSize(void) { return m_Size; }

	aqua::CVector2 GetVelocity(void) { return m_Velocity; }

	void SetPosition(aqua::CVector2 pos) { m_Position = pos; }

	bool IsActive(void) { return m_ActiveFlag; }

	bool IsFall(void) { return m_FallFlag; }

private:
	enum class ANM_STATE
	{
		RUN,
		JUMP,
	};

	void Jump(void);

	void Fall(void);
		
	aqua::CSprite m_Sprite;
	aqua::CAnimationSprite m_AnmSprite;
	aqua::CVector2 m_Position;
	aqua::CVector2 m_Velocity;
	aqua::CVector2 m_Size;
	aqua::CTimer m_FallTimer;
	aqua::CTimer m_EasingTimer;
	CStage* m_Stage;
	CStageObjectManager* m_StageObjectManager;
	static const aqua::CVector2 m_default_pos;
	static const int m_max_jump_count;
	static const int m_default_max_life;
	static const float m_fall_limit;
	static const float m_easing_limit;
	static const float m_max_fall_speed;
	static const float m_jump_power;
	int m_AirJumpCount;
	int m_FadeCount;
	int m_Life;
	int m_MaxLife;
	bool m_LandingFlag;
	bool m_FallFlag;
	bool m_ActiveFlag;
};