#include "health_bar.h"
#include "../../player_manager/player/player.h"
#include "../../translate/translate.h"

const aqua::CVector2 CHealthBar::m_p1_label_pos = aqua::CVector2(320.0f, 800.0f);
const aqua::CVector2 CHealthBar::m_p2_label_pos = aqua::CVector2(1530.0f, 800.0f);

CHealthBar::CHealthBar(aqua::IGameObject* parent)
	: aqua::IGameObject(parent, "HealthBar")
{
}

void CHealthBar::Initialize(IPlayer* player, aqua::controller::DEVICE_ID device, aqua::CVector2 pos)
{
	m_Player = player;
	m_Life = m_Player->GetLife();
	m_MaxLife = m_Player->GetMaxLife();
	m_Health.Create("data/health_back.png");
	m_HealthBack.Create("data/health_back.png");
	m_Damage.Create("data/health_back.png");
	m_HealthFrame.Create("data/health_frame.png");
	m_HealthLabel.Create(48);
	m_Health.color = 0xff00ff00;
	m_HealthBack.color = 0x80000000;
	m_Damage.color = 0xffff0000;
	m_HealthLabel.text = "";
	m_DamageTimer.Setup(2.0f);
	m_TranslateFlag = false;
	m_HealthBar.Create("data/health_bar.png");
	m_HealthBar.color = 0xff00ff00;
	if (device == aqua::controller::DEVICE_ID::P1)
		m_HealthLabel.position = m_p1_label_pos;
	else if (device == aqua::controller::DEVICE_ID::P2)
		m_HealthLabel.position = m_p2_label_pos;
	m_Screen.Create(m_HealthBar.GetTextureWidth(), m_HealthBar.GetTextureHeight(), true);
	m_Sc.Create(m_Screen);
	m_Sc.position = pos;
	if (device == aqua::controller::DEVICE_ID::P2)
		m_Sc.scale.x = -1.0f;
}

void CHealthBar::Initialize(int life, int max_life, aqua::controller::DEVICE_ID device, aqua::CVector2 pos)
{
	m_Player = nullptr;
	m_Life = life;
	m_MaxLife = max_life;
	m_Health.Create("data/health_back.png");
	m_HealthBack.Create("data/health_back.png");
	m_Damage.Create("data/health_back.png");
	m_HealthFrame.Create("data/health_frame.png");
	m_HealthLabel.Create(48);
	m_Health.color = 0xff00ff00;
	m_HealthBack.color = 0x80000000;
	m_Damage.color = 0xffff0000;
	m_HealthLabel.text = "";
	m_DamageTimer.Setup(2.0f);
	m_TranslateFlag = false;
	m_HealthBar.Create("data/health_bar.png");
	m_HealthBar.color = 0xff00ff00;
	if (device == aqua::controller::DEVICE_ID::P1)
		m_HealthLabel.position = m_p1_label_pos;
	else if (device == aqua::controller::DEVICE_ID::P2)
		m_HealthLabel.position = m_p2_label_pos;
	m_Screen.Create(m_HealthBar.GetTextureWidth(), m_HealthBar.GetTextureHeight(), true);
	m_Sc.Create(m_Screen);
	m_Sc.position = pos;
	if (device == aqua::controller::DEVICE_ID::P2)
		m_Sc.scale.x = -1.0f;
}

void CHealthBar::Update(void)
{
	if (m_Player != nullptr)
	{
		m_Life = m_Player->GetLife();
		m_MaxLife = m_Player->GetMaxLife();
	}

	m_Health.anchor.y = (float)m_Health.GetTextureHeight() / 2.0f;

	m_Health.scale.x = ((float)m_Life / (float)m_MaxLife);
	if (m_Health.scale.x < 0.0f)
		m_Health.scale.x = 0.0f;

	if (m_Health.scale.x != m_Damage.scale.x)
		m_TranslateFlag = true;

	m_HealthBar.rect.right = (int)((float)m_Life / (float)m_MaxLife * (float)m_HealthBar.GetTextureWidth());
	if (m_HealthBar.rect.right < 0)
		m_HealthBar.rect.right = 0;

	Translate();

	m_HealthLabel.text = std::to_string(m_Life);
}

void CHealthBar::Draw(void)
{
	m_Screen.Begin();
	m_HealthBack.Draw();
	m_Damage.Draw();
	//m_Health.Draw();
	m_HealthBar.Draw();
	m_HealthFrame.Draw();
	m_Screen.End();
	m_Sc.Draw();
	m_HealthLabel.Draw();
}

void CHealthBar::Finalize(void)
{
	m_Health.Delete();
	m_HealthBack.Delete();
	m_Damage.Delete();
	m_HealthFrame.Delete();
	m_HealthLabel.Delete();
	m_HealthBar.Delete();
	IGameObject::Finalize();
}

void CHealthBar::Translate(void)
{
	if (!m_TranslateFlag) return;

	m_DamageTimer.Update();
	if (m_DamageTimer.Finished())
	{
		m_TranslateFlag = false;
		m_DamageTimer.Reset();
	}
	CTranslate* translate = aqua::CreateGameObject<CTranslate>(this);
	translate->Translate(m_Damage.scale.x, m_PreScaleX, m_Health.scale.x, m_DamageTimer, false, EASING::IN_CIRC);
}
