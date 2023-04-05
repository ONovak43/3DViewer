#pragma once
#include "Renderer/Buffer.hpp"

namespace VL
{
	namespace OpenGL
	{
        class OpenGLBuffer
        {
        public:
            explicit OpenGLBuffer(GLenum type);
            ~OpenGLBuffer();
            void bind() const;
            void unbind() const;

            void setStaticData(const void* data, uint32_t size);
            template<typename T>
            inline void setStaticData(const std::vector<T>& data);
            void setDynamicData(const void* data, uint32_t size);
            template<typename T>
            inline void setDynamicData(const std::vector<T>& data);
            void setSubData(const void* data, uint32_t size, uint32_t offset = 0, uint32_t bufferOffset = 0);

            void* map() const;
            void unmap() const;
            void resize(uint32_t size);

            [[nodiscard]] uint32_t getSize() const;
            [[nodiscard]] uint32_t getId() const;

        private:
            uint32_t m_id = 0;
            uint32_t m_size = 0;
            GLenum m_type = 0;
        };

		class OpenGLVertexBuffer
            : public VL::IVertexBuffer
		{
        public:
            OpenGLVertexBuffer();
            explicit OpenGLVertexBuffer(uint32_t size);
            explicit OpenGLVertexBuffer(const std::vector<float>& data);
            ~OpenGLVertexBuffer() override = default;
            void bind() const override;
            void unbind() const override;

            void setStaticData(const void* data, uint32_t size) override;
            void setStaticData(const std::vector<float>& data) override;
            void setDynamicData(const void* data, uint32_t size) override;
            void setDynamicData(const std::vector<float>& data) override;
            void setSubData(const void* data, uint32_t size, uint32_t offset = 0, uint32_t bufferOffset = 0) override;

            void* map() const override;
            void unmap() const override;
            void resize(uint32_t size) override;

            [[nodiscard]] uint32_t getSize() const override;
            [[nodiscard]] uint32_t getId() const override;
        private:
            OpenGLBuffer m_buffer;
		};

        class OpenGLIndexBuffer
            : public VL::IIndexBuffer
        {
        public:
            OpenGLIndexBuffer();
            explicit OpenGLIndexBuffer(const std::vector<uint32_t>& data);
            ~OpenGLIndexBuffer() override = default;
            void bind() const override;
            void unbind() const override;

            void setStaticData(const void* data, uint32_t size) override;
            void setStaticData(const std::vector<float>& data) override;
            void setDynamicData(const void* data, uint32_t size) override;
            void setDynamicData(const std::vector<float>& data) override;
            void setSubData(const void* data, uint32_t size, uint32_t offset = 0, uint32_t bufferOffset = 0) override;

            void* map() const override;
            void unmap() const override;
            void resize(uint32_t size) override;

            [[nodiscard]] uint32_t getSize() const override;
            [[nodiscard]] uint32_t getId() const override;
        private:
            OpenGLBuffer m_buffer;
        };
    }
}

#include "OpenGLBuffer.inl"

