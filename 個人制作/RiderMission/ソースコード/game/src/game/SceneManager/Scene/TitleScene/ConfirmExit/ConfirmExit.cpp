#include "ConfirmExit.h"

const aqua::CVector2 CConfirmExit::m_default_exit_label_pos = aqua::CVector2(250.0f, 400.0f);
const aqua::CVector2 CConfirmExit::m_default_cancel_label_pos = aqua::CVector2(650.0f, 400.0f);
const aqua::CVector2 CConfirmExit::m_default_cursor_box_pos = aqua::CVector2::ZERO;

CConfirmExit::CConfirmExit(aqua::IGameObject* parent)
	:IScene(parent, "ConfirmExit")
{
}

void CConfirmExit::Initialize(void)
{
	m_ConfirmMessage.Create(64);
	m_ConfirmMessage.text = "ゲームを終了します";
	m_ConfirmMessage.position = aqua::CVector2(350.0f, 200.0f);
	m_ExitLabel.Create(64);
	m_ExitLabel.text = "　終　了　";
	m_ExitLabel.position = m_default_exit_label_pos;
	m_CancelLabel.Create(64);
	m_CancelLabel.text = "キャンセル";
	m_CancelLabel.position = m_default_cancel_label_pos;
	m_CursorBox.Setup(m_default_cursor_box_pos, (float)m_ExitLabel.GetTextWidth(), (float)m_ExitLabel.GetFontHeight(), 0x50ffffff);
	m_CursorState = CURSOR_STATE::CANCEL;
	m_BackPlane.Setup(aqua::CVector2(135.0f, 50.0f), 1000.0f, 600.0f, 0x80000000);
}

void CConfirmExit::Update(void)
{
	switch (m_CursorState)
	{
	case CURSOR_STATE::CANCEL: Cancel(); break;
	case CURSOR_STATE::EXIT: Exit(); break;
	}
	{
		using namespace aqua::mouse;

		int w = GetWheel();

		if (w != 0)
			m_CursorState = (CURSOR_STATE)(((int)m_CursorState + 1) % 2);
		
	}
}

void CConfirmExit::Draw(void)
{
	m_BackPlane.Draw();
	m_ConfirmMessage.Draw();
	m_ExitLabel.Draw();
	m_CancelLabel.Draw();
	m_CursorBox.Draw();
}

void CConfirmExit::Finalize(void)
{
	m_ConfirmMessage.Delete();
	m_ExitLabel.Delete();
	m_CancelLabel.Delete();
}

void CConfirmExit::Cancel(void)
{
	using namespace aqua::mouse;
	m_CursorBox.position = m_default_cancel_label_pos;
	if (Trigger(BUTTON_ID::LEFT))
		Pop();
}
void CConfirmExit::Exit(void)
{
	using namespace aqua::mouse;
	m_CursorBox.position = m_default_exit_label_pos;
	if (Trigger(BUTTON_ID::LEFT))
		aqua::ExitGame();
}
