#pragma once

/*!
 *  @file       white.h
 *  @brief      �z���C�g
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../player.h"

/*!
 *  @class      CWhite
 *
 *  @brief      �z���C�g�N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/26
 *
 *  @version    1.0
 */
class CWhite
	: public IPlayer
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 *
	 *  @param[in]  parent  �e�I�u�W�F�N�g
	 */
	CWhite(aqua::IGameObject* parent);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CWhite(void) override = default;

    /*!
     *  @brief      ������
     */
    void        Initialize(void) override;

    /*!
     *  @brief      �X�V
     */
    void        Update(void) override;

    /*!
     *  @brief      �`��
     */
    void        Draw(void) override;

    /*!
     *  @brief      ���
     */
    void        Finalize(void) override;

private:
};