#include "demo_scene.h"
#include "../../../../game_object/controller_stick_operation/controller_stick_operation.h"
#include "game/game_object/translate/translate.h"

CDemoScene::CDemoScene(aqua::IGameObject* parent)
	: IScene(parent, "DemoScene")
{
}

void CDemoScene::Initialize(void)
{
	m_DemoLabel.Create(128);
	m_DemoLabel.position = aqua::CVector2(450.0f, 900.0f);
	m_DemoLabel.text = "--ƒfƒ‚ƒvƒŒƒC’†--";
	m_DemoMovie.Create("data/movie/demo_movie.mp4");
	m_DemoMovie.Play();
	m_Timer.Setup(3.0f);
}

void CDemoScene::Update(void)
{
	using namespace aqua::controller;
	if (m_DemoMovie.Finished() ||
		TriggerAll(DEVICE_ID::P1) || 
		TriggerAll(DEVICE_ID::P2))
		Change(SCENE_ID::TITLE);

	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->FadeDirection(m_DemoLabel.color, m_Timer);
}

void CDemoScene::Draw(void)
{
	m_DemoMovie.Draw();
	m_DemoLabel.Draw();
}

void CDemoScene::Finalize(void)
{
	m_DemoLabel.Delete();
	m_DemoMovie.Delete();
	IGameObject::Finalize();
}

bool CDemoScene::TriggerAll(aqua::controller::DEVICE_ID device)
{
	using namespace aqua::controller;
	bool button = false;
	bool stick = false;
	button = ((aqua::controller::Trigger(device, BUTTON_ID::A)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::B)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::X)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::Y)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::BACK)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::UP)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::DOWN)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::LEFT)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::LEFT_SHOULDER)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::LEFT_THUMB)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::RIGHT)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::RIGHT_SHOULDER)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::RIGHT_THUMB)) ||
		(aqua::controller::Trigger(device, BUTTON_ID::START)));
	CControllerStickOperation* controller = (CControllerStickOperation*)aqua::FindGameObject("ControllerStickOperation");
	stick = controller->StickTriggerLeftAll(device, 0.5f);
	return (button || stick);
}
