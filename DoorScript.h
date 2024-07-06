#pragma once
#include "BoxCollider.h"
#include "ECS.h"
#include "InputManager.h"
#include "Interactive.h"
#include "Script.h"
#include "Transform.h"

struct DoorScript : public Script
{
	DoorScript(Entity* ent)
		:Script(ent)
	{}
	virtual ~DoorScript() = default;

	void Awake() override
	{
		m_pOwner->getWorld()->each<PlayerInformation>([&](Entity* ent,const ComponentHandle<PlayerInformation> playerInfo)
			{
				m_PlayerInfo = playerInfo;
			});
	}

	void Update(float deltaTime) override
	{
		bool m_IsInteract = m_pOwner->get<Interactive>()->m_IsInteract;
		if (m_pOwner->has<BoxCollider>())
		{
			if (m_pOwner->get<BoxCollider>()->m_IsRaycastHit)
			{
				// �ܰ��� ó��
				if (InputM->GetKeyDown(Key::E) && m_IsDoorActive == false)		// ��ȣ�ۿ� �߿��� Ű�� �ν����� �ʴ´�.
				{
					if (m_pOwner->get<Interactive>()->m_DoorIndex == 1)
						m_PlayerInfo->m_InteractingCount++;
					if (!m_IsInteract)
					{
						m_pOwner->getWorld()->each<Interactive>([&](Entity* ent, ComponentHandle<Interactive> interactive)
							{
								if(interactive->m_DoorIndex == m_pOwner->get<Interactive>()->m_DoorIndex)
									interactive->m_IsInteract = !m_IsInteract;
							});						
					}

					m_pOwner->getWorld()->each<Interactive>([&](Entity* ent, ComponentHandle<Interactive> interactive)
						{
							if (interactive->m_DoorIndex == m_pOwner->get<Interactive>()->m_DoorIndex)
								interactive->m_IsInteract = !m_IsInteract;

						});

					m_IsDoorActive = true;
				}
				
				// ��ȣ�ۿ� UI ���
				if (m_pOwner->has<Sprite2D>())
				{
					if (m_IsDoorActive == false)
					{
						m_pOwner->get<Sprite2D>().get().m_IsRendered = true;
					}
					// ���� ������ �߿��� ��ȣ�ۿ� UI �� ������� �ʴ´�.
					else if (m_IsDoorActive == true)
					{
						m_pOwner->get<Sprite2D>().get().m_IsRendered = false;
					}
				}

			}
			else
			{
				if (m_pOwner->has<Sprite2D>())
					m_pOwner->get<Sprite2D>().get().m_IsRendered = false;
			}

		}

		
		if(m_pOwner->has<Interactive>())
		{
			// ���� ���������� ���� ���¿����� ���� �����δ�.
			if (m_pOwner->get<Interactive>()->m_IsInteract)
			{
				// ���� �� ���ȴ�. (��ȣ�ۿ� ��)
				if (m_pOwner->get<Transform>()->m_Position.GetX() >= 150.f || m_pOwner->get<Transform>()->m_Position.GetX() <= -150.f)
				{
					m_pOwner->get<Transform>()->m_Position.SetX(150.f * m_pOwner->get<Interactive>()->m_OpeningDir);
					m_IsDoorActive = false;
					if(m_pOwner->get<Interactive>()->m_DoorIndex == 1)
					{
						m_PlayerInfo->m_Room6Check = false;
					}
				}
				else
				{
					m_pOwner->get<Transform>()->m_Position.AddX(m_pOwner->get<Interactive>()->m_OpeningDir * OBJECT_SPEED * deltaTime);
					m_IsDoorActive = true;
				}
			}
			else
			{
				// ���� �� ������. (��ȣ�ۿ� ��)
				if (m_pOwner->get<Transform>()->m_Position.GetX() <= 50.f && m_pOwner->get<Transform>()->m_Position.GetX() >= -50.f)
				{
					m_pOwner->get<Transform>()->m_Position.SetX(50.f * m_pOwner->get<Interactive>()->m_OpeningDir);
					m_IsDoorActive = false;
					if (m_pOwner->get<Interactive>()->m_DoorIndex == 1)
					{
						m_PlayerInfo->m_Room6Check = true;
					}
				}
				else
				{
					m_pOwner->get<Transform>()->m_Position.AddX(-m_pOwner->get<Interactive>()->m_OpeningDir * OBJECT_SPEED * deltaTime);
					m_IsDoorActive = true;
				}
			}
		}

	}

private:
	bool m_IsDoorActive = false;
	ComponentHandle<PlayerInformation> m_PlayerInfo;
};