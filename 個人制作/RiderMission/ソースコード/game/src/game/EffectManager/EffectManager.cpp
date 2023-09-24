#include "EffectManager.h"
#include "Effect/CoinFlash/CoinFlash.h"

CEffectManager::CEffectManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "EffectManager")
{
}

void CEffectManager::Create(EFFECT_ID id, const aqua::CVector2& pos)
{
	IEffect* effect = nullptr;

	switch (id)
	{
	case EFFECT_ID::COIN_FLASH:	effect = aqua::CreateGameObject<CCoinFlash>(this);  break;
	}

	if (effect == nullptr) return;

	effect->Initialize(pos);
	effect->Play();
	effect->Draw();
}
