#pragma once
#include <memory>
#include "Renderer/Buffer.hpp"

namespace VL
{
	struct VertexAttribute
	{
		enum class Type {
			NONE,
			BYTE,
			USHORT,
			INT,
			VEC2I,
			VEC3I,
			VEC4I,
			UINT,
			FLOAT,
			VEC2F,
			VEC3F,
			VEC4F,
			MAT3,
			MAT4
		};

		bool m_normalized;
		uint32_t m_count;
		uint32_t m_offset;
		uint32_t m_size;
		Type m_type;

		VertexAttribute(uint32_t count, Type type, uint32_t offset, uint32_t size = 0);
	};

	class VertexArray
	{
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;
		virtual void bind() const = 0;
		virtual void unbind() const = 0;		
		virtual void setVertexBuffer(const std::shared_ptr<VL::IVertexBuffer>& buffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<VL::IIndexBuffer>& buffer) = 0;
		virtual std::shared_ptr<IVertexBuffer>& getVertexBuffer() = 0;
		virtual std::shared_ptr<IIndexBuffer>& getIndexBuffer() = 0;
		virtual void addVertexAtributes(const std::vector<VertexAttribute>& attributes, uint32_t defaultStride) = 0;
	};

	constexpr std::size_t vertexTypeSize(VertexAttribute::Type type);
}

#include "VertexArray.inl"
