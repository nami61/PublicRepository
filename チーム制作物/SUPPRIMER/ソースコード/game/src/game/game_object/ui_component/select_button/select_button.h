#pragma once

/*!
 *  @file       select_button.h
 *  @brief      �Z���N�g�{�^��
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

/*!
 *  @class      CSelectButton
 *
 *  @brief      �{�^���N���X
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/26
 *
 *  @version    1.0
 */
class CSelectButton
	: public aqua::IGameObject
{
public:
	/*!
	 *  @brief      �R���X�g���N�^
	 *
	 *  @param[in]  parent  �e�I�u�W�F�N�g
	 */
	CSelectButton(aqua::IGameObject* parent);

	/*!
	 *  @brief      �f�X�g���N�^
	 */
	~CSelectButton(void) = default;

	/*!
	 *  @brief      �X�V
	 */
	void        Update(void) override;

	/*!
	 *  @brief      �`��
	 */
	void        Draw(void) override;

	/*!
	 *  @brief      ����
	 * 
	 *	@param[in]	position  �{�^���̔z�u�ʒu
	 *	@param[in]	reverse_direction  �t�����t���O(false = ������)
	 */
	void        Create(aqua::CVector2 position, bool reverse_direction) ;

	void        Create(aqua::CVector2 position, bool reverse_direction, aqua::controller::DEVICE_ID device) ;

	/*!
	 *  @brief      �폜
	 */
	void        Delete(void);

	/*!
	 *  @brief		����
	 */
	bool		IsClick(void) { return m_ClickFlag; }

private:
	/*!
	 *  @brief      ������
	 */
	void        Initialize(void) override;

	/*!
	 *  @brief      ���
	 */
	void        Finalize(void) override;

	/*!
	 *	@brief		�}�E�X�J�[�\���Ƃ̓����蔻��
	 */
	//void		CheckHitMouse(void);

	//bool		m_HitMouseFlag;		//! �}�E�X�Ƃ̓����蔻��t���O
	//bool		m_ClickMouseFlag;	//! �}�E�X�̓��̓t���O
	bool		m_ClickFlag;		//! �{�^���̓��̓t���O
	aqua::CSprite m_Sprite;		//! �{�^���X�v���C�g
	aqua::CVector2 m_Position;	//! �{�^���ʒu
	aqua::controller::DEVICE_ID m_DeviceId;

};