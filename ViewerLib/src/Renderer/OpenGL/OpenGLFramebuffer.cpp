#include "pch.hpp"
#include "OpenGLFramebuffer.hpp"
#include "Renderer/Texture.hpp"

namespace VL
{
	namespace OpenGL
	{
		namespace
		{
			GLuint createDepthBuffer(uint32_t width, uint32_t height)
			{
				GLuint id = 0;
				glGenRenderbuffers(1, &id);
				glBindRenderbuffer(GL_RENDERBUFFER, id);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
				glBindRenderbuffer(GL_RENDERBUFFER, 0);
				return id;
			}
		}

		OpenGLFramebuffer::OpenGLFramebuffer(uint32_t width, uint32_t height, bool depthBuffer)
		{
			glGenFramebuffers(1, &m_id);
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
			m_colorBuffer = std::make_unique<OpenGLTexture>(width, height, TEXTURE_TYPE::TEXTURE_2D);

			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_colorBuffer->getId(), 0);

			if (depthBuffer)
			{
				m_depthBuffer = createDepthBuffer(width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		OpenGLFramebuffer::~OpenGLFramebuffer()
		{
			if (m_id != 0)
			{
				glDeleteFramebuffers(1, &m_id);
			}

			if (m_depthBuffer)
			{
				glDeleteRenderbuffers(1, &m_depthBuffer);
				m_depthBuffer = 0;
			}
		}

		void OpenGLFramebuffer::bind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		}

		void OpenGLFramebuffer::unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void OpenGLFramebuffer::clearColor(const vec4& color, float depth, uint32_t stencil, bool clearColor)
		{
			glClearColor(color[0], color[1], color[2], color[3]);

			auto flags = clearColor ? GL_COLOR_BUFFER_BIT : 0;

			if (m_depthBuffer)
			{
				flags |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
				clearDepth(depth);
				glClearStencil(stencil);
			}

			glClear(flags);
		}

		void OpenGLFramebuffer::clearDepth(float depth)
		{
			if (m_depthBuffer)
			{
				glClearDepth(depth);
				glClear(GL_DEPTH_BUFFER_BIT);
			}
		}

		void OpenGLFramebuffer::clearStencil(int32_t stencil)
		{
			if (m_depthBuffer)
			{
				glClearStencil(stencil);
				glClear(GL_STENCIL_BUFFER_BIT);
			}
		}
	}
}
