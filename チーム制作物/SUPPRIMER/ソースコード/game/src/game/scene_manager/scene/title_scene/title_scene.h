
/*!
 *  @file       title_scene.h
 *  @brief      タイトルシーン
 *  @author     Roi Namisato
 *  @date       2023/06/22
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Roi Namisato. All rights reserved.
 */

#pragma once

#include "..\scene.h"
#include "../../../game_object/player_manager/player/player_id.h"

class IPlayer;
class CPlayerManager;
class CDeviceCommonData;
class CPlayerPrev;
class CPlayerDescription;
class CBlockDirection;
class CTitleLogo;
class CBackground;
class CPlayerNumber;
class CSoundManager;

 /*!
  *  @class      CTitleScene
  *
  *  @brief      タイトルシーンクラス
  *
  *  @author     Roi Namisato
  *
  *  @date       2023/06/22
  *
  *  @version    1.0
  */
class CTitleScene
    : public IScene
{
public:
    /*!
     *  @brief      コンストラクタ
     *
     *  @param[in]  parent  親のオブジェクト
     */
    CTitleScene(aqua::IGameObject* parent);

    /*!
     *  @brief      デストラクタ
     */
    ~CTitleScene(void) = default;

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

    void        ChangeDrawPlayer(void);

private:
    enum class SELECT_BUTTON_ID
    {
        PLAYER_ONE_LEFT,
        PLAYER_ONE_RIGHT,
        PLAYER_TWO_LEFT,
        PLAYER_TWO_RIGHT,
        MAX,
    };

    static const float m_default_threshold_value;
    static const aqua::CVector2 m_p1_default_pos;
    static const aqua::CVector2 m_p2_default_pos;
    static const aqua::CVector2 m_p1_ready_pos;
    static const aqua::CVector2 m_p2_ready_pos;
    static const aqua::CVector2 m_controller_panel_pos;
    bool m_P1DecisionFlag;
    bool m_P2DecisionFlag;
    bool m_ContinuousInputP1;
    bool m_ContinuousInputP2;
    CPlayerManager* m_PlayerManager;            //! プレイヤーマネージャー
    PLAYER_ID m_CurrentIDP1;
    PLAYER_ID m_CurrentIDP2;
    CDeviceCommonData* m_CommonData;
    aqua::CSprite m_ControllerPanel;
    aqua::CSprite m_P1ReadySprite;
    aqua::CSprite m_P2ReadySprite;
    aqua::CBoxPrimitive m_P1ReadyPlane;
    aqua::CBoxPrimitive m_P2ReadyPlane;
    aqua::CTimer m_FadeTimer;
    aqua::CTimer m_ChangeDemoSceneTimer;
    CPlayerPrev* m_P1Prev;
    CPlayerPrev* m_P2Prev;
    CBlockDirection* m_BlockDirection;
    CTitleLogo* m_TitleLogo;
    CBackground* m_BG;
    CPlayerNumber* m_PlayerNumber;
    CSoundManager* m_SoundManager;
    CPlayerDescription* m_P1Description;
    CPlayerDescription* m_P2Description;
};
