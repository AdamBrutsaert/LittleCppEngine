#include "Precompiled.h"
#include "Core/Scene.h"

#include "Core/Application.h"

namespace Genesis
{
    void Scene::push(std::shared_ptr<Layer> const& layer)
    {
        Application::PushLayer(layer);
    }

	void Scene::pop()
    {
        Application::PopLayer();
    }
}
