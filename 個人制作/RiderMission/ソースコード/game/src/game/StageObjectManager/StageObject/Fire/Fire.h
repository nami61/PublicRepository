#pragma once

#include "../StageObject.h"

class CPlayer;
class CSoundManager;

class CFire :public IStageObject
{
public:
	CFire(aqua::IGameObject* parent);
	~CFire(void) override = default;

	void Initialize(aqua::CVector2 pos) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	bool IsHitPlayer(void);

private:
	static const int m_default_damage;
	int m_Damage;
	bool m_IsAppear;
	aqua::CAnimationSprite m_AnmSprite;
	CPlayer* m_Player;
	CSoundManager* m_SoundManager;
};