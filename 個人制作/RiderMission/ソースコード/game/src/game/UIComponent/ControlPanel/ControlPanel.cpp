#include "ControlPanel.h"

const aqua::CVector2 CControlPanelUI::m_default_position = aqua::CVector2(250.0f, 620.0f);

CControlPanelUI::CControlPanelUI(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "ControlPanel")
{
}

void CControlPanelUI::Initialize(void)
{
	m_Sprite.Create("data/texture/control_panel_ui.png");
	m_Sprite.position = m_default_position;
	m_BackPlane.Setup(aqua::CVector2(0.0f, m_default_position.y), (float)aqua::GetWindowWidth(), (float)m_Sprite.GetTextureHeight(), 0x80000000);

	IGameObject::Initialize();
}

void CControlPanelUI::Update(void)
{
}

void CControlPanelUI::Draw(void)
{
	m_BackPlane.Draw();
	m_Sprite.Draw();

	IGameObject::Draw();
}

void CControlPanelUI::Finalize(void)
{
	m_BackPlane.Draw();
	m_Sprite.Delete();

	IGameObject::Finalize();
}
