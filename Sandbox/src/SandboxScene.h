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
};