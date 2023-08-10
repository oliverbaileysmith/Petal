#pragma once

// Equivalent to GLFW mouse button codes

namespace ptl
{
	enum class MouseButtonCode
	{
		_1         = 0,
		_2         = 1,
		_3         = 2,
		_4         = 3,
		_5         = 4,
		_6         = 5,
		_7         = 6,
		_8         = 7,
		_LEFT      = MouseButtonCode::_1,
		_RIGHT     = MouseButtonCode::_2,
		_MIDDLE    = MouseButtonCode::_3,
	};

	inline std::ostream& operator<<(std::ostream& os, const MouseButtonCode mouseButtonCode)
	{
		return os << (int32_t)mouseButtonCode;
	}
}