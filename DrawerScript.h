#pragma once
#include "BoxCollider.h"
#include "InputManager.h"
#include "Interactive.h"
#include "Script.h"
#include "Transform.h"

struct DrawerScript : public Script
{
	DrawerScript(Entity* ent)
		:Script(ent)
	{
	}
	virtual ~DrawerScript() override = default;

	void Awake() override
	{
		m_pOwner->getWorld()->each<PlayerInformation>([&](Entity* ent, const ComponentHandle<PlayerInformation> playerInfo)
			{
				m_PlayerInfo = playerInfo;
			});
	}

	virtual void Update(float deltaTime) override
	{
		if(m_pOwner->has<BoxCollider>())
		{
			auto isRaycastHit = m_pOwner->get<BoxCollider>()->m_IsRaycastHit;
			if (isRaycastHit == true)
			{
				// �ܰ��� ó��
				if (InputM->GetKeyDown(Key::E) && m_IsDrawerActive == false)
				{
					m_pOwner->get<Interactive>()->m_IsInteract = !m_pOwner->get<Interactive>()->m_IsInteract;
					if(m_pOwner->get<Interactive>()->m_IsInteract)
					{
						m_PlayerInfo->m_Room7Check++;
					}
					else
					{
						m_PlayerInfo->m_Room7Check--;
					}
					m_IsDrawerActive = true;
				}

				// ��ȣ�ۿ� UI ���
				if (m_pOwner->has<Sprite2D>())
				{
					if (m_IsDrawerActive == false)
					{
						m_pOwner->get<Sprite2D>().get().m_IsRendered = true;
					}
					else if (m_IsDrawerActive == true)
					{
						m_pOwner->get<Sprite2D>().get().m_IsRendered = false;
					}
				}

			}
			else if (isRaycastHit == false)
			{
				if (m_pOwner->has<Sprite2D>())
					m_pOwner->get<Sprite2D>().get().m_IsRendered = false;
			}
		}
		
		if (m_pOwner->has<Interactive>())
		{
			// ������ ���� ������ ���� ���¿����� ���� �����δ�.
			if(m_pOwner->get<Interactive>()->m_IsInteract)
			{
				// ������ �� ���ȴ�. (��ȣ�ۿ� ��)
				if(m_pOwner->get<Transform>()->m_Position.GetZ() <= -35.f)
				{
					m_pOwner->get<Transform>()->m_Position.SetZ(-35.f);
					m_IsDrawerActive = false;
				}
				else
				{
					m_pOwner->get<Transform>()->m_Position.SetZ(m_pOwner->get<Transform>()->m_Position.GetZ() - OBJECT_SPEED * deltaTime);
					m_IsDrawerActive = true;
				}
			}
			else
			{
				// ������ �� ������. (��ȣ�ۿ� ��)
				if (m_pOwner->get<Transform>()->m_Position.GetZ() >= 0.f)
				{
					m_pOwner->get<Transform>()->m_Position.SetZ(0.f);
					m_IsDrawerActive = false;
				}
				else
				{
					m_pOwner->get<Transform>()->m_Position.SetZ(m_pOwner->get<Transform>()->m_Position.GetZ() + OBJECT_SPEED * deltaTime);
					m_IsDrawerActive = true;
				}
			}
		}
	}

private:
	bool m_IsDrawerActive = false;
	ComponentHandle<PlayerInformation> m_PlayerInfo;
};
