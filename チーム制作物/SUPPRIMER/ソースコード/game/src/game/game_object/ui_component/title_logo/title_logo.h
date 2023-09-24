#pragma once

/*!
 *  @file       title_logo.h
 *  @brief      タイトルロゴ
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
 *  @brief      タイトルロゴクラス
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
	 *  @brief      コンストラクタ
	 *
	 *  @param[in]  parent  親オブジェクト
	 */
	CTitleLogo(aqua::IGameObject* parent);

	/*!
	 *  @brief      デストラクタ
	 */
	~CTitleLogo(void) = default;

    /*!
     *  @brief      初期化
     */
    void        Initialize(void) override;

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      描画
     */
    void        Draw(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

private:
    static const aqua::CVector2 m_default_sprite_position;  //! ロゴの初期位置
    static const aqua::CVector2 m_default_message_position; //! メッセージの初期位置
    aqua::CBoxPrimitive m_Plane;
    aqua::CSprite m_Sprite;         //! ロゴのスプライト
    aqua::CSprite m_StartMessage;   //! スタートメッセージ
    //aqua::CVector2 m_Position     //! ロゴの位置
};