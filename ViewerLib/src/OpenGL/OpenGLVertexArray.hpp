#pragma once
#include "Renderer/Buffer.hpp"
#include "Renderer/VertexArray.hpp"
#include "OpenGLBuffer.hpp"

namespace VL
{
	namespace OpenGL
	{
		class OpenGLVertexArray
			: public VL::VertexArray
		{
		public:
			OpenGLVertexArray();
			~OpenGLVertexArray();
			
			void bind() const override;
			void unbind() const override;

			void setVertexBuffer(const std::shared_ptr<VL::IVertexBuffer>& buffer) override;
			void setIndexBuffer(const std::shared_ptr<VL::IIndexBuffer>& buffer) override;

			std::shared_ptr<IVertexBuffer>& getVertexBuffer() override { return m_vertexBuffer; };
			inline std::shared_ptr<IIndexBuffer>& getIndexBuffer() override { return m_indexBuffer; };

			void addVertexAtributes(const std::vector<VertexAttribute>& attributes, uint32_t defaultStride = 0) override;

		private:
			uint32_t m_id;
			std::shared_ptr<IVertexBuffer> m_vertexBuffer;
			std::shared_ptr<IIndexBuffer> m_indexBuffer;
		};

		constexpr GLenum convertVertexType(VertexAttribute::Type type);
	}
}

#include "OpenGLVertexArray.inl"
