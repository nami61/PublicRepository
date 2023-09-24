#pragma once

/*!
 *  @file       select_button.h
 *  @brief      セレクトボタン
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
 *  @brief      ボタンクラス
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
	 *  @brief      コンストラクタ
	 *
	 *  @param[in]  parent  親オブジェクト
	 */
	CSelectButton(aqua::IGameObject* parent);

	/*!
	 *  @brief      デストラクタ
	 */
	~CSelectButton(void) = default;

	/*!
	 *  @brief      更新
	 */
	void        Update(void) override;

	/*!
	 *  @brief      描画
	 */
	void        Draw(void) override;

	/*!
	 *  @brief      生成
	 * 
	 *	@param[in]	position  ボタンの配置位置
	 *	@param[in]	reverse_direction  逆方向フラグ(false = 左向き)
	 */
	void        Create(aqua::CVector2 position, bool reverse_direction) ;

	void        Create(aqua::CVector2 position, bool reverse_direction, aqua::controller::DEVICE_ID device) ;

	/*!
	 *  @brief      削除
	 */
	void        Delete(void);

	/*!
	 *  @brief		入力
	 */
	bool		IsClick(void) { return m_ClickFlag; }

private:
	/*!
	 *  @brief      初期化
	 */
	void        Initialize(void) override;

	/*!
	 *  @brief      解放
	 */
	void        Finalize(void) override;

	/*!
	 *	@brief		マウスカーソルとの当たり判定
	 */
	//void		CheckHitMouse(void);

	//bool		m_HitMouseFlag;		//! マウスとの当たり判定フラグ
	//bool		m_ClickMouseFlag;	//! マウスの入力フラグ
	bool		m_ClickFlag;		//! ボタンの入力フラグ
	aqua::CSprite m_Sprite;		//! ボタンスプライト
	aqua::CVector2 m_Position;	//! ボタン位置
	aqua::controller::DEVICE_ID m_DeviceId;

};