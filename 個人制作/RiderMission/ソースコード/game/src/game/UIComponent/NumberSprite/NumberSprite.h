#pragma once

#include "aqua.h"

class CNumberSprite :public aqua::IGameObject
{
public:
	CNumberSprite(aqua::IGameObject* parent);
	~CNumberSprite(void) = default;

	void Create(const std::string file_name, int max_digit = 1);

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void SetValue(int value) { m_Value = value; }

	int GetValue(void) { return m_Value; }

	void SetPosition(const aqua::CVector2& pos){ m_Position = pos; }

	const aqua::CVector2& GetPosition(void){ return m_Position; }

private:
	static const int m_decimal;
	std::vector<aqua::CSprite> m_Sprites;
	int m_Value;
	aqua::CVector2 m_Position;
};