#pragma once
#include "Renderer/IFramebuffer.hpp"
#include "Renderer/OpenGL/OpenGLTexture.hpp"

namespace VL
{
    namespace OpenGL
    {
        class OpenGLFramebuffer :
            public IFramebuffer
        {
        public:
			OpenGLFramebuffer(uint32_t width, uint32_t height, bool depthBuffer);
			~OpenGLFramebuffer() override;

			void bind() override;
			void unbind() override;
			void clearColor(const vec4& color, float depth, uint32_t stencil, bool clearColor) override;
			void clearDepth(float depth) override;
			void clearStencil(int32_t stencil) override;

        private:
            GLuint m_id = 0;
			std::unique_ptr<OpenGLTexture> m_colorBuffer = nullptr;
			GLuint m_depthBuffer = 0;
        };

        GLuint createDepthBuffer(uint32_t width, uint32_t height);
    }
}


