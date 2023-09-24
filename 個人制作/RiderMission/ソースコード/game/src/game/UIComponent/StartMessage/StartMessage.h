#pragma once

#include "aqua.h"

class CStartMessageUI :public aqua::IGameObject
{
public:
	CStartMessageUI(aqua::IGameObject* parent);
	~CStartMessageUI(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

private:
	void BarAnimation(void);

	void SpriteFadeOut(aqua::CSprite& sprite);

	enum class BAR
	{
		TOP_FIRST,
		TOP_SECOND,
		BOTTOM_FIRST,
		BOTTOM_SECOND,
		MAX,
	};

	static const aqua::CVector2 m_default_message_pos;
	static const aqua::CVector2 m_default_top_bar_pos;
	static const aqua::CVector2 m_default_bottom_bar_pos;
	static const float m_bar_animation_speed;
	static const float m_fade_limit;
	aqua::CSprite m_StartMessage;
	aqua::CSprite* m_BarSprite;
	aqua::CVector2 m_Scale;
	aqua::CTimer m_FadeTimer;
	
};