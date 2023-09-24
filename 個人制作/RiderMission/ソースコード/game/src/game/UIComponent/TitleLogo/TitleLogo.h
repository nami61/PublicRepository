#pragma once

#include "aqua.h"

class CTitleLogo :public aqua::IGameObject
{
public:
    CTitleLogo(aqua::IGameObject* parent);
    ~CTitleLogo(void) = default;

    void Initialize(void) override;

    void Update(void) override;

    void Draw(void) override;

    void Finalize(void) override;

private:
    static const aqua::CVector2 m_default_logo_pos;
    static const aqua::CVector2 m_logo_start_pos;
    static const aqua::CVector2 m_default_player_pos;
    static const aqua::CVector2 m_default_effect_pos;
    aqua::CSprite m_TitleLogo;
    aqua::CSprite m_TitleLogoShadow;
    aqua::CSprite m_Player;
    aqua::CSprite m_PlayerEffect;
    aqua::CLabel m_ClickMessage;
    aqua::CBoxPrimitive m_BackPlane;
    aqua::CTimer m_TranslateTimer;
    aqua::CTimer m_FadeTimer;
    aqua::CTimer m_RectTimer;
};