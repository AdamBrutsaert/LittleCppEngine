#pragma once

#include <Genesis.h>

class SandboxLayer : public Genesis::Layer {
public:
	SandboxLayer();

private:
    void onAttach() override final;
	void onDetach() override final;
	void onUpdate(float dt) override final;

private:
	Genesis::OrthographicCameraController m_CameraController;

	uint32_t m_TextureIndex;
	float m_TextureElapsed;
	std::shared_ptr<Genesis::Texture> m_Texture;
};
