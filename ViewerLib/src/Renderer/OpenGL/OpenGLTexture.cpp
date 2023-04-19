#include "pch.hpp"
#include "OpenGLTexture.hpp"
#include "Assets/AssetManager.hpp"

namespace VL
{
	namespace OpenGL
	{
		OpenGLTexture::OpenGLTexture(const std::string& path, TEXTURE_TYPE type)
			: VL::ITexture(), m_type(GL_TEXTURE_2D), m_width(0), m_height(0), m_id(0)
		{
			ASSERT(type == TEXTURE_TYPE::TEXTURE_2D, "Only 2D textures are supported for now");
			auto image = AssetManager::getInstance().getImageAsset(path); // Problem

			if (image == nullptr)
			{
				std::cerr << "Failed to load texture: " << path << "\n";
				return;
			}
			createTexture();

			bind();
			glTexImage2D(m_type, 0, GL_RGBA, 
				static_cast<int32_t>(image->width), 
				static_cast<int32_t>(image->height), 
				0, GL_RGBA, GL_UNSIGNED_BYTE, 
				image->data.data()
			);
			unbind();
		}

		OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type)
			: VL::ITexture(), m_type(GL_TEXTURE_2D), m_width(0), m_height(0)
		{
			ASSERT(type == TEXTURE_TYPE::TEXTURE_2D, "Only 2D textures are supported for now");
			bind();
			createTexture();
			glTexImage2D(m_type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			unbind();
		}

		OpenGLTexture::~OpenGLTexture()
		{
			if (m_id != 0)
			{
				glDeleteTextures(1, &m_id);
			}
		}

		void OpenGLTexture::bind() const
		{
			glBindTexture(m_type, m_id);
		}

		void OpenGLTexture::bind(uint32_t slot) const
		{
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(m_type, m_id);		
		}

		void OpenGLTexture::unbind() const
		{
			glBindTexture(m_type, 0);
		}

		void OpenGLTexture::generateMipMap(int32_t maxLOD)
		{
			bind();
			setParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			setParameteri(GL_TEXTURE_MAX_LOD, maxLOD);
			glGenerateMipmap(m_type);
			unbind();
		}

		void OpenGLTexture::setData(const void* data, size_t size)
		{
			glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		uint32_t OpenGLTexture::getWidth() const
		{
			return m_width;
		}

		uint32_t OpenGLTexture::getHeight() const
		{
			return m_height;
		}

		uint32_t OpenGLTexture::getId() const
		{
			return m_id;
		}

		TEXTURE_TYPE OpenGLTexture::getType() const
		{
			TEXTURE_TYPE result = TEXTURE_TYPE::TEXTURE_2D;

			switch (m_type)
			{
			case GL_TEXTURE_1D:
				result = TEXTURE_TYPE::TEXTURE_1D;
				break;
			case GL_TEXTURE_2D:
				result = TEXTURE_TYPE::TEXTURE_2D;
				break;
			case GL_TEXTURE_3D:
				result = TEXTURE_TYPE::TEXTURE_3D;
				break;
			}

			return result;
		}

		void OpenGLTexture::createTexture()
		{
			glGenTextures(1, &m_id);
			setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
			setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
			setParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			setParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		void OpenGLTexture::setParameteri(GLenum parameterName, GLenum parameterValue)
		{
			glTexParameteri(m_type, parameterName, parameterValue);
		}

		GLenum OpenGLTexture::typeToGLenum(TEXTURE_TYPE type)
		{
			GLenum result = GL_TEXTURE_2D;
			switch (type)
			{
			case TEXTURE_TYPE::TEXTURE_1D:
				result = GL_TEXTURE_1D;
				break;
			case TEXTURE_TYPE::TEXTURE_2D:
				result = GL_TEXTURE_2D;
				break;
			case TEXTURE_TYPE::TEXTURE_3D:
				result = GL_TEXTURE_CUBE_MAP;
				break;
			}
			return result;
		}
	}
}
