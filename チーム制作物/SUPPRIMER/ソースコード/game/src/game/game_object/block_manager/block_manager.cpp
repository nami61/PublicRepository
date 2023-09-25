#include "block_manager.h"
#include "block/white_block/white_block.h"
#include "block/pink_block/pink_block.h"
#include "block/blue_block/blue_block.h"
#include "block/green_block/green_block.h"
#include "../../game_object/ui_component/cursor/cursor.h"
#include "../../game_object/device_common_data/device_common_data.h"
#include "../effect_manager/effect_manager.h"
#include <algorithm>

const int CBlockManager::m_block_array_width = 16;
const int CBlockManager::m_block_array_height = 16;
const aqua::CVector2 CBlockManager::m_field_pos_p1 = { 308.0f, 230.0f };
const aqua::CVector2 CBlockManager::m_field_pos_p2 = { 1108.0f, 230.0f };

CBlockManager::CBlockManager(aqua::IGameObject* parent)
	:IGameObject(parent, "BlockManager")
	, m_CurrentVanishedBlocksP1(0)
	, m_CurrentVanishedBlocksP2(0)
{
}

void CBlockManager::Initialize(CCursor* cursor1, CCursor* cursor2)
{
	m_Data = (CDeviceCommonData*)aqua::FindGameObject("DeviceCommonData");
	DeployBlocks();
	m_CursorP1 = cursor1;
	m_CursorP2 = cursor2;
	m_EffectManager = (CEffectManager*)aqua::FindGameObject("EffectManager");
}

void CBlockManager::Update(void)
{
	if (!m_DeleteBlockArrayP1.empty())
	{
		DeleteBlock(m_P1BlockList, aqua::controller::DEVICE_ID::P1);
		BlockFall(m_P1BlockList);
		BlockSlide(m_P1BlockList);
		m_DeleteBlockArrayP1.clear();
	}

	if (!m_DeleteBlockArrayP2.empty())
	{
		DeleteBlock(m_P2BlockList, aqua::controller::DEVICE_ID::P2);
		BlockFall(m_P2BlockList);
		BlockSlide(m_P2BlockList);
		m_DeleteBlockArrayP2.clear();
	}

	m_CurrentVanishedBlocksP1 = 0;
	m_CurrentVanishedBlocksP2 = 0;

	IBlock* temp_block = nullptr;
	for (auto& block : m_P1BlockList)
	{
		block->Update();
		m_CursorP1->CheckHitCursor(block->GetPosition(), block->GetTextureWidth(), block->GetTextureHeight(), block->GetHitFlag());
		if (block->IsHitCursor())
		{
			temp_block = block;
			continue;
		}
	}

	if (temp_block != nullptr &&
		(aqua::controller::Trigger(aqua::controller::DEVICE_ID::P1, aqua::controller::BUTTON_ID::A) ||
			aqua::controller::Trigger(aqua::controller::DEVICE_ID::P1, aqua::controller::BUTTON_ID::B) ||
			aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::SPACE)))
	{
		int count = 0;
		count = BlockCount(temp_block->GetID(), aqua::controller::DEVICE_ID::P1, m_P1BlockList, temp_block->GetFieldWidth(), temp_block->GetFieldHeight(), 0);
		if (count >= 2)
		{
			m_CurrentVanishedBlocksP1 = count;
			m_Data->SetVanishedBonus(aqua::controller::DEVICE_ID::P1, count);
			ComparisonID(aqua::controller::DEVICE_ID::P1, m_DeleteBlockArrayP1.at(0)->GetID());
			ComparisonMaxVanishedBlocks(aqua::controller::DEVICE_ID::P1);
			AddTotalVanishedBlocks(aqua::controller::DEVICE_ID::P1);
		}
		else if (count == 1)
		{
			m_DeleteBlockArrayP1.clear();
			temp_block->SetReferenceFlag(false);
		}
	}

	temp_block = nullptr;
	for (auto& block : m_P2BlockList)
	{
		block->Update();
		m_CursorP2->CheckHitCursor(block->GetPosition(), block->GetTextureWidth(), block->GetTextureHeight(), block->GetHitFlag());
		if (block->IsHitCursor())
		{
			temp_block = block;
			continue;
		}
	}

	if (temp_block != nullptr &&
		(aqua::controller::Trigger(aqua::controller::DEVICE_ID::P2, aqua::controller::BUTTON_ID::A) ||
			aqua::controller::Trigger(aqua::controller::DEVICE_ID::P2, aqua::controller::BUTTON_ID::B) ||
			aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RETURN)))
	{
		int count = 0;
		count = BlockCount(temp_block->GetID(), aqua::controller::DEVICE_ID::P2, m_P2BlockList, temp_block->GetFieldWidth(), temp_block->GetFieldHeight(), 0);
		if (count >= 2)
		{
			m_CurrentVanishedBlocksP2 = count;
			m_Data->SetVanishedBonus(aqua::controller::DEVICE_ID::P2, count);
			ComparisonID(aqua::controller::DEVICE_ID::P2, m_DeleteBlockArrayP2.at(0)->GetID());
			ComparisonMaxVanishedBlocks(aqua::controller::DEVICE_ID::P2);
			AddTotalVanishedBlocks(aqua::controller::DEVICE_ID::P2);
		}
		else if (count == 1)
		{
			m_DeleteBlockArrayP2.clear();
			temp_block->SetReferenceFlag(false);
		}
	}
	//if(aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::E))
		//m_EffectManager->Create(EFFECT_ID::DEBUFF, aqua::CVector2(100.0f,100.0f));
	IGameObject::Update();
}

void CBlockManager::Draw(void)
{
	for (auto& block : m_P1BlockList)
		block->Draw();

	for (auto& block : m_P2BlockList)
		block->Draw();

	m_EffectManager->Draw();
}

void CBlockManager::Finalize(void)
{
	for (auto& block : m_P1BlockList)
	{
		block->Finalize();
		block->DeleteObject();
		AQUA_SAFE_DELETE(block);
	}

	for (auto& block : m_P2BlockList)
	{
		block->Finalize();
		block->DeleteObject();
		AQUA_SAFE_DELETE(block);
	}

	m_P1BlockList.clear();
	m_P2BlockList.clear();

}

IBlock* CBlockManager::Create(BLOCK_ID id)
{
	IBlock* block = nullptr;
	switch (id)
	{
	case BLOCK_ID::WHITE:	block = aqua::CreateGameObject<CWhiteBlock>(this);	break;
	case BLOCK_ID::BLUE:	block = aqua::CreateGameObject<CBlueBlock>(this);	break;
	case BLOCK_ID::GREEN:	block = aqua::CreateGameObject<CGreenBlock>(this);	break;
	case BLOCK_ID::PINK:	block = aqua::CreateGameObject<CPinkBlock>(this);	break;
	}
	block->SetID(id);
	return block;
}

void CBlockManager::DeleteBlock(std::list<IBlock*>& list, aqua::controller::DEVICE_ID device)
{
	using namespace aqua::controller;
	if (device == DEVICE_ID::P1)
	{
		for (auto& block : m_DeleteBlockArrayP1)
		{
			m_EffectManager->Create(EFFECT_ID::VANISH, block->GetCenterPosition());
			auto itr = std::find(list.begin(), list.end(), block);
			if (itr != list.end())
				list.erase(itr);
			block->DeleteObject();
		}
	}
	if (device == DEVICE_ID::P2)
	{
		for (auto& block : m_DeleteBlockArrayP2)
		{
			m_EffectManager->Create(EFFECT_ID::VANISH, block->GetCenterPosition());
			auto itr = std::find(list.begin(), list.end(), block);
			if (itr != list.end())
				list.erase(itr);
			block->DeleteObject();
		}
	}
}

//// 繋がっているブロックの数を数える(再起処理)
//int CBlockManager::BlockCount(
//	BLOCK_ID id, const std::vector<std::vector<IBlock*>>& array, int i, int j, int num
//)
//{
//	// 配列外参照防止
//	if (i < 0)return 0;
//	if (i >= m_block_array_height)return 0;
//	if (j < 0)return 0;
//	if (j >= m_block_array_width)return 0;
//
//	// nullチェック
//	//if (array.at(i).at(j) == nullptr)return 0;
//
//	// IDが一致しない場合に処理を終了する
//	if (array.at(i).at(j)->GetID() != id)return 0;
//
//	// 調べた後なら処理を終了する
//	if (array.at(i).at(j)->IsReferenced()) return 0;
//
//	// 調べたらフラグを立てる
//	array.at(i).at(j)->SetReferenceFlag(true);
//
//	++num;
//
//	m_DeleteBlockArray.push_back(array.at(i).at(j));
//
//	// 左を調べる
//	num += BlockCount(id, array, i, j - 1, 0);
//	// 右を調べる
//	num += BlockCount(id, array, i, j + 1, 0);
//	// 上を調べる
//	num += BlockCount(id, array, i - 1, j, 0);
//	// 下を調べる
//	num += BlockCount(id, array, i + 1, j, 0);
//
//	return num;
//}

int CBlockManager::BlockCount(BLOCK_ID b_id, aqua::controller::DEVICE_ID d_id, const std::list<IBlock*>& list, int w, int h, int num)
{
	IBlock* block = nullptr;
	for (auto& elem : list)
	{
		if (elem->GetFieldWidth() == w && elem->GetFieldHeight() == h)
			block = elem;
	}

	// nullチェック
	if (block == nullptr)return 0;

	// IDが一致しない場合に処理を終了する
	if (block->GetID() != b_id)return 0;

	// 調べた後なら処理を終了する
	if (block->IsReferenced()) return 0;

	// 調べたらフラグを立てる
	block->SetReferenceFlag(true);

	++num;

	if (d_id == aqua::controller::DEVICE_ID::P1)
		m_DeleteBlockArrayP1.push_back(block);
	if (d_id == aqua::controller::DEVICE_ID::P2)
		m_DeleteBlockArrayP2.push_back(block);

	// 左を調べる
	num += BlockCount(b_id, d_id, list, w - 1, h, 0);
	// 右を調べる
	num += BlockCount(b_id, d_id, list, w + 1, h, 0);
	// 上を調べる
	num += BlockCount(b_id, d_id, list, w, h - 1, 0);
	// 下を調べる
	num += BlockCount(b_id, d_id, list, w, h + 1, 0);

	return num;
}

void CBlockManager::BlockFall(const std::list<IBlock*>& list)
{
	for (int i = 0; i < m_block_array_height; ++i)
	{
		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			int search_w = (*it)->GetFieldWidth();
			int search_h = (*it)->GetFieldHeight() + 1;

			if (search_h >= m_block_array_height)continue;

			if (std::find_if(list.begin(), list.end(), [&](IBlock* elem)->bool
				{
					return(elem->GetFieldWidth() == search_w && elem->GetFieldHeight() == search_h);
				}) == list.end())
			{
				(*it)->SetPosition
				(
					aqua::CVector2((*it)->GetPosition().x,
						(*it)->GetPosition().y + (*it)->GetTextureHeight() * (search_h - (*it)->GetFieldHeight()))
				);
				(*it)->SetFieldPos(search_w, search_h);
			}
		}
	}
}

void CBlockManager::BlockSlide(const std::list<IBlock*>& list)
{
	std::list<int> slide_col;

	for (int x = m_block_array_width - 1; x >= 0; --x)
	{
		if (std::find_if(list.begin(), list.end(), [&](IBlock* elem)->bool
			{
				return(elem->GetFieldWidth() == x && elem->GetFieldHeight() == m_block_array_height - 1);
			}) == list.end())
			slide_col.push_back(x);
	}

	for (auto elem : slide_col)
	{
		for (auto it = list.rbegin(); it != list.rend(); ++it)
		{
			if ((*it)->GetFieldWidth() < elem)continue;
			int search_w = (*it)->GetFieldWidth() - 1;
			int search_h = (*it)->GetFieldHeight();

			(*it)->SetPosition
			(
				aqua::CVector2((*it)->GetPosition().x + (*it)->GetTextureWidth() * (search_w - (*it)->GetFieldWidth()),
					(*it)->GetPosition().y)
			);
			(*it)->SetFieldPos(search_w, search_h);
		}
	}
}

void CBlockManager::Reset(void)
{
	ClearBlockList();
	m_CurrentVanishedBlocksP1 = 0;
	m_CurrentVanishedBlocksP2 = 0;
	DeployBlocks();
}

int CBlockManager::GetVanishedBlocks(aqua::controller::DEVICE_ID id)
{
	int blocks = 0;
	switch (id)
	{
	case aqua::controller::DEVICE_ID::P1:
		blocks = m_CurrentVanishedBlocksP1;
		break;
	case aqua::controller::DEVICE_ID::P2:
		blocks = m_CurrentVanishedBlocksP2;
		break;
	}
	return blocks;
}

BLOCK_ID CBlockManager::GetCurrentVanishedBlock(aqua::controller::DEVICE_ID id)
{
	BLOCK_ID block_id = BLOCK_ID::MAX;
	switch (id)
	{
	case aqua::controller::DEVICE_ID::P1:
		if (!m_DeleteBlockArrayP1.empty())
			block_id = m_DeleteBlockArrayP1.at(0)->GetID();
		break;
	case aqua::controller::DEVICE_ID::P2:
		if (!m_DeleteBlockArrayP2.empty())
			block_id = m_DeleteBlockArrayP2.at(0)->GetID();
		break;
	}
	return block_id;
}

void CBlockManager::ComparisonID(aqua::controller::DEVICE_ID d_id, BLOCK_ID b_id)
{
	if ((int)b_id != (int)m_Data->GetPlayerID(d_id)) return;
	switch (d_id)
	{
	case aqua::controller::DEVICE_ID::P1: m_Data->SetColorBonus(d_id, (int)m_DeleteBlockArrayP1.size()); break;
	case aqua::controller::DEVICE_ID::P2: m_Data->SetColorBonus(d_id, (int)m_DeleteBlockArrayP2.size()); break;
	}
}

void CBlockManager::ComparisonMaxVanishedBlocks(aqua::controller::DEVICE_ID id)
{
	switch (id)
	{
	case aqua::controller::DEVICE_ID::P1:
		if (m_Data->GetMaxVanishedBlocks(id) < m_CurrentVanishedBlocksP1)
			m_Data->SetMaxVanishedBlocks(id, m_CurrentVanishedBlocksP1);
		break;
	case aqua::controller::DEVICE_ID::P2:
		if (m_Data->GetMaxVanishedBlocks(id) < m_CurrentVanishedBlocksP2)
			m_Data->SetMaxVanishedBlocks(id, m_CurrentVanishedBlocksP2);
		break;
	}
}

void CBlockManager::AddTotalVanishedBlocks(aqua::controller::DEVICE_ID id)
{
	switch (id)
	{
	case aqua::controller::DEVICE_ID::P1:
		m_Data->SetTotalVanishedBlocks(id, (int)m_DeleteBlockArrayP1.size());
		break;
	case aqua::controller::DEVICE_ID::P2:
		m_Data->SetTotalVanishedBlocks(id, (int)m_DeleteBlockArrayP2.size());
		break;
	}
}

void CBlockManager::DeployBlocks(void)
{
	for (int h = 0; h < m_block_array_height; ++h)
	{
		for (int w = 0; w < m_block_array_width; ++w)
		{
			IBlock* block;
			block = Create((BLOCK_ID)DxLib::GetRand((int)BLOCK_ID::MAX - 1));
			if (block == nullptr) return;
			block->SetPosition(aqua::CVector2(
				m_field_pos_p1.x + block->GetTextureWidth() * w,
				m_field_pos_p1.y + block->GetTextureHeight() * h));
			block->SetFieldPos(w, h);
			block->Update();
			m_P1BlockList.push_back(block);

			IBlock* block2;
			block2 = Create(block->GetID());
			if (block2 == nullptr) return;
			block2->SetPosition(aqua::CVector2(
				m_field_pos_p2.x + block2->GetTextureWidth() * w,
				m_field_pos_p2.y + block2->GetTextureHeight() * h));
			block2->SetFieldPos(w, h);
			block2->Update();
			m_P2BlockList.push_back(block2);
		}
	}

	/*IBlock* block;
	block = Create(BLOCK_ID::PINK);
	block->SetPosition(aqua::CVector2(m_field_pos_p1.x))*/
}

void CBlockManager::ClearBlockList(void)
{
	for (auto& block : m_P1BlockList)
		block->DeleteObject();
	for (auto& block : m_P2BlockList)
		block->DeleteObject();
	m_P1BlockList.clear();
	m_P2BlockList.clear();
}
