#include "block_direction.h"
#include "game/game_object/block_manager/block/blue_block/blue_block.h"
#include "game/game_object/block_manager/block/green_block/green_block.h"
#include "game/game_object/block_manager/block/pink_block/pink_block.h"
#include "game/game_object/block_manager/block/white_block/white_block.h"

CBlockDirection::CBlockDirection(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "BlockDirection")
{
}

void CBlockDirection::Initialize(void)
{
	m_Timer.Setup(0.5f);
}

void CBlockDirection::Update(void)
{
	m_Timer.Update();
	if (m_Timer.Finished())
	{
		m_Timer.Reset();
		Create((BLOCK_ID)GetRand((int)BLOCK_ID::MAX));
	}

	IGameObject::Update();
}

void CBlockDirection::Draw(void)
{
	IGameObject::Draw();
}

void CBlockDirection::Finalize(void)
{
	IGameObject::Finalize();
}

void CBlockDirection::Create(BLOCK_ID id)
{
	IBlock* block = nullptr;
	switch (id)
	{
	case BLOCK_ID::WHITE: block = aqua::CreateGameObject<CWhiteBlock>(this); break;
	case BLOCK_ID::PINK: block = aqua::CreateGameObject<CPinkBlock>(this); break;
	case BLOCK_ID::BLUE: block = aqua::CreateGameObject<CBlueBlock>(this); break;
	case BLOCK_ID::GREEN: block = aqua::CreateGameObject<CGreenBlock>(this); break;
	}
	if (block == nullptr) return;
	block->SetPosition(aqua::CVector2((float)GetRand(aqua::GetWindowWidth() - (int)block->GetTextureWidth()), 0.0f));
	block->SetRotaSpeed(5.0f + (float)GetRand(5));
	block->Fall();
}
