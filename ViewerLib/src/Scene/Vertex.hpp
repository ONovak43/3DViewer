#pragma once
#include "Math/Vectors.hpp"
#include <array>

namespace VL
{
	struct Vertex1P
	{
		vec3 m_position;
	};

	struct Vertex1P1N1UV
	{
		vec3 m_position;
		vec3 m_normal;
		vec2 m_uv;
	};
}