#pragma once

/*!
 *  @file       title_logo.h
 *  @brief      �^�C�g�����S
 *  @author     Roi Namisato
 *  @date       2023/06/24
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h" 

/*!
 *  @class      CTitleLogo
 *
 *  @brief      �^�C�g�����S�N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/24
 *
 *  @version    1.0
 */
class CTitleLogo 
    : public aqua::IGameObject
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 *
	 *  @param[in]  parent  �e�I�u�W�F�N�g
	 */
	CTitleLogo(aqua::IGameObject* parent);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CTitleLogo(void) = default;

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
    static const aqua::CVector2 m_default_sprite_position;  //! ���S�̏����ʒu
    static const aqua::CVector2 m_default_message_position; //! ���b�Z�[�W�̏����ʒu
    aqua::CBoxPrimitive m_Plane;
    aqua::CSprite m_Sprite;         //! ���S�̃X�v���C�g
    aqua::CSprite m_StartMessage;   //! �X�^�[�g���b�Z�[�W
    //aqua::CVector2 m_Position     //! ���S�̈ʒu
};