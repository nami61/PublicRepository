#include "controller_stick_operation.h"

CControllerStickOperation::CControllerStickOperation(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "ControllerStickOperation")
	, m_Stick{}
	, m_StickPreview{}
{
}

void CControllerStickOperation::Update(void)
{
	using namespace aqua::controller;
	for (int i = 0; i < (int)DEVICE_ID::MAX; ++i)
	{
		m_StickPreview[i] = m_Stick[i];

		m_Stick[i] = GetAnalogStickLeft((DEVICE_ID)i);
	}
}

bool CControllerStickOperation::StickTriggerLeft(aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction, float threshold)
{
	switch (direction)
	{
	case aqua::controller::STICK_DIRECTION::LEFT:
		return (m_Stick[(int)device].x <= -threshold) && (m_StickPreview[(int)device].x > -threshold);
	case aqua::controller::STICK_DIRECTION::RIGHT:
		return (m_Stick[(int)device].x >= threshold) && (m_StickPreview[(int)device].x < threshold);
	case aqua::controller::STICK_DIRECTION::UP:
		return (m_Stick[(int)device].y <= -threshold) && (m_StickPreview[(int)device].y > -threshold);
	case aqua::controller::STICK_DIRECTION::DOWN:
		return (m_Stick[(int)device].y >= threshold) && (m_StickPreview[(int)device].y < threshold);
	}
	return false;
}

bool CControllerStickOperation::StickButtonLeft(aqua::controller::DEVICE_ID device, aqua::controller::STICK_DIRECTION direction, float threshold)
{
	switch (direction)
	{
	case aqua::controller::STICK_DIRECTION::LEFT:
		return (m_Stick[(int)device].x <= -threshold);
	case aqua::controller::STICK_DIRECTION::RIGHT:
		return (m_Stick[(int)device].x >= threshold);
	case aqua::controller::STICK_DIRECTION::UP:
		return (m_Stick[(int)device].y <= -threshold);
	case aqua::controller::STICK_DIRECTION::DOWN:
		return (m_Stick[(int)device].y >= threshold);
	}
	return false;
}

bool CControllerStickOperation::StickTriggerLeftAll(aqua::controller::DEVICE_ID device, float threshold)
{
	using namespace aqua::controller;
	return (
		StickTriggerLeft(device, STICK_DIRECTION::LEFT, threshold) ||
		StickTriggerLeft(device, STICK_DIRECTION::RIGHT, threshold) ||
		StickTriggerLeft(device, STICK_DIRECTION::UP, threshold) ||
		StickTriggerLeft(device, STICK_DIRECTION::DOWN, threshold));
}
