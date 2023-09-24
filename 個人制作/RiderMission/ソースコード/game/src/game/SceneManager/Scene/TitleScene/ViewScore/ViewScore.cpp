#include "ViewScore.h"
#include "../../../../ScoreManager/ScoreManager.h"

const aqua::CVector2 CViewScore::m_default_score_pos = aqua::CVector2(800.0f, 300.0f);
const aqua::CVector2 CViewScore::m_default_label_pos = aqua::CVector2(200.0f, 180.0f);

CViewScore::CViewScore(aqua::IGameObject* parent)
	:IScene(parent, "ViewScore")
{
}

void CViewScore::Initialize(void)
{
	m_ScoreManager = (CScoreManager*)aqua::FindGameObject("ScoreManager");
	m_Score.Create(128, 4);
	m_Score.position = m_default_score_pos;
	m_Score.text = std::to_string(m_ScoreManager->GetHiScore());
	m_Message.Create(64, 2);
	m_Message.text = "現在のハイスコア";
	m_Message.position = m_default_label_pos;
	m_Plane.Setup(aqua::CVector2(0.0f, 150.0f), (float)aqua::GetWindowWidth(), 400.0f, 0x80000000);
}

void CViewScore::Update(void)
{
	if(aqua::mouse::Trigger(aqua::mouse::BUTTON_ID::LEFT))
		Pop();
	
	IGameObject::Update();
}

void CViewScore::Draw(void)
{
	m_Plane.Draw();
	m_Message.Draw();
	m_Score.Draw();
	IGameObject::Draw();
}

void CViewScore::Finalize(void)
{
	m_Message.Delete();
	m_Score.Delete();
	IGameObject::Finalize();
}
