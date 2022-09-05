#pragma once

namespace Genesis
{
	class Scene {
	public:
		virtual ~Scene() = default;

	protected:
		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(float dt) = 0;

	private:
		friend class Application;
	};
}
