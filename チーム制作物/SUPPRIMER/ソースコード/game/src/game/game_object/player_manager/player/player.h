#pragma once

/*!
 *  @file       player.h
 *  @brief      プレイヤー
 *  @author     Roi Namisato
 *  @date       2023/06/26
 *  @version    1.0
 *
 *  Copyright (c) 2013-2020, Roi Namisato. All rights reserved.
 */

#include "aqua.h"
#include "player_id.h"
#include "../../block_manager/block/block_id.h"

class CEffectManager;

/*!
 *  @class      IPlayer
 *
 *  @brief      プレイヤー仮想クラス
 *
 *  @author     Roi Namisato
 *
 *  @date       2023/06/26
 *
 *  @version    1.0
 */
class IPlayer
    : public aqua::IGameObject
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親オブジェクト
     *  @param[in]	name	オブジェクト名
     */
    IPlayer(aqua::IGameObject* parent, const std::string& name);

    /*!
     *  @brief      デストラクタ
     */
    ~IPlayer(void) = default;

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

    /*!
     *   @brief     位置設定
     */
    void        SetPosition(const aqua::CVector2& pos) { m_AnmSprite.position = m_Position = pos; }

    /*!
    *    @brief     中心位置取得
    */
    aqua::CVector2        GetCenterPosition(void) { return m_Position + aqua::CVector2(m_AnmSprite.GetFrameWidth() / 2.0f, m_AnmSprite.GetFrameHeight() / 2.0f); }
  
    /*!
     *   @brief     拡大率設定
     */
    void        SetScale(const aqua::CVector2 scale) { m_AnmSprite.scale = scale; }

    /*!
     *  @brief      PLAYER_IDを取得
     */
    PLAYER_ID   GetPlayerID(void) { return m_PlayerID; }

    void SetPlayerID(PLAYER_ID id) { m_PlayerID = id; }

    void SetDeviceID(aqua::controller::DEVICE_ID device) { m_DeviceID = device; }

    bool IsReady(void) { return m_ReadyFlag; }

    void InputReady(void) { m_ReadyFlag = !m_ReadyFlag; }

    int GetLife(void) { return m_Life; }

    int GetMaxLife(void) { return m_max_life; }

    int GetCounterValue(void) { return m_CounterValue; }

    bool GetCounterState(void) { return m_CounterState; }

    bool GetGuardState(void) { return m_GuardState; }

    bool GetPoisonState(void) { return m_PoisonState; }

    bool& GetPoisonAttack(void) { return m_PoisonAttack; }

    bool IsDead(void) { return (m_State == STATE::DEAD); }

    void Damage(int damage);

    void Damage(int damage, bool& poison_attack);

    int Counter(void);

    int Attack(int blocks, BLOCK_ID b_id, PLAYER_ID p_id);

protected:
    enum class STATE
    {
        ACTIVE,
        DEAD,
    };

    void Heal(int heal);
    static const int m_max_life; //! 体力の最大値
    int m_Life;                 //! 体力
    int m_CounterValue;         //! カウンター値
    int m_AtkDownValue;
    float m_GuardValue;
    bool m_ReadyFlag;           //! 準備フラグ
    aqua::CAnimationSprite m_AnmSprite;
    aqua::CVector2 m_Position;  //! プレイヤーの位置
    aqua::controller::DEVICE_ID m_DeviceID;
    PLAYER_ID m_PlayerID;
    STATE m_State;
    bool m_CounterState;
    bool m_PoisonState;
    bool m_GuardState;
    bool m_PoisonAttack;
    CEffectManager* m_EffectManager;
};