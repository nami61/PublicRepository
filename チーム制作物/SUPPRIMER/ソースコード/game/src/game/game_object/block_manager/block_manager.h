#pragma once

/*!
 *  @file       block_manager.h
 *  @brief      ブロック管理
 *  @author     Takami Shimizu
 *  @date       2023/07/23
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Takami Shimizu. All rights reserved.
 */

#include "aqua.h"
#include "block/block.h"

class IBlock;
class CCursor;
class CDeviceCommonData;
class CEffectManager;

/*!
 *  @class      CBlockManager
 *
 *  @brief      ブロックマネージャークラス
 *
 *  @author     Takami Shimizu
 *
 *  @date       2020/07/23
 *
 *  @version    1.0
 */

class CBlockManager :public aqua::IGameObject
{
public:
	/*!
	 *  @brief      コンストラクタ
	 *
	 *  @param[in]  parent  親オブジェクト
	 */
	CBlockManager(aqua::IGameObject* parent);

	/*!
	 *  @brief      デストラクタ
	 */
	~CBlockManager(void) = default;

	/*!
	 *  @brief      初期化
	 */
	void Initialize(CCursor* cursor1, CCursor* cursor2);

	/*!
	 *  @brief      更新
	 */
	void Update(void)		override;

	/*!
	 *  @brief      描画
	 */
	void Draw(void)			override;

	/*!
	 *  @brief      解放
	 */
	void Finalize(void)		override;

	/*!
	 *  @brief      生成
	 * 
	 *  @param[in]  id   ブロックID
	 */
	IBlock* Create(BLOCK_ID id);

	/*!
	 *  @brief      ブロック削除
	 * 
	 *  @param[in]  list  ブロックリスト
	 */
	void	DeleteBlock(std::list<IBlock*>&, aqua::controller::DEVICE_ID device);
//	int		BlockCount(BLOCK_ID id, const std::vector<std::vector<IBlock*>>& array, int i, int j, int num);
	int		BlockCount(BLOCK_ID b_id, aqua::controller::DEVICE_ID d_id, const std::list<IBlock*>& list, int w, int h, int num);
	void	BlockFall(const std::list<IBlock*>& list);
	void	BlockSlide(const std::list<IBlock*>& list);
	void	Reset(void);
	int		GetVanishedBlocks(aqua::controller::DEVICE_ID id);
	BLOCK_ID GetCurrentVanishedBlock(aqua::controller::DEVICE_ID id);

private:
	void    ComparisonID(aqua::controller::DEVICE_ID d_id, BLOCK_ID b_id);
	void	ComparisonMaxVanishedBlocks(aqua::controller::DEVICE_ID id);
	void	AddTotalVanishedBlocks(aqua::controller::DEVICE_ID id);
	void	DeployBlocks(void);
	void	ClearBlockList(void);

	static const int m_block_array_width;		//!< 横のブロック数
	static const int m_block_array_height;		//!< 縦のブロック数

	static const aqua::CVector2 m_field_pos_p1;			//!< 1Pブロック枠の位置
	static const aqua::CVector2 m_field_pos_p2;			//!< 2Pブロック枠の位置

	int m_CurrentVanishedBlocksP1;
	int m_CurrentVanishedBlocksP2;

	std::list<IBlock*> m_P1BlockList;		//生成したブロックのリスト
	std::list<IBlock*> m_P2BlockList;		//生成したブロックのリスト

	std::vector<IBlock*>				m_DeleteBlockArrayP1;
	std::vector<IBlock*>				m_DeleteBlockArrayP2;

	CCursor* m_CursorP1;
	CCursor* m_CursorP2;
	CDeviceCommonData* m_Data;
	CEffectManager* m_EffectManager;
};