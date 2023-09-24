#pragma once

/*!
 *  @file       pink.h
 *  @brief      �s���N
 *  @author     Roi Namisato
 *  @date       2023/06/27
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../player.h"

/*!
 *  @class      CPink
 *
 *  @brief      �s���N�N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/27
 *
 *  @version    1.0
 */
class CPink
	: public IPlayer 
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     * 
     *  @param[in]  parent  �e�I�u�W�F�N�g
     */
	CPink(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
	~CPink(void) override = default;

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
};