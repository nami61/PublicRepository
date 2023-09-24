#include "NumberSprite.h"

const int CNumberSprite::m_decimal = 10;

CNumberSprite::CNumberSprite(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "NumberSprite")
{
}

void CNumberSprite::Create(const std::string file_name, int max_digit)
{
	for (int i = 0; i < max_digit; ++i)
	{
		aqua::CSprite elem;
		elem.Create(file_name);
		m_Sprites.push_back(elem);
		int once_digit_width = m_Sprites.at(i).GetTextureWidth() / m_decimal;
		m_Sprites.at(i).position.x -= (float)((once_digit_width * i) - (once_digit_width * max_digit));
		m_Sprites.at(i).rect.right = once_digit_width;
	}


	m_Value = 0;

	IGameObject::Initialize();
}

void CNumberSprite::Update(void)
{
	IGameObject::Update();
}

void CNumberSprite::Draw(void)
{
	for (auto& sprite : m_Sprites)
		sprite.Draw();

	IGameObject::Draw();
}

void CNumberSprite::Finalize(void)
{
	for (auto& sprite : m_Sprites)
		sprite.Delete();

	IGameObject::Finalize();
}
