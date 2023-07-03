#include "pch.hpp"
#include "OpenGLTexture.hpp"
#include "Assets/AssetManager.hpp"
#include <ranges>

namespace VL
{
	namespace OpenGL
	{
		OpenGLTexture::OpenGLTexture(const std::string& path, TEXTURE_TYPE type)
			: VL::ITexture(), m_type(GL_TEXTURE_2D), m_width(0), m_height(0), m_id(0)
		{
			ASSERT(type == TEXTURE_TYPE::TEXTURE_2D || type == TEXTURE_TYPE::TEXTURE_CUBE_MAP, "Only 2D textures and cube maps are supported for now");
			switch (type)
			{
			case TEXTURE_TYPE::TEXTURE_2D:
				prepare2DTexture(path);
				break;
			case TEXTURE_TYPE::TEXTURE_CUBE_MAP:
				prepareCubeMapTexture(path);
				break;
			}
		}

		OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height, TEXTURE_TYPE type)
			: VL::ITexture(), m_type(GL_TEXTURE_2D), m_width(0), m_height(0), m_id(0)
		{
			ASSERT(type == TEXTURE_TYPE::TEXTURE_2D || type == TEXTURE_TYPE::TEXTURE_CUBE_MAP, "Only 2D textures and cube maps are supported for now");			
			switch (type)
			{
			case TEXTURE_TYPE::TEXTURE_2D:
				create2DTexture();
				bind();
				glTexImage2D(m_type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
				unbind();
				break;
			case TEXTURE_TYPE::TEXTURE_CUBE_MAP:
				createCubeMap();
				bind();
				for (auto i = 0; i < 6; ++i)
				{
					glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);						
				}
				unbind();
				break;
			}		
		}

		void OpenGLTexture::prepare2DTexture(const std::string& imagePath)
		{
			auto image = AssetManager::getInstance().getImageAsset(imagePath, false);

			if (image == nullptr)
			{
				std::cerr << "Failed to load texture: " << imagePath << "\n";
				return;
			}
			create2DTexture();

			bind();
			auto format = GL_GREEN + image->channels;
			glTexImage2D(m_type, 0, format,
				image->width, image->height,
				0, format,GL_UNSIGNED_BYTE,
				image->data
			);
			unbind();
		}

		void OpenGLTexture::prepareCubeMapTexture(const std::string& imagesPath)
		{			
			auto imagesPathSplited = imagesPath
				| std::ranges::views::split(';')
				| std::ranges::views::transform([](auto&& str) { return std::string_view(&*str.begin(), std::ranges::distance(str)); });

			if (std::ranges::distance(imagesPathSplited) != 6)
			{
				std::cerr << "Failed to load cube map texture: " << imagesPath << "\nThere are not 6 textures!\n";
				return;
			}

			createCubeMap();

			auto i = 0;
			for (auto&& imagePath : imagesPathSplited)
			{
				std::string imageStr{ imagePath };
				auto image = AssetManager::getInstance().getImageAsset(imageStr, false);

				if (image == nullptr)
				{
					std::cerr << "Failed to load texture: " << imagePath << "\n";
					return;
				}
				
				bind();
				auto format = GL_GREEN + image->channels;
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format,
					image->width,
					image->height,
					0, format, GL_UNSIGNED_BYTE,
					image->data
				);
				unbind();
				i++;
			}

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
			ASSERT(getType() == TEXTURE_TYPE::TEXTURE_2D, "Only 2D textures are supported for now");
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
			case GL_TEXTURE_CUBE_MAP:
				result = TEXTURE_TYPE::TEXTURE_CUBE_MAP;
				break;
			}

			return result;
		}

		void OpenGLTexture::create2DTexture()
		{
			glGenTextures(1, &m_id);
			setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
			setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
			setParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			setParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}

		void OpenGLTexture::createCubeMap()
		{
			glGenTextures(1, &m_id);
			setParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			setParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			setParameteri(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
			case TEXTURE_TYPE::TEXTURE_CUBE_MAP:
				result = GL_TEXTURE_CUBE_MAP;
				break;
			}
			return result;
		}
	}
}
