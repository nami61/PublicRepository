#include "Translate.h"

CTranslate::CTranslate(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Translate")
	, m_IsFinish(false)
{
}

void CTranslate::Translate(float& target, const float& start, const float& end, aqua::CTimer& timer, bool roop, DIRECTION_MODE dir_mode)
{
	static const float distance = start - end;
	static const float back_value = distance / 2.0f;
	float current_distance = end - target;

	if (m_IsFinish && roop)
	{
		target = start;
		m_IsFinish = false;
		timer.Reset();
	}

	timer.Update();
	if (timer.Finished())
	{
		target = end;
		m_IsFinish = true;
		return;
	}

	float result = 0.0f;
	switch (dir_mode)
	{
	case DIRECTION_MODE::LINEAR:
		result = aqua::easing::Linear(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUAD:
		result = aqua::easing::InQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUAD:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUAD:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_CUBIC:
		result = aqua::easing::InCubic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_CUBIC:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_CUBIC:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUART:
		result = aqua::easing::InQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUART:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUART:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUINTIC:
		result = aqua::easing::InQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUINTIC:
		result = aqua::easing::OutQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUINTIC:
		result = aqua::easing::InOutQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_SINE:
		result = aqua::easing::InSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_SINE:
		result = aqua::easing::OutSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_SINE:
		result = aqua::easing::InOutSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_EXP:
		result = aqua::easing::InExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_EXP:
		result = aqua::easing::OutExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_EXP:
		result = aqua::easing::InOutExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_CIRC:
		result = aqua::easing::InCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_CIRC:
		result = aqua::easing::OutCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_CIRC:
		result = aqua::easing::InOutCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_BOUNCE:
		result = aqua::easing::InBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::OUT_BOUNCE:
		result = aqua::easing::OutBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_BOUNCE:
		result = aqua::easing::InOutBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_BACK:
		result = aqua::easing::InBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::OUT_BACK:
		result = aqua::easing::OutBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_BACK:
		result = aqua::easing::InOutBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	}

	target += result;
}

void CTranslate::Translate(int& target, const int& start, const int& end, aqua::CTimer& timer, bool roop, DIRECTION_MODE dir_mode)
{
	static const float distance = (float)(start - end);
	static const float back_value = distance / 2.0f;
	static const float epsilon = distance * 0.005f;
	float current_distance = (float)(end - target);

	if (m_IsFinish && roop)
	{
		target = start;
		m_IsFinish = false;
		timer.Reset();
	}

	timer.Update();

	timer.Update();
	if (timer.Finished() || current_distance <= epsilon)
	{
		target = end;
		m_IsFinish = true;
		return;
	}

	float result = 0.0f;
	switch (dir_mode)
	{
	case DIRECTION_MODE::LINEAR:
		result = aqua::easing::Linear(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUAD:
		result = aqua::easing::InQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUAD:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUAD:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_CUBIC:
		result = aqua::easing::InCubic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_CUBIC:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_CUBIC:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUART:
		result = aqua::easing::InQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUART:
		result = aqua::easing::OutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUART:
		result = aqua::easing::InOutQuad(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_QUINTIC:
		result = aqua::easing::InQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_QUINTIC:
		result = aqua::easing::OutQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_QUINTIC:
		result = aqua::easing::InOutQuintic(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_SINE:
		result = aqua::easing::InSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_SINE:
		result = aqua::easing::OutSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_SINE:
		result = aqua::easing::InOutSine(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_EXP:
		result = aqua::easing::InExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_EXP:
		result = aqua::easing::OutExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_EXP:
		result = aqua::easing::InOutExp(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_CIRC:
		result = aqua::easing::InCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::OUT_CIRC:
		result = aqua::easing::OutCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_CIRC:
		result = aqua::easing::InOutCirc(timer.GetTime(), timer.GetLimit(), 0.0f, current_distance);
		break;
	case DIRECTION_MODE::IN_BOUNCE:
		result = aqua::easing::InBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::OUT_BOUNCE:
		result = aqua::easing::OutBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_BOUNCE:
		result = aqua::easing::InOutBounce(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_BACK:
		result = aqua::easing::InBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::OUT_BACK:
		result = aqua::easing::OutBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	case DIRECTION_MODE::IN_OUT_BACK:
		result = aqua::easing::InOutBack(timer.GetTime(), timer.GetLimit(), back_value, current_distance);
		break;
	}

	target += (int)result;
}

void CTranslate::FadeDirection(aqua::CColor& color, aqua::CTimer& timer, unsigned int min, unsigned int max, FADE_ID dir_mode)
{
	if (max > 255) max = 255;

	timer.Update();
	if (timer.Finished())
		timer.Reset();
	float angle = (timer.GetTime() / timer.GetLimit()) * 360.0f;

	switch (dir_mode)
	{
	case FADE_ID::SIN:
		color.alpha = (unsigned char)min + (unsigned char)abs(sinf(aqua::DegToRad(angle)) * (float)(max - min));
		break;
	case FADE_ID::COS:
		color.alpha = (unsigned char)min + (unsigned char)abs(cosf(aqua::DegToRad(angle)) * (float)(max - min));
		break;
	}
}

