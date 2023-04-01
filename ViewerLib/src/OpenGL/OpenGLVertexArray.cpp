#include "pch.hpp"
#include "OpenGLVertexArray.hpp"
#include "OpenGLBuffer.hpp"

namespace VL
{
	namespace OpenGL
	{
		OpenGLVertexArray::OpenGLVertexArray()
		{
			glGenVertexArrays(1, &m_id);
		}

		OpenGLVertexArray::~OpenGLVertexArray()
		{
			if (m_id != 0)
			{
				glDeleteVertexArrays(1, &m_id);
			}
		}

		void OpenGLVertexArray::bind() const
		{
			glBindVertexArray(m_id);
			if (m_vertexBuffer) {
				m_vertexBuffer->bind();
			}
			if (m_indexBuffer) {
				m_indexBuffer->bind();
			}
		}

		void OpenGLVertexArray::unbind() const
		{
			glBindVertexArray(0);
		}

		void OpenGLVertexArray::setVertexBuffer(const std::shared_ptr<VL::IVertexBuffer>& buffer)
		{
			m_vertexBuffer = buffer; 
		}

		void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<VL::IIndexBuffer>& buffer)
		{
			m_indexBuffer = buffer;
		}

		void OpenGLVertexArray::addVertexAtributes(const std::vector<VertexAttribute>& attributes, uint32_t defaultStride)
		{
			ASSERT(m_vertexBuffer != nullptr, "Vertex buffer is not set");

			bind();

			using Type = VertexAttribute::Type;
			
			for (auto i = 0; i < attributes.size(); i++)
			{
				const auto& [normalized, count, offset, size, type] = attributes[i];
				const auto normalize = normalized ? GL_TRUE : GL_FALSE;
				const auto stride = size ? size : defaultStride;
				const auto typeGL = convertVertexType(type);

				if (attributes[i].m_type == Type::BYTE)
				{
					glVertexAttribIPointer(i, count, typeGL, stride, reinterpret_cast<void*>(offset));
				}
				else {
					glVertexAttribPointer(i, count, typeGL, normalize, stride, reinterpret_cast<void*>(offset));
				}

				glEnableVertexAttribArray(i);
			}

			unbind();
		}
	}
}
