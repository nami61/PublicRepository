#include <fstream>
#include "StageObjectManager.h"
#include "../Collision/Collision.h"
#include "StageObject/Turf/Turf.h"
#include "StageObject/Fire/Fire.h"
#include "StageObject/Coin/Coin.h"
#include "StageObject/End/End.h"

const CStageObjectManager::TEXT_FILE_LIST CStageObjectManager::m_text_file_list
{
	"data/map_data/start.txt",
	"data/map_data/first.txt",
	"data/map_data/to_second.txt",
	"data/map_data/second.txt",
	"data/map_data/to_third.txt",
	"data/map_data/third.txt",
	"data/map_data/end.txt",
};

CStageObjectManager::CStageObjectManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "StageObjectManager")
{
}

void CStageObjectManager::Initialize(void)
{
	LoadMapData();
	m_CurrentMap = 0;
	m_IsEndMap = false;
	m_IsEndGame = false;
	m_StartDeployFlag = false;
	IGameObject::Initialize();
}

void CStageObjectManager::Update(void)
{
	if (!m_StartDeployFlag)
	{
		DeployStageObject(MAP_ID::START);
		m_StartDeployFlag = true;
	}

	if (m_IsEndMap)
	{
		m_IsEndMap = false;
		++m_CurrentMap;
		if (m_CurrentMap == m_text_file_list.size())
			m_IsEndGame = true;
		else
			DeployStageObject((MAP_ID)m_CurrentMap);
	}

	IGameObject::Update();
}

void CStageObjectManager::Finalize(void)
{
	IGameObject::Finalize();
}

void CStageObjectManager::Create(aqua::CVector2 pos, STAGE_OBJECT_ID id)
{
	IStageObject* stage_obj = nullptr;

	switch (id)
	{
	case STAGE_OBJECT_ID::NONE: break;
	case STAGE_OBJECT_ID::TURF: stage_obj = aqua::CreateGameObject<CTurf>(this); break;
	case STAGE_OBJECT_ID::COIN:	stage_obj = aqua::CreateGameObject<CCoin>(this); break;
	case STAGE_OBJECT_ID::FIRE:	stage_obj = aqua::CreateGameObject<CFire>(this); break;
	case STAGE_OBJECT_ID::END: stage_obj = aqua::CreateGameObject<CEnd>(this); break;
	}

	if (stage_obj == nullptr) return;

	stage_obj->Initialize(pos);
	stage_obj->Update();
}

void CStageObjectManager::LoadMapData(void)
{
	for (int fileNumber = 0; fileNumber < m_text_file_list.size(); ++fileNumber)
	{
		std::vector<std::vector<std::tuple<int, int, char>>> textData;
		std::string line;
		std::fstream file(m_text_file_list.at(fileNumber));
		int row = 0;
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				std::vector<std::tuple<int, int, char>> mapRow;
				for (int col = 0; col < line.size(); ++col)
				{
					mapRow.push_back(std::make_tuple(col, row, line[col]));
				}
				textData.push_back(mapRow);
				++row;
			}
			file.close();
		}

		std::vector<STAGE_OBJECT_DATA> map;
		for (const auto& mapRow : textData)
		{
			for (const auto& element : mapRow)
			{
				STAGE_OBJECT_DATA data;
				data.x = std::get<(int)MAP_DATA_PARAM::X>(element);
				data.y = std::get<(int)MAP_DATA_PARAM::Y>(element);
				switch (std::get<(int)MAP_DATA_PARAM::CHAR>(element))
				{
				case ' ': data.id = STAGE_OBJECT_ID::NONE; break;
				case '#': data.id = STAGE_OBJECT_ID::TURF; break;
				case 'C': data.id = STAGE_OBJECT_ID::COIN; break;
				case 'F': data.id = STAGE_OBJECT_ID::FIRE; break;
				case 'E': data.id = STAGE_OBJECT_ID::END; break;
				}
				map.push_back(data);
			}
		}
		m_MapDataList.push_back(map);
	}
}

void CStageObjectManager::DeployStageObject(MAP_ID id)
{
	std::vector<STAGE_OBJECT_DATA> mapData;

	switch (id)
	{
	case MAP_ID::START: mapData = m_MapDataList.at((int)MAP_ID::START); break;
	case MAP_ID::FIRST: mapData = m_MapDataList.at((int)MAP_ID::FIRST); break;
	case MAP_ID::TO_SECOND: mapData = m_MapDataList.at((int)MAP_ID::TO_SECOND); break;
	case MAP_ID::SECOND: mapData = m_MapDataList.at((int)MAP_ID::SECOND); break;
	case MAP_ID::TO_THIRD: mapData = m_MapDataList.at((int)MAP_ID::TO_THIRD); break;
	case MAP_ID::THIRD: mapData = m_MapDataList.at((int)MAP_ID::THIRD); break;
	case MAP_ID::END: mapData = m_MapDataList.at((int)MAP_ID::END); break;
	}

	for (auto& data : mapData)
	{
		aqua::CVector2 pos = aqua::CVector2::ZERO;
		pos.x = (float)(data.x * 64);
		pos.y = (float)(data.y * 96);
		if (id != MAP_ID::START)
			pos.x += (float)aqua::GetWindowWidth();
		Create(pos, data.id);
	}
}

void CStageObjectManager::PlayerCast(aqua::CVector2 p_pos, float p_vel_y, float p_width, float p_height, bool p_fall, aqua::CVector2& dest, bool& on_ground)
{
	dest = p_pos + aqua::CVector2(0.0f, p_vel_y);
	on_ground = false;

	if (p_fall) return;

	if (p_vel_y < 0.0f) return;

	for (auto& elem : m_ChildObjectList)
	{
		IStageObject* land = (IStageObject*)elem;
		if (land->GetObjectCategory() != STAGE_OBJECT_CATEGORY::FLOOR) continue;

		aqua::CVector2 floorPos = land->GetPosition();
		aqua::CVector2 floorSize = land->GetSize();

		if (p_pos.x + p_width < floorPos.x) continue;
		if (p_pos.x > floorPos.x + floorSize.x) continue;

		if (p_pos.y + p_height <= floorPos.y && dest.y + p_height > floorPos.y)
			dest.y = floorPos.y - p_height;

		if(dest.y == floorPos.y - p_height)
			on_ground = true;
	}
}

bool CStageObjectManager::FindGround(aqua::CVector2 p_pos, float p_width, float p_height)
{
	for (auto& elem : m_ChildObjectList)
	{
		IStageObject* land = (IStageObject*)elem;
		if (land->GetObjectCategory() != STAGE_OBJECT_CATEGORY::FLOOR) continue;
		if (land->GetPosition().x < p_pos.x)continue;

		aqua::CVector2 floorPos = land->GetPosition();
		aqua::CVector2 floorSize = land->GetSize();

		if ((p_pos.x + (p_width * 2.0f) > floorPos.x) && (p_pos.y + p_height < floorPos.y))
			return true;
		
	}
	return false;
}
