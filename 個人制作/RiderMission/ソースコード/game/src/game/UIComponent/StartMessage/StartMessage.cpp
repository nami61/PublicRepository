#include "StartMessage.h"

const aqua::CVector2 CStartMessageUI::m_default_message_pos = aqua::CVector2(120.0f, 100.0f);
const aqua::CVector2 CStartMessageUI::m_default_top_bar_pos = aqua::CVector2(0.0f, 0.0f);
const aqua::CVector2 CStartMessageUI::m_default_bottom_bar_pos = aqua::CVector2(0.0f, 600.0f);
const float CStartMessageUI::m_bar_animation_speed = 5.0f;
const float CStartMessageUI::m_fade_limit = 7.0f;

CStartMessageUI::CStartMessageUI(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "StartMessageUI")
{
}

void CStartMessageUI::Initialize(void)
{
	m_StartMessage.Create("data/texture/start_message.png");
	m_StartMessage.position = m_default_message_pos;

	int maxSprite = (int)BAR::MAX;
	m_BarSprite = AQUA_NEW aqua::CSprite[maxSprite];
	for (int spriteNumber = 0; spriteNumber < maxSprite; ++spriteNumber)
		m_BarSprite[spriteNumber].Create("data/texture/start_message_bar.png");

	m_BarSprite[(int)BAR::TOP_FIRST].position = m_default_top_bar_pos;
	m_BarSprite[(int)BAR::BOTTOM_FIRST].position = m_default_bottom_bar_pos;
	m_BarSprite[(int)BAR::BOTTOM_SECOND].position.y = m_default_bottom_bar_pos.y;

	m_FadeTimer.Setup(m_fade_limit);
}

void CStartMessageUI::Update(void)
{
	SpriteFadeOut(m_StartMessage);

	BarAnimation();
}

void CStartMessageUI::Draw(void)
{
	m_StartMessage.Draw();

	for (int spriteNumber = 0; spriteNumber < (int)BAR::MAX; ++spriteNumber)
		m_BarSprite[spriteNumber].Draw();
}

void CStartMessageUI::Finalize(void)
{
	m_StartMessage.Delete();

	//for (int spriteNumber = 0; spriteNumber < (int)BAR::MAX; ++spriteNumber)
		//m_BarSprite[spriteNumber].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_BarSprite);
}

void CStartMessageUI::BarAnimation(void)
{
	float edgeScreenTop = (float)(-m_BarSprite[(int)BAR::TOP_FIRST].GetTextureWidth());
	float edgeScreenBottom = (float)m_BarSprite[(int)BAR::BOTTOM_FIRST].GetTextureWidth();
	float barWidth = (float)m_BarSprite[(int)BAR::TOP_FIRST].GetTextureWidth();

	if (m_BarSprite[(int)BAR::TOP_FIRST].position.x <= edgeScreenTop)
		m_BarSprite[(int)BAR::TOP_FIRST].position.x = m_default_top_bar_pos.x;
	if (m_BarSprite[(int)BAR::BOTTOM_FIRST].position.x >= edgeScreenBottom)
		m_BarSprite[(int)BAR::BOTTOM_FIRST].position.x = m_default_bottom_bar_pos.x;

	m_BarSprite[(int)BAR::TOP_FIRST].position.x -= m_bar_animation_speed;
	m_BarSprite[(int)BAR::TOP_SECOND].position.x = m_BarSprite[(int)BAR::TOP_FIRST].position.x + barWidth;

	m_BarSprite[(int)BAR::BOTTOM_FIRST].position.x += m_bar_animation_speed;
	m_BarSprite[(int)BAR::BOTTOM_SECOND].position.x = m_BarSprite[(int)BAR::BOTTOM_FIRST].position.x - barWidth;

	for (int spriteNumber = 0; spriteNumber < (int)BAR::MAX; ++spriteNumber)
		SpriteFadeOut(m_BarSprite[spriteNumber]);
}

void CStartMessageUI::SpriteFadeOut(aqua::CSprite& sprite)
{
	m_FadeTimer.Update();

	float alpha = 255.0f - (aqua::easing::InCirc(m_FadeTimer.GetTime(), m_FadeTimer.GetLimit()) * 255.0f);
	sprite.color.alpha = (unsigned char)alpha;

	if (m_FadeTimer.Finished())
		return;
}
