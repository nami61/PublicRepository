#pragma once

/*!
 *  @file       player.h
 *  @brief      �v���C���[
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
 *  @brief      �v���C���[���z�N���X
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
     *  @brief      �R���X�g���N�^
     *
     *  @param[in]  parent  �e�I�u�W�F�N�g
     *  @param[in]	name	�I�u�W�F�N�g��
     */
    IPlayer(aqua::IGameObject* parent, const std::string& name);

    /*!
     *  @brief      �f�X�g���N�^
     */
    ~IPlayer(void) = default;

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

    /*!
     *   @brief     �ʒu�ݒ�
     */
    void        SetPosition(const aqua::CVector2& pos) { m_AnmSprite.position = m_Position = pos; }

    /*!
    *    @brief     ���S�ʒu�擾
    */
    aqua::CVector2        GetCenterPosition(void) { return m_Position + aqua::CVector2(m_AnmSprite.GetFrameWidth() / 2.0f, m_AnmSprite.GetFrameHeight() / 2.0f); }
  
    /*!
     *   @brief     �g�嗦�ݒ�
     */
    void        SetScale(const aqua::CVector2 scale) { m_AnmSprite.scale = scale; }

    /*!
     *  @brief      PLAYER_ID���擾
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
    static const int m_max_life; //! �̗͂̍ő�l
    int m_Life;                 //! �̗�
    int m_CounterValue;         //! �J�E���^�[�l
    int m_AtkDownValue;
    float m_GuardValue;
    bool m_ReadyFlag;           //! �����t���O
    aqua::CAnimationSprite m_AnmSprite;
    aqua::CVector2 m_Position;  //! �v���C���[�̈ʒu
    aqua::controller::DEVICE_ID m_DeviceID;
    PLAYER_ID m_PlayerID;
    STATE m_State;
    bool m_CounterState;
    bool m_PoisonState;
    bool m_GuardState;
    bool m_PoisonAttack;
    CEffectManager* m_EffectManager;
};