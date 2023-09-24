#include "End.h"
#include "../../StageObjectManager.h"

CEnd::CEnd(aqua::IGameObject* parent)
	:IStageObject(parent, "End")
{
}

void CEnd::Initialize(aqua::CVector2 pos)
{
	m_StageObjectManager = (CStageObjectManager*)aqua::FindGameObject("StageObjectManager");
	m_Position = pos;
	m_IsAppear = false;
	m_Category = STAGE_OBJECT_CATEGORY::EMPTY;
	IStageObject::Initialize();
}

void CEnd::Update(void)
{
	if (m_Position.x < (float)aqua::GetWindowWidth() + 10.0f)
	{
		m_StageObjectManager->EndMap(true);
		m_ActiveFlag = false;
	}

	m_Position.x -= m_Velocity.x;
	if (m_Position.x < (float)aqua::GetWindowWidth() + 64.0f)
		m_IsAppear = true;

	IStageObject::Update();
}

void CEnd::Draw(void)
{
}

void CEnd::Finalize(void)
{
}
