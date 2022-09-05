#pragma once

#include "Layer.h"

#include <vector>
#include <memory>

namespace Genesis
{
	class Scene {
	public:
		virtual ~Scene() = default;

	protected:
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(float dt) = 0;

		void push(std::shared_ptr<Layer> const& layer);
		void pop();

	private:
		friend class Application;
		std::vector<std::shared_ptr<Layer>> m_Layers;
	};
}
