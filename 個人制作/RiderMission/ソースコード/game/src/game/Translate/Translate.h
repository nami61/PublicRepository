#pragma once

#include "aqua.h"

enum class DIRECTION_MODE
{
	LINEAR,
	IN_QUAD,
	OUT_QUAD,
	IN_OUT_QUAD,
	IN_CUBIC,
	OUT_CUBIC,
	IN_OUT_CUBIC,
	IN_QUART,
	OUT_QUART,
	IN_OUT_QUART,
	IN_QUINTIC,
	OUT_QUINTIC,
	IN_OUT_QUINTIC,
	IN_SINE,
	OUT_SINE,
	IN_OUT_SINE,
	IN_EXP,
	OUT_EXP,
	IN_OUT_EXP,
	IN_CIRC,
	OUT_CIRC,
	IN_OUT_CIRC,
	IN_BOUNCE,
	OUT_BOUNCE,
	IN_OUT_BOUNCE,
	IN_BACK,
	OUT_BACK,
	IN_OUT_BACK,
};

enum class FADE_ID
{
	SIN,
	COS,
};

class CTranslate :public aqua::IGameObject
{
public:
	CTranslate(aqua::IGameObject* parent);
	~CTranslate(void) = default;
	
	void Translate(float& target, const float& start, const float& end, aqua::CTimer& timer, bool roop = false, DIRECTION_MODE dir_mode = DIRECTION_MODE::LINEAR);
	
	void Translate(int& target, const int& start, const int& end, aqua::CTimer& timer, bool roop = false, DIRECTION_MODE dir_mode = DIRECTION_MODE::LINEAR);
	
	void FadeDirection(aqua::CColor& color, aqua::CTimer& timer, unsigned int min = 0, unsigned int max = 255, FADE_ID dir_mode = FADE_ID::COS);

	bool Finished(void) { return m_IsFinish; }

private:
	bool m_IsFinish;
};