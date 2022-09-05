#pragma once

#include <Genesis.h>

class SandboxScene : public Genesis::Scene
{
public:
	SandboxScene();

private:
	void onAttach() override final;
	void onDetach() override final;
	void onUpdate(float dt) override final;

private:
	float m_Elapsed;
	uint32_t m_Ticks;

	Genesis::OrthographicCameraController m_CameraController;

	uint32_t m_TextureIndex;
	float m_TextureElapsed;
	std::shared_ptr<Genesis::Texture> m_Texture;
};
