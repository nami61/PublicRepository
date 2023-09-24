#include "StageObject.h"
#include "../../Stage/Stage.h"

IStageObject::IStageObject(aqua::IGameObject* parent, const std::string& name)
	:aqua::IGameObject(parent, name, "StageObject")
{
}

void IStageObject::Initialize(void)
{
	m_Stage = (CStage*)aqua::FindGameObject("Stage");

	m_Velocity.x = m_Stage->GetStageObjectSpeed();

	m_ActiveFlag = true;

	m_Category = STAGE_OBJECT_CATEGORY::DUMMY;
}

void IStageObject::Initialize(aqua::CVector2 pos)
{
	(void)pos;
}

void IStageObject::Update(void)
{
	if (!m_ActiveFlag)
		DeleteObject();

	if (m_Velocity.x != m_Stage->GetStageObjectSpeed())
		m_Velocity.x = m_Stage->GetStageObjectSpeed();

	IGameObject::Update();
}

void IStageObject::Draw(void)
{
}

void IStageObject::Finalize(void)
{
}
