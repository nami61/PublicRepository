#pragma once

/*!
 *  @file       block_manager.h
 *  @brief      �u���b�N�Ǘ�
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
 *  @brief      �u���b�N�}�l�[�W���[�N���X
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
	 *  @brief      �R���X�g���N�^
	 *
	 *  @param[in]  parent  �e�I�u�W�F�N�g
	 */
	CBlockManager(aqua::IGameObject* parent);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CBlockManager(void) = default;

	/*!
	 *  @brief      ������
	 */
	void Initialize(CCursor* cursor1, CCursor* cursor2);

	/*!
	 *  @brief      �X�V
	 */
	void Update(void)		override;

	/*!
	 *  @brief      �`��
	 */
	void Draw(void)			override;

	/*!
	 *  @brief      ���
	 */
	void Finalize(void)		override;

	/*!
	 *  @brief      ����
	 * 
	 *  @param[in]  id   �u���b�NID
	 */
	IBlock* Create(BLOCK_ID id);

	/*!
	 *  @brief      �u���b�N�폜
	 * 
	 *  @param[in]  list  �u���b�N���X�g
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

	static const int m_block_array_width;		//!< ���̃u���b�N��
	static const int m_block_array_height;		//!< �c�̃u���b�N��

	static const aqua::CVector2 m_field_pos_p1;			//!< 1P�u���b�N�g�̈ʒu
	static const aqua::CVector2 m_field_pos_p2;			//!< 2P�u���b�N�g�̈ʒu

	int m_CurrentVanishedBlocksP1;
	int m_CurrentVanishedBlocksP2;

	std::list<IBlock*> m_P1BlockList;		//���������u���b�N�̃��X�g
	std::list<IBlock*> m_P2BlockList;		//���������u���b�N�̃��X�g

	std::vector<IBlock*>				m_DeleteBlockArrayP1;
	std::vector<IBlock*>				m_DeleteBlockArrayP2;

	CCursor* m_CursorP1;
	CCursor* m_CursorP2;
	CDeviceCommonData* m_Data;
	CEffectManager* m_EffectManager;
};