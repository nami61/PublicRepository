#pragma once

#include "../../Scene.h"

class CConfirmExit :public IScene
{
public:
	CConfirmExit(aqua::IGameObject* parent);
	~CConfirmExit() = default;

	void Initialize(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Finalize(void) override;

private:
	void Cancel(void);
	void Exit(void);

	enum class CURSOR_STATE
	{
		EXIT,
		CANCEL,
	};

	static const aqua::CVector2 m_default_exit_label_pos;
	static const aqua::CVector2 m_default_cancel_label_pos;
	static const aqua::CVector2 m_default_cursor_box_pos;
	aqua::CLabel m_ConfirmMessage;
	aqua::CLabel m_ExitLabel;
	aqua::CLabel m_CancelLabel;
	aqua::CBoxPrimitive m_CursorBox;
	aqua::CBoxPrimitive m_BackPlane;
	CURSOR_STATE m_CursorState;
};