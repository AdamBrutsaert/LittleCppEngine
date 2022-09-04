#pragma once

#include <Genesis.h>

class SandboxScene : public Genesis::Scene
{
public:
	SandboxScene();

	void onAttach() override final;
	void onDetach() override final;
	void onUpdate(float dt) override final;

private:
	float m_Elapsed;
	uint32_t m_Ticks;

	Genesis::Texture* m_Texture;

	Genesis::MessageSubscriber<Genesis::Message::WindowResize> m_Subscriber;
	Genesis::MessageSubscriber<Genesis::Message::KeyPressed> m_Subscriber1;
	Genesis::MessageSubscriber<Genesis::Message::KeyReleased> m_Subscriber2;
};