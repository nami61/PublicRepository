#pragma once

/*!
 *  @file       translate.h
 *  @brief      �g�����X���[�g
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"

enum class EASING
{
	LINEAR,
	IN_QUAD,
	OUT_QUAD,
	IN_OUT_QUAD,
	IN_CUBIC,
	OUT_CUBIC,
	IN_OUT_CUBIC,
	IN_QUART,
	OUT_QUART,
	IN_OUT_QUART,
	IN_QUINTIC,
	OUT_QUINTIC,
	IN_OUT_QUINTIC,
	IN_SINE,
	OUT_SINE,
	IN_OUT_SINE,
	IN_EXP,
	OUT_EXP,
	IN_OUT_EXP,
	IN_CIRC,
	OUT_CIRC,
	IN_OUT_CIRC,
	IN_BOUNCE,
	OUT_BOUNCE,
	IN_OUT_BOUNCE,
	IN_BACK,
	OUT_BACK,
	IN_OUT_BACK,
};

enum class DIRECTION_ID
{
	SIN,
	COS,
};

 /*!
  *  @class      CTranslate
  *
  *  @brief      �g�����X���[�g�N���X
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/06/26
  *
  *  @version    1.0
  */
class CTranslate :public aqua::IGameObject
{
public:
	CTranslate(aqua::IGameObject* parent);
	~CTranslate(void) = default;
	
	/*!
	 *  @brief  �C�[�W���O���g�����l�̕ύX<br>
	 *			float�p
	 * 
	 *  @param[in]  target  �ύX���������Ώ�
	 *  @param[in]  start   �����l
	 *  @param[in]  end     �ŏI�l
	 *  @param[in]  timer   ����
	 *  @param[in]  roop    ���[�v���邩
	 *  @param[in]  EASING  �K������C�[�W���O
	 */
	void Translate(float& target, const float& start, const float& end, aqua::CTimer& timer, bool roop = false, EASING dir_mode = EASING::LINEAR);
	
	/*!
	 *  @brief  �C�[�W���O���g�����l�̕ύX<br>
	 *			int�p
	 *
	 *  @param[in]  target  �ύX���������Ώ�
	 *  @param[in]  start   �����l
	 *  @param[in]  end     �ŏI�l
	 *  @param[in]  timer   ����
	 *  @param[in]  roop    ���[�v���邩
	 *  @param[in]  EASING  �K������C�[�W���O
	 */
	void Translate(int& target, const int& start, const int& end, aqua::CTimer& timer, bool roop = false, EASING dir_mode = EASING::LINEAR);
	
	void FadeDirection(aqua::CColor& color, aqua::CTimer& timer, unsigned int min = 0, unsigned int max = 255, DIRECTION_ID dir_mode = DIRECTION_ID::COS);

	bool Finished(void) { return m_IsFinish; }

private:
	bool m_IsFinish;
};