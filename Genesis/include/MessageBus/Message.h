#pragma once

#include <typeinfo>

#include "Core/Key.h"
#include "Core/MouseButton.h"

namespace Genesis {

	using MessageID = std::size_t;

	template <typename M> inline constexpr MessageID GetMessageID() noexcept {
	  return typeid(M).hash_code();
	}

	namespace Message
	{
		struct WindowResize {
			uint32_t width;
			uint32_t height;
		};

		struct KeyPressed {
			Key key;
		};

		struct KeyReleased {
			Key key;
		};

		struct KeyRepeat {
			Key key;
		};

		struct MouseButtonPressed {
			MouseButton button;
		};
		
		struct MouseButtonReleased {
			MouseButton button;
		};

		struct MouseMove {
			int32_t x;
			int32_t y;
		};

		struct MouseScroll {
			double x;
			double y;
		};
	}
}
