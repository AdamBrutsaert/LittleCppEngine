#include "SandboxScene.h"

using namespace Genesis;

struct Rectangle
{
	float x;
	float y;
	float width;
	float height;
};

struct Color
{
	float r;
	float g;
	float b;
};

struct Textured
{
	std::shared_ptr<Texture> texture;
	glm::vec4 subrect;
};

SandboxScene::SandboxScene() : m_Ticks(0), m_Elapsed(0), m_CameraController(), m_TextureElapsed(0), m_TextureIndex(0)
{
}

void SandboxScene::onAttach()
{
	m_CameraController.onAttach();
	m_Texture = Texture::Create("res/Conveyor Belt.png");

	auto entity = m_World.create();
	m_World.emplace<Rectangle>(entity, -1.0f, -1.0f, 1.0f, 1.0f);
	m_World.emplace<Color>(entity, 0.92f, 0.53f, 1.0f);

	entity = m_World.create();
	m_World.emplace<Rectangle>(entity, -0.5f, -0.5f, 1.0f, 1.0f);
	m_World.emplace<Textured>(entity, m_Texture, glm::vec4{ 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });

	entity = m_World.create();
	m_World.emplace<Rectangle>(entity, -0.5f, 0.5f, 1.0f, 1.0f);
	m_World.emplace<Textured>(entity, m_Texture, glm::vec4{ 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });

	entity = m_World.create();
	m_World.emplace<Rectangle>(entity, -0.5f, 1.5f, 1.0f, 1.0f);
	m_World.emplace<Textured>(entity, m_Texture, glm::vec4{ 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f });
}

void SandboxScene::onDetach()
{
	m_Texture = nullptr;
	m_CameraController.onDetach();
}

void SandboxScene::onUpdate(float dt)
{
	m_CameraController.onUpdate(dt);

	m_Ticks++;
	m_Elapsed += dt;
	if (m_Elapsed >= 1.0f) {
		Application::GetWindow()->setTitle("Ticks : " + std::to_string(m_Ticks));
		m_Ticks = 0;
		m_Elapsed -= 1.0f;
	}

	m_TextureElapsed += dt;
	if (m_TextureElapsed >= 0.1f) {
		m_TextureIndex = (m_TextureIndex + 1) % 8;
		m_TextureElapsed -= 0.1f;

		m_World.view<Textured>().each([this](auto const entity, auto& texture) {
			texture.subrect = glm::vec4{ 0.125f * m_TextureIndex, 0.75f, 0.125f, 0.25f };
		});
	}

	Renderer::ResetStatistics();
	Renderer::Begin(m_CameraController.getCamera().getProjectionView());

	m_World.view<Rectangle const, Color const>().each([](auto const entity, auto const& rect, auto const& color) {
		Renderer::DrawQuad({ rect.x, rect.y }, { rect.width, rect.height}, { color.r, color.g, color.b });
	});

	m_World.view<Rectangle const, Textured const>().each([](auto const entity, auto const& rect, auto const& texture) {
		Renderer::DrawQuad({ rect.x, rect.y }, { rect.width, rect.height}, texture.texture, texture.subrect);
	});
	
	Renderer::End();
}
