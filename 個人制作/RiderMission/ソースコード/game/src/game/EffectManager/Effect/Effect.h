#pragma once

#include "aqua.h"

class IEffect :public aqua::IGameObject
{
public:
	IEffect(aqua::IGameObject* parent, const std::string& name);
	virtual ~IEffect(void) = default;

	void Initialize(void) override;
	virtual void Initialize(const aqua::CVector2& pos);
	virtual void Update(void) override ;
	virtual void Draw(void) override;
	virtual void Finalize(void) override;
	void SetPosition(const aqua::CVector2& pos) { m_Position = pos; }
	void Play(void) { m_Effect.Play(); }
	void Stop(void) { m_Effect.Stop(); }

protected:
	aqua::CVector2 m_Position;
	aqua::CVector2 m_Velocity;
	aqua::CEffect2D m_Effect;
};