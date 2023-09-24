#pragma once

/*!
 *  @file       green.h
 *  @brief      �O���[��
 *  @author     Roi Namisato
 *  @date       2023/06/27
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "../player.h"

/*!
 *  @class      CGreen
 *
 *  @brief      �O���[���N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/27
 *
 *  @version    1.0
 */
class CGreen
    : public IPlayer
{
public:
    /*!
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     */
    CGreen(aqua::IGameObject* parent);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~CGreen(void) override = default;

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