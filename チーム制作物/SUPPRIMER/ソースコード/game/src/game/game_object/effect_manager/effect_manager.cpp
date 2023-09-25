#include "effect_manager.h"
#include "effect/effect.h"
#include "effect/counter/counter.h"
#include "effect/debuff/debuff.h"
#include "effect/guard/guard.h"
#include "effect/vanish/vanish.h"
#include "effect/heal/heal.h"

CEffectManager::CEffectManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "EffectManager")
{
}

void CEffectManager::Create(EFFECT_ID id, const aqua::CVector2& pos)
{
	IEffect* effect = nullptr;

	switch (id)
	{
	case EFFECT_ID::COUNTER:effect = aqua::CreateGameObject<CCounter>(this); break;
	case EFFECT_ID::DEBUFF: effect = aqua::CreateGameObject<CDebuff>(this); break;
	case EFFECT_ID::GURAD:  effect = aqua::CreateGameObject<CGuard>(this); break;
	case EFFECT_ID::VANISH: effect = aqua::CreateGameObject<CVanish>(this); break;
	case EFFECT_ID::HEAL: effect = aqua::CreateGameObject<CHeal>(this); break;
	}

	if (effect == nullptr) return;
	effect->Initialize(pos);
}
