#include "pch.hpp"
#include "OpenGLBuffer.hpp"

namespace VL
{
    namespace OpenGL
    {
        // --------------------------------------------
        // ------------- OPENGL BUFFER ----------------
        // --------------------------------------------
        OpenGLBuffer::OpenGLBuffer(GLenum type)
            : m_type(type)
        {
            glGenBuffers(1, &m_id);
        }

        OpenGLBuffer::~OpenGLBuffer()
        {
            if (m_id != 0)
            {
                glDeleteBuffers(1, &m_id);
            }
        }

        void OpenGLBuffer::bind() const
        {
            glBindBuffer(m_type, m_id);
        }

        void OpenGLBuffer::unbind() const
        {
            glBindBuffer(m_type, 0);
        }

        void OpenGLBuffer::setStaticData(const void* data, uint32_t size)
        {
            ASSERT(m_id != 0, "Writing data to an invalid buffer.");

            bind();
            m_size = size;
            glBufferData(m_type, size, data, GL_STATIC_DRAW); // TODO
        }

        void OpenGLBuffer::setDynamicData(const void* data, uint32_t size)
        {
            ASSERT(m_id == 0, "Writing data to an invalid buffer.");

            bind();
            m_size = size;
            glBufferData(m_type, size, data, GL_DYNAMIC_DRAW); // TODO
        }

        void OpenGLBuffer::setSubData(const void* data, uint32_t size, uint32_t offset, uint32_t bufferOffset)
        {
            ASSERT(m_id == 0, "Writing data to an invalid buffer.");

            bind();
            m_size = size;
            glBufferSubData(m_type, (static_cast<GLintptr>(bufferOffset) * m_size) + offset, size, data);
        }

        void* OpenGLBuffer::map() const
        {
            bind();
            return glMapBuffer(m_type, GL_WRITE_ONLY);
        }

        void OpenGLBuffer::unmap() const
        {
            bind();
            glUnmapBuffer(m_type);
        }

        void OpenGLBuffer::resize(uint32_t size)
        {
            bind();
            glBufferData(m_type, size, nullptr, GL_STATIC_DRAW);
            m_size = size;
        }

        uint32_t OpenGLBuffer::getSize() const
        {
            return m_size;
        }

        uint32_t OpenGLBuffer::getId() const
        {
            return m_id;
        }

        // --------------------------------------------
        // ------------- VERTEX BUFFER ----------------
        // --------------------------------------------
        OpenGLVertexBuffer::OpenGLVertexBuffer()
            : m_buffer(GL_ARRAY_BUFFER)
        {
        }

        OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
            : OpenGLVertexBuffer()
        {
            m_buffer.setDynamicData(nullptr, size);
        }

        OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& data)
            : OpenGLVertexBuffer()
        {
            m_buffer.setStaticData(data);
        }

        void OpenGLVertexBuffer::bind() const
        {
            m_buffer.bind();
        }

        void OpenGLVertexBuffer::unbind() const
        {
            m_buffer.unbind();
        }

        void OpenGLVertexBuffer::setStaticData(const void* data, uint32_t size)
        {
            m_buffer.setStaticData(data, size);
        }

        void OpenGLVertexBuffer::setStaticData(const std::vector<float>& data)
        {
            m_buffer.setStaticData(data);
        }

        void OpenGLVertexBuffer::setDynamicData(const void* data, uint32_t size)
        {
            m_buffer.setDynamicData(data, size);
        }

        void OpenGLVertexBuffer::setDynamicData(const std::vector<float>& data)
        {
            m_buffer.setDynamicData(data);
        }

        void OpenGLVertexBuffer::setSubData(const void* data, uint32_t size, uint32_t offset, uint32_t bufferOffset)
        {
            m_buffer.setSubData(data, size, offset, bufferOffset);
        }

        void* OpenGLVertexBuffer::map() const
        {
            return m_buffer.map();
        }

        void OpenGLVertexBuffer::unmap() const
        {
            m_buffer.unmap();
        }

        void OpenGLVertexBuffer::resize(uint32_t size)
        {
            m_buffer.resize(size);
        }

        uint32_t OpenGLVertexBuffer::getSize() const
        {
            return m_buffer.getSize();
        }

        uint32_t OpenGLVertexBuffer::getId() const
        {
            return m_buffer.getId();
        }

        
        // --------------------------------------------
        // ------------- INDEX BUFFER -----------------
        // --------------------------------------------
        OpenGLIndexBuffer::OpenGLIndexBuffer()
            : m_buffer(GL_ELEMENT_ARRAY_BUFFER)
        {
        }

        OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t>& data)
            : OpenGLIndexBuffer()
        {
            m_buffer.setStaticData(data);
		}

        void OpenGLIndexBuffer::bind() const
        {
            m_buffer.bind();
        }

        void OpenGLIndexBuffer::unbind() const
        {
            m_buffer.unbind();
        }

        void OpenGLIndexBuffer::setStaticData(const void* data, uint32_t size)
        {
            m_buffer.setStaticData(data, size);
        }

        void OpenGLIndexBuffer::setStaticData(const std::vector<float>& data)
        {
            m_buffer.setStaticData(data);
        }

        void OpenGLIndexBuffer::setDynamicData(const void* data, uint32_t size)
        {
            m_buffer.setDynamicData(data, size);
        }

        void OpenGLIndexBuffer::setDynamicData(const std::vector<float>& data)
        {
            m_buffer.setDynamicData(data);
        }

        void OpenGLIndexBuffer::setSubData(const void* data, uint32_t size, uint32_t offset, uint32_t bufferOffset)
        {
            m_buffer.setSubData(data, size, offset, bufferOffset);
        }

        void* OpenGLIndexBuffer::map() const
        {
            return m_buffer.map();
        }

        void OpenGLIndexBuffer::unmap() const
        {
            m_buffer.unmap();
        }

        void OpenGLIndexBuffer::resize(uint32_t size)
        {
            m_buffer.resize(size);
        }

        uint32_t OpenGLIndexBuffer::getSize() const
        {
            return m_buffer.getSize();
        }

        uint32_t OpenGLIndexBuffer::getId() const
        {
            return m_buffer.getId();
        }
    }
}
