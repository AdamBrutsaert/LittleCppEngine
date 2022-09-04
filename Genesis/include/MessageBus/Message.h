#pragma once

#include <typeinfo>

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
			uint32_t key;
		};

		struct KeyReleased {
			uint32_t key;
		};
	}
}
