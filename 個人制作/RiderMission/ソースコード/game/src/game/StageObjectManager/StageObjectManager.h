#pragma once

#include "aqua.h"
#include "StageObject/StageObjectID.h"
#include "StageObject/StageObjectCategory.h"

class IStageObject;

enum class MAP_ID
{
	START,
	FIRST,
	TO_SECOND,
	SECOND,
	TO_THIRD,
	THIRD,
	END,
};

class CStageObjectManager :public aqua::IGameObject
{
public:
	CStageObjectManager(aqua::IGameObject* parent);
	~CStageObjectManager(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Finalize(void) override;

	void Create(aqua::CVector2 pos, STAGE_OBJECT_ID id);

	void LoadMapData(void);

	void DeployStageObject(MAP_ID id);

	void PlayerCast(aqua::CVector2 p_pos, float p_vel_y, float p_width, float p_height, bool p_fall, aqua::CVector2& dest, bool& on_ground);

	bool FindGround(aqua::CVector2 p_pos, float p_width, float p_height);

	void EndMap(bool end) { m_IsEndMap = end; }

	bool IsEndGame(void) { return m_IsEndGame; }

private:
	struct STAGE_OBJECT_DATA
	{
		int x;
		int y;
		STAGE_OBJECT_ID id;
	};

	enum class MAP_DATA_PARAM
	{
		X,
		Y,
		CHAR,
	};

	using TEXT_FILE_LIST = std::vector<std::string>;
	static const TEXT_FILE_LIST m_text_file_list;
	int m_CurrentMap;
	bool m_StartDeployFlag;
	bool m_IsEndMap;
	bool m_IsEndGame;
	std::vector<std::vector<STAGE_OBJECT_DATA>> m_MapDataList;
};