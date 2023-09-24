#pragma once

#include "aqua.h"
#include "StageObjectCategory.h"

class CStage;

class IStageObject :public aqua::IGameObject
{
public:
	IStageObject(aqua::IGameObject* parent, const std::string& name);
	virtual ~IStageObject(void) = default;

	void Initialize(void) override;

	virtual void Initialize(aqua::CVector2 pos);

	virtual void Update(void) override;

	virtual void Draw(void) override;

	virtual void Finalize(void) override;

	aqua::CVector2 GetPosition(void) { return m_Position; }

	aqua::CVector2 GetSize(void) { return m_Size; }

	bool IsActive(void) { return m_ActiveFlag; }

	STAGE_OBJECT_CATEGORY GetObjectCategory(void) { return m_Category; }

protected:
	aqua::CVector2 m_Position;
	aqua::CVector2 m_Velocity;
	aqua::CVector2 m_Size;
	bool m_ActiveFlag;
	STAGE_OBJECT_CATEGORY m_Category;
	CStage* m_Stage;
};