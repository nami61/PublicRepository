#pragma once

#include "../Scene.h"

class CScoreManager;
class CSoundManager;
class CEffectManager;
class CTitleLogo;
class CTranslate;

class CTitleScene :public IScene
{
public:
    CTitleScene(aqua::IGameObject* parent);
    ~CTitleScene(void) override = default;

    void Initialize(void) override;

    void Update(void) override;

    void Draw(void) override;

    void Finalize(void) override;

private:
    enum class SCENE_STATE
    {
        TITLE_IN,
        TITLE_UPDATE,
    };

    enum class CURSOR_STATE
    {
        GAME_START,
        VIEW_SCORE,
        GAME_END,
    };

    void TitleIn(void);

    void TitleUpdate(void);

    void GameStart(void);

    void ViewScore(void);

    void GameEnd(void);

    static const aqua::CVector2 m_message_pos;
    static const aqua::CVector2 m_message_space;
    static const aqua::CVector2 m_cursor_space;
    static const aqua::CVector2 m_default_title_logo_pos;
    static const int    m_message_size;
    static const float  m_cursor_animation_interval;
    aqua::CBoxPrimitive m_BackPanel;
    aqua::CBoxPrimitive m_CurrentSelectionBar; //選択するカーソルバー
    aqua::CSprite       m_BackGroundSprite;
    aqua::CLabel        m_StartMessage;
    aqua::CLabel        m_ViewScore;
    aqua::CLabel        m_EndMessage;
    aqua::CTimer        m_FadeTimer;
    aqua::CTimer        m_CursorTimer;
    aqua::CTimer        m_TranslateTimer;
    aqua::CTimer        m_ControlPanelFadeTimer;
    aqua::CTimer        m_ControlPanelWaitTimer;
    aqua::CTimer        m_ControlPanelAppearTimer;
    aqua::CSurface      m_Surface;
    aqua::CSprite       m_SurfaceSprite;
    SCENE_STATE         m_SceneState;
    CURSOR_STATE        m_State;
    CURSOR_STATE        m_CurrentState;
    bool                m_TranslateFlag;    //サーフェス用
    CScoreManager* m_CurrentScoreManager; //スコア
    CSoundManager* m_SoundManager;  // サウンド
    CEffectManager* m_EffectManager;// エフェクト
    CTitleLogo* m_TitleLogo;       // タイトルロゴUI
    aqua::CSprite m_ControlPanel;
};