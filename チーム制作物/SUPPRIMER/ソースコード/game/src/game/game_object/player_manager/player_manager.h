#pragma once

/*!
 *  @file       player_manager.h
 *  @brief      �v���C���[�}�l�[�W���[
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "player/player.h"
#include "player/player_id.h"

/*!
 *  @class      CPlayerManager
 *
 *  @brief      �v���C���[�Ǘ��N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/26
 *
 *  @version    1.0
 */
class CPlayerManager
	: public aqua::IGameObject
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 *
	 *  @param[in]  parent  �e�I�u�W�F�N�g
	 */
	CPlayerManager(aqua::IGameObject* parent);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CPlayerManager(void) = default;

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

    /*!
     *  @brief      ����
     * 
     *  @param[in]  id  �v���C���[ID
     */
    IPlayer*        Create(PLAYER_ID p_id, aqua::controller::DEVICE_ID d_id);

private:
    static const aqua::CVector2 p_one_pos; //! �v���C���[�ʒu
    static const aqua::CVector2 p_two_pos; //! �v���C���[�ʒu
};