#pragma once

#include "MessageBus/MessageBus.h"

namespace Genesis
{
	class Scene {
	public:
		virtual ~Scene() = default;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(float dt) = 0;
	};
}