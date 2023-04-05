#pragma once
#include <cstdint>

namespace VL
{
	enum class TEXTURE_TYPE
	{
		TEXTURE_1D = GL_TEXTURE_1D,
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_3D = GL_TEXTURE_3D,
	};

	class ITexture
	{
	public:
		virtual ~ITexture() = default;
		virtual void bind() const = 0;
		virtual void bind(uint32_t slot) const = 0;
		virtual void unbind() const = 0;
		virtual void generateMipMap(int32_t maxLOD) = 0;
		virtual void setData(const void* data, size_t size) = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		[[nodiscard]] virtual uint32_t getId() const = 0;
		[[nodiscard]] virtual TEXTURE_TYPE getType() const = 0;
	};
}
