#pragma once

/*!
 *  @file       player_manager.h
 *  @brief      プレイヤーマネージャー
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "player/player.h"
#include "player/player_id.h"

/*!
 *  @class      CPlayerManager
 *
 *  @brief      プレイヤー管理クラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/26
 *
 *  @version    1.0
 */
class CPlayerManager
	: public aqua::IGameObject
{
public:
	/*!
	 *  @brief      コンストラクタ
	 *
	 *  @param[in]  parent  親オブジェクト
	 */
	CPlayerManager(aqua::IGameObject* parent);

	/*!
	 *  @brief      デストラクタ
	 */
	~CPlayerManager(void) = default;

    /*!
     *  @brief      更新
     */
    void        Update(void) override;

    /*!
     *  @brief      解放
     */
    void        Finalize(void) override;

    /*!
     *  @brief      生成
     * 
     *  @param[in]  id  プレイヤーID
     */
    IPlayer*        Create(PLAYER_ID p_id, aqua::controller::DEVICE_ID d_id);

private:
    static const aqua::CVector2 p_one_pos; //! プレイヤー位置
    static const aqua::CVector2 p_two_pos; //! プレイヤー位置
};