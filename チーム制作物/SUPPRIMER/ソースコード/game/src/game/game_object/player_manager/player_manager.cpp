#include "player_manager.h"
#include "player/white/white.h"
#include "player/pink/pink.h"
#include "player/blue/blue.h"
#include "player/green/green.h"

const aqua::CVector2 CPlayerManager::p_one_pos = aqua::CVector2(50.0f, 500.0f);
const aqua::CVector2 CPlayerManager::p_two_pos = aqua::CVector2(1850.0f, 500.0f);

/*
 *  コンストラクタ
 */
CPlayerManager::CPlayerManager(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "PlayerManager")
{
}

/*
 *  更新
 */
void CPlayerManager::Update(void)
{
    IGameObject::Update();
}

/*
 *  解放
 */
void CPlayerManager::Finalize(void)
{
    IGameObject::Finalize();
}

/*
 *  生成
 */
IPlayer* CPlayerManager::Create(PLAYER_ID id, aqua::controller::DEVICE_ID device)
{
    IPlayer* player = nullptr;

    switch (id)
    {
    case PLAYER_ID::WHITE: player = aqua::CreateGameObject<CWhite>(this); break;
    case PLAYER_ID::PINK:  player = aqua::CreateGameObject<CPink>(this);  break;
    case PLAYER_ID::BLUE:  player = aqua::CreateGameObject<CBlue>(this);  break;
    case PLAYER_ID::GREEN: player = aqua::CreateGameObject<CGreen>(this); break;
    }

    if (player == nullptr) return nullptr;

    switch (device)
    {
    using namespace aqua::controller;
    case DEVICE_ID::P1: 
        player->SetPosition(p_one_pos); 
        break;
    case DEVICE_ID::P2: 
        player->SetPosition(p_two_pos); 
        player->SetScale(aqua::CVector2(-1.0f, 1.0f)); 
        break;
    }
    player->Initialize();
    player->SetPlayerID(id);
    player->SetDeviceID(device);

    return player;
}
