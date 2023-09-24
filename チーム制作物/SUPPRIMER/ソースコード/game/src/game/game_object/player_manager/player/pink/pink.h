#pragma once

/*!
 *  @file       pink.h
 *  @brief      ピンク
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
 *  @brief      ピンククラス
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
     *  @brief      コンストラクタ
     * 
     *  @param[in]  parent  親オブジェクト
     */
	CPink(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
	~CPink(void) override = default;

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
};