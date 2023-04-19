#pragma once
#include "Math/Vectors.hpp"
#include "Math/Matrices.hpp"

namespace VL
{
	class IShaderProgram
	{
	public:
		virtual ~IShaderProgram() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setInt(const std::string& name, int32_t value) = 0;
		virtual void setUInt(const std::string& name, uint32_t value) = 0;
		virtual void setFloat(const std::string& name, float value) = 0;

		virtual void setVec2(const std::string& name, vec2 value) = 0;
		virtual void setVec3(const std::string& name, vec3 value) = 0;
		virtual void setVec4(const std::string& name, vec4 value) = 0;
		virtual void setMat3(const std::string& name, mat3 value, bool transpose = false) = 0;
		virtual void setMat4(const std::string& name, mat4 value, bool transpose = false) = 0;

	};
}