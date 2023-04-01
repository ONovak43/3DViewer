#pragma once
#include <cstdint>

namespace VL
{
	class Buffer
	{
	public:
		Buffer() = default;
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) noexcept = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) noexcept = delete;
		virtual ~Buffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;
		virtual void setStaticData(const void* data, uint32_t size) = 0;
		virtual void setStaticData(const std::vector<float>& data) = 0;
		virtual void setDynamicData(const void* data, uint32_t size) = 0;
		virtual void setDynamicData(const std::vector<float>& data) = 0;
		virtual void setSubData(const void* data, uint32_t size, uint32_t offset, uint32_t bufferOffset) = 0;
		virtual void* map() const = 0;
		virtual void unmap() const = 0;
		virtual void resize(uint32_t size) = 0;
		virtual uint32_t getSize() const = 0;
		virtual uint32_t getId() const = 0;
	};

	class IVertexBuffer
		: public Buffer
	{
	public:
		virtual ~IVertexBuffer() = default;
	};

	class IIndexBuffer
		: public Buffer
	{
	public:
		virtual ~IIndexBuffer() = default;
	};
}