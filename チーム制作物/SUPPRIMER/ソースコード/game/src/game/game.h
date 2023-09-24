
/*!
 *  @file       game.h
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2020/04/01
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Kazuya Maruyama. All rights reserved.
 */

#pragma once

#include "aqua.h"

 /*!
  *  @class      CGame
  *
  *  @brief      ゲームクラス
  *
  *  @author     Kazuya Maruyama
  *
  *  @date       2020/04/01
  *
  *  @version    1.0
  */
class CGame final
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     */
    CGame(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CGame(void) = default;

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
    //! 画面クリアカラー
    static const unsigned int   m_clear_color;
};
